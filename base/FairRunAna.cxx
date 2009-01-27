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
#include <iostream>
#include <list>
#include "TSeqCollection.h"
#include "TGeoManager.h"
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
   FriendFileList(new TObjArray()),
   MergedFileList(new TObjArray()),
   InputFile(0),
   fCurrentFileName (""),
   fWildcard(""),
   fChainList(0),
   current(0),
   fInputFileStruct(),
   LoadGeo( kFALSE),
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
   delete FriendFileList;
   delete MergedFileList;
}
//_____________________________________________________________________________
void FairRunAna::Init() {
   if(InputFile ){
      if ("" == fWildcard) {
         fRootManager->OpenInFile(InputFile, kTRUE);
      }else{
         fRootManager->OpenInFile(InputFile);
         fRootManager->SetWildcard(fWildcard);
      }
      // chain mechanism
      std::list<TString>::const_iterator iter;
      for(iter = fChainList.begin(); iter != fChainList.end(); iter++) {
         fRootManager->AddFile( (*iter) );
      }
      cout << endl
      << "-I- FairRunAna::Init : " << endl
      << InputFile->GetName() << "  is connected with:";
         list<TString>* friendList =
         fInputFileStruct[TString(InputFile->GetName())];
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
      for ( i=0;i<MergedFileList->GetEntriesFast();i++) { 
         fRootManager->AddAndMerge((TFile*) MergedFileList->At(i));
      } 
      //Load geometry from first input
	  if(LoadGeo)InputFile->Get("FAIRGeom");
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

	  
   } //  if(InputFile )

  //Init the Chain ptr
   current = fChainList.begin();
   TFile *Output = fRootManager->OpenOutFile(Outfname);
   gROOT->GetListOfBrowsables()->Add(fTask);
   // Init the RTDB containers
   fRtdb= GetRuntimeDb();
   FairBaseParSet* par=(FairBaseParSet*)
            (fRtdb->getContainer("FairBaseParSet"));
   FairFieldFactory *fieldfact= FairFieldFactory::Instance();
   if(fieldfact)fieldfact->SetParm();
   // Assure that basic info is there for the run
   if(par && InputFile){
      fRootManager->ReadEvent(0);
      fEvtHeader = (FairEventHeader*)
      fRootManager->ActivateBranch("EventHeader.");
      //Copy the Event Header Info to Output
      fRootManager->Register("EventHeader.","EvtHeader",fEvtHeader, kTRUE);
      fRunId = fEvtHeader->GetRunId();
      // Init the containers in Tasks
      fTask->SetParTask();
      fRtdb->initContainers( fRunId );
   }


 // create a field 
    if(fieldfact) fField= fieldfact->createFairField();

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
}


void FairRunAna::Run(Int_t Ev_start, Int_t Ev_end)
{
  UInt_t tmpId =0;

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


void FairRunAna::AddAndMerge (const char *Name)
{
  TFile *fFile = new TFile(Name);
  if (fFile->IsZombie()) {
    Fatal("FairRunAna::AddAndMerge","Error opening output file");
  }else{
    AddAndMerge(fFile);
  }

}
//_____________________________________________________________________________
TFile *FairRunAna::SetInputFile(TString name)
{
   InputFile= new TFile(name);
   if (InputFile->IsZombie()) {
            cout << "-E- FairRunAna: Error opening Input file" << endl;
             exit(-1);
         }else{
   }
        fCurrentFileName = name;
        cout << "-I- FairRunAna: Opening Input file: " << fCurrentFileName << endl;
   return InputFile;
}


//_____________________________________________________________________________
void FairRunAna::SetInputFile(TFile *f)
{
  if (f->IsZombie()) {
      cout << "-E- FairRunAna: Error opening Input file" << endl;
    exit(-1);
  }else{
    InputFile=f;
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
void FairRunAna::DumpInputFileStruct() {
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
 TString name = *current++;
 return name;
}




//_____________________________________________________________________________


ClassImp(FairRunAna)

