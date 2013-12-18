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
#include "TTree.h"
#include "TSeqCollection.h"
#include "TGeoManager.h"
#include "TKey.h"
#include "TF1.h"
#include "TSystem.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"

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



//_____________________________________________________________________________
FairRunOnline::FairRunOnline(FairSource* source)
  :FairRun(),
   fIsInitialized(kFALSE),
   fEvtHeader(0),
   fStatic(kFALSE),
   fField(0),
   fSource(source),
   fFolder(new TFolder("HISTO", "HISTO")),
   fGenerateHtml(kFALSE)
{
  fgRinstance = this;
  fAna = kTRUE;
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



//_____________________________________________________________________________
void FairRunOnline::Init()
{
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

  // Initialize the source
  fSource->Init();

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
  }
}
//_____________________________________________________________________________



//_____________________________________________________________________________
void FairRunOnline::Run(Int_t nev, Int_t dummy)
{
  fOutFile->cd();

  Int_t status;
  if(nev < 0) {
    while(kTRUE) {
      fSource->Reset();
      status = fSource->ReadEvent();
      if(1 == status) {
        break;
      }
      fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());
      fTask->ExecuteTask("");
      fRootManager->Fill();
      fRootManager->DeleteOldWriteoutBufferData();
      fTask->FinishEvent();
    }
  } else {
    for (Int_t i = 0; i < nev; i++) {
      fSource->Reset();
      status = fSource->ReadEvent();
      if(1 == status) {
        break;
      }
      fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());
      fTask->ExecuteTask("");
      fRootManager->Fill();
      fRootManager->DeleteOldWriteoutBufferData();
      fTask->FinishEvent();
    }
  }

  fRootManager->StoreAllWriteoutBufferData();
  fTask->FinishTask();
  fRootManager->LastFill();
  fRootManager->Write();

  fSource->Close();

  WriteObjects();

  if(fGenerateHtml) {
    GenerateHtml();
  }
}
//_____________________________________________________________________________



//_____________________________________________________________________________
void FairRunOnline::SetGenerateHtml(Bool_t flag)
{
  fGenerateHtml = flag;
}
//_____________________________________________________________________________



//_____________________________________________________________________________
void FairRunOnline::GenerateHtml()
{
  TString htmlName = TString(fOutname);
  TString rootName = TString(fOutname);
  Int_t last = htmlName.Last('/');
  if(-1 == last) {
    htmlName = "index.html";
  } else {
    htmlName.Remove(last+1, htmlName.Length()-last-1);
    htmlName += TString("index.html");
    rootName.Remove(0, last+1);
  }

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
