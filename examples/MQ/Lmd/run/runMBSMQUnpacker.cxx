/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runMBSUnpacker.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 1:57 PM
 */

#include "runFairMQDevice.h"
#include "FairMQUnpacker.h"
#include "FairMBSUnpacker.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("lmd-type",      po::value<short>(),       "sub-event type")
        ("lmd-sub-type",  po::value<short>(),       "sub-event subType")
        ("lmd-proc-id",   po::value<short>(),       "sub-event procId")
        ("lmd-sub-crate", po::value<short>(),       "sub-event subCrate")
        ("lmd-control",   po::value<short>(),       "sub-event control")
        ("lmd-chan-name", po::value<std::string>(), "MQ-channel name for this sub-event");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new FairMQUnpacker<FairMBSUnpacker>();
}
