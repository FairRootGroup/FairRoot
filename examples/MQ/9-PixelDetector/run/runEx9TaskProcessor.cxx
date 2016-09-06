/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"

#include "PixelFindHits.h"
#include "PixelFindTracks.h"
#include "PixelFitTracks.h"

// 9-PixelDetector example
#include "FairMQEx9TaskProcessor.h"

using HitFinder   = FairMQEx9TaskProcessor<PixelFindHits>;
using TrackFinder = FairMQEx9TaskProcessor<PixelFindTracks>;
using TrackFitter = FairMQEx9TaskProcessor<PixelFitTracks>;

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
  options.add_options()
    ("task-name",   bpo::value<std::string>()->required()                  ,  "Name of task to run")
    ("keep-data",   bpo::value<std::string>()                              ,  "Name of data to keep in stream")
    ("in-channel",  bpo::value<std::string>()->default_value("data-in")   , "input channel name")
    ("out-channel", bpo::value<std::string>()->default_value("data-out") , "output channel name")
    ("par-channel", bpo::value<std::string>()->default_value("param")    , "param channel name");
}

FairMQDevice* getDevice(const FairMQProgOptions& config)
{
  std::string taskname = config.GetValue<std::string>("task-name");

  std::cout << "get device with setting!" << std::endl;

  if      ( strcmp(taskname.c_str(),"PixelFindHits") == 0 ) {
    return new HitFinder();
  }
  else if ( strcmp(taskname.c_str(),"PixelFindTracks") == 0 ) {
    return new TrackFinder();
  }
  else if ( strcmp(taskname.c_str(),"PixelFitTracks") == 0 ) {
    return new TrackFitter();
  }

  return 0;
}
