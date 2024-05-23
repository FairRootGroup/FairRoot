/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQPIXALTTASKPROCESSORBIN_H_
#define FAIRMQPIXALTTASKPROCESSORBIN_H_

#include "FairEventHeader.h"
#include "FairGeoParSet.h"
#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts
#include "FairParGenericSet.h"
#include "PixelDigi.h"
#include "PixelPayload.h"
#include "RootSerializer.h"

#include <TClonesArray.h>
#include <TList.h>
#include <string>

template<typename T>
class FairMQPixAltTaskProcessorBin : public fair::mq::Device
{
  public:
    FairMQPixAltTaskProcessorBin()
        : FairMQDevice()
        , fInputChannelName("data-in")
        , fOutputChannelName("data-out")
        , fParamChannelName("param")
        , fEventHeader(NULL)
        , fNewRunId(1)
        , fCurrentRunId(-1)
        , fDataToKeep("")
        , fReceivedMsgs(0)
        , fSentMsgs(0)
        , fFairTask(NULL)
        , fParCList(NULL)
        , fGeoPar(nullptr)
    {}

    virtual ~FairMQPixAltTaskProcessorBin()
    {
        delete fGeoPar;
        fGeoPar = nullptr;
        delete fFairTask;
    }

    void SetDataToKeep(const std::string& tStr) { fDataToKeep = tStr; }

    void SetInputChannelName(const std::string& tstr) { fInputChannelName = tstr; }
    void SetOutputChannelName(const std::string& tstr) { fOutputChannelName = tstr; }
    void SetParamChannelName(const std::string& tstr) { fParamChannelName = tstr; }

  protected:
    bool ProcessData(fair::mq::Parts& parts, int)
    {
        // LOG(debug)<<"message received with " << parts.Size() << " parts!";
        fReceivedMsgs++;

        if (parts.Size() == 0)
            return 0;   // probably impossible, but still check

        // expecting even number of parts in the form: header,data,header,data,header,data and so on...
        int nPPE = 2;   // nof parts per event

        if (parts.Size() % nPPE >= 1)
            LOG(info) << "received " << parts.Size() << " parts, will ignore last part!!!";

        // creating output multipart message
        fair::mq::Parts partsOut;

        for (decltype(parts.Size()) ievent = 0; ievent < parts.Size() / nPPE; ievent++) {
            // the first part should be the event header
            PixelPayload::EventHeader* payloadE =
                static_cast<PixelPayload::EventHeader*>(parts.At(nPPE * ievent)->GetData());
            // LOG(debug) << "GOT EVENT " << payloadE->fMCEntryNo << " OF RUN " << payloadE->fRunId << " (part " <<
            // payloadE->fPartNo << ")";

            fNewRunId = payloadE->fRunId;
            if (fNewRunId != fCurrentRunId) {
                fCurrentRunId = fNewRunId;
                UpdateParameters();
                fFairTask->InitMQ(fParCList);

                LOG(info) << "Parameters updated, back to ProcessData(" << parts.Size() << " parts!)";
            }

            // the second part should the TClonesArray with necessary data... now assuming Digi
            PixelPayload::Digi* payloadD = static_cast<PixelPayload::Digi*>(parts.At(nPPE * ievent + 1)->GetData());
            int digiArraySize = parts.At(nPPE * ievent + 1)->GetSize();
            int nofDigis = digiArraySize / sizeof(PixelPayload::Digi);

            // LOG(debug) << "    EVENT HAS " << nofDigis << " DIGIS!!!";

            // create eventHeader part
            PixelPayload::EventHeader* header = new PixelPayload::EventHeader();
            header->fRunId = payloadE->fRunId;
            header->fMCEntryNo = payloadE->fMCEntryNo;
            header->fPartNo = payloadE->fPartNo;
            auto msgHeader(NewMessage(header, sizeof(PixelPayload::EventHeader), [](void* data, void* /*hint*/) {
                delete static_cast<PixelPayload::EventHeader*>(data);
            }));
            partsOut.AddPart(std::move(msgHeader));

            // create part with hits
            int hitsSize = nofDigis * sizeof(PixelPayload::Hit);

            auto msgTCA = NewMessage(hitsSize);

            PixelPayload::Hit* hitPayload = static_cast<PixelPayload::Hit*>(msgTCA->GetData());

            // actually find hits
            int nofHits = 0;
            fFairTask->ExecMQ(payloadD, nofDigis, hitPayload, nofHits);

            partsOut.AddPart(std::move(msgTCA));
        }

        Send(partsOut, fOutputChannelName);
        fSentMsgs++;

        return true;
    }

    virtual void Init()
    {
        fDataToKeep = fConfig->GetValue<std::string>("keep-data");
        fInputChannelName = fConfig->GetValue<std::string>("in-channel");
        fOutputChannelName = fConfig->GetValue<std::string>("out-channel");
        fParamChannelName = fConfig->GetValue<std::string>("par-channel");

        // fHitFinder->InitMQ(fRootParFileName,fAsciiParFileName);
        fFairTask = new T();
        fFairTask->SetStreamProcessing(kTRUE);
        fGeoPar = new FairGeoParSet("FairGeoParSet");
        fParCList = new TList();
        fParCList->Add(fGeoPar);
        fFairTask->GetParList(fParCList);

        OnData(fInputChannelName, &FairMQPixAltTaskProcessorBin<T>::ProcessData);
    }

    virtual void PostRun()
    {
        LOG(info) << "FairMQPixAltTaskProcessorBin<T>::PostRun() Received " << fReceivedMsgs << " and sent "
                  << fSentMsgs << " messages!";
    }

  private:
    std::string fInputChannelName;
    std::string fOutputChannelName;
    std::string fParamChannelName;

    void UpdateParameters()
    {
        for (int iparC = 0; iparC < fParCList->GetEntries(); iparC++) {
            FairParGenericSet* tempObj = (FairParGenericSet*)(fParCList->At(iparC));
            fParCList->Remove(tempObj);
            fParCList->AddAt(UpdateParameter(tempObj), iparC);
        }
    }

    FairParGenericSet* UpdateParameter(FairParGenericSet* thisPar)
    {
        std::string paramName = thisPar->GetName();

        std::string* reqStr = new std::string(paramName + "," + std::to_string(fCurrentRunId));
        LOG(warn) << "Requesting parameter \"" << paramName << "\" for Run ID " << fCurrentRunId << " (" << thisPar
                  << ")";
        auto req(NewMessage(const_cast<char*>(reqStr->c_str()),
                            reqStr->length(),
                            [](void* /*data*/, void* obj) { delete static_cast<std::string*>(obj); },
                            reqStr));
        auto rep(NewMessage());

        if (Send(req, fParamChannelName) > 0) {
            if (Receive(rep, fParamChannelName) > 0) {
                thisPar = nullptr;
                RootSerializer().Deserialize(*rep, thisPar);
                LOG(info) << "Received parameter" << paramName << " from the server (" << thisPar << ")";
                return thisPar;
            }
        }
        return nullptr;
    }

    FairEventHeader* fEventHeader;

    int fNewRunId;
    int fCurrentRunId;

    std::string fDataToKeep;

    int fReceivedMsgs = 0;
    int fSentMsgs = 0;

    T* fFairTask;
    TList* fParCList;
    FairGeoParSet* fGeoPar;

    FairMQPixAltTaskProcessorBin(const FairMQPixAltTaskProcessorBin&);
    FairMQPixAltTaskProcessorBin& operator=(const FairMQPixAltTaskProcessorBin&);
};

#endif /* FAIRMQPIXALTTASKPROCESSOR_H_ */
