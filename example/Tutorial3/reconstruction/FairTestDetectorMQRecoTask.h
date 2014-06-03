/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORMQRECOTASK_H
#define FAIRTESTDETECTORMQRECOTASK_H

#include <iostream>
#include <sstream>

#ifndef __CINT__ // Boost serialization
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#endif //__CINT__

#include "TMath.h"
#include "TClonesArray.h"

#include "FairRootManager.h"
#include "FairMQLogger.h"
#include "FairMQProcessorTask.h"
#include "FairMQMessage.h"

#include "FairTestDetectorRecoTask.h"
#include "FairTestDetectorPayload.h"
#include "FairTestDetectorHit.h"
#include "FairTestDetectorDigi.h"

#if __cplusplus >= 201103L
//#include <memory>
//#include <chrono>
#include "has_BoostSerialization.h"
#endif

#include "TMessage.h"

using std::cout;
using std::endl;

class TClonesArray;
template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
class FairTestDetectorMQRecoTask : public FairMQProcessorTask
{
  public:
    /** Default constructor **/
    FairTestDetectorMQRecoTask();
    FairTestDetectorMQRecoTask(Int_t verbose);

    /** Destructor **/
    virtual ~FairTestDetectorMQRecoTask();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(FairMQMessage* msg, Option_t* opt);

    // boost serialize function
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& fDigiVector;
        ar& fHitVector;
    }

  private:
    FairTestDetectorRecoTask* fRecoTask;
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
    std::vector<TIn> fDigiVector;
    std::vector<TOut> fHitVector;
    bool fHasBoostSerialization;
#endif // for BOOST serialization
};

////////// Template implementation of exec in FairTestDetectorMQRecoTask.tpl :
#include "FairTestDetectorMQRecoTask.tpl"

#endif /* FAIRTESTDETECTORMQRECOTASK_H */
