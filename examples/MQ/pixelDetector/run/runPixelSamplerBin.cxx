#include "runFairMQDevice.h"

// PixelDetector example
#include "FairMQPixelSamplerBin.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
  options.add_options()
    ("file-name",   bpo::value<std::vector<std::string>>()                                  , "Path to the input file")
    ("max-index",   bpo::value<int64_t>                 ()->default_value(-1)               , "number of events to read")
    ("branch-name", bpo::value<std::vector<std::string>>()                                  , "branch name")
    ("out-channel", bpo::value<std::string>             ()->default_value("data-out")       , "output channel name")
    ("ack-channel", bpo::value<std::string>             ()->default_value("")               , "ack channel name");
;
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
  return new FairMQPixelSamplerBin;
}
