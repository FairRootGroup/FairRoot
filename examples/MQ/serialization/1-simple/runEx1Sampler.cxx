/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runSamplerRoot.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 1:57 PM
 */

#include "Ex1Sampler.h"
#include "runFairMQDevice.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("input-file", bpo::value<std::string>(), "Path to the input file");
    // clang-format on
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/) { return new Ex1Sampler(); }
