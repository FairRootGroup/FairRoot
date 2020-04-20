/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQExParamsClient.h"
#include "runFairMQDevice.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("parameter-name", bpo::value<std::string>()->default_value("FairMQExParamsParOne"), "Parameter Name")
        ("max-iterations", bpo::value<uint64_t>()->default_value(0),                         "Maximum number of iterations of Run/ConditionalRun/OnData (0 - infinite)");
    // clang-format on
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/) { return new FairMQExParamsClient(); }
