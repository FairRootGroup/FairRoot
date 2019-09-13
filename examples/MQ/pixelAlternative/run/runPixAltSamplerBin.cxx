/********************************************************************************
 * Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"

// PixelAlternative example
#include "FairMQPixAltSamplerBin.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("file-name",   bpo::value<std::vector<std::string>>()                           , "Path to the input file")
        ("max-index",   bpo::value<int64_t>                 ()->default_value(-1)        , "number of events to read")
        ("out-channel", bpo::value<std::string>             ()->default_value("data-out"), "output channel name")
        ("ack-channel", bpo::value<std::string>             ()->default_value("")        , "ack channel name")
        ("aggregate",   bpo::value<int>                     ()->default_value(1)         , "aggregate level");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new FairMQPixAltSamplerBin;
}
