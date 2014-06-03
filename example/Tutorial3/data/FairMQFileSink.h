/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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

#if __cplusplus >= 201103L
#include "has_BoostSerialization.h"
#endif

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

template <typename TIn, typename TPayloadIn>
class FairMQFileSink : public FairMQDevice
{
  public:
    FairMQFileSink();
    virtual ~FairMQFileSink();
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
    std::vector<TIn> fHitVector;
    bool fHasBoostSerialization;
#endif // for BOOST serialization
};

////////// Template implementation of Run() in FairMQFileSink.tpl :
#include "FairMQFileSink.tpl"

#endif /* FAIRMQFILESINK_H_ */
