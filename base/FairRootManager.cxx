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
#include "FairGenericStack.h"
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
   cbmout(0),  
   cbmroot(0),
   fInFile(0),
   fInChain( new TChain("cbmsim", "/cbmroot")),
   fOutFile(0),
   fOutTree(0), 
   listFolder(0),
   fListOfTrees(0), 
   fListOfClones(0),
   fListOfStack(0),
   isMerging(kFALSE),  
   fMergedStack(0),
   fListOfMergedClones(0),
   fObj2(new TObject*[100]),
   fNObj(-1),
   tmpPtrTree(0),
   fPtrTree(0),
   fCurrentEntries(0),
   fBranchSeqId(0),
   fBranchNameList(new TList())

{
//
  if (fgInstance) {
    Fatal("FairRootManager", "Singleton instance already exists.");
    return;
  }  
  fgInstance = this;
}

//_____________________________________________________________________________
TFile *FairRootManager::OpenInFile(TFile* f, Bool_t Connect)
{
  fInFile=f;
  if (fInFile->IsZombie()) {
    cout << "Error opening input file: " << endl;
    exit(-1);
  }else{
    if(Connect) {

      if (!fInChain )
      fInChain = new TChain("cbmsim", "/cbmroot");

      fInChain->Add( fInFile->GetName() );

    }


    cbmroot= dynamic_cast <TFolder *> (fInFile->Get("cbmroot"));
    if(!cbmroot){
       cbmroot= dynamic_cast <TFolder *> (fInFile->Get("cbmout"));
       if(!cbmroot){
          cbmroot= gROOT->GetRootFolder()->AddFolder("cbmroot", "Main Folder");   
       }else{
          cbmroot->SetName("cbmroot");
       }

    }


    gROOT->GetListOfBrowsables()->Add(cbmroot);
    listFolder.Add( cbmroot );
  }

  
  fInChain->GetEntry(0);
  fPtrTree = fInChain->GetTree();
  fCurrentEntries =  (Int_t) fInChain->GetTree()->GetEntries();
  
  //  fInFile->Close();
  //  fInFile = fInChain->GetFile();
  // cout << "-I FairRootManager: Opening input file: " << fInFile->GetName()
 //      << " Nb entries: " << fCurrentEntries << endl;
  return  fInFile;
}
//_____________________________________________________________________________}
void FairRootManager::SetWildcard(TString Wildcard) {
 fInChain->Add(Wildcard);
}
//_____________________________________________________________________________}
void FairRootManager::AddFile(TString name) {
  //  cout << "-I- FairRootManager: adding file " << name << endl;
    fInChain->Add(name);
}    
//_____________________________________________________________________________}
void FairRootManager::AddFriend( TFile *f ){
 
  if (fInChain) {

     fInChain->AddFriend("cbmsim",f); 
     TFolder *added=NULL; 
     added = dynamic_cast <TFolder *> (f->Get("cbmout"));
     if(added==0){
       added = dynamic_cast <TFolder *> (f->Get("cbmroot"));       
     }
     listFolder.Add( added );  

  }else{

    Fatal("\033[5m\033[31m FairRootManager::AddFriend","not input tree. \033[0m\n");

  }
}

////	"\033[5m\033[31mThis is blue.\033[0m\n" 
//_____________________________________________________________________________}
void  FairRootManager::AddAndMerge (TFile *f ) {
 
  cout << "-I  FairRootManager::AddAndMerge called for file: " << 
    f->GetName() << endl;
  if ( fInChain ) {

    // do the merging ...  
   
   TFolder *added=NULL; 
    added = dynamic_cast <TFolder *> (f->Get("cbmout"));
    
    if ( added == 0 ) {      
      // test consistency on branches
      TObjArray *brList = (TObjArray*) fInChain->GetListOfBranches(); 
      Int_t nBranches =  brList->GetEntriesFast();
      // Get the TTree from file
      TTree* t = (TTree* ) f->Get("cbmsim"); 
      if ( nBranches == t->GetListOfBranches()->GetEntriesFast() 
          && ( t->GetEntries() >= fInChain->GetEntries() )  ) {   	
	fListOfTrees.Add ( t ) ; 
	// Get Run Info
       // FairMCApplication *fcbm = (FairMCApplication*) f->Get("Fair");

	TFolder *fd = (TFolder*) f->Get("cbmroot");
	FairGenericStack *stack = (FairGenericStack*) fd->FindObjectAny("FairStack");
        //Create memory-mapped stack 
        if (!isMerging) {
                   fMergedStack = new FairGenericStack(1000);
      	} 
        // activate stack 
        t->SetBranchAddress("FairStack",&stack);
        fListOfStack.Add( stack ); 

        // Get Clones and activate them 
	// Get Objects from tree
       TObjArray * clist = new TObjArray(); 
	for (Int_t k=0; k<nBranches; k++ ){
	  TBranch * br = (TBranch*) brList->At(k); 
	  cout << "-I FairRootManager: Branches: " << br->GetName() << endl;
	  TObject * obj = (TObject* ) fd->FindObjectAny( br->GetName() );  
	  if (obj ) {
	   cout << "-I FairRootManager: Object name " << obj->GetName() 
                << " class: " << obj->IsA()->GetName() << endl;    

	     if (strcmp(obj->IsA()->GetName(),"TClonesArray") == 0 ){
               TClass * cl = ((TClonesArray*) obj)->GetClass();
               if (!isMerging ) {
                  cout << "-I FairRootManager: Adding class " 
                       << cl->GetName() << endl; 
                  
		  TClonesArray * m_clone = new TClonesArray(cl->GetName());
		  m_clone->SetName(   br->GetName() );                 
                  fListOfMergedClones.Add( m_clone );
	       }  
	       // Internal bookkeepin of clones
	
                clist->Add( (TClonesArray*) 
                             fd->FindObjectAny( br->GetName() ) );     
		
             
                //Set Branch address for clones
		Int_t nobj = clist->GetEntriesFast(); 
                TClonesArray *clon = (TClonesArray*) clist->At(nobj-1);          
                 t->SetBranchAddress(clon->GetName(),&clon);   

	     }


	    
	  } else Fatal("FairRootManager::AddAndMerge","No object found in Tree");
	    
	}//! branches        
       fListOfClones.Add( clist );	

      } else {
	Fatal(" FairRootManager::AddAndMerge "," Branches inconsistency ");
      } 
      
      
    }else{ 
      Fatal(" FairRootManager::AddAndMerge "," No merging of Analysis Output or inconsistent Nentries");   
    }  
   
  isMerging = kTRUE;    
  } else {
  isMerging = kFALSE;     
    Fatal(" FairRootManager::AddAndMerge ","No Input File defined"); 

  }
 
}


//_____________________________________________________________________________
TFile *FairRootManager::OpenOutFile(TFile* f)      
{

 fOutFile=f;
 if (fOutFile->IsZombie()) {
     cout << "-E- FairRootManager: Error opening output file " << endl;
  exit(-1);
 }
  FairRun* fRun = FairRun::Instance();

 if(!fRun->IsAna()){
  cbmroot= gROOT->GetRootFolder()->AddFolder("cbmroot", "Main Folder");
  gROOT->GetListOfBrowsables()->Add(cbmroot);
 }else{
  cbmout= gROOT->GetRootFolder()->AddFolder("cbmout", "Main Output Folder");
  gROOT->GetListOfBrowsables()->Add(cbmout);
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
FairRootManager::~FairRootManager() 
{
//
   if(cbmout) delete cbmout;  
   if(cbmroot) delete cbmroot;
   if(fInChain) delete fInChain;
   if(fOutTree)  delete fOutTree;
   if(tmpPtrTree)delete tmpPtrTree;
   if(fPtrTree)delete fPtrTree;
   if(fInFile) delete fInFile;
   if(fOutFile) {
      fOutFile->cd();
     delete fOutFile;
   }

  fgInstance = 0;
  delete fObj2;
}
//_____________________________________________________________________________
void  FairRootManager::Register(const char* name, const char* folderName , TNamed *obj, Bool_t toFile)
{
   if(toFile){  /**Write the Object to the Tree*/
     TFolder *folder=0;
     TFolder *f=0;
     if(cbmout==0){
        f=(TFolder *)cbmroot->FindObjectAny(folderName);
        if(f==0)folder= cbmroot->AddFolder(folderName,folderName);
        else folder=f;           
     }else{
        f=(TFolder *)cbmout->FindObjectAny(folderName);
        if(f==0)folder= cbmout->AddFolder(folderName,folderName);      
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

//_____________________________________________________________________-- ________
void  FairRootManager::Register(const char* name,const char* Foldername ,TCollection *obj, Bool_t toFile)
{	
/**
* This method do exactly the same as the one before but for TCollection which is a TObject and not a TNamed (MT)
*/
   if(toFile){  /**Write the Object to the Tree*/
      TFolder *folder=0;
      TFolder *f=0;
      if(cbmout==0){
         f=(TFolder *)cbmroot->FindObjectAny(Foldername);
         if(f==0)folder= cbmroot->AddFolder(Foldername,Foldername);
         else folder=f;
      }else{
         f=(TFolder *)cbmout->FindObjectAny(Foldername);
         if(f==0)  folder= cbmout->AddFolder(Foldername,Foldername);      
         else folder=f;
      }
      obj->SetName(name);
      folder->Add(obj);
    }
    /**Keep the Object in Memory, and do not write it to the tree*/
   AddMemoryBranch(name, obj );
   //cout << " FairRootManager::Register Adding branch:(collection)  " << name << " In folder : " << Foldername << endl;
	
	if(fBranchNameList->FindObject(name)==0){;
	   fBranchNameList->AddLast(new TObjString(name));
       fBranchSeqId++;
	}
}
 //_____________________________________________________________________________ 

TString FairRootManager::GetBranchName(Int_t id)
{
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
  if(fOutTree!=0){
    fOutTree->Fill();
  }else{
      cout << "-E- FairRootManager::Fill()  No Output Tree"  << endl;
  }
}  

//_____________________________________________________________________________
void FairRootManager:: Write()
{
// Writes the tree in the file.
// ---

  if(fOutTree!=0){
    // Get the file handle to the current output file from the tree. 
    // If ROOT splits the file (due to the size of the file) the file 
    // handle fOutFile is lost and the program crash while writing the
    // last part of the last file.

    fOutFile = fOutTree->GetCurrentFile(); 

    fOutFile->cd();
    fOutTree->Write();
  }else{
     cout << "-E- FairRootManager::Write()  No Output Tree"  << endl;
  }
  
}

void FairRootManager:: WriteGeometry()
{
// Writes the geometry in the file.
// ---

  if(fOutTree!=0){
    fOutFile = fOutTree->GetCurrentFile(); 
    fOutFile->cd();
    gGeoManager->Write();
  }

}

void FairRootManager::CreateGeometryFile(const char *geofile)
{
// Writes the geometry in a separate file.
// This is only to have a file which can be read without the
// framework. The geomanager used by the framework is still
// stored in the parameter file or database
// ---

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

    if(cbmroot!=0 && fInFile==0){
       cbmroot->Write();
    }
    if(cbmout!=0){
       cbmout->Write(); 
    }
}

//_____________________________________________________________________________
void  FairRootManager::ReadEvent(Int_t i)
{
// Reads the event data for i-th event for all connected branches.
// ---
    if (isMerging ) {

	cout << "-I FairRootManager Readevent and merge:" << fListOfTrees.GetEntriesFast() << endl;
	for (Int_t j=0; j<fListOfTrees.GetEntriesFast(); j++ ) {
	    TTree * t = (TTree*) fListOfTrees.At(j);
	    t->GetEntry( i );
	}
	ReindexStack();
    }else{ 
	fInChain->GetEntry(i);
	FairRunAna* fRun = FairRunAna::Instance();
	if ( (i == fCurrentEntries)  &&
	    fInChain->GetListOfFriends()  ) {
	    // get the next file name in the list of chained files
	    TString cfilename = fRun->GetNextFileName();

	    // clear the Friend contents of Chains
	    TList *lf = fInChain->GetListOfFriends();
//            if (lf) { lf->Clear(); }
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
}

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
  if ( isMerging ){
      fObj2[fNObj] = GetMergedObject(BrName);
      return fObj2[fNObj];
  }else{
        fObj2[fNObj]  =  GetMemoryBranch ( BrName );
      if ( fObj2[fNObj]   ){
          return  fObj2[fNObj];
      }
      for(Int_t i=0;i<listFolder.GetEntriesFast();i++){
	     TFolder *fold = (TFolder*) listFolder.At(i);
	     fObj2[fNObj] = fold->FindObjectAny(BrName);
	     if (fObj2[fNObj] ) break;
      }
      if(!fObj2[fNObj]){
	     cout << "-E- FairRootManager Branch: "
			  << BrName  << " not found in Tree" << endl;
	  //	  Fatal(" No Branch in the tree", BrName );
	  return 0;
      } else {
	    fInChain->SetBranchStatus(BrName,1);
	    fInChain->SetBranchAddress(BrName,&fObj2[fNObj]);
      }
      AddMemoryBranch( BrName , fObj2[fNObj] );
      return  fObj2[fNObj];
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
 TObject* FairRootManager::GetObject(const char* BrName)
 {
 	TObject *Obj =NULL;
	if(cbmout) Obj = cbmout->FindObjectAny(BrName);
	if(!Obj){
	   Obj=GetMemoryBranch(BrName);
	 }
	 if(cbmroot && !Obj){
		
	    Obj=cbmroot->FindObjectAny(BrName);
	    Obj=ActivateBranch(BrName);
	//	cout<< "FairRootManager::GetObject Try folder for simulations! " <<  Obj <<   endl; 
	 }
	 if(!Obj) {
		 Obj=ActivateBranch(BrName);
	// 	cout << "now ActivatedBranch "<<endl;
	 }	
   //  cout<< "FairRootManager::GetObject will return  " << Obj <<" " << BrName <<  endl;	 
	 return Obj;
 }
//_____________________________________________________________________________
TObject* FairRootManager::GetMergedObject(const char* BrName)
{
  TObject *Obj =NULL;
  TString ObjName (BrName); 
  if ( ObjName.Contains("MCTrack") ) {
      return fMergedStack;
  }
  else {
    Obj = fListOfMergedClones.FindObject(BrName);     
    cout << " -I FairRootManager Branch name " << BrName << " " << Obj << endl;
    return Obj;
  }

}
//_____________________________________________________________________________

void FairRootManager::ReindexStack(){

  // Reset the Stack 
  fMergedStack->Reset();
  Int_t nStack = fListOfStack.GetEntriesFast(); 
  Int_t offset[nStack];
  Int_t n[nStack];
  Int_t i= 0; 
  
  // calculate offsets
  for (i=0;i<nStack;i++ ){offset[i]=n[i]=0;}    
  for (i=0;i<nStack;i++ ){    
    FairGenericStack *st = (FairGenericStack*) fListOfStack.At(i);
    n[i] = st->GetNtrack();
    if ( i == 0 ) offset[i] = 0 ; 
    if ( i == 1 ) offset[i] = n[i-1]; 
    if ( i>1 ) offset [i] = offset[i-1] + n[i-1]; 
  } 
  for (i=0; i<nStack; i++ ){
        FairGenericStack *st = (FairGenericStack*) fListOfStack.At(i);
        TParticle *part = NULL;  
        // cout << "-I Nparticle " << st->GetNtrack() << endl;
        for (Int_t j=0;j<st->GetNtrack();j++){
	  part =  st->GetParticle ( j ) ;        
          // shift what's needed .. 
          if (i>0) {
                 for (Int_t k=0;k<2; k++ ) part->SetMother(k,part->GetMother(k)+offset[i]); 
            }
          fMergedStack->AddParticle(part);       
	}      

  }
  
  // reindex clones 
  for (Int_t k=0;k<fListOfMergedClones.GetEntriesFast() ; k++ ) 
     ((TClonesArray*)fListOfMergedClones.At(k))->Clear();
  Int_t ncl = fListOfClones.GetEntriesFast(); 
  for (Int_t ii=0; ii< ncl; ii++ ) {
    TObjArray *clist= (TObjArray*) fListOfClones.At( ii );
    Int_t ncl2 =  clist->GetEntriesFast(); 
   
    for (Int_t kk=0;kk< ncl2; kk++ ){ 
      TClonesArray* clone = (TClonesArray*) clist->At( kk ); 
      TClonesArray* clone2 = (TClonesArray*) fListOfMergedClones.At( kk ); 
      //   cout << " k: " << kk << " entries " << clone2->GetEntriesFast() << endl;
     CopyClones ( clone , clone2, offset[ii] );  
    
    } 
  } 


}
//_____________________________________________________________________________
void FairRootManager::CopyClones(TClonesArray *cl1, TClonesArray* cl2 , Int_t offset ){

  // copy clone mechanism 
  TString str1( cl1->GetClass()->GetName() ); 
  TString str2( cl2->GetClass()->GetName() ); 
  // get clones
//  TClonesArray &particleRef = *cl2;
  FairMCApplication *fcbm = FairMCApplication::Instance(); 
    
//  Int_t i=0;
    // test name 
  if ( str1 != str2 ) Fatal("FairRootManager::CopyClones"," inconsistency "); 

  // Sts 
  if ( (str1.Contains("FairSTSDoublePoint") ) 
       || (str1.Contains("FairSTSPoint") ) ) {
    // cout << " -I  FairSTSDouble Point found at " << offset << " class " << str2 <<  endl; 
    // reindex the points 
    FairDetector * sts = fcbm->GetDetector("STS");
    sts->CopyClones(cl1,cl2,offset);

  } 

 
  //Tof
  if ( str1.Contains("FairTofPoint") ) {
    // cout << " -I  FairSTSDouble Point found at " << offset << " class " << str2 <<  endl; 
    // reindex the points 
    FairDetector * tof = fcbm->GetDetector("TOF");
    tof->CopyClones(cl1,cl2,offset);
  } 

  //Trd
  if ( str1.Contains("FairTRDPoint") ) {
    // cout << " -I  FairSTSDouble Point found at " << offset << " class " << str2 <<  endl; 
    // reindex the points 
    FairDetector * trd = fcbm->GetDetector("TRD");
    trd->CopyClones(cl1,cl2,offset);
  } 


  //Rich
  if ( str1.Contains("FairRichPoint") ) {
    // cout << " -I  FairRichDouble Point found at " << offset << " class " << str2 <<  endl; 
    // reindex the points 
    FairDetector * trd = fcbm->GetDetector("RICH");
    trd->CopyClones(cl1,cl2,offset);
  } 

}

//_____________________________________________________________________________
void  FairRootManager::AddMemoryBranch( const char* fName, TObject* pObj ){
	
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
FairGeoNode*  FairRootManager::GetGeoParameter(const char* detname, const char* gname){
 TFolder *detf= NULL;
    FairGeoNode *node = NULL;
    TList *lgeo=NULL;
    TString lname(detname);
    lname+="GeoPar";
    TFolder *froot =  dynamic_cast<TFolder*> (gROOT->FindObject("cbmroot"));
    if ( froot )  detf = dynamic_cast<TFolder*> (froot->FindObjectAny( detname ));
    else cout << "-E- GetGeoParameter() Main Folder not found ! " << endl;
//    detf->ls();
    if ( detf    )  lgeo = dynamic_cast<TList*> (detf->FindObjectAny( lname.Data() ));
    else cout << "-E- GetGeoParameter() GeoPar: " << lname << endl;
    if ( lgeo    )  node = dynamic_cast<FairGeoNode*> (lgeo->FindObject(gname));
    else cout << "-E- GetGeoParameter() GeoList not found " << endl;
    return node;

}

//_____________________________________________________________________________
void FairRootManager::TranicateBranchNames(TTree *fTree, const char *folderName)
{
  TFolder *cbm=(TFolder *)gROOT->FindObjectAny(folderName);
  if(cbm){
     TCollection* lf=cbm->GetListOfFolders();
     //TObject *evth = cbm->FindObject("EventHeader");
     TIterator* iter= lf->MakeIterator();
     TObjArray* Br= fTree->GetListOfBranches();
     TIterator* BrIter= Br->MakeIterator();
     TObject *obj;
     TObject *BrObj;

    // troncate in sub folder
    while((obj=iter->Next())) {
      TString ffn=cbm->GetName();
      ffn=ffn+".";
      ffn=ffn+obj->GetName();
      ffn=ffn+".";
      BrIter->Reset();
      while((BrObj=BrIter->Next())) {
        TBranch *b=(TBranch *)BrObj;
        TranicateBranchNames(b, ffn);
      }
    }
    delete  iter;
    delete  BrIter;
 }
}
//_____________________________________________________________________________
void FairRootManager::TranicateBranchNames(TBranch *b, TString ffn)
{
  TObject *BrObj;
  TString nn= b->GetName();
  nn.ReplaceAll(ffn.Data(),"");
  b->SetName(nn.Data());
  TObjArray* Br= b->GetListOfBranches();
  TIterator* BrIter= Br->MakeIterator();
  BrIter->Reset();
  while((BrObj=BrIter->Next())) {
    TBranch *bb=(TBranch *)BrObj;
    TranicateBranchNames(bb, ffn);
  }
  delete  BrIter;
}

//_____________________________________________________________________________

Int_t FairRootManager::CheckBranch(const char* BrName)
{

	Int_t returnvalue=0;
	TObject *Obj1 =NULL;
	if(cbmout)           Obj1 = cbmout->FindObjectAny(BrName);  //Branch in output folder
	if(cbmroot && !Obj1) Obj1 = cbmroot->FindObjectAny(BrName); //Branch comes from simulation file
	
	TObject *Obj2 =NULL;
	Obj2=GetMemoryBranch(BrName);  // Branch in Memory
	
	if (Obj1!=0) returnvalue=1;		
	else if(Obj2!=0) returnvalue=2;
	else returnvalue= 0;

	return returnvalue;

}

//_____________________________________________________________________________
void  FairRootManager::SetBranchNameList(TList *list)
{
	
	for(Int_t t=0; t<list->GetEntries(); t++){
		fBranchNameList->AddAt(list->At(t),t); 
	}
	
	
}
ClassImp(FairRootManager)







 
