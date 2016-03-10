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
#include <array>

#ifndef __CINT__ // Boost serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/binary_object.hpp>
#endif //__CINT__

#include "TMath.h"
#include "TClonesArray.h"

#include "FairRootManager.h"
#include "FairMQLogger.h"
#include "FairMQProcessorTask.h"
#include "FairMQMessage.h"
#include "FairMQTools.h"

#include "FairTestDetectorRecoTask.h"
#include "FairTestDetectorPayload.h"
#include "FairTestDetectorHit.h"
#include "FairTestDetectorDigi.h"

#include "baseMQtools.h"

#include "TMessage.h"

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
class FairTestDetectorMQRecoTask : public FairMQProcessorTask
{
  public:
    FairTestDetectorMQRecoTask()
        : fRecoTask(nullptr)
        , fDigiVector()
        , fHitVector()
        , fBigBuffer(FairMQ::tools::make_unique<std::array<unsigned char, BIGBUFFERSIZE>>())
    {
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (std::is_same<TPayloadIn, boost::archive::binary_iarchive>::value || std::is_same<TPayloadIn, boost::archive::text_iarchive>::value)
        {
            if (baseMQ::tools::resolve::has_BoostSerialization<TIn, void(TPayloadIn&, const unsigned int)>::value == 0)
            {
                LOG(ERROR) << "Method 'void serialize(TIn & ar, const unsigned int version)' was not found in input class";
                LOG(ERROR) << "Boost serialization for Input Payload requested, but the input type does not support it. Check the TIn parameter. Aborting.";
                exit(EXIT_FAILURE);
            }
        }
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (std::is_same<TPayloadOut, boost::archive::binary_oarchive>::value || std::is_same<TPayloadOut, boost::archive::text_oarchive>::value)
        {
            if (baseMQ::tools::resolve::has_BoostSerialization<TOut, void(TPayloadOut&, const unsigned int)>::value == 0)
            {
                LOG(ERROR) << "Method 'void serialize(TOut & ar, const unsigned int version)' was not found in input class";
                LOG(ERROR) << "Boost serialization for Output Payload requested, but the output type does not support it. Check the TOut parameter. Aborting.";
                exit(EXIT_FAILURE);
            }
        }
    }

    FairTestDetectorMQRecoTask(Int_t verbose)
        : fRecoTask(nullptr)
        , fDigiVector()
        , fHitVector()
        , fBigBuffer(FairMQ::tools::make_unique<std::array<unsigned char, BIGBUFFERSIZE>>())
    {
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (std::is_same<TPayloadIn, boost::archive::binary_iarchive>::value || std::is_same<TPayloadIn, boost::archive::text_iarchive>::value)
        {
            if (baseMQ::tools::resolve::has_BoostSerialization<TIn, void(TPayloadIn&, const unsigned int)>::value == 0)
            {
                LOG(ERROR) << "Method 'void serialize(TIn & ar, const unsigned int version)' was not found in input class";
                LOG(ERROR) << "Boost serialization for Input Payload requested, but the input type does not support it. Check the TIn parameter. Aborting.";
                exit(EXIT_FAILURE);
            }
        }

        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (std::is_same<TPayloadOut, boost::archive::binary_oarchive>::value || std::is_same<TPayloadOut, boost::archive::text_oarchive>::value)
        {
            if (baseMQ::tools::resolve::has_BoostSerialization<TOut, void(TPayloadOut&, const unsigned int)>::value == 0)
            {
                LOG(ERROR) << "Method 'void serialize(TOut & ar, const unsigned int version)' was not found in input class";
                LOG(ERROR) << "Boost serialization for Output Payload requested, but the output type does not support it. Check the TOut parameter. Aborting.";
                exit(EXIT_FAILURE);
            }
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

  private:
    FairTestDetectorRecoTask* fRecoTask;
#ifndef __CINT__ // for BOOST serialization
    std::vector<TIn> fDigiVector;
    std::vector<TOut> fHitVector;
    std::unique_ptr<std::array<unsigned char, BIGBUFFERSIZE>> fBigBuffer;
#endif // for BOOST serialization
};

// Template implementation of exec in FairTestDetectorMQRecoTask.tpl :
#include "FairTestDetectorMQRecoTaskBin.tpl"
#include "FairTestDetectorMQRecoTaskBoost.tpl"
#include "FairTestDetectorMQRecoTaskFlatBuffers.tpl"
#include "FairTestDetectorMQRecoTaskMsgpack.tpl"
#include "FairTestDetectorMQRecoTaskProtobuf.tpl"
#include "FairTestDetectorMQRecoTaskTMessage.tpl"

#endif /* FAIRTESTDETECTORMQRECOTASK_H */
