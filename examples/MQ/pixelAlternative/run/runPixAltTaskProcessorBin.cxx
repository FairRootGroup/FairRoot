/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// PixelAlternative example
#include "FairMQPixAltTaskProcessorBin.h"
#include "FairRunFairMQDevice.h"
#include "PixelAltFindHits.h"

#include <fairlogger/Logger.h>
#include <iostream>

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

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    std::string taskname = config.GetValue<std::string>("task-name");

    std::cout << "get device with setting!" << std::endl;

    if (taskname == "PixelAltFindHits") {
        using Processor = FairMQPixAltTaskProcessorBin<PixelAltFindHits>;
        return std::unique_ptr<Processor>(new Processor());
    }

    LOG(info) << "TASK \"" << taskname << "\" UNKNOWN!!!";
    return {nullptr};
}
