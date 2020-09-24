/********************************************************************************
 * Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <iosfwd>                                           // for string
#include <string>                                           // for basic_string

#include "runFairMQDevice.h"                                // for FairMQDev...
// PixelAlternative example
#include "FairMQPixAltFileSinkBin.h"                        // for FairMQPix...

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("file-name",   bpo::value<std::string>()                          , "Path to the output file")
        ("in-channel",  bpo::value<std::string>()->default_value("data-in"), "input channel name")
        ("ack-channel", bpo::value<std::string>()                          , "ack channel name");
    // clang-format on
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/) { return new FairMQPixAltFileSinkBin(); }
