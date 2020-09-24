/********************************************************************************
 * Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"                 // for FairMQDevicePtr, addCust...
// PixelDetector example
#include "FairMQPixelMerger.h"               // for FairMQPixelMerger

namespace boost {
namespace program_options {
class options_description;
}  // namespace program_options
}  // namespace boost

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& /*options*/) {}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/) { return new FairMQPixelMerger(); }
