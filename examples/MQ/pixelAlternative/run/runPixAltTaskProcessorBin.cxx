/********************************************************************************
 * Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <functional>                                       // for __base
#include <iostream>                                         // for string
#include <string>                                           // for basic_string

#include "PixelAltFindHits.h"                               // for PixelAltF...
#include "runFairMQDevice.h"                                // for FairMQDev...
// PixelAlternative example
#include "FairMQPixAltTaskProcessorBin.h"                   // for FairMQPix...

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("task-name",   bpo::value<std::string>()->required(),                "Name of task to run")
        ("keep-data",   bpo::value<std::string>(),                            "Name of data to keep in stream")
        ("in-channel",  bpo::value<std::string>()->default_value("data-in"),  "input channel name")
        ("out-channel", bpo::value<std::string>()->default_value("data-out"), "output channel name")
        ("par-channel", bpo::value<std::string>()->default_value("param"),    "param channel name");
    // clang-format on
}

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
    std::string taskname = config.GetValue<std::string>("task-name");

    std::cout << "get device with setting!" << std::endl;

    if (taskname == "PixelAltFindHits") {
        return new FairMQPixAltTaskProcessorBin<PixelAltFindHits>();
    }

    LOG(info) << "TASK \"" << taskname << "\" UNKNOWN!!!";
    return 0;
}
