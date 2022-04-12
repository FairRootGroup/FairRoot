/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQPixelFileSink.h"
#include "FairRunFairMQDevice.h"

#include <string>

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("file-name",   bpo::value<std::string>(),                           "Path to the output file")
        ("in-channel",  bpo::value<std::string>()->default_value("data-in"), "input channel name")
        ("ack-channel", bpo::value<std::string>(),                           "ack channel name");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions&)
{
    return std::unique_ptr<FairMQPixelFileSink>(new FairMQPixelFileSink());
}
