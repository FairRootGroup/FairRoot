// -------------------------------------------------------------------------
// -----                   FairRootManager source file                 -----
// -----            Created 06/01/04  by M. Al-Turany/D. Bertini       -----
// -------------------------------------------------------------------------

// Class FairRootManager
// ------------------
// Class that takes care of Root IO.
#include "FairRootManager.h"
#include "FairDetector.h"
#include "FairRunAna.h"    
#include "FairRun.h"    
#include "FairMCApplication.h"
#include "FairGeoNode.h"

#include "TFriendElement.h"
#include "TObjArray.h"
#include "TFolder.h"
#include "TCollection.h"
#include "TParticle.h"
#include "TList.h"
#include "TGeoManager.h"
#include "TROOT.h"
#include "TClonesArray.h"
#include "TList.h"

#include <iostream>
#include <map>
#include <list>

using std::cout;
using std::endl;
using std::map;
using std::list;
using std::pair;

FairRootManager* FairRootManager::fgInstance = 0;
//_____________________________________________________________________________
FairRootManager* FairRootManager::Instance()
{
// Returns singleton instance.
// ---
  return fgInstance;
}  
//_____________________________________________________________________________
FairRootManager::FairRootManager()
  : TObject(),
    fCbmout(NULL),  
    fCbmroot(NULL),
    fCurrentTime(0),
    fInFile(NULL),
    fInChain( new TChain("cbmsim", "/cbmroot")),
    fOutFile(NULL),
    fOutTree(NULL), 
    fListFolder(0),
    fObj2(new TObject*[100]),
    fNObj(-1),
    fMap(),
    fPtrTree(NULL),
    fCurrentEntries(0),
    fBranchSeqId(0),
    fBranchNameList(new TList()),
    fDataContainer(),
    fActiveContainer(),
    fCompressData(kFALSE),
    fTimeStamps(kFALSE),
    fBranchPerMap(kFALSE),
    fBrPerMap(),
    fBrPerMapIter()
{
   if (fgInstance) {
      Fatal("FairRootManager", "Singleton instance already exists.");
      return;
   }
   fgInstance = this;
}
//_____________________________________________________________________________
FairRootManager::~FairRootManager() 
{
//
//  cout<<"Enter Destructor of FairRootManager"<<endl;
  if(fCbmout) delete fCbmout;  
  if(fCbmroot) delete fCbmroot;
  if(fInFile) delete fInFile;
  if(fInChain) delete fInChain;
  if(fOutTree)  delete fOutTree;
  if(fOutFile) {
    fOutFile->cd();
    delete fOutFile;
  }
  //  fObj2->Delete();
  delete fObj2;
  if(fPtrTree)delete fPtrTree;
  fBranchNameList->Delete();
  delete fBranchNameList;
  fgInstance = 0;
  //  cout<<"Leave Destructor of FairRootManager"<<endl;
}
//_____________________________________________________________________________
TFile *FairRootManager::OpenInFile(TFile* f, Bool_t Connect)
{
   /** Check if the file is there and readable otherwise exit*/
   fInFile=f;
   if (fInFile->IsZombie()) {
      cout << "Error opening input file: " << endl;
      exit(-1);
   }else{
      /** if connect is true, this file is part of the input and should go to a chain*/
      if(Connect) {
         if (!fInChain )
         fInChain = new TChain("cbmsim", "/cbmroot");
         fInChain->Add( fInFile->GetName() );
      }
      /** get the folder structure from file which describe the input tree */
      fCbmroot= dynamic_cast <TFolder *> (fInFile->Get("cbmroot"));
      if(!fCbmroot){
         fCbmroot= dynamic_cast <TFolder *> (fInFile->Get("cbmout"));
         if(!fCbmroot){
            fCbmroot= gROOT->GetRootFolder()->AddFolder("cbmroot", "Main Folder");   
         }else{
            fCbmroot->SetName("cbmroot");
         }
      }
      /**Get The list of branches from the input file and add it to the actual list*/
      TList *list= dynamic_cast <TList *> (fInFile->Get("BranchList"));
      if(list) {
         TObjString *Obj=0;
          for(Int_t i =0; i< list->GetEntries(); i++){
             Obj=dynamic_cast <TObjString *> (list->At(i));
             if(fBranchNameList->FindObject(Obj->GetString().Data())==0){
                fBranchNameList->AddLast(Obj);
                fBranchSeqId++;
             }
          } 
      }
      gROOT->GetListOfBrowsables()->Add(fCbmroot);
      fListFolder.Add( fCbmroot );
   }
   fInChain->GetEntry(0);
   fPtrTree = fInChain->GetTree();
   fCurrentEntries =  (Int_t) fInChain->GetTree()->GetEntries();
   return  fInFile;
}
//_____________________________________________________________________________}
void FairRootManager::AddFriend( TFile *f ){
 
  if (f->IsZombie()) {
     cout << "-E- FairRootManager: Error opening friend file " << endl;
	 exit(-1);
  }
	
  if (fInChain) {
    fInChain->AddFriend("cbmsim",f); 
    TFolder *added=NULL; 
    added = dynamic_cast <TFolder *> (f->Get("cbmout"));
    if(added==0){
       added = dynamic_cast <TFolder *> (f->Get("cbmroot"));       
    }
//	cout << "Add Folder to the list " << added->GetName() <<" from file " << f->GetName()<< endl;  
    fListFolder.Add( added );  


    /**Get The list of branches from the friend file and add it to the actual list*/
    TList *list= dynamic_cast <TList *> (f->Get("BranchList"));
    if(list) {
       TObjString *Obj=0;
       for(Int_t i =0; i< list->GetEntries(); i++){
          Obj=dynamic_cast <TObjString *> (list->At(i));
          if(fBranchNameList->FindObject(Obj->GetString().Data())==0) { 
               fBranchNameList->AddLast(Obj);
               fBranchSeqId++;
		  }
       } 
    }
  }else{

    Fatal("\033[5m\033[31m FairRootManager::AddFriend","not input tree. \033[0m\n");

  }
}
//_____________________________________________________________________________
Bool_t  FairRootManager::DataContainersEmpty()
{
	for(std::map<TString, std::queue<TClonesArray*> >::iterator it = fDataContainer.begin(); it != fDataContainer.end(); it++){
		if (it->second.empty() == false){
			return kFALSE;
		}
	}
	return kTRUE;
}
//_____________________________________________________________________________
Bool_t	FairRootManager::DataContainersFilled()
{
	for(std::map<TString, std::queue<TClonesArray*> >::iterator it = fDataContainer.begin(); it != fDataContainer.end(); it++){
		if (it->second.empty() == true)
			return kFALSE;
	}
	return kTRUE;
}
//_____________________________________________________________________________
TFile *FairRootManager::OpenOutFile(TFile* f)      
{
   fOutFile=f;
   /**Check the output file, if anything wronge with it exit!*/
   if (fOutFile->IsZombie()) {
      cout << "-E- FairRootManager: Error opening output file " << endl;
      exit(-1);
   }
   FairRun* fRun = FairRun::Instance();
   /**Check if a simulation run!*/
   if(!fRun->IsAna()){
      fCbmroot= gROOT->GetRootFolder()->AddFolder("cbmroot", "Main Folder");
      gROOT->GetListOfBrowsables()->Add(fCbmroot);
   }else{ 
      fCbmout= gROOT->GetRootFolder()->AddFolder("cbmout", "Main Output Folder");
      gROOT->GetListOfBrowsables()->Add(fCbmout);
   }
   return fOutFile;
}
//_____________________________________________________________________________
TFile *FairRootManager::OpenInFile(const char* fname, Bool_t Connect)
{
   if(fInFile) CloseInFile();
   fInFile = new TFile(fname);
   return OpenInFile(fInFile, Connect); 
}
//_____________________________________________________________________________
TFile *FairRootManager::OpenOutFile(const char* fname)
{
   if(fOutFile) CloseOutFile();
   fOutFile = new TFile(fname, "recreate");
   return OpenOutFile(fOutFile);
}
//_____________________________________________________________________________
void  FairRootManager::Register(const char* name, const char* folderName , TNamed *obj, Bool_t toFile)
{
   if(toFile){  /**Write the Object to the Tree*/
     TFolder *folder=0;
     TFolder *f=0;
     if(fCbmout==0){
        f=(TFolder *)fCbmroot->FindObjectAny(folderName);
        if(f==0)folder= fCbmroot->AddFolder(folderName,folderName);
        else folder=f;           
     }else{
        f=(TFolder *)fCbmout->FindObjectAny(folderName);
        if(f==0)folder= fCbmout->AddFolder(folderName,folderName);      
        else folder=f;  
     }
     obj->SetName(name);
     folder->Add(obj);
   }
   AddMemoryBranch(name, obj );
   //cout << " FairRootManager::Register Adding branch:(Obj) " << name << " In folder : " << folderName << endl;
   if(fBranchNameList->FindObject(name)==0){;
      fBranchNameList->AddLast(new TObjString(name));
      fBranchSeqId++;
   }
}

//_____________________________________________________________________________
void  FairRootManager::Register(const char* name,const char* Foldername ,TCollection *obj, Bool_t toFile)
{	
/**
* This method do exactly the same as the one before but for TCollection which is a TObject and not a TNamed (MT)
*/
   if(toFile){  /**Write the Object to the Tree*/
      TFolder *folder=0;
      TFolder *f=0;
      if(fCbmout==0){
         f=(TFolder *)fCbmroot->FindObjectAny(Foldername);
         if(f==0)folder= fCbmroot->AddFolder(Foldername,Foldername);
         else folder=f;
      }else{
         f=(TFolder *)fCbmout->FindObjectAny(Foldername);
         if(f==0)  folder= fCbmout->AddFolder(Foldername,Foldername);      
         else folder=f;
      }
      obj->SetName(name);
      folder->Add(obj);
   }
    /**Keep the Object in Memory, and do not write it to the tree*/
   AddMemoryBranch(name, obj );
   if(fBranchNameList->FindObject(name)==0){;
      fBranchNameList->AddLast(new TObjString(name));
      fBranchSeqId++;
   }
}
//_____________________________________________________________________________
TClonesArray* FairRootManager::Register(TString branchName, TString className, TString folderName, Bool_t toFile){

   TClonesArray* outputArray;
   fActiveContainer[branchName] = new TClonesArray(className);
   if (fCompressData){
      std::queue<TClonesArray*> myQueue;
      fDataContainer[branchName] = myQueue;
      outputArray = new TClonesArray(className);
   } else outputArray = fActiveContainer[branchName];
   Register(branchName, folderName, outputArray, toFile);
   return fActiveContainer[branchName];
}
//_____________________________________________________________________________
TClonesArray* FairRootManager::GetTClonesArray(TString branchName){
   if (fActiveContainer.find(branchName) != fActiveContainer.end()){  
      /**if a TClonesArray is registered in the active container*/
      if (fCompressData && fActiveContainer[branchName]->GetEntries() > 0){
         /**if the container is not empty push it into the DataContainer storage and create a new one*/
         fDataContainer[branchName].push(fActiveContainer[branchName]);
         fActiveContainer[branchName] = new TClonesArray(fActiveContainer[branchName]->GetClass()->GetName());
       }
       return fActiveContainer[branchName]; // return the container
    } else std::cout << "-E- Branch: " << branchName << " not registered!" << std::endl;	
   // error if the branch is not registered
   return 0;
}


//_____________________________________________________________________________
TClonesArray* FairRootManager::GetDataContainer(TString branchName)
{
   if (DataContainersFilled()){
      return fDataContainer[branchName].front();
   }
   return 0;
}
//_____________________________________________________________________________
TClonesArray* FairRootManager::ForceGetDataContainer(TString branchName)
{
	TClonesArray* result = 0;
	if (fDataContainer.find(branchName)!= fDataContainer.end()){
		if (!fDataContainer[branchName].empty()){
			result = fDataContainer[branchName].front();
			fDataContainer[branchName].pop();
		}
	}
	return result;
}
 //_____________________________________________________________________________ 
TString FairRootManager::GetBranchName(Int_t id)
{
   /**Return the branch name from the id*/
   if(id < fBranchSeqId){
      TObjString *ObjStr= (TObjString *) fBranchNameList->At(id);
      return ObjStr->GetString();
   }else{
      TString NotFound("Branch not found");
      return NotFound;
   }
}
 //_____________________________________________________________________________

Int_t FairRootManager::GetBranchId(TString BrName)
{
   /**Return the branch id from the name*/
   TObjString *ObjStr;
   Int_t Id=-1;
   for(Int_t t=0; t<fBranchNameList->GetEntries(); t++){
      ObjStr= (TObjString *) fBranchNameList->At(t);
      if(BrName==ObjStr->GetString()){
      Id=t;
      break;
   } 	
	}
	return Id;
	
}
 //_____________________________________________________________________________
void  FairRootManager::Fill()
{
// Fills the tree.
// ---
	if (fCompressData){
		if (DataContainersFilled()) {
			AssignTClonesArrays();
			ForceFill();
		}
	}
	else ForceFill();
}
void FairRootManager::ForceFill()
{
	if (fOutTree != 0) {
		fOutTree->Fill();
	} else {
		cout << "-E- FairRootManager::Fill()  No Output Tree" << endl;
	}
}
//_____________________________________________________________________________
void FairRootManager:: Write()
{
/** Writes the tree in the file.*/
	if (fCompressData)
		SaveAllContainers();
  if(fOutTree!=0){
  /** Get the file handle to the current output file from the tree. 
    * If ROOT splits the file (due to the size of the file) the file 
    * handle fOutFile is lost and the program crash while writing the
    * last part of the last file.
  */
      fOutFile = fOutTree->GetCurrentFile(); 
      fOutFile->cd();
      fOutTree->Write();
  }else{
     cout << "-E- FairRootManager::Write()  No Output Tree"  << endl;
  }
}
//_____________________________________________________________________________
void FairRootManager:: WriteGeometry()
{
/** Writes the geometry in the current output file.*/

   if(fOutTree!=0){
      fOutFile = fOutTree->GetCurrentFile(); 
      fOutFile->cd();
      gGeoManager->Write();
   }
}
//_____________________________________________________________________________

void FairRootManager::CreateGeometryFile(const char *geofile)
{
/** Writes the geometry in a separate file.
 *  This is only to have a file which can be read without the
 *  framework. The geomanager used by the framework is still
 *  stored in the parameter file or database
*/
   TFile* oldfile=gFile;
   TFile* file=new TFile(geofile,"RECREATE");
   file->cd();
   gGeoManager->Write();
   file->Close();
   file->Delete();
   gFile=oldfile;
}

//_____________________________________________________________________________
void FairRootManager:: WriteFolder()
{
   fOutFile->cd();
   if(fCbmroot!=0 && fInFile==0){
      fCbmroot->Write();
   }
   if(fCbmout!=0){
       fCbmout->Write(); 
   }
   fBranchNameList->Write("BranchList", TObject::kSingleKey);
}
//_____________________________________________________________________________
void  FairRootManager::ReadEvent(Int_t i)
{
/** Reads the event data for i-th event for all connected branches.*/
   fInChain->GetEntry(i);
   FairRunAna* fRun = FairRunAna::Instance();
   if ( (i == fCurrentEntries)  && fInChain->GetListOfFriends()  ) {
      // get the next file name in the list of chained files
      TString cfilename = fRun->GetNextFileName();
      // clear the Friend contents of Chains
      TList *lf = fInChain->GetListOfFriends();
      if(lf) {
         TFriendElement *fr;
         TFile *file;
         for(Int_t ii = 0; ii < lf->GetEntries(); ii++) {
            fr = (TFriendElement*) lf->At(ii);
            file = fr->GetFile();
            file->Close();
         }
         lf->Clear();
      }
      cout << endl;
      cout << "-I FairRootManager: switching to chained file: " << cfilename <<  endl;
      map<TString, list<TString>* >  fileS = fRun->GetFileStructure();
      list<TString>* lFriends = fileS[cfilename];
      list<TString>::const_iterator iter;
      for(iter = lFriends->begin(); iter != lFriends->end(); iter++) {
         cout << "                         connected friends: " << *iter << endl;
         fInChain->AddFriend("cbmsim", new TFile(*iter));
      }
         cout << endl;
         fInChain->GetEntry(i);
         fCurrentEntries += (Int_t ) fInChain->GetTree()->GetEntries();
      }
 
}
//_____________________________________________________________________________
Bool_t FairRootManager::ReadNextEvent(Double_t dt)
{
	Bool_t readentry=kFALSE; 
	///TODO
	return readentry;
}


//_____________________________________________________________________________
 TObject* FairRootManager::GetObject(const char* BrName)
{
   /**Get Data object by name*/
   TObject *Obj =NULL;
   /**Try to fine the object in the folder structure, object already activated by other task or call*/
   if(fCbmout) Obj = fCbmout->FindObjectAny(BrName);
   /**if the object does not exist then it could be a memory branch */
   if(!Obj){  Obj=GetMemoryBranch(BrName); }
   /**if the object does not exist then look in the input tree */
   if(fCbmroot && !Obj){
      /** there is an input tree and the object was not in memory */
      Obj=fCbmroot->FindObjectAny(BrName);
      Obj=ActivateBranch(BrName);
   }
   if(!Obj) {  Obj=ActivateBranch(BrName); }	
   return Obj;
 }

//_____________________________________________________________________________
FairGeoNode*  FairRootManager::GetGeoParameter(const char* detname, const char* gname){
   TFolder *detf= NULL;
   FairGeoNode *node = NULL;
   TList *lgeo=NULL;
   TString lname(detname);
   lname+="GeoPar";
   TFolder *froot =  dynamic_cast<TFolder*> (gROOT->FindObject("cbmroot"));
   if ( froot )  detf = dynamic_cast<TFolder*> (froot->FindObjectAny( detname ));
   else cout << "-E- GetGeoParameter() Main Folder not found ! " << endl;
   if ( detf    )  lgeo = dynamic_cast<TList*> (detf->FindObjectAny( lname.Data() ));
   else cout << "-E- GetGeoParameter() GeoPar: " << lname << endl;
   if ( lgeo    )  node = dynamic_cast<FairGeoNode*> (lgeo->FindObject(gname));
   else cout << "-E- GetGeoParameter() GeoList not found " << endl;
   return node;
}

//_____________________________________________________________________________

void FairRootManager::TruncateBranchNames(TTree *fTree, const char *folderName)
{
  /** If a object is created in a folder the corresponding branch
  * in the tree is crated with a wrong name.
  * The name of the branch is created as follows
  * mainFolder.subFolder.nameOfStoredObject
  * e.g. cbmroot.Event.ExampleClass.
  * The name which is wanted is only nameOfStoredObject
  * e.g. ExampleClass.
  * This is corrected in this function
  * If the folder does not exist don't do anything
  */
  TFolder *cbm=(TFolder *)gROOT->FindObjectAny(folderName);
  if(cbm){
     TCollection* lf=cbm->GetListOfFolders();
     TIterator* iter= lf->MakeIterator();
     TObjArray* Br= fTree->GetListOfBranches();
     TIterator* BrIter= Br->MakeIterator();
     TObject *obj;
     TObject *BrObj;

     /** correct branch names in all folders below the main output folder*/
    while((obj=iter->Next())) {

      /** Create TString with the part of the branch name which should be
      * removed. This is mainFolderName.folderName. e.g. cbmroot.Event.
      * This part of the branch name is obsolete, so it is removed from
      * the branch name.
      */
      TString ffn=cbm->GetName();
      ffn=ffn+".";
      ffn=ffn+obj->GetName();
      ffn=ffn+".";

      /** Correct name of all branches and leaves which correspond to
      * the subfolder. To do so loop over all branches and check
      * if the branch corresponds with the folder. If it corresponds
      * correct the branch names of all sub branches.
      * Only correct branch names for up to now uncorrected branches.
      */
      BrIter->Reset();

      while((BrObj=BrIter->Next())) {
        TBranch *b=(TBranch *)BrObj;
	TruncateBranchNames(b, ffn);
      }
    }

    // Remove all occurence of FairMCEventHeader and FairEventHeader from 
    // all branches containing that string.
    // This is not the correct way to do it, but up tonow we don't understand
    // why this part comes in when storing a derrived class from 
    // FairMCEventHeader or FairEventHeader.
 
    iter->Reset();
    while((obj=iter->Next())) {

      TString ffn=".FairMCEventHeader";
      BrIter->Reset();

      while((BrObj=BrIter->Next())) {
        TBranch *b=(TBranch *)BrObj;
	TruncateBranchNames(b, ffn);
      }
    }

    iter->Reset();
    while((obj=iter->Next())) {

      TString ffn=".FairEventHeader";
      BrIter->Reset();

      while((BrObj=BrIter->Next())) {
        TBranch *b=(TBranch *)BrObj;
	TruncateBranchNames(b, ffn);
      }
    }

    delete  iter;
    delete  BrIter;
 }
}
//_____________________________________________________________________________

void FairRootManager::TruncateBranchNames(TBranch *b, TString ffn)
{
  /** Get the branch name from the branch object, remove common
  *  and wrong part of the name and and set branch name to
  *  the new corrected name. This has to be done recursivly for
  *  all subbranches/leaves
  *  Remove wrong part of branch name
  */
  TObject *BrObj;
  TString nn= b->GetName();
  //  cout<<"nn.Data before: "<<nn.Data()<<endl;
  nn.ReplaceAll(ffn.Data(),"");
  //  cout<<"nn.Data after: "<<nn.Data()<<endl;
  //  cout <<"##################"<<endl;
  b->SetName(nn.Data());
  TObjArray* Br= b->GetListOfBranches();
  TIterator* BrIter= Br->MakeIterator();
  BrIter->Reset();

  while((BrObj=BrIter->Next())) {
    TBranch *bb=(TBranch *)BrObj;
    TruncateBranchNames(bb, ffn);
  }
  delete  BrIter;
}
//_____________________________________________________________________________

Int_t FairRootManager::CheckBranch(const char* BrName)
{
   /**The first time this method is called the map is generated and then used*/ 
   if(!fBranchPerMap){
      CreatePerMap();
      return CheckBranchSt(BrName);
   }else{
      fBrPerMapIter=fBrPerMap.find(BrName);
      if(fBrPerMapIter!=fBrPerMap.end()) return fBrPerMapIter->second;
      else  return 0;
   }
}

//_____________________________________________________________________________
void  FairRootManager::SetBranchNameList(TList *list)
{
   for(Int_t t=0; t<list->GetEntries(); t++){
      fBranchNameList->AddAt(list->At(t),t); 
   }
}






//_____________________________________________________________________________
/** Private functions*/
//_____________________________________________________________________________


TObject * FairRootManager::ActivateBranch(const char *BrName)
{
/** Set the branch address for a given branch name and return a TObject pointer,
 the user have to cast this pointer to the right type.
 The function has been revisited ! Now it test if in the task init() mutilple
 calls to activate branch is done , and then just forward the pointer.
 <DB>
 **/
   fNObj++;
   fObj2[fNObj]  =  GetMemoryBranch ( BrName );
   if ( fObj2[fNObj]   ){
      return  fObj2[fNObj];
   }
   /**try to find the object decribing the branch in the folder structure in file*/
   for(Int_t i=0;i<fListFolder.GetEntriesFast();i++){
      TFolder *fold = (TFolder*) fListFolder.At(i);
      fObj2[fNObj] = fold->FindObjectAny(BrName);
      if (fObj2[fNObj] ) break;
   }
   
   if(!fObj2[fNObj]){
       /** if we do not find an object corresponding to the branch in the folder structure
		*  then we have no idea about what type of object is this and we cannot set the branch address
		*/
	   cout << "-E- FairRootManager Branch: "  << BrName  << " not found in Tree" << endl;
	  //Fatal(" No Branch in the tree", BrName );
	  return 0;
   }else {
      fInChain->SetBranchStatus(BrName,1);
      fInChain->SetBranchAddress(BrName,&fObj2[fNObj]);
   }
   
   AddMemoryBranch( BrName , fObj2[fNObj] );
   return  fObj2[fNObj];

}

//_____________________________________________________________________________



void  FairRootManager::AddMemoryBranch( const char* fName, TObject* pObj ){
   /**branch will be available ionly in Memory, will not be written to disk */
   map < TString, TObject*>::iterator p;
   TString BrName=fName;
   p=fMap.find(BrName);
   if(p!=fMap.end()){
       //  cout << " -E- FairRootManager::AddMemoryBranch " << BrName << " is already inserted " << endl;
   }else{
      //  cout << " -E- FairRootManager::AddMemoryBranch " << BrName << " isAdded " << endl;
   	fMap.insert(pair<TString, TObject*> (BrName, pObj));
   }
}
//_____________________________________________________________________________
void FairRootManager::AssignTClonesArrays(){
	 for(std::map<TString, std::queue<TClonesArray*> >::iterator it = fDataContainer.begin(); it != fDataContainer.end(); it++){
		AssignTClonesArray(it->first);
	 }
}
//_____________________________________________________________________________
void FairRootManager::AssignTClonesArray(TString branchName){
	TClonesArray* output = (TClonesArray*)GetObject(branchName);
	TClonesArray* input = ForceGetDataContainer(branchName);
	output->Clear();
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,27,4)
	if (input != 0){
		output->AbsorbObjects(input);
	}
#else
	cout <<"FairRootManager::AssignTClonesArray(TString branchName) "<<endl;
        cout <<"Is only available in ROOT 5.27-04 "<<endl;
#endif
}
//_____________________________________________________________________________
Int_t FairRootManager::CheckBranchSt(const char* BrName)
{
   Int_t returnvalue=0;
   TObject *Obj1 =NULL;
   if (fCbmroot) Obj1 = fCbmroot->FindObjectAny(BrName);
   if(fCbmout && !Obj1) Obj1 = fCbmout->FindObjectAny(BrName);  //Branch in output folder
   if(!Obj1){
      for(Int_t i=0;i<fListFolder.GetEntriesFast();i++){
//		  cout << "Search in Folder: " << i << "  " <<  listFolder.At(i) << endl;
         TFolder *fold = dynamic_cast<TFolder *> (fListFolder.At(i));
         if(fold!=0)Obj1= fold->FindObjectAny(BrName);
         if (Obj1) break;
      }
   }
   TObject *Obj2 =NULL;
   Obj2=GetMemoryBranch(BrName);  // Branch in Memory
   if (Obj1!=0) returnvalue=1;		
   else if(Obj2!=0) returnvalue=2;
   else returnvalue= 0;

   /**  1 : Branch is Persistance
        2 : Memory Branch
        0 : Branch does not exist
   */
   return returnvalue;
}
//_____________________________________________________________________________
void  FairRootManager::CreatePerMap()
{
//   cout << " FairRootManager::CreatePerMap() " << endl;
   fBranchPerMap=kTRUE;
   for (Int_t i=0; i<fBranchSeqId; i++){
      TObjString *name= (TObjString *)(fBranchNameList->At(i));
//      cout << " FairRootManager::CreatePerMap() Obj At " << i << "  is "  << name->GetString() << endl;
      TString BrName=name->GetString();
      fBrPerMap.insert(pair<TString, Int_t> (BrName, CheckBranchSt(BrName.Data())));
   }

}
//_____________________________________________________________________________
TObject*  FairRootManager::GetMemoryBranch( const char* fName ) {
 
 //return fMap[BrName];
  TString BrName=fName;
  map < TString, TObject*>::iterator p;
  p=fMap.find(BrName);

  if(p!=fMap.end()){
	return p->second;
    //    cout << " -E- FairRootManager::GetMemoryBranch " << BrName << " is found " << endl;
  }else{
   // cout << " -E- FairRootManager::GetMemoryBranch " << BrName << " Not found " << endl;
	return 0;
  }
}
//_____________________________________________________________________________
void FairRootManager::SaveAllContainers(){
   while(!DataContainersEmpty()){
      AssignTClonesArrays();
      ForceFill();
   }
}
//_____________________________________________________________________________

ClassImp(FairRootManager)







 
