/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairRunOnline source file                   -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#include "FairRunOnline.h"

#include "FairRootManager.h"
#include "FairTask.h"
#include "FairBaseParSet.h"
#include "FairEventHeader.h"
#include "FairFieldFactory.h"
#include "FairRuntimeDb.h"
#include "FairRunIdGenerator.h"
#include "FairLogger.h"
#include "FairFileHeader.h"
#include "FairParIo.h"
#include "FairField.h"
#include "FairSource.h"

#include "FairGeoInterface.h"
#include "FairGeoLoader.h"
#include "FairGeoParSet.h"

#include "TROOT.h"
#include "TSystem.h"
#include "TTree.h"
#include "TSeqCollection.h"
#include "TGeoManager.h"
#include "TKey.h"
#include "TF1.h"
#include "TSystem.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"

#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;



//_____________________________________________________________________________
FairRunOnline* FairRunOnline::fgRinstance = 0;



//_____________________________________________________________________________
FairRunOnline* FairRunOnline::Instance()
{
  return fgRinstance;
}


FairRunOnline::FairRunOnline()
  :FairRun(),
   fAutomaticFinish(kTRUE),
   fIsInitialized(kFALSE),
   fEvtHeader(0),
   fStatic(kFALSE),
   fField(0),
   fSource(NULL),
   fFolder(new TFolder("HISTO", "HISTO")),
   fGenerateHtml(kFALSE),
   fHistFileName(""),
   fRefreshRate(1000)
{
  fgRinstance = this;
  fAna = kTRUE;
  LOG(INFO)<<Form("FairRunOnline constructed at 0x%08x",this)<<FairLogger::endl;
}
//_____________________________________________________________________________
FairRunOnline::FairRunOnline(FairSource* source)
  :FairRun(),
   fAutomaticFinish(kTRUE),
   fIsInitialized(kFALSE),
   fEvtHeader(0),
   fStatic(kFALSE),
   fField(0),
   fSource(source),
   fFolder(new TFolder("HISTO", "HISTO")),
   fGenerateHtml(kFALSE),
   fHistFileName(""),
   fRefreshRate(1000)
{
  fgRinstance = this;
  fAna = kTRUE;
  LOG(INFO)<<Form("FairRunOnline (source) constructed at 0x%08x",this)<<FairLogger::endl;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRunOnline::~FairRunOnline()
{
  //  delete fFriendFileList;
  if (fField) {
    delete fField;
  }
  if (gGeoManager) {
    delete gGeoManager;
  }
  if(fSource) {
    delete fSource;
  }
  if(fFolder) {
    fFolder->Delete();
    delete fFolder;
  }
}
//_____________________________________________________________________________



Bool_t gIsInterrupted;

void handler_ctrlc(int s)
{
  gIsInterrupted = kTRUE;
}



//_____________________________________________________________________________
void FairRunOnline::Init()
{
  LOG(INFO)<<"FairRunOnline::Init"<<FairLogger::endl;
  if (fIsInitialized) {
    fLogger->Fatal(MESSAGE_ORIGIN,"Error Init is already called before!");
    exit(-1);
  } else {
    fIsInitialized = kTRUE;
  }

  //  FairGeoLoader* loader = new FairGeoLoader("TGeo", "Geo Loader");
  //  FairGeoInterface* GeoInterFace = loader->getGeoInterface();
  //  GeoInterFace->SetNoOfSets(ListOfModules->GetEntries());
  //  GeoInterFace->setMediaFile(MatFname.Data());
  //  GeoInterFace->readMedia();

  // Add a Generated run ID to the FairRunTimeDb
  FairRunIdGenerator genid;
  fRunId = genid.generateId();
  fRtdb->addRun(fRunId);
  fFileHeader->SetRunId(fRunId);
  FairBaseParSet* par = dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));
  FairGeoParSet* geopar = dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));
  geopar->SetGeometry(gGeoManager);
  if(fField) {
    fField->Init();
    fField->FillParContainer();
  }
  TList* containerList = fRtdb->getListOfContainers();
  TIter next(containerList);
  FairParSet* cont;
  TObjArray* ContList= new TObjArray();
  while ((cont=dynamic_cast<FairParSet*>(next()))) {
    ContList->Add(new TObjString(cont->GetName()));
  }
  par->SetContListStr(ContList);
  par->setChanged();
  par->setInputVersion(fRunId,1);
  geopar->setChanged();
  geopar->setInputVersion(fRunId,1);

  fRootManager->WriteFileHeader(fFileHeader);

  fTask->SetParTask();
  fRtdb->initContainers(fRunId);

  //  InitContainers();
  // --- Get event header from Run
  fEvtHeader = dynamic_cast<FairEventHeader*> (FairRunOnline::Instance()->GetEventHeader());
  if ( ! fEvtHeader ) {
    LOG(FATAL) << "FairRunOnline::InitContainers:No event header in run!" << FairLogger::endl;
    return;
  }
  LOG(INFO) << "FairRunOnline::InitContainers: event header at " << fEvtHeader << FairLogger::endl;
  fRootManager->Register("EventHeader.", "Event", fEvtHeader, kTRUE);

  // Initialize the source
  if(! fSource->Init()) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Init of the source failed...");
    exit(-1);
  }

  // Now call the User initialize for Tasks
  fTask->InitTask();

  // create the output tree after tasks initialisation
  fOutFile->cd();
  TTree* outTree =new TTree("cbmsim", "/cbmout", 99);
  fRootManager->TruncateBranchNames(outTree, "cbmout");
  fRootManager->SetOutTree(outTree);
  fRootManager->WriteFolder();
}
//_____________________________________________________________________________


//_____________________________________________________________________________
void FairRunOnline::InitContainers()
{

  fRtdb = GetRuntimeDb();
  FairBaseParSet* par=(FairBaseParSet*)
                      (fRtdb->getContainer("FairBaseParSet"));
  LOG(INFO)<<Form("FairRunOnline::InitContainers: par = 0x%08x",par)<<FairLogger::endl;
  if (NULL == par)
    LOG(WARNING)<<"FairRunOnline::InitContainers: no  'FairBaseParSet' container !"<<FairLogger::endl;

  if (par) {
    fEvtHeader = (FairEventHeader*)fRootManager->GetObjectFromInTree("EventHeader.");

    fRunId = fEvtHeader->GetRunId();

    //Copy the Event Header Info to Output
    fEvtHeader->Register();

    // Init the containers in Tasks
    fRtdb->initContainers(fRunId);
    fTask->ReInitTask();
    //    fTask->SetParTask();
    fRtdb->initContainers( fRunId );
    //     if (gGeoManager==0) {
    //       par->GetGeometry();
    //     }
  } else
  {
  // --- Get event header from Run
  fEvtHeader = dynamic_cast<FairEventHeader*> (FairRunOnline::Instance()->GetEventHeader());
  if ( ! fEvtHeader ) {
    LOG(FATAL) << "FairRunOnline::InitContainers:No event header in run!" << FairLogger::endl;
    return;
  }
  LOG(INFO) << "FairRunOnline::InitContainers: event header at " << fEvtHeader << FairLogger::endl;
  fRootManager->Register("EventHeader.", "Event", fEvtHeader, kTRUE);
  }
}
//_____________________________________________________________________________
Int_t FairRunOnline::EventLoop()
{
  gSystem->IgnoreInterrupt();
  gIsInterrupted = kFALSE;
  signal(SIGINT, handler_ctrlc);

  fSource->Reset();
  Int_t status = fSource->ReadEvent();
  if(1 == status || 2 == status) {
    return status;
  }


  Int_t tmpId = GetEventHeader()->GetRunId();
  
  if ( tmpId != fRunId ) {
//    LOG(INFO) << "Call Reinit due to changed RunID" << FairLogger::endl;
//    fRunId = tmpId;
//    Reinit( fRunId );
//    fTask->ReInitTask();
  }


  fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());
  fTask->ExecuteTask("");
  fRootManager->Fill();
  fRootManager->DeleteOldWriteoutBufferData();
  fTask->FinishEvent();
  fNevents += 1;
  if(fGenerateHtml && 0 == (fNevents%fRefreshRate))
  {
    WriteObjects();
    GenerateHtml();
  }
    
  if(gIsInterrupted)
  {
    return 1;
  }

  return 0;
}


//_____________________________________________________________________________
void FairRunOnline::Run(Int_t nev, Int_t dummy)
{
  fOutFile->cd();
    
  fNevents = 0;

  Int_t status;
  if(nev < 0) {
    while(kTRUE) {
      status = EventLoop();
      if(1 == status) {
        break;
      } else if(2 == status) {
        continue;
      }
      if(gIsInterrupted)
      {
        break;
      }
    }
  } else {
    for (Int_t i = 0; i < nev; i++) {
      status = EventLoop();
      if(1 == status) {
        break;
      } else if(2 == status) {
        i -= 1;
        continue;
      }
      if(gIsInterrupted)
      {
        break;
      }
    }
  }
 
  fRootManager->StoreAllWriteoutBufferData();
  if (fAutomaticFinish) {
    Finish();
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunOnline::Finish()
{
  fTask->FinishTask();
  fRootManager->LastFill();
  fRootManager->Write();

  fSource->Close();

  if(fGenerateHtml) {
    WriteObjects();
    GenerateHtml();
  }
}

//_____________________________________________________________________________
void FairRunOnline::SetGenerateHtml(Bool_t flag, const char* histFileName, Int_t refreshRate)
{
  fGenerateHtml = flag;
  fHistFileName = TString(histFileName);
  fRefreshRate = refreshRate;
}
//_____________________________________________________________________________



//_____________________________________________________________________________
void FairRunOnline::GenerateHtml()
{
  TString htmlName = TString(fHistFileName);
  TString rootName = TString(fHistFileName);
  Int_t last = htmlName.Last('/');
  if(-1 != last) {
    rootName.Remove(0, last+1);
  }
  htmlName.Remove(htmlName.Length()-4, htmlName.Length()-1);
  htmlName += TString("html");

  ofstream* ofile = new ofstream(htmlName);
  (*ofile) << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl
           << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"" << endl
           << "\"http://www.w3.org/TR/xhtml1/DTD/xhtml1transitional.dtd\">" << endl
           << "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">" << endl
           << "<head>" << endl
           << "<title>Read a ROOT file in Javascript (Demonstration)</title>" << endl
           << "<meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\" />" << endl
           << "<link rel=\"stylesheet\" type=\"text/css\" href=\"http://root.cern.ch/js/style/JSRootInterface.css\" />" << endl
           << "<script type=\"text/javascript\" src=\"http://root.cern.ch/js/scripts/JSRootInterface.js\"></script>" << endl
           << "</head>" << endl
           << "<body onload=\"BuildSimpleGUI()\">" << endl
           << "<div id=\"simpleGUI\"" << endl
           << "files=\"" << rootName << "\"></div>" << endl
           << "</body>" << endl
           << "</html>" << endl;
  ofile->close();
  delete ofile;
}
//_____________________________________________________________________________



//_____________________________________________________________________________
void FairRunOnline::WriteObjects()
{
  TDirectory *oldDir = gDirectory;

  TFile *file = new TFile(fHistFileName, "RECREATE");

  // Create iterator with the folder content
  TIter iter(fFolder->GetListOfFolders());

  // Pointer to an object
  TObject* object;

  // Class name of the object
  TString className;

  // Histogram pointers
  TH1* h1;
  TH2* h2;

  // Loop over objects in the folder
  while((object = iter())) {

    // Get class name
    className = object->ClassName();

    // Recognise objects
    if(0 == className.CompareTo("TH1F")) {
      // If a histogram - plot it and save canvas
      h1 = (TH1F*) object;
      h1->Write();
    } else if(0 == className.CompareTo("TH2F")) {
      // If a histogram - plot it and save canvas
      h2 = (TH2F*) object;
      h2->Write();
    } else if(0 == className.CompareTo("TH1D")) {
      // If a histogram - plot it and save canvas
      h1 = (TH1D*) object;
      h1->Write();
    } else if(0 == className.CompareTo("TH2D")) {
      // If a histogram - plot it and save canvas
      h2 = (TH2D*) object;
      h2->Write();
    }
  }

  file->Close();

  oldDir->cd();
}
//_____________________________________________________________________________



//_____________________________________________________________________________
void FairRunOnline::Reinit(UInt_t runId)
{
  // reinit procedure
  fRtdb->initContainers( runId );
}
//_____________________________________________________________________________



//_____________________________________________________________________________
void  FairRunOnline::SetContainerStatic(Bool_t tempBool)
{
  fStatic=tempBool;
  if ( fStatic ) {
    fLogger->Info(MESSAGE_ORIGIN, "Parameter Cont. initialisation is static");
  } else {
    fLogger->Info(MESSAGE_ORIGIN, "Parameter Cont. initialisation is NOT static");
  }
}
//_____________________________________________________________________________



//_____________________________________________________________________________
void FairRunOnline::AddObject(TObject* object)
{
  if(! fFolder) {
    return;
  }
  fFolder->Add(object);
}
//_____________________________________________________________________________



ClassImp(FairRunOnline)
