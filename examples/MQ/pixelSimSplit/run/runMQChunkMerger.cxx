
#include <iosfwd>                                           // for string
#include <string>                                           // for basic_string

#include "runFairMQDevice.h"                                // for FairMQDev...
// MQRunSim
#include "FairMQChunkMerger.h"                              // for FairMQChu...

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("in-channel",  bpo::value<std::string>()->default_value("data-in"),  "input channel name")
        ("out-channel", bpo::value<std::string>()->default_value("data-out"), "output channel name");
    // clang-format on
}

FairMQDevicePtr getDevice([[gnu::unused]] const FairMQProgOptions& config) { return new FairMQChunkMerger(); }
