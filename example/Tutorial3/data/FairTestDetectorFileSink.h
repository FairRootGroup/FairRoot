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
    FairTestDetectorFileSink();
    virtual ~FairTestDetectorFileSink();
    virtual void InitOutputFile(TString defaultId = "100");

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& fHitVector;
    }

  protected:
    virtual void Run();

  private:
    TFile* fOutFile;
    TTree* fTree;
    TClonesArray* fOutput;
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
    vector<TIn> fHitVector;
    bool fHasBoostSerialization;
#endif // for BOOST serialization

    /// Copy Constructor
    FairTestDetectorFileSink(const FairTestDetectorFileSink&);
    FairTestDetectorFileSink operator=(const FairTestDetectorFileSink&);
};

////////// Template implementation of Run() in FairTestDetectorFileSink.tpl :
#include "FairTestDetectorFileSink.tpl"

#endif /* FAIRTESTDETECTORFILESINK_H_ */
