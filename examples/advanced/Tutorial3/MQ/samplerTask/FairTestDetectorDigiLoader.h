/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * File:   FairTestDetectorDigiLoader.h
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 */

#ifndef FAIRTESTDETECTORDIGILOADER_H
#define FAIRTESTDETECTORDIGILOADER_H

#include <iostream>
#include <type_traits>
#include <array>

#include <boost/timer/timer.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/binary_object.hpp>

#include "TMessage.h"

#include "FairTestDetectorPayload.h"
#include "FairTestDetectorDigi.h"

#include "FairMQSamplerTask.h"
#include "FairMQLogger.h"
#include "FairMQTools.h"

#include "baseMQtools.h"

template <typename TOut, typename TPayloadOut>
class FairTestDetectorDigiLoader : public FairMQSamplerTask
{
  public:
    FairTestDetectorDigiLoader()
        : FairMQSamplerTask("Load class TOut")
        , fDigiVector()
        , fBigBuffer(FairMQ::tools::make_unique<std::array<unsigned char, BIGBUFFERSIZE>>())
    {
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

    virtual ~FairTestDetectorDigiLoader()
    {
        if (fDigiVector.size() > 0)
        {
            fDigiVector.clear();
        }
    }

    virtual void Exec(Option_t* opt);

  private:
#ifndef __CINT__ // for BOOST serialization
    std::vector<TOut> fDigiVector;
    std::unique_ptr<std::array<unsigned char, BIGBUFFERSIZE>> fBigBuffer;
#endif // for BOOST serialization
};

// Template implementation is in FairTestDetectorDigiLoader.tpl :
#include "FairTestDetectorDigiLoaderBin.tpl"
#include "FairTestDetectorDigiLoaderBoost.tpl"
#include "FairTestDetectorDigiLoaderFlatBuffers.tpl"
#include "FairTestDetectorDigiLoaderMsgpack.tpl"
#include "FairTestDetectorDigiLoaderProtobuf.tpl"
#include "FairTestDetectorDigiLoaderTMessage.tpl"

#endif /* FAIRTESTDETECTORDIGILOADER_H */
