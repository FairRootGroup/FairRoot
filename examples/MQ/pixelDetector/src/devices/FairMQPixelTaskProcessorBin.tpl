/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// special class to expose protected TMessage constructor
class PixelTMessage2 : public TMessage
{
  public:
    PixelTMessage2(void* buf, Int_t len)
        : TMessage(buf, len)
    {
        ResetBit(kIsOwner);
    }
};

template <typename T>
FairMQPixelTaskProcessorBin<T>::FairMQPixelTaskProcessorBin()
    : fInputChannelName("data-in")
    , fOutputChannelName("data-out")
    , fParamChannelName("param")
    , fStaticParameters(false)
    , fEventHeader(nullptr)
    , fInput(nullptr)
    , fOutput(nullptr)
    , fInputArray(nullptr)
    , fOutputArray(nullptr)
    , fNewRunId(1)
    , fCurrentRunId(-1)
    , fDataToKeep("")
    , fReceivedMsgs(0)
    , fSentMsgs(0)
    , fFairTask(nullptr)
    , fParCList(nullptr)
    , fGeoPar(nullptr)
{
}

template <typename T>
FairMQPixelTaskProcessorBin<T>::~FairMQPixelTaskProcessorBin()
{
    LOG(info) << "deteling fGeoPar";
    delete fGeoPar;
    fGeoPar = nullptr;

    LOG(info) << "deteling fInput";
    delete fInput;
    fInput = nullptr;

    LOG(info) << "deteling fOutput";
    delete fOutput;
    fOutput = nullptr;

    LOG(info) << "deteling fInputArray";
    delete fInputArray;
    fInputArray = nullptr;

    LOG(info) << "deteling fOutputArray";
    delete fOutputArray;
    fOutputArray = nullptr;

    delete fFairTask;
}


template <typename T>
void FairMQPixelTaskProcessorBin<T>::Init()
{
    fDataToKeep        = fConfig->GetValue<std::string>("keep-data");
    fInputChannelName  = fConfig->GetValue<std::string>("in-channel");
    fOutputChannelName = fConfig->GetValue<std::string>("out-channel");
    fParamChannelName  = fConfig->GetValue<std::string>("par-channel");
    fStaticParameters  = fConfig->GetValue<bool>       ("static-pars");

    // fHitFinder->InitMQ(fRootParFileName,fAsciiParFileName);
    fFairTask = new T();
    fFairTask->SetStreamProcessing(kTRUE);
    fGeoPar = new FairGeoParSet("FairGeoParSet");
    fParCList = new TList();
    fParCList->Add(fGeoPar);
    fFairTask->GetParList(fParCList);

    fOutput = new TList();
    fInput = new TList();

    fInputArray = new TClonesArray("PixelDigi");
    fInputArray->SetName("PixelDigis");
    fInput->Add(fInputArray);
    // fOutputArray = new TClonesArray("PixelHit");
    // fOutputArray->SetName("PixelHits");

    OnData(fInputChannelName, &FairMQPixelTaskProcessorBin<T>::ProcessData);
}

template <typename T>
bool FairMQPixelTaskProcessorBin<T>::ProcessData(FairMQParts& parts, int /*index*/)
{
    // LOG(debug) << "message received with " << parts.Size() << " parts!";
    fReceivedMsgs++;

    if (parts.Size() == 0) return 0; // probably impossible, but still check

    // the first part should be the event header
    PixelPayload::EventHeader* payloadE = static_cast<PixelPayload::EventHeader*>(parts.At(0)->GetData());
    // LOG(debug) << "GOT EVENT " << payloadE->fMCEntryNo << " OF RUN " << payloadE->fRunId << " (part " << payloadE->fPartNo << ")";

    if ( fStaticParameters == false || fCurrentRunId == -1 ) {
        fNewRunId = payloadE->fRunId;
        if (fNewRunId != fCurrentRunId)
            {
                fCurrentRunId = fNewRunId;
                UpdateParameters();
                fFairTask->InitMQ(fParCList);

                LOG(info) << "Parameters updated, back to ProcessData(" << parts.Size() << " parts!)";
            }
    }

    // the second part should the TClonesArray with necessary data... now assuming Digi
    PixelPayload::Digi* payloadD = static_cast<PixelPayload::Digi*>(parts.At(1)->GetData());
    int digiArraySize = parts.At(1)->GetSize();
    int nofDigis      = digiArraySize / sizeof(PixelPayload::Digi);

    fInputArray->Clear();
    for (int idigi = 0; idigi < nofDigis; idigi++)
    {
        new ((*fInputArray)[idigi]) PixelDigi(-1,
                                              payloadD[idigi].fDetectorID,
                                              payloadD[idigi].fFeID,
                                              payloadD[idigi].fCol,
                                              payloadD[idigi].fRow,
                                              payloadD[idigi].fCharge);
    }

    // LOG(debug) << "    EVENT HAS " << nofDigis << " DIGIS!!!";

    // Execute hit finder task
    fOutput->Clear();
    // LOG(info) << " The blocking line... analyzing event " << fEventHeader->GetMCEntryNumber();
    fFairTask->ExecMQ(fInput, fOutput);

    FairMQParts partsOut;

    PixelPayload::EventHeader* header = new PixelPayload::EventHeader();
    header->fRunId     = payloadE->fRunId;
    header->fMCEntryNo = payloadE->fMCEntryNo;
    header->fPartNo    = payloadE->fPartNo;

    FairMQMessagePtr msgHeader(NewMessage(header,
                                          sizeof(PixelPayload::EventHeader),
                                          [](void* data, void* /*hint*/) { delete static_cast<PixelPayload::EventHeader*>(data); },
                                          nullptr));
    partsOut.AddPart(std::move(msgHeader));

    for (int iobj = 0; iobj < fOutput->GetEntries(); iobj++)
    {
        if (strcmp(fOutput->At(iobj)->GetName(),"PixelHits") == 0)
        {
            Int_t nofEntries = ((TClonesArray*)fOutput->At(iobj))->GetEntries();
            size_t hitsSize = nofEntries * sizeof(PixelPayload::Hit);

            FairMQMessagePtr msgTCA(NewMessage(hitsSize));

            PixelPayload::Hit* hitPayload = static_cast<PixelPayload::Hit*>(msgTCA->GetData());

            for (int ihit = 0; ihit < nofEntries; ihit++)
            {
                PixelHit* hit = static_cast<PixelHit*>(((TClonesArray*)fOutput->At(iobj))->At(ihit));
                if (!hit)
                {
                    continue;
                }
                new (&hitPayload[ihit]) PixelPayload::Hit();
                hitPayload[ihit].fDetectorID = hit->GetDetectorID();
                hitPayload[ihit].posX        = hit->GetX();
                hitPayload[ihit].posY        = hit->GetY();
                hitPayload[ihit].posZ        = hit->GetZ();
                hitPayload[ihit].dposX       = hit->GetDx();
                hitPayload[ihit].dposY       = hit->GetDy();
                hitPayload[ihit].dposZ       = hit->GetDz();
            }
            // LOG(debug) << "second part has size = " << hitsSize;
            partsOut.AddPart(std::move(msgTCA));

            // LOG(debug) << "Output array should have " << nofEntries << "hits";
        }
    }

    Send(partsOut, fOutputChannelName);
    fSentMsgs++;

    return true;
}

template <typename T>
void FairMQPixelTaskProcessorBin<T>::PostRun()
{
    LOG(info) << "FairMQPixelTaskProcessorBin<T>::PostRun() Received " << fReceivedMsgs << " and sent " << fSentMsgs << " messages!";
}

template <typename T>
void FairMQPixelTaskProcessorBin<T>::UpdateParameters()
{
    for (int iparC = 0; iparC < fParCList->GetEntries(); iparC++)
    {
        FairParGenericSet* tempObj = (FairParGenericSet*)(fParCList->At(iparC));
        fParCList->Remove(tempObj);
        fParCList->AddAt(UpdateParameter(tempObj), iparC);
    }
}

template <typename T>
FairParGenericSet* FairMQPixelTaskProcessorBin<T>::UpdateParameter(FairParGenericSet* thisPar)
{
    std::string paramName = thisPar->GetName();
    //  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    std::string* reqStr = new std::string(paramName + "," + std::to_string(fCurrentRunId));
    LOG(warn) << "Requesting parameter \"" << paramName << "\" for Run ID " << fCurrentRunId << " (" << thisPar << ")";
    FairMQMessagePtr req(NewMessage(const_cast<char*>(reqStr->c_str()),
                                                  reqStr->length(),
                                                  [](void* /* data */, void* hint){ delete static_cast<std::string*>(hint); },
                                                  reqStr));
    FairMQMessagePtr rep(NewMessage());

    if (Send(req,fParamChannelName) > 0)
    {
        if (Receive(rep,fParamChannelName) > 0)
        {
            PixelTMessage2 tm(rep->GetData(), rep->GetSize());
            thisPar = (FairParGenericSet*)tm.ReadObject(tm.GetClass());
            LOG(warn) << "Received parameter"<< paramName <<" from the server (" << thisPar << ")";
            return thisPar;
        }
    }

    return nullptr;
}
