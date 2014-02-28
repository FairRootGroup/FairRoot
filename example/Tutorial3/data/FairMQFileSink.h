/**
 * FairMQFileSink.h
 *
 * @since 2013-06-05
 * @author A. Rybalchenko
 */

#ifndef FAIRMQFILESINK_H_
#define FAIRMQFILESINK_H_

#include <iostream>

#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include "TString.h"

#include "FairMQDevice.h"
#include "FairMQFileSink.h"
#include "FairMQLogger.h"

#include "FairTestDetectorPayload.h"
#include "FairTestDetectorHit.h"

#ifndef __CINT__
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#endif //__CINT__


class TVector3;
class TFile;
class TTree;
class TClonesArray;

template <typename TIn, typename TBoostIArchive>
class FairMQFileSink: public FairMQDevice
{
  public:
    FairMQFileSink(){}
    virtual ~FairMQFileSink()
    {
        fTree->Write();
        fOutFile->Close();
        if(fHitVector.size()>0) fHitVector.clear();
    }
    virtual void InitOutputFile(TString defaultId = "100")
    {
        fOutput = new TClonesArray("FairTestDetectorHit");

        char out[256];
        sprintf(out, "filesink%s.root", defaultId.Data());

        fOutFile = new TFile(out,"recreate");
        fTree = new TTree("MQOut", "Test output");
        fTree->Branch("Output","TClonesArray", &fOutput, 64000, 99);
    }
  protected:
    virtual void Run();
  private:
    TFile* fOutFile;
    TTree* fTree;
    TClonesArray* fOutput;
    #ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
    std:: vector<TIn> fHitVector;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & fHitVector;
    }
    #endif // for BOOST serialization
};


////////// Template implementation of Run() in FairMQFileSink.tpl :
#include "FairMQFileSink.tpl"

#endif /* FAIRMQFILESINK_H_ */
