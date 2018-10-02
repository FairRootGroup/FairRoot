#include "runFairMQDevice.h"

// MQRunSim
#include "FairPrimaryGenerator.h"
#include "FairBoxGenerator.h"
#include "FairMQChunkMerger.h"

#include "TRandom.h"
#include "TRint.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TVirtualMC.h"
#include "TVirtualMCApplication.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
}

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
    FairMQChunkMerger* mqDevice = new FairMQChunkMerger();

    return mqDevice;
}
