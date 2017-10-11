/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runSamplerRoot.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 1:57 PM
 */

#include "runFairMQDevice.h"
#include "FairMQLmdSampler.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("input-file-name", bpo::value<std::string>(),  "Path to the input file")
        ("lmd-type",        bpo::value<short>(),        "sub-event type")
        ("lmd-sub-type",    bpo::value<short>(),        "sub-event subType")
        ("lmd-proc-id",     bpo::value<short>(),        "sub-event procId")
        ("lmd-sub-crate",   bpo::value<short>(),        "sub-event subCrate")
        ("lmd-control",     bpo::value<short>(),        "sub-event control")
        ("lmd-chan-name",   bpo::value<std::string>(),  "MQ-channel name for this sub-event");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new FairMQLmdSampler();
}
