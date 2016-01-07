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

#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include "TString.h"
#include "TSystem.h"

#include "FairMQDevice.h"
#include "FairMQLogger.h"

#include "FairTestDetectorPayload.h"
#include "FairTestDetectorHit.h"

#include "baseMQtools.h"

#include "TMessage.h"

#ifndef __CINT__
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#endif //__CINT__

class TVector3;
class TFile;
class TTree;
class TClonesArray;

using namespace std;

template <typename TIn, typename TPayloadIn>
class FairTestDetectorFileSink : public FairMQDevice
{
  public:
    FairTestDetectorFileSink()
        : fOutput(nullptr)
        , fOutFile(nullptr)
        , fTree(nullptr)
        , fHitVector()
        , fHasBoostSerialization(false)
    {
        gSystem->ResetSignal(kSigInterrupt);
        gSystem->ResetSignal(kSigTermination);

        // Check if boost serialization is available if it is chosen
        using namespace baseMQ::tools::resolve;
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (is_same<TPayloadIn, boost::archive::binary_iarchive>::value || is_same<TPayloadIn, boost::archive::text_iarchive>::value)
        {
            if (has_BoostSerialization<TIn, void(TPayloadIn&, const unsigned int)>::value == 1)
            {
                fHasBoostSerialization = true;
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

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& fHitVector;
    }

  protected:
    virtual void Run();

  private:
    TClonesArray* fOutput;
    TFile* fOutFile;
    TTree* fTree;

#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
    vector<TIn> fHitVector;
    bool fHasBoostSerialization;
#endif // for BOOST serialization
};

// Template implementation of Run() in FairTestDetectorFileSink.tpl :
#include "FairTestDetectorFileSinkBoost.tpl"
#include "FairTestDetectorFileSinkBin.tpl"
#include "FairTestDetectorFileSinkProtobuf.tpl"
#include "FairTestDetectorFileSinkTMessage.tpl"

#endif /* FAIRTESTDETECTORFILESINK_H_ */
