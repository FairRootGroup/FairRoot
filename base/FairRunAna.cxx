// -------------------------------------------------------------------------
// -----                   FairRunAna source file                      -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#include "FairRunAna.h"

#include "FairRootManager.h"
#include "FairTask.h"
#include "FairBaseParSet.h"
#include "FairEventHeader.h"
#include "FairFieldFactory.h"
#include "FairRuntimeDb.h"
#include "TROOT.h"
#include "TTree.h"
#include "FairTrajFilter.h"
#include "TSeqCollection.h"
#include "TGeoManager.h"
#include "TKey.h"
#include "FairRunIdGenerator.h"

#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;


//_____________________________________________________________________________
FairRunAna * FairRunAna::fgRinstance= 0;
//_____________________________________________________________________________
FairRunAna * FairRunAna::Instance(){

        return fgRinstance;
}
//_____________________________________________________________________________
FairRunAna::FairRunAna() 
  :FairRun(),
   fFriendFileList(new TObjArray()),
   fMergedFileList(new TObjArray()),
   fInputFile(0),
   fInputGeoFile(0),
   fCurrentFileName (""),
   fWildcard(""),
   fChainList(0),
   fcurrent(0),
   fInputFileStruct(),
   fLoadGeo( kFALSE),
   fEvtHeader(0),
   fRtdb(0),
   fRunId(0),
   fStatic(kFALSE),
   fField(0)
{

   fgRinstance=this;
   fAna=kTRUE;
}
//_____________________________________________________________________________

FairRunAna::~FairRunAna()
{
   delete fFriendFileList;
   delete fMergedFileList;
}

//_____________________________________________________________________________

void  FairRunAna::SetGeomFile(const char *GeoFileName)
{
   TFile *CurrentFile=gFile;
   fInputGeoFile= new TFile(GeoFileName);
   if (fInputGeoFile->IsZombie()) {
       cout << "-E- FairRunAna: Error opening Geometry Input file" << endl;
       fInputGeoFile=0;
   }
    
   cout << "-I- FairRunAna: Opening Geometry input file: " << GeoFileName << endl;
   gFile=CurrentFile;
}

//_____________________________________________________________________________

void FairRunAna::Init() {
   if(fInputFile ){
      if ("" == fWildcard) {
         fRootManager->OpenInFile(fInputFile, kTRUE);
      }else{
         fRootManager->OpenInFile(fInputFile);
         fRootManager->SetWildcard(fWildcard);
      }
      // chain mechanism
      std::list<TString>::const_iterator iter;
      for(iter = fChainList.begin(); iter != fChainList.end(); iter++) {
         fRootManager->AddFile( (*iter) );
      }
      cout << endl
      << "-I- FairRunAna::Init : " << endl
      << fInputFile->GetName() << "  is connected with:";
         list<TString>* friendList =
         fInputFileStruct[TString(fInputFile->GetName())];
      if(NULL != friendList) {
         list<TString>::iterator iter1;
         for(iter1 = friendList->begin();
         iter1 != friendList->end(); iter1++) {
            cout << "   " << (*iter1);
            fRootManager->AddFriend(new TFile(*iter1));
         }
      }
      cout << endl << endl;
      // merge case
      Int_t i = 0;
    /*  for ( i=0;i<fMergedFileList->GetEntriesFast();i++) { 
         fRootManager->AddAndMerge((TFile*) fMergedFileList->At(i));
      }
    */ 
      //Load geometry
	  if(fLoadGeo) {
            if(fInputGeoFile!=0){  //First check if the user has a separate Geo file!
               TIter next(fInputGeoFile->GetListOfKeys());
               TKey *key;
               while ((key = (TKey*)next())) {
                 if (strcmp(key->GetClassName(),"TGeoManager") != 0) continue;
                 gGeoManager = (TGeoManager*)key->ReadObj();
                 break;
               }
            }else{ //try the input file 
              fInputFile->Get("FAIRGeom");
            }
          }
	  //check that the geometry was loaded if not try all connected files!
	  if(gGeoManager==0) {
		 cout << "-I-  Geometry was not found in the input file we will look in the friends if any!" << endl;
		 TFile *currentfile= gFile;
		 TFile *nextfile=0;
		 TSeqCollection *fileList=gROOT->GetListOfFiles();
		 for (Int_t k=0; k<fileList->GetEntries(); k++){
			nextfile=(TFile *)fileList->At(k);
			if(nextfile) nextfile->Get("FAIRGeom");
			if(gGeoManager) break;
		 }	
		 gFile=currentfile;	
	  }
   }else{ //  if(fInputFile )
        // NO input file but there is a geometry file
       if(fLoadGeo) {
          if(fInputGeoFile!=0){  //First check if the user has a separate Geo file!
             TIter next(fInputGeoFile->GetListOfKeys());
             TKey *key;
             while ((key = (TKey*)next())) {
                if (strcmp(key->GetClassName(),"TGeoManager") != 0) continue;
                gGeoManager = (TGeoManager*)key->ReadObj();
                break;
            }
         }
       }
   }
  //Init the Chain ptr
   fcurrent = fChainList.begin();
   TFile *Output = fRootManager->OpenOutFile(Outfname);
   gROOT->GetListOfBrowsables()->Add(fTask);
   // Init the RTDB containers
   fRtdb= GetRuntimeDb();
   FairBaseParSet* par=(FairBaseParSet*)
            (fRtdb->getContainer("FairBaseParSet"));
  
	
   // Assure that basic info is there for the run
   if(par && fInputFile){
      fRootManager->ReadEvent(0);
      fEvtHeader = (FairEventHeader*)
      fRootManager->ActivateBranch("EventHeader.");
      //Copy the Event Header Info to Output
      fRootManager->Register("EventHeader.","EvtHeader",fEvtHeader, kTRUE);
      fRunId = fEvtHeader->GetRunId();
      // Init the containers in Tasks
//	   cout << "Run Id for this run : " << fRunId << endl;
      fRtdb->initContainers(fRunId);   
      fTask->SetParTask();
      fRtdb->initContainers( fRunId );
	  if(gGeoManager==0)par->GetGeometry(); 
	//  fRootManager->SetBranchNameList(par->GetBranchNameList());
   }else{
   
      FairEventHeader *evt = new FairEventHeader();
      fRootManager->Register("EventHeader.","EvtHeader",evt, kTRUE);
      FairRunIdGenerator genid;
      fRunId = genid.generateId();
      fRtdb->addRun(fRunId);
      evt->SetRunId( fRunId);
      fTask->SetParTask();
      fRtdb->initContainers( fRunId );
      
   }
	FairFieldFactory *fieldfact= FairFieldFactory::Instance();
	if(fieldfact)fieldfact->SetParm();
	
	
		
	fRtdb->initContainers(fRunId);	
	
	
   // create a field 
   // <DB>
   // Add test for external FairField settings
    if(fieldfact && !fField) fField= fieldfact->createFairField();
   // Now call the User initialize for Tasks
   fTask->InitTask();
  // if the vis manager is available then initialize it!
   FairTrajFilter *fTrajFilter = FairTrajFilter::Instance();
   if(fTrajFilter) fTrajFilter->Init();
   // create the output tree after tasks initialisation
   Output->cd();
   TTree *outTree =new TTree("cbmsim", "/cbmout", 99);
   fRootManager->TranicateBranchNames(outTree, "cbmout");
   fRootManager->SetOutTree(outTree);
   fRootManager->WriteFolder();

  // gDirectory->cd(0);
  // fTask->Write("TaskList");
 //  if(fInputFile==0 && gGeoManager)fRootManager->WriteGeometry();
}


void FairRunAna::Run(Int_t Ev_start, Int_t Ev_end)
{
  UInt_t tmpId =0;
  if (fInputFile==0){ 
     DummyRun(Ev_start,Ev_end);
     return;
  }
  if(Ev_end==0){ 
     if (Ev_start==0){
        Ev_end=Int_t((fRootManager->GetInChain())->GetEntries());
	 }else {
       Ev_end =  Ev_start;  
       if ( Ev_end > ((fRootManager->GetInChain())->GetEntries()) ){
           Ev_end = (Int_t) (fRootManager->GetInChain())->GetEntries();
       }
       Ev_start=0;
     }
  }else{
	  Int_t fileEnd=(fRootManager->GetInChain())->GetEntries();
	  if(Ev_end > fileEnd){
		  cout << "-------------------Warning---------------------------" << endl;
		  cout << " -W FairRunAna : File has less events than requested!!" << endl;
		  cout << " File contains : " << fileEnd  << " Events" << endl;
		  cout << " Requested number of events = " <<  Ev_end <<  " Events"<< endl;
		  cout << " The number of events is set to " << fileEnd << " Events"<< endl;
		  cout << "-----------------------------------------------------" << endl;
	      Ev_end = fileEnd;
	  }
	  
  }
 
  for (int i=Ev_start; i< Ev_end;i++){
     fRootManager->ReadEvent(i);
     tmpId = fEvtHeader->GetRunId();
     if ( tmpId != fRunId ) {
          fRunId = tmpId;
          if( !fStatic ) {
          cout << " -I FairRunAna : reinitialization done for RunID: "
               << fRunId << endl;

          Reinit( fRunId );
          fTask->ReInitTask();
          }
     }

     fTask->ExecuteTask("");
     fRootManager->Fill();
     fTask->FinishEvent();
	 
	 if(NULL !=  FairTrajFilter::Instance())  FairTrajFilter::Instance()->Reset();
     
  }
  fTask->FinishTask();
  fRootManager->Write();

}
//_____________________________________________________________________________
void FairRunAna::Run(Long64_t entry)
{
   UInt_t tmpId =0;
   fRootManager->ReadEvent(entry);
   tmpId = fEvtHeader->GetRunId();
   if ( tmpId != fRunId ) {
      fRunId = tmpId;
      if( !fStatic ) {
         cout << " -I FairRunAna : reinitialization done for RunID: "
              << fRunId << endl;

         Reinit( fRunId );
         fTask->ReInitTask();
        }
   }
   fTask->ExecuteTask("");
   fRootManager->Fill();
   fTask->FinishTask();
   fRootManager->Write();
}
//_____________________________________________________________________________
void FairRunAna::DummyRun(Int_t Ev_start, Int_t Ev_end)
{
  
   /** This methode is just for testing, if you are not sure about what you do, don't use it */
   for (int i=Ev_start; i< Ev_end;i++){
      fTask->ExecuteTask("");
      fRootManager->Fill();
   }
   fTask->FinishTask();
   fRootManager->Write();

 }
//_____________________________________________________________________________
/*
void FairRunAna::AddAndMerge (const char *Name)
{
  TFile *fFile = new TFile(Name);
  if (fFile->IsZombie()) {
    Fatal("FairRunAna::AddAndMerge","Error opening output file");
  }else{
    AddAndMerge(fFile);
  }

}
*/
//_____________________________________________________________________________
TFile *FairRunAna::SetInputFile(TString name)
{
   fInputFile= new TFile(name);
   if (fInputFile->IsZombie()) {
            cout << "-E- FairRunAna: Error opening Input file" << endl;
             exit(-1);
         }else{
   }
        fCurrentFileName = name;
        cout << "-I- FairRunAna: Opening Input file: " << fCurrentFileName << endl;
   return fInputFile;
}


//_____________________________________________________________________________
void FairRunAna::SetInputFile(TFile *f)
{
  if (f->IsZombie()) {
      cout << "-E- FairRunAna: Error opening Input file" << endl;
    exit(-1);
  }else{
    fInputFile=f;
  }
   fCurrentFileName = TString( f->GetName());
}

//_____________________________________________________________________________
void FairRunAna::AddFriend (TString Name)
{
  cout << "-I- FairRunAna Input file: " << fCurrentFileName <<
          " is connected to friend: " << Name << endl;
  if ( fInputFileStruct[fCurrentFileName]){
      fInputFileStruct[fCurrentFileName]->push_back(Name);
  }else {
      fInputFileStruct[fCurrentFileName] = new list<TString>;
      fInputFileStruct[fCurrentFileName]->push_back(Name);
  }
}
//_____________________________________________________________________________
void FairRunAna::DumpfInputFileStruct() {
  // to be finished ...   
}
//_____________________________________________________________________________
void FairRunAna::Reinit(UInt_t runId) {
    // reinit procedure
    fRtdb->initContainers( runId );
}
//_____________________________________________________________________________

void FairRunAna::AddFile(TString name){
    cout << "-I- FairRunAna Adding input file: " << name << endl;
    fChainList.push_back(name);
    fCurrentFileName = name;
}
//_____________________________________________________________________________
TString FairRunAna::GetNextFileName(){
 TString name = *fcurrent++;
 return name;
}
//_____________________________________________________________________________

ClassImp(FairRunAna)


