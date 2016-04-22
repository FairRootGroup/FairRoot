/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// special class to expose protected TMessage constructor
class Ex9TMessage2 : public TMessage
{
  public:
  Ex9TMessage2(void* buf, Int_t len)
    : TMessage(buf, len)
  {
    ResetBit(kIsOwner);
  }
};

// helper function to clean up the object holding the data after it is transported.
void free_tmessage4(void* /*data*/, void *hint)
{
    delete (TMessage*)hint;
}

template <typename T>
FairMQEx9TaskProcessorBin<T>::FairMQEx9TaskProcessorBin()
  : FairMQDevice()
  , fEventHeader(NULL)
  , fInput(NULL)
  , fOutput(NULL)
  , fInputArray(NULL)
  , fOutputArray(NULL)
  , fNewRunId(1)
  , fCurrentRunId(-1)
  , fDataToKeep("")
  , fFairTask(NULL)
  , fParCList(NULL)
  , fGeoPar(nullptr)
{

}

template <typename T>
FairMQEx9TaskProcessorBin<T>::~FairMQEx9TaskProcessorBin()
{
  LOG(INFO) << "deteling fGeoPar"; 
 if(fGeoPar)
    {
      delete fGeoPar;
      fGeoPar=nullptr;
    }
   
  LOG(INFO) << "deteling fInput";
 if(fInput)
    {
      delete fInput;
      fInput=nullptr;
    }
  
  LOG(INFO) << "deteling fOutput";
  if(fOutput)
    {
      delete fOutput;
      fOutput=nullptr;
    }

  LOG(INFO) << "deteling fInputArray";
  if(fInputArray)
    {
      delete fInputArray;
      fInputArray=nullptr;
    }
  
  LOG(INFO) << "deteling fOutputArray";
  if(fOutputArray)
    {
      delete fOutputArray;
      fOutputArray=nullptr;
    }

  delete fFairTask;
}


template <typename T>
void FairMQEx9TaskProcessorBin<T>::Init()
{
    //fHitFinder->InitMQ(fRootParFileName,fAsciiParFileName);
  fFairTask = new T();
  fGeoPar = new FairGeoParSet("FairGeoParSet");
  fParCList = new TList();
  fParCList->Add(fGeoPar);
  fFairTask->GetParList(fParCList);
  
  fOutput = new TList();
  fInput = new TList();

  fInputArray = new TClonesArray("PixelDigi");
  fInputArray->SetName("PixelDigis"); 
  fInput->Add(fInputArray);
//  fOutputArray = new TClonesArray("PixelHit");
//  fOutputArray->SetName("PixelHits");
}

template <typename T>
void FairMQEx9TaskProcessorBin<T>::Run()
{
    int receivedMsgs = 0;
    int sentMsgs = 0;
    TObject* objectToKeep = NULL;

    while (CheckCurrentState(RUNNING))
    {
      FairMQParts parts;
      
      if ( Receive(parts,"data-in") >= 0 )
        {
	  LOG(TRACE)<<"message received with " << parts.Size() << " parts!";
	  receivedMsgs++;

          if ( parts.Size() == 0 ) continue; // probably impossible, but still check

          // the first part should be the event header
	  PixelPayload::EventHeader* payloadE = static_cast<PixelPayload::EventHeader*>(parts.At(0)->GetData());
          LOG(TRACE) << "GOT EVENT " << payloadE->fMCEntryNo << " OF RUN " << payloadE->fRunId << " (part " << payloadE->fPartNo << ")";

	  fNewRunId = payloadE->fRunId;
	  if(fNewRunId!=fCurrentRunId)
            {
	      fCurrentRunId=fNewRunId;
	      UpdateParameters();
	      fFairTask->InitMQ(fParCList);
            }

	  // the second part should the TClonesArray with necessary data... now assuming Digi
	  PixelPayload::Digi* payloadD = static_cast<PixelPayload::Digi*>(parts.At(1)->GetData());
	  int digiArraySize = parts.At(1)->GetSize();
	  int nofDigis      = digiArraySize / sizeof(PixelPayload::Digi);

  	  fInputArray->Clear();
	  for ( int idigi = 0 ; idigi < nofDigis ; idigi++ ) {
	      new ((*fInputArray)[idigi]) PixelDigi(-1,
	                                            payloadD[idigi].fDetectorID,
	                                            payloadD[idigi].fFeID,
	                                            payloadD[idigi].fCol,
	                                            payloadD[idigi].fRow,
	                                            payloadD[idigi].fCharge);
	  }

	  LOG(TRACE) << "    EVENT HAS " << nofDigis << " DIGIS!!!";

	  // Execute hit finder task
	  fOutput->Clear();
	  //	  LOG(INFO) << " The blocking line... analyzing event " << fEventHeader->GetMCEntryNumber();
	  fFairTask->ExecMQ(fInput,fOutput);

	  FairMQParts partsOut;

	  PixelPayload::EventHeader* header = new PixelPayload::EventHeader();
	  header->fRunId     = payloadE->fRunId;
	  header->fMCEntryNo = payloadE->fMCEntryNo;
	  header->fPartNo    = payloadE->fPartNo;

	  FairMQMessage* msgHeader = NewMessage(header,
						sizeof(PixelPayload::EventHeader),
						[](void* data, void* hint) { delete static_cast<PixelPayload::EventHeader*>(data); }
 						);
	  partsOut.AddPart(msgHeader);

	  for ( int iobj = 0 ; iobj < fOutput->GetEntries() ; iobj++ ) {
	    if ( strcmp(fOutput->At(iobj)->GetName(),"PixelHits") == 0 ) {
              Int_t nofEntries = ((TClonesArray*)fOutput->At(iobj))->GetEntries();
  	      size_t hitsSize = nofEntries * sizeof(PixelPayload::Hit);
	  
	      FairMQMessage*  msgTCA = NewMessage(hitsSize);
	  
	      PixelPayload::Hit* hitPayload = static_cast<PixelPayload::Hit*>(msgTCA->GetData());
	  
	      for ( int ihit = 0 ; ihit < nofEntries ; ihit++ ) {
	        PixelHit* hit = static_cast<PixelHit*>(((TClonesArray*)fOutput->At(iobj))->At(ihit));
	        if ( !hit ) {
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
	      LOG(TRACE) << "second part has size = " << hitsSize;
	      partsOut.AddPart(msgTCA);

	      LOG(TRACE) << "Output array should have " << nofEntries << "hits";
	    }
          }


	  Send(partsOut, "data-out");
	  sentMsgs++;
        }
    }
    
    MQLOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
}




template <typename T>
void FairMQEx9TaskProcessorBin<T>::CustomCleanup(void* /*data*/, void *hint)
{
    delete (std::string*)hint;
}



template <typename T>
void FairMQEx9TaskProcessorBin<T>::SetProperty(const int key, const std::string& value)
{
    switch (key)
    {
        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}



template <typename T>
std::string FairMQEx9TaskProcessorBin<T>::GetProperty(const int key, const std::string& default_)
{
    switch (key)
    {
        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}


template <typename T>
void FairMQEx9TaskProcessorBin<T>::SetProperty(const int key, const int value)
{
    FairMQDevice::SetProperty(key, value);
}

template <typename T>
int FairMQEx9TaskProcessorBin<T>::GetProperty(const int key, const int value)
{
    return FairMQDevice::GetProperty(key, value);
}







template <typename T>
void FairMQEx9TaskProcessorBin<T>::UpdateParameters() {
  for ( int iparC = 0 ; iparC < fParCList->GetEntries() ; iparC++ ) {
    FairParGenericSet* tempObj = (FairParGenericSet*)(fParCList->At(iparC));
    fParCList->Remove(tempObj);
    fParCList->AddAt(UpdateParameter(tempObj),iparC);
  }
}

template <typename T>
FairParGenericSet* FairMQEx9TaskProcessorBin<T>::UpdateParameter(FairParGenericSet* thisPar) {
  std::string paramName = thisPar->GetName();
  //  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
  std::string* reqStr = new std::string(paramName + "," + std::to_string(fCurrentRunId));
  LOG(WARN) << "Requesting parameter \"" << paramName << "\" for Run ID " << fCurrentRunId << " (" << thisPar << ")";
  std::unique_ptr<FairMQMessage> req(NewMessage(const_cast<char*>(reqStr->c_str()), reqStr->length(), CustomCleanup, reqStr));
  std::unique_ptr<FairMQMessage> rep(NewMessage());
  
  if (Send(req,"param") > 0)
    {
      if (Receive(rep,"param") > 0)
	{
	  Ex9TMessage2 tm(rep->GetData(), rep->GetSize());
	  thisPar = (FairParGenericSet*)tm.ReadObject(tm.GetClass());
	  LOG(WARN) << "Received parameter"<< paramName <<" from the server (" << thisPar << ")";
	  return thisPar;
	}
    } 
  return NULL;
}
