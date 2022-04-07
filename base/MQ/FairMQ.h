/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRROOT_BASE_MQ_FAIRMQ_H
#define FAIRROOT_BASE_MQ_FAIRMQ_H

#include <fairmq/Version.h>
#ifdef FAIRMQ_VERSION_DEC
#undef FAIRMQ_VERSION_DEC   // bugged
#endif
#if defined FAIRMQ_VERSION_MAJOR && defined FAIRMQ_VERSION_MINOR && defined FAIRMQ_VERSION_PATCH
#define FAIRMQ_VERSION_DEC (FAIRMQ_VERSION_MAJOR * 100000) + (FAIRMQ_VERSION_MINOR * 1000) + (FAIRMQ_VERSION_PATCH * 10)
#else
#define FAIRMQ_VERSION_DEC 9999999
#endif

// see https://github.com/FairRootGroup/FairMQ/discussions/423
#if FAIRMQ_VERSION_DEC < 104410

#include <FairMQChannel.h>               // for FairMQChannel
#include <FairMQDevice.h>                // for FairMQDevice
#include <FairMQMessage.h>               // for FairMQMessage, FairMQMessagePtr
#include <FairMQParts.h>                 // for FairMQParts
#include <FairMQTransportFactory.h>      // for FairMQTransportFactory
#include <options/FairMQProgOptions.h>   // for FairMQProgOptions

namespace fair {
namespace mq {
using Channel = ::FairMQChannel;
using Device = ::FairMQDevice;
using Message = ::FairMQMessage;
using MessagePtr = ::FairMQMessagePtr;
using Parts = ::FairMQParts;
using ProgOptions = ::FairMQProgOptions;
using TransportFactory = ::FairMQTransportFactory;
}   // namespace mq
}   // namespace fair

#else

#include <fairmq/Channel.h>            // for fair::mq::Channel
#include <fairmq/Device.h>             // for fair::mq::Device
#include <fairmq/Message.h>            // for fair::mq::Message, fair::mq::MessagePtr
#include <fairmq/Parts.h>              // for fair::mq::Parts
#include <fairmq/ProgOptions.h>        // for fair::mq::ProgOptions
#include <fairmq/TransportFactory.h>   // for fair::mq::TransportFactory

#endif

#endif   // FAIRROOT_BASE_MQ_FAIRMQ_H
