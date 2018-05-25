#include "runFairMQDevice.h"

// MQRunSim
#include "FairMQSimDevice.h"
#include "FairRuntimeDb.h"
#include "FairModule.h"
#include "FairCave.h"
#include "FairPrimaryGenerator.h"
#include "FairBoxGenerator.h"
#include "FairParRootFileIo.h"
#include "FairParAsciiFileIo.h"

#include "Pixel.h"
#include "PixelDigitize.h"

#include "FairOnlineSink.h"
//#include "FairRootFileSink.h"

#include "TRandom.h"
#include "TRint.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TVirtualMC.h"
#include "TVirtualMCApplication.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
  options.add_options()
    ("random-seed",          bpo::value<int64_t>    ()->default_value(0)              , "Random seed number")
    ("transport-name",       bpo::value<std::string>()->default_value("TGeant3")      , "Transport name")
    ("nof-events",           bpo::value<int64_t>    ()->required()                    , "Number of events to simulate")
    ("fairroot-config-dir",  bpo::value<std::string>()->default_value("")             , "FairRoot config dir")
    ("param-channel-name",   bpo::value<std::string>()->default_value("updateChannel"), "Parameter update channel name")
    ;
}

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
  gRandom->SetSeed(config.GetValue<int64_t> ("random-seed"));

  TString dir = getenv("VMCWORKDIR");
  TString tutdir = dir + "/MQ/pixelDetector";

  TString tut_geomdir = dir + "/common/geometry";
  gSystem->Setenv("GEOMPATH",tut_geomdir.Data());

  TString tut_configdir = config.GetValue<std::string>("fairroot-config-dir");
  if ( tut_configdir.Length() < 1 ) 
    tut_configdir = dir + "/common/gconfig";
  gSystem->Setenv("CONFIG_DIR",tut_configdir.Data());

  FairMQSimDevice* run = new FairMQSimDevice();

  //  TString outputfilename = Form("outputfile_%d.root",(int)(getpid()));
  //  FairRootFileSink* sink = new FairRootFileSink(outputfilename);
  FairOnlineSink* sink = new FairOnlineSink();
  sink->SetMQSimDevice(run);
  run->SetSink(sink);

  run->SetParamUpdateChannelName(config.GetValue<std::string>("param-channel-name"));

  run->SetNofEvents       (config.GetValue<int64_t>    ("nof-events"));
  run->SetTransportName   (config.GetValue<std::string>("transport-name"));
  run->SetMaterials       ("media.geo");

  TObjArray* detArray = new TObjArray();
  FairModule* cave= new FairCave("CAVE");
  cave->SetGeometryFileName("cave_vacuum.geo");
  detArray->Add(cave);
  Pixel*  det = new Pixel("PixelDetector", kTRUE);
  det->SetGeometryFileName("pixel.geo");
  detArray->Add(det);
  run->SetDetectorArray   (detArray);

  TString partName[] = {"pions","eplus","proton"};
  Int_t   partPdgC[] = {    211,     11,    2212};
  Int_t chosenPart  = 0;

  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
  FairBoxGenerator* boxGen = new FairBoxGenerator(partPdgC[chosenPart], 5);
  boxGen->SetPRange(1,2);
  boxGen->SetThetaRange(0,40);
  boxGen->SetPhiRange(0,360);
  primGen->AddGenerator(boxGen);
  run->SetGenerator       (primGen);

  run->SetStoreTraj       (false);

  // ---------------------------------------------------
  if ( 1==0 )
    {
      // try to run digi task in the simulation device
      TString digParFile = tutdir + "/param/pixel_digi.par";
      FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo();
      parIo1->open(digParFile.Data(),"in");
      run->SetFirstParameter(parIo1);

      TObjArray* taskArray = new TObjArray();
      PixelDigitize* digiTask = new PixelDigitize();
      taskArray->Add(digiTask);
      run->SetTaskArray(taskArray);
    }
  // ---------------------------------------------------

  return run;
}
