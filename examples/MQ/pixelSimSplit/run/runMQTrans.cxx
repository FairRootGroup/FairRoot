/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// MQRunSim
#include "FairCave.h"
#include "FairMQTransportDevice.h"
#include "FairModule.h"
#include "FairOnlineSink.h"
#include "FairParAsciiFileIo.h"
#include "FairRunFairMQDevice.h"
#include "PixelDigitize.h"

#include <TObjArray.h>
#include <TRandom.h>
#include <TString.h>
#include <TSystem.h>
#include <cstdlib>
#include <string>
#include <vector>

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("random-seed",         bpo::value<int64_t>()->default_value(0),                   "Random seed number")
        ("transport-name",      bpo::value<std::string>()->default_value("TGeant3"),       "Transport name")
        ("fairroot-config-dir", bpo::value<std::string>()->default_value(""),              "FairRoot config dir")
        ("param-channel-name",  bpo::value<std::string>()->default_value("updateChannel"), "Parameter update channel name")
        ("running-mode",        bpo::value<std::string>()->default_value("pp"),            "pp to pull, rr to request")
        ("detector-library",    bpo::value<std::vector<std::string>>(),                    "detector library")
        ("run-digi-tasks",      bpo::value<bool>()->default_value(false),                  "Run digi tasks");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    gRandom->SetSeed(config.GetValue<int64_t>("random-seed"));

    TString dir = getenv("VMCWORKDIR");
    TString tutdir = dir + "/MQ/pixelDetector";

    TString tut_geomdir = dir + "/common/geometry";
    gSystem->Setenv("GEOMPATH", tut_geomdir.Data());

    TString tut_configdir = config.GetValue<std::string>("fairroot-config-dir");
    if (tut_configdir.Length() < 1)
        tut_configdir = dir + "/common/gconfig";
    gSystem->Setenv("CONFIG_DIR", tut_configdir.Data());

    auto run = std::make_unique<FairMQTransportDevice>();
    run->RunInPullMode(true);
    if (config.GetValue<std::string>("running-mode") == "rr") {
        LOG(info) << "Going to request data.";
        run->RunInPullMode(false);
    } else {
        LOG(info) << "Going to pull data.";
    }

    //  TString outputfilename = Form("outputfile_%d.root",(int)(getpid()));
    //  FairRootFileSink* sink = new FairRootFileSink(outputfilename);
    auto sink = std::make_unique<FairOnlineSink>();
    sink->SetMQRunDevice(run.get());
    run->SetSink(std::move(sink));

    run->SetParamUpdateChannelName(config.GetValue<std::string>("param-channel-name"));

    run->SetTransportName(config.GetValue<std::string>("transport-name"));
    run->SetMaterials("media.geo");

    TObjArray* detArray = new TObjArray();
    FairModule* cave = new FairCave("CAVE");
    cave->SetGeometryFileName("cave_vacuum.geo");
    detArray->Add(cave);
    // Pixel*  det = new Pixel("PixelDetector", kTRUE);
    // det->SetGeometryFileName("pixel.geo");
    // detArray->Add(det);
    run->SetDetectorArray(detArray);

    run->SetStoreTraj(false);

    if ((config.GetValue<bool>("run-digi-tasks")) == true) {
        // Attach tasks if needed
        TString digParFile = tutdir + "/param/pixel_digi.par";
        FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo();
        parIo1->open(digParFile.Data(), "in");
        run->SetFirstParameter(parIo1);

        TObjArray* taskArray = new TObjArray();
        PixelDigitize* digiTask = new PixelDigitize();
        taskArray->Add(digiTask);
        run->SetTaskArray(taskArray);
    }

    return run;
}
