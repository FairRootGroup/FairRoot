/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"

// PixelAlternative example
#include "FairMQPixAltFileSinkBin.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
  options.add_options()
    ("file-name",   bpo::value<std::string>             ()                           , "Path to the output file")
    ("in-channel",  bpo::value<std::string>             ()->default_value("data-in") , "input channel name")
    ("ack-channel", bpo::value<std::string>             ()                           , "ack channel name");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
  return new FairMQPixAltFileSinkBin();
}
