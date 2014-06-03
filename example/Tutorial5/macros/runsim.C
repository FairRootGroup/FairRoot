/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
{

  TString dir = getenv("VMCWORKDIR");
  TString tutdir = dir + "/Tutorial5";

  TString tut_geomdir = dir + "/geometry";
  gSystem->Setenv("GEOMPATH",tut_geomdir.Data());

  TString tut_configdir = dir + "/gconfig";
  gSystem->Setenv("CONFIG_DIR",tut_configdir.Data());

  FairRunSim* fRun = new FairRunSim();
  fRun->SetName("TGeant3");                      // Transport engine
  fRun->SetOutputFile("dummysim.root");          // Output file
  fRun->SetMaterials("media.geo");

  FairModule* Cave= new FairCave("CAVE");
  Cave->SetGeometryFileName("cave.geo");
  fRun->AddModule(Cave);

  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
  fRun->SetGenerator(primGen);

  FairRuntimeDb* rtdb=fRun->GetRuntimeDb();
  Bool_t kParameterMerged=kTRUE;
  FairParRootFileIo* output=new FairParRootFileIo(kParameterMerged);
  output->open("par.root","RECREATE");
  rtdb->setOutput(output);

  fRun->Init();
  fRun->Run(10);
  rtdb->saveOutput();

}

