/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRROOT_FAIRRUNFAIRMQDEVICE_H
#define FAIRROOT_FAIRRUNFAIRMQDEVICE_H

#include <fairmq/Version.h>
#ifdef FAIRMQ_VERSION_DEC
#undef FAIRMQ_VERSION_DEC   // bugged
#endif
#if defined FAIRMQ_VERSION_MAJOR && defined FAIRMQ_VERSION_MINOR && defined FAIRMQ_VERSION_PATCH
#define FAIRMQ_VERSION_DEC (FAIRMQ_VERSION_MAJOR * 100000) + (FAIRMQ_VERSION_MINOR * 1000) + (FAIRMQ_VERSION_PATCH * 10)
#else
#define FAIRMQ_VERSION_DEC 9999999
#endif

#if FAIRMQ_VERSION_DEC < 104340
#include <fairmq/runFairMQDevice.h>
#include <memory>   // for std::unique_ptr

namespace fair {
namespace mq {
using Device = ::FairMQDevice;
using ProgOptions = ::FairMQProgOptions;
}   // namespace mq
}   // namespace fair
#else
// see https://github.com/FairRootGroup/FairMQ/commit/978191fa6c252714b73dde70d6737ac1cc4e529a
#include <fairmq/runDevice.h>
#endif

// FairRoot API during transition period
// to be implemented by the user, keeping the old const& arg for the transition
std::unique_ptr<fair::mq::Device> fairGetDevice(fair::mq::ProgOptions const&);

// FairMQ API
#if FAIRMQ_VERSION_DEC < 104340
// getDevice from <fairmq/runFairMQDevice.h>
FairMQDevicePtr getDevice(fair::mq::ProgOptions const& options)
{
    return fairGetDevice(options).release();
}
#elif FAIRMQ_VERSION_DEC < 104380
// see https://github.com/FairRootGroup/FairMQ/commit/978191fa6c252714b73dde70d6737ac1cc4e529a
std::unique_ptr<fair::mq::Device> getDevice(fair::mq::ProgOptions const& options)
{
    return fairGetDevice(options);
}
#else
// see https://github.com/FairRootGroup/FairMQ/commit/a7dbeadd1c8f3f82c43067b05290e4393a44f1ac
std::unique_ptr<fair::mq::Device> getDevice(fair::mq::ProgOptions& options)
{
    return fairGetDevice(options);
}
#endif

#endif   // FAIRROOT_FAIRRUNFAIRMQDEVICE_H
