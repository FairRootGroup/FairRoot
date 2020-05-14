#include "runFairMQDevice.h"

// MQRunSim
#include "FairMQChunkMerger.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("in-channel",  bpo::value<std::string>()->default_value("data-in"),  "input channel name")
        ("out-channel", bpo::value<std::string>()->default_value("data-out"), "output channel name");
    // clang-format on
}

FairMQDevicePtr getDevice(__attribute__((unused)) const FairMQProgOptions& config) { return new FairMQChunkMerger(); }
