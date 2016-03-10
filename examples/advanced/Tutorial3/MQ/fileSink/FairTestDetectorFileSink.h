/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
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

#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include "TString.h"
#include "TSystem.h"

#include "FairMQDevice.h"
#include "FairMQTools.h"
#include "FairMQLogger.h"

#include "FairTestDetectorPayload.h"
#include "FairTestDetectorHit.h"

#include "baseMQtools.h"

#include "TMessage.h"

#ifndef __CINT__
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/binary_object.hpp>
#endif //__CINT__

template <typename TIn, typename TPayloadIn>
class FairTestDetectorFileSink : public FairMQDevice
{
  public:
    FairTestDetectorFileSink()
        : fOutput(nullptr)
        , fOutFile(nullptr)
        , fTree(nullptr)
        , fHitVector()
        , fBigBuffer(FairMQ::tools::make_unique<std::array<unsigned char, BIGBUFFERSIZE>>())
    {
        gSystem->ResetSignal(kSigInterrupt);
        gSystem->ResetSignal(kSigTermination);

        // Check if boost serialization is available if it is chosen
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (std::is_same<TPayloadIn, boost::archive::binary_iarchive>::value || std::is_same<TPayloadIn, boost::archive::text_iarchive>::value)
        {
            if (baseMQ::tools::resolve::has_BoostSerialization<TIn, void(TPayloadIn&, const unsigned int)>::value == 0)
            {
                LOG(ERROR) << "Boost serialization for Input Payload requested, but the input type does not support it. Check the TIn parameter. Aborting.";
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
        if (fHitVector.size() > 0)
        {
            fHitVector.clear();
        }
        if (fOutput)
        {
            delete fOutput;
        }
        delete fOutFile;
    }

    virtual void InitOutputFile(TString defaultId = "100")
    {
        fOutput = new TClonesArray("FairTestDetectorHit");
        char out[256];
        sprintf(out, "filesink%s.root", defaultId.Data());

        fOutFile = new TFile(out, "recreate");
        fTree = new TTree("MQOut", "Test output");
        fTree->Branch("Output", "TClonesArray", &fOutput, 64000, 99);
    }

  protected:
    virtual void Run();

  private:
    TClonesArray* fOutput;
    TFile* fOutFile;
    TTree* fTree;

#ifndef __CINT__ // for BOOST serialization
    std::vector<TIn> fHitVector;
    std::unique_ptr<std::array<unsigned char, BIGBUFFERSIZE>> fBigBuffer;
#endif // for BOOST serialization
};

// Template implementation of Run() in FairTestDetectorFileSink.tpl :
#include "FairTestDetectorFileSinkBin.tpl"
#include "FairTestDetectorFileSinkBoost.tpl"
#include "FairTestDetectorFileSinkFlatBuffers.tpl"
#include "FairTestDetectorFileSinkMsgpack.tpl"
#include "FairTestDetectorFileSinkProtobuf.tpl"
#include "FairTestDetectorFileSinkTMessage.tpl"

#endif /* FAIRTESTDETECTORFILESINK_H_ */
