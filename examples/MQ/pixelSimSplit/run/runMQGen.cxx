#include "runFairMQDevice.h"   // for FairMQDev...

#include <ProgOptionsFwd.h>      // for FairMQPro...
#include <RtypesCore.h>          // for Int_t
#include <TRandom.h>             // for TRandom
#include <TString.h>             // for TString
#include <TSystem.h>             // for TSystem
#include <cstdint>               // for int64_t
#include <fairlogger/Logger.h>   // for LOG, Logger
#include <iosfwd>                // for string
#include <stdlib.h>              // for getenv
#include <string>                // for basic_string
// MQRunSim
#include "FairBoxGenerator.h"               // for FairBoxGe...
#include "FairMQPrimaryGeneratorDevice.h"   // for FairMQPri...
#include "FairPrimaryGenerator.h"           // for FairPrima...

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("random-seed",         bpo::value<int64_t>()->default_value(0),        "Random seed number")
        ("nof-events",          bpo::value<int64_t>()->required(),              "Number of events to simulate")
        ("running-mode",        bpo::value<std::string>()->default_value("pp"), "pp to push, rr to reply")
        ("fairroot-config-dir", bpo::value<std::string>()->default_value(""),   "FairRoot config dir")
        ("chunk-size",          bpo::value<int64_t>()->default_value(0),        "Max nof primaries in chunk")
        ("ack-channel",         bpo::value<std::string>()->default_value(""),   "Ack channel name");
    // clang-format on
}

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
    gRandom->SetSeed(config.GetValue<int64_t>("random-seed"));

    TString dir = getenv("VMCWORKDIR");
    TString tutdir = dir + "/MQ/pixelDetector";

    TString tut_configdir = config.GetValue<std::string>("fairroot-config-dir");
    if (tut_configdir.Length() < 1)
        tut_configdir = dir + "/common/gconfig";
    gSystem->Setenv("CONFIG_DIR", tut_configdir.Data());

    Int_t partPdgC[] = {211, 11, 2212};   //{"pions","eplus","proton"}
    Int_t chosenPart = 0;

    FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
    FairBoxGenerator* boxGen = new FairBoxGenerator(partPdgC[chosenPart], 100);
    boxGen->SetPRange(1, 2);
    boxGen->SetThetaRange(0, 180);
    boxGen->SetPhiRange(0, 360);
    primGen->AddGenerator(boxGen);

    FairMQPrimaryGeneratorDevice* mqDevice = new FairMQPrimaryGeneratorDevice();
    LOG(INFO) << "Going to generate " << config.GetValue<int64_t>("nof-events") << " events.";
    mqDevice->SetChunkSize(config.GetValue<int64_t>("chunk-size"));
    mqDevice->RunInPushMode(true);
    if (config.GetValue<std::string>("running-mode") == "rr") {
        LOG(INFO) << "Going to reply with data.";
        mqDevice->RunInPushMode(false);
    } else {
        LOG(INFO) << "Going to push data.";
    }

    mqDevice->SetNofEvents(config.GetValue<int64_t>("nof-events"));
    mqDevice->SetGenerator(primGen);

    return mqDevice;
}
