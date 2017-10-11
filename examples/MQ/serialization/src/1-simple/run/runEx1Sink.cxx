/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"
#include "Ex1Sink.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("output-file", bpo::value<std::string>(), "Path to the output file")
        ("num-msgs", bpo::value<int>()->default_value(0), "Stop after <n> msgs (0 - no limit).");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new Ex1Sink();
}
