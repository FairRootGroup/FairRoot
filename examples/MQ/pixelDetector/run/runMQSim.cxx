/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairBoxGenerator.h"
#include "FairCave.h"
#include "FairMQSimDevice.h"
#include "FairModule.h"
#include "FairOnlineSink.h"
#include "FairParAsciiFileIo.h"
#include "FairPrimaryGenerator.h"
#include "FairRunFairMQDevice.h"
#include "Pixel.h"
#include "PixelDigitize.h"

#include <Rtypes.h>
#include <TObjArray.h>
#include <TRandom.h>
#include <TString.h>
#include <TSystem.h>
#include <cstdint>
#include <cstdlib>
#include <stdexcept>
#include <string>

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("random-seed",         bpo::value<int64_t>    ()->default_value(0),               "Random seed number")
        ("transport-name",      bpo::value<std::string>()->default_value("TGeant3"),       "Transport name")
        ("nof-events",          bpo::value<int64_t>    ()->required(),                     "Number of events to simulate")
        ("fairroot-config-dir", bpo::value<std::string>()->default_value(""),              "FairRoot config dir")
        ("param-channel-name",  bpo::value<std::string>()->default_value("updateChannel"), "Parameter update channel name")
        ("run-digi-tasks",      bpo::value<bool>       ()->default_value(false),           "Run digi tasks")
        // clang-format on
        ;
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    gRandom->SetSeed(config.GetValue<int64_t>("random-seed"));

    char* cdir = getenv("VMCWORKDIR");

    if (cdir == nullptr) {
        throw std::runtime_error("VMCWORKDIR not initialized");
    }

    std::string dir = cdir;
    std::string tutdir = dir + "/MQ/pixelDetector";

    std::string tutGeomDir = dir + "/common/geometry";
    gSystem->Setenv("GEOMPATH", tutGeomDir.c_str());

    std::string tutConfigDir = config.GetValue<std::string>("fairroot-config-dir");
    if (tutConfigDir.empty()) {
        tutConfigDir = dir + "/common/gconfig";
    }
    gSystem->Setenv("CONFIG_DIR", tutConfigDir.c_str());

    auto run = std::make_unique<FairMQSimDevice>();

    FairOnlineSink* sink = new FairOnlineSink();
    sink->SetMQRunDevice(run.get());
    run->SetSink(sink);

    run->SetParamUpdateChannelName(config.GetValue<std::string>("param-channel-name"));

    run->SetNofEvents(config.GetValue<int64_t>("nof-events"));
    run->SetTransportName(config.GetValue<std::string>("transport-name"));
    run->SetMaterials("media.geo");

    TObjArray* detArray = new TObjArray();
    FairModule* cave = new FairCave("CAVE");
    cave->SetGeometryFileName("cave_vacuum.geo");
    detArray->Add(cave);
    Pixel* det = new Pixel("PixelDetector", kTRUE);
    det->SetGeometryFileName("pixel.geo");
    detArray->Add(det);
    run->SetDetectorArray(detArray);

    TString partName[] = {"pions", "eplus", "proton"};
    Int_t partPdgC[] = {211, 11, 2212};
    Int_t chosenPart = 0;

    FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
    FairBoxGenerator* boxGen = new FairBoxGenerator(partPdgC[chosenPart], 100);
    boxGen->SetPRange(1, 2);
    boxGen->SetThetaRange(0, 180);
    boxGen->SetPhiRange(0, 360);
    primGen->AddGenerator(boxGen);
    run->SetGenerator(primGen);

    run->SetStoreTraj(false);

    if (config.GetValue<bool>("run-digi-tasks")) {
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
