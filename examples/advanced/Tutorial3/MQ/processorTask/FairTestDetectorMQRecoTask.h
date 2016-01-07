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

#include "baseMQtools.h"

#include "TMessage.h"

using namespace std;

class TClonesArray;

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
class FairTestDetectorMQRecoTask : public FairMQProcessorTask
{
  public:
    /** Default constructor **/
    FairTestDetectorMQRecoTask()
        : fRecoTask(nullptr)
        , fDigiVector()
        , fHitVector()
        , fHasBoostSerialization(false)
    {
        using namespace baseMQ::tools::resolve;
        bool checkInputClass = false;
        bool checkOutputClass = false;
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (is_same<TPayloadIn, boost::archive::binary_iarchive>::value || is_same<TPayloadIn, boost::archive::text_iarchive>::value)
        {
            if (has_BoostSerialization<TIn, void(TPayloadIn&, const unsigned int)>::value == 1)
            {
                checkInputClass = true;
            }
        }
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (is_same<TPayloadOut, boost::archive::binary_oarchive>::value || is_same<TPayloadOut, boost::archive::text_oarchive>::value)
        {
            if (has_BoostSerialization<TOut, void(TPayloadOut&, const unsigned int)>::value == 1)
            {
                checkOutputClass = true;
            }
        }

        if (checkInputClass && checkOutputClass)
        {
            fHasBoostSerialization = true;
        }
    }

    FairTestDetectorMQRecoTask(Int_t verbose)
        : fRecoTask(nullptr)
        , fDigiVector()
        , fHitVector()
        , fHasBoostSerialization(false)
    {
        using namespace baseMQ::tools::resolve;
        bool checkInputClass = false;
        bool checkOutputClass = false;

        if (is_same<TPayloadIn, boost::archive::binary_iarchive>::value || is_same<TPayloadIn, boost::archive::text_iarchive>::value)
        {
            if (has_BoostSerialization<TIn, void(TPayloadIn&, const unsigned int)>::value == 1)
            {
                checkInputClass = true;
            }
            else
            {
                LOG(ERROR) << "Method 'void serialize(TIn & ar, const unsigned int version)' was not found in input class";
            }
        }
        else
        {
            LOG(ERROR) << "Output payload is not of supported boost archive type";
            LOG(ERROR) << "Boost inpput archive type supported : ";
            LOG(ERROR) << "boost::archive::binary_iarchive and boost::archive::text_iarchive";
        }

        if (is_same<TPayloadOut, boost::archive::binary_oarchive>::value || is_same<TPayloadOut, boost::archive::text_oarchive>::value)
        {
            if (has_BoostSerialization<TOut, void(TPayloadOut&, const unsigned int)>::value == 1)
            {
                checkOutputClass = true;
            }
            else
            {
                LOG(ERROR) << "Method 'void serialize(TOut & ar, const unsigned int version)' was not found in input class";
            }
        }
        else
        {
            LOG(ERROR) << "Output payload is not of supported boost archive type";
            LOG(ERROR) << "Boost output archive type supported : ";
            LOG(ERROR) << "boost::archive::binary_oarchive and boost::archive::text_oarchive";
        }

        if (checkInputClass && checkOutputClass)
        {
            fHasBoostSerialization = true;
        }
    }
    FairTestDetectorMQRecoTask(const FairTestDetectorMQRecoTask&) = delete;
    FairTestDetectorMQRecoTask operator=(const FairTestDetectorMQRecoTask&) = delete;

    /** Destructor **/
    virtual ~FairTestDetectorMQRecoTask()
    {
        if (fRecoTask->fDigiArray)
        {
            fRecoTask->fDigiArray->Delete();
            delete fRecoTask->fDigiArray;
        }
        if (fRecoTask->fHitArray)
        {
            fRecoTask->fHitArray->Delete();
            delete fRecoTask->fHitArray;
        }
        delete fRecoTask;
        if (fDigiVector.size() > 0)
        {
            fDigiVector.clear();
        }
        if (fHitVector.size() > 0)
        {
            fHitVector.clear();
        }
    }

    /** Virtual method Init **/
    virtual InitStatus Init()
    {
        fRecoTask = new FairTestDetectorRecoTask();
        fRecoTask->fDigiArray = new TClonesArray("FairTestDetectorDigi");
        fRecoTask->fHitArray = new TClonesArray("FairTestDetectorHit");

        return kSUCCESS;
    }

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt = "0");

    // boost serialize function
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& fDigiVector;
        ar& fHitVector;
    }

  private:
    FairTestDetectorRecoTask* fRecoTask;
    bool fHasBoostSerialization;
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
    vector<TIn> fDigiVector;
    vector<TOut> fHitVector;
#endif // for BOOST serialization
};

// Template implementation of exec in FairTestDetectorMQRecoTask.tpl :
#include "FairTestDetectorMQRecoTaskBoost.tpl"
#include "FairTestDetectorMQRecoTaskBin.tpl"
#include "FairTestDetectorMQRecoTaskProtobuf.tpl"
#include "FairTestDetectorMQRecoTaskTMessage.tpl"

#endif /* FAIRTESTDETECTORMQRECOTASK_H */
