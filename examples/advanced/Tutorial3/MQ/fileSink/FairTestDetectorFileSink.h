/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairTestDetectorFileSink.h
 *
 * @since 2013-06-05
 * @author A. Rybalchenko
 */

#ifndef FAIRTESTDETECTORFILESINK_H_
#define FAIRTESTDETECTORFILESINK_H_

#include <iostream>
#include <array>
#include <string>

#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include "TSystem.h"

#include "FairMQDevice.h"
#include "FairMQLogger.h"

#include "FairTestDetectorPayload.h"
#include "FairTestDetectorHit.h"

#include "baseMQtools.h"

#include "TMessage.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/binary_object.hpp>

template <typename TIn, typename TPayloadIn>
class FairTestDetectorFileSink : public FairMQDevice
{
  public:
    FairTestDetectorFileSink()
        : fOutput(nullptr)
        , fOutFile(nullptr)
        , fTree(nullptr)
        , fReceivedMsgs(0)
        , fInChannelName("data2")
        , fAckChannelName("ack")
        , fHitVector()
    {
        gSystem->ResetSignal(kSigInterrupt);
        gSystem->ResetSignal(kSigTermination);

        // Check if boost serialization is available if it is chosen
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (std::is_same<TPayloadIn, boost::archive::binary_iarchive>::value || std::is_same<TPayloadIn, boost::archive::text_iarchive>::value)
        {
            if (baseMQ::tools::resolve::has_BoostSerialization<TIn, void(TPayloadIn&, const unsigned int)>::value == 0)
            {
                LOG(error) << "Boost serialization for Input Payload requested, but the input type does not support it. Check the TIn parameter. Aborting.";
                exit(EXIT_FAILURE);
            }
        }
    }
    FairTestDetectorFileSink(const FairTestDetectorFileSink&) = delete;
    FairTestDetectorFileSink operator=(const FairTestDetectorFileSink&) = delete;

    virtual ~FairTestDetectorFileSink()
    {
        fTree->Write();
        fOutFile->Close();
        fHitVector.clear();
        delete fOutput;
        delete fOutFile;
    }

    virtual void InitOutputFile(std::string defaultId = "100")
    {
        fOutput = new TClonesArray("FairTestDetectorHit");
        char out[256];
        sprintf(out, "filesink%s.root", defaultId.c_str());

        fOutFile = TFile::Open(out, "recreate");
        fTree = new TTree("MQOut", "Test output");
        fTree->Branch("Output", "TClonesArray", &fOutput, 64000, 99);
    }

  protected:
    virtual void Init()
    {
        std::string inChannelName = fConfig->GetValue<std::string>("in-channel");
        std::string ackChannelName = fConfig->GetValue<std::string>("ack-channel");
        // check if the returned value actually exists, for the compatibility with old devices.
        if (inChannelName != "")
        {
            fInChannelName = inChannelName;
        }
        if (ackChannelName != "")
        {
            fAckChannelName = ackChannelName;
        }

        InitOutputFile("_" + fConfig->GetValue<std::string>("data-format"));
    }
    virtual void PostRun()
    {
        LOG(info) << "I've received " << fReceivedMsgs << " messages!";
    }
    virtual void InitTask();


  private:
    TClonesArray* fOutput;
    TFile* fOutFile;
    TTree* fTree;
    int fReceivedMsgs;
    std::string fInChannelName;
    std::string fAckChannelName;

    std::vector<TIn> fHitVector;
};

// Template implementation of Run() in FairTestDetectorFileSink.tpl :
#include "FairTestDetectorFileSinkBin.tpl"
#include "FairTestDetectorFileSinkBoost.tpl"
#include "FairTestDetectorFileSinkFlatBuffers.tpl"
#include "FairTestDetectorFileSinkMsgpack.tpl"
#include "FairTestDetectorFileSinkProtobuf.tpl"
#include "FairTestDetectorFileSinkTMessage.tpl"

#endif /* FAIRTESTDETECTORFILESINK_H_ */
