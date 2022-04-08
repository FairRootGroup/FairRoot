/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "PixelDigitize.h"
#include "PixelFindHits.h"
#include "PixelFindTracks.h"
#include "PixelFitTracks.h"

// PixelDetector example
#include "FairMQPixelTaskProcessor.h"
#include "FairRunFairMQDevice.h"

#include <string>

using Digitizer = FairMQPixelTaskProcessor<PixelDigitize>;
using HitFinder = FairMQPixelTaskProcessor<PixelFindHits>;
using TrackFinder = FairMQPixelTaskProcessor<PixelFindTracks>;
using TrackFitter = FairMQPixelTaskProcessor<PixelFitTracks>;

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("task-name",   bpo::value<std::string>()->required(),                "Name of task to run")
        ("keep-data",   bpo::value<std::string>(),                            "Name of data to keep in stream")
        ("in-channel",  bpo::value<std::string>()->default_value("data-in"),  "input channel name")
        ("out-channel", bpo::value<std::string>()->default_value("data-out"), "output channel name")
        ("par-channel", bpo::value<std::string>()->default_value("param"),    "param channel name")
        ("static-pars", bpo::value<bool>()->default_value(false),             "static parameters flag");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    std::string taskname = config.GetValue<std::string>("task-name");

    LOG(info) << "get device with setting!";

    if (taskname == "PixelFindHits") {
        return std::make_unique<HitFinder>();
    } else if (taskname == "PixelFindTracks") {
        return std::make_unique<TrackFinder>();
    } else if (taskname == "PixelFitTracks") {
        return std::make_unique<TrackFitter>();
    } else if (taskname == "PixelDigitize") {
        return std::make_unique<Digitizer>();
    }

    return {nullptr};
}
