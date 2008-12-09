// Class CbmRootManager
// ------------------
// Class that takes care of Root IO.

#include "CbmRootManager.h"

#include "CbmDetector.h"
#include "CbmRunAna.h"    
#include "CbmRun.h"    
#include "CbmMCApplication.h"
#include "CbmGenericStack.h"
#include "CbmGeoNode.h"
#include "TFriendElement.h"
#include "TObjArray.h"
#include "TFolder.h"
#include "TCollection.h"
#include "TParticle.h"
#include "TList.h"
#include "TGeoManager.h"
#include "TROOT.h"
#include "TClonesArray.h"
#include <iostream>
#include <map>
#include <list>

using std::cout;
using std::endl;
using std::map;
using std::list;
using std::pair;

CbmRootManager* CbmRootManager::fgInstance = 0;

//_____________________________________________________________________________
CbmRootManager* CbmRootManager::Instance()
{
// Returns singleton instance.
// ---
  return fgInstance;
}  

//_____________________________________________________________________________
CbmRootManager::CbmRootManager()
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
    	fCurrentEntries(0)

{
//
  if (fgInstance) {
    Fatal("CbmRootManager", "Singleton instance already exists.");
    return;
  }  
  fgInstance = this;
}

//_____________________________________________________________________________
TFile *CbmRootManager::OpenInFile(TFile* f, Bool_t Connect)
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
  // cout << "-I CbmRootManager: Opening input file: " << fInFile->GetName()
 //      << " Nb entries: " << fCurrentEntries << endl;
  return  fInFile;
}
//_____________________________________________________________________________}
void CbmRootManager::SetWildcard(TString Wildcard) {
 fInChain->Add(Wildcard);
}
//_____________________________________________________________________________}
void CbmRootManager::AddFile(TString name) {
  //  cout << "-I- CbmRootManager: adding file " << name << endl;
    fInChain->Add(name);
}    
//_____________________________________________________________________________}
void CbmRootManager::AddFriend( TFile *f ){
 
  if (fInChain) {

     fInChain->AddFriend("cbmsim",f); 
     TFolder *added=NULL; 
     added = dynamic_cast <TFolder *> (f->Get("cbmout"));
     if(added==0){
       added = dynamic_cast <TFolder *> (f->Get("cbmroot"));       
     }
     listFolder.Add( added );  

  }else{

    Fatal(" CbmRootManager::AddFriend","not input tree");

  }
}
//_____________________________________________________________________________}
void  CbmRootManager::AddAndMerge (TFile *f ) {
 
  cout << "-I  CbmRootManager::AddAndMerge called for file: " << 
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
       // CbmMCApplication *fcbm = (CbmMCApplication*) f->Get("Cbm");

	TFolder *fd = (TFolder*) f->Get("cbmroot");
	CbmGenericStack *stack = (CbmGenericStack*) fd->FindObjectAny("CbmStack");
        //Create memory-mapped stack 
        if (!isMerging) {
                   fMergedStack = new CbmGenericStack(1000);
      	} 
        // activate stack 
        t->SetBranchAddress("CbmStack",&stack);
        fListOfStack.Add( stack ); 

        // Get Clones and activate them 
	// Get Objects from tree
       TObjArray * clist = new TObjArray(); 
	for (Int_t k=0; k<nBranches; k++ ){
	  TBranch * br = (TBranch*) brList->At(k); 
	  cout << "-I CbmRootManager: Branches: " << br->GetName() << endl;
	  TObject * obj = (TObject* ) fd->FindObjectAny( br->GetName() );  
	  if (obj ) {
	   cout << "-I CbmRootManager: Object name " << obj->GetName() 
                << " class: " << obj->IsA()->GetName() << endl;    

	     if (strcmp(obj->IsA()->GetName(),"TClonesArray") == 0 ){
               TClass * cl = ((TClonesArray*) obj)->GetClass();
               if (!isMerging ) {
                  cout << "-I CbmRootManager: Adding class " 
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


	    
	  } else Fatal("CbmRootManager::AddAndMerge","No object found in Tree");
	    
	}//! branches        
       fListOfClones.Add( clist );	

      } else {
	Fatal(" CbmRootManager::AddAndMerge "," Branches inconsistency ");
      } 
      
      
    }else{ 
      Fatal(" CbmRootManager::AddAndMerge "," No merging of Analysis Output or inconsistent Nentries");   
    }  
   
  isMerging = kTRUE;    
  } else {
  isMerging = kFALSE;     
    Fatal(" CbmRootManager::AddAndMerge ","No Input File defined"); 

  }
 
}


//_____________________________________________________________________________
TFile *CbmRootManager::OpenOutFile(TFile* f)      
{

 fOutFile=f;
 if (fOutFile->IsZombie()) {
     cout << "-E- CbmRootManager: Error opening output file " << endl;
  exit(-1);
 }
  CbmRun* fRun = CbmRun::Instance();

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
TFile *CbmRootManager::OpenInFile(const char* fname, Bool_t Connect)
{
 
  if(fInFile) CloseInFile();
  fInFile = new TFile(fname);
  return OpenInFile(fInFile, Connect);
      
  
}
//_____________________________________________________________________________
TFile *CbmRootManager::OpenOutFile(const char* fname)
{
 
  if(fOutFile) CloseOutFile();
  fOutFile = new TFile(fname, "recreate");
  return OpenOutFile(fOutFile);
 
}
//_____________________________________________________________________________
CbmRootManager::~CbmRootManager() 
{
//
  if(fInFile) delete fInFile;
  if(fOutFile) {
        fOutFile->cd();
  //	fOutFile->Write();
  	delete fOutFile;
  }
  fgInstance = 0;
  delete fObj2;
}
//_____________________________________________________________________________
void  CbmRootManager::Register(const char* name, const char* folderName , TNamed *obj, Bool_t toFile)
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
   }else{
      AddActivatedBranch(name, obj );
   }
}

//_____________________________________________________________________________
void  CbmRootManager::Register(const char* name,const char* Foldername ,TCollection *obj, Bool_t toFile)
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
   }else{	/**Keep the Object in Memory, and do not write it to the tree*/
      AddActivatedBranch(name, obj );
   }	
}
 //_____________________________________________________________________________
void  CbmRootManager::Fill()
{
// Fills the tree.
// ---
  if(fOutTree!=0){
    fOutTree->Fill();
  }else{
      cout << "-E- CbmRootManager::Fill()  No Output Tree"  << endl;
  }
}  

//_____________________________________________________________________________
void CbmRootManager:: Write()
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
     cout << "-E- CbmRootManager::Write()  No Output Tree"  << endl;
  }
  
}

void CbmRootManager:: WriteGeometry()
{
// Writes the geometry in the file.
// ---

  if(fOutTree!=0){
    fOutFile = fOutTree->GetCurrentFile(); 
    fOutFile->cd();
    gGeoManager->Write();
  }

}
//_____________________________________________________________________________
void CbmRootManager:: WriteFolder()
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
void  CbmRootManager::ReadEvent(Int_t i)
{
// Reads the event data for i-th event for all connected branches.
// ---
    if (isMerging ) {

	cout << "-I CbmRootManager Readevent and merge:" << fListOfTrees.GetEntriesFast() << endl;
	for (Int_t j=0; j<fListOfTrees.GetEntriesFast(); j++ ) {
	    TTree * t = (TTree*) fListOfTrees.At(j);
	    t->GetEntry( i );
	}
	ReindexStack();
    }else{ 
	fInChain->GetEntry(i);
	CbmRunAna* fRun = CbmRunAna::Instance();
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
	    cout << "-I CbmRootManager: switching to chained file: " << cfilename <<  endl;
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

TObject * CbmRootManager::ActivateBranch(const char *BrName)
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
        fObj2[fNObj]  =  CheckActivatedBranch ( BrName );
      if ( fObj2[fNObj]   ){
          return  fObj2[fNObj];
      }
      for(Int_t i=0;i<listFolder.GetEntriesFast();i++){
	  TFolder *fold = (TFolder*) listFolder.At(i);
	  fObj2[fNObj] = fold->FindObjectAny(BrName);
	  if (fObj2[fNObj] ) break;
      }
      if(!fObj2[fNObj]){
	  cout << "-E- CbmRootManager Branch: "
	      << BrName  << " not found in Tree" << endl;
	  //	  Fatal(" No Branch in the tree", BrName );
	  return 0;
      } else {
	  fInChain->SetBranchStatus(BrName,1);
	  fInChain->SetBranchAddress(BrName,&fObj2[fNObj]);
      }
      AddActivatedBranch( BrName , fObj2[fNObj] );
      return  fObj2[fNObj];
  }
}
//_____________________________________________________________________________
TObject*  CbmRootManager::CheckActivatedBranch( const char* fName ) {
 
 //return fMap[BrName];
    TString BrName=fName;
  map < TString, TObject*>::iterator p;
  p=fMap.find(BrName);

  if(p!=fMap.end()){
	return p->second;
     //   cout << " -E- CbmRootManager::CheckActivatedBranch " << BrName << " is found " << endl;
  }else{
    //    cout << " -E- CbmRootManager::CheckActivatedBranch " << BrName << " Not found " << endl;
	return 0;
  }
}
//_____________________________________________________________________________
 TObject* CbmRootManager::GetObject(const char* BrName)
 {
 	TObject *Obj =NULL;
	Obj=GetRegisteredObject( BrName);

  	if(!Obj) {
		 Obj=ActivateBranch(BrName);
	// 	cout << "now ActivatedBranch "<<endl;
		 }
//	cout<< "CbmRootManager::GetObject will return  " << Obj <<" " << BrName
//	<<  endl;	 
	return Obj;
 }
//_____________________________________________________________________________

TObject* CbmRootManager::GetRegisteredObject(const char* BrName)
{
  TObject *Obj =NULL;
  if(cbmout) Obj = cbmout->FindObjectAny(BrName);
  if(!Obj){
	  Obj=CheckActivatedBranch(BrName);
  }
  if(!Obj){
	  Obj=cbmroot->FindObjectAny(BrName);
  }

  return Obj;
}
//_____________________________________________________________________________
TObject* CbmRootManager::GetMergedObject(const char* BrName)
{
  TObject *Obj =NULL;
  TString ObjName (BrName); 
  if ( ObjName.Contains("MCTrack") ) {
      return fMergedStack;
  }
  else {
    Obj = fListOfMergedClones.FindObject(BrName);     
    cout << " -I CbmRootManager Branch name " << BrName << " " << Obj << endl;
    return Obj;
  }

}
//_____________________________________________________________________________

void CbmRootManager::ReindexStack(){

  // Reset the Stack 
  fMergedStack->Reset();
  Int_t nStack = fListOfStack.GetEntriesFast(); 
  Int_t offset[nStack];
  Int_t n[nStack];
  Int_t i= 0; 
  
  // calculate offsets
  for (i=0;i<nStack;i++ ){offset[i]=n[i]=0;}    
  for (i=0;i<nStack;i++ ){    
    CbmGenericStack *st = (CbmGenericStack*) fListOfStack.At(i);
    n[i] = st->GetNtrack();
    if ( i == 0 ) offset[i] = 0 ; 
    if ( i == 1 ) offset[i] = n[i-1]; 
    if ( i>1 ) offset [i] = offset[i-1] + n[i-1]; 
  } 
  for (i=0; i<nStack; i++ ){
        CbmGenericStack *st = (CbmGenericStack*) fListOfStack.At(i);
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
void CbmRootManager::CopyClones(TClonesArray *cl1, TClonesArray* cl2 , Int_t offset ){

  // copy clone mechanism 
  TString str1( cl1->GetClass()->GetName() ); 
  TString str2( cl2->GetClass()->GetName() ); 
  // get clones
//  TClonesArray &particleRef = *cl2;
  CbmMCApplication *fcbm = CbmMCApplication::Instance(); 
    
//  Int_t i=0;
    // test name 
  if ( str1 != str2 ) Fatal("CbmRootManager::CopyClones"," inconsistency "); 

  // Sts 
  if ( (str1.Contains("CbmSTSDoublePoint") ) 
       || (str1.Contains("CbmSTSPoint") ) ) {
    // cout << " -I  CbmSTSDouble Point found at " << offset << " class " << str2 <<  endl; 
    // reindex the points 
    CbmDetector * sts = fcbm->GetDetector("STS");
    sts->CopyClones(cl1,cl2,offset);

  } 

 
  //Tof
  if ( str1.Contains("CbmTofPoint") ) {
    // cout << " -I  CbmSTSDouble Point found at " << offset << " class " << str2 <<  endl; 
    // reindex the points 
    CbmDetector * tof = fcbm->GetDetector("TOF");
    tof->CopyClones(cl1,cl2,offset);
  } 

  //Trd
  if ( str1.Contains("CbmTRDPoint") ) {
    // cout << " -I  CbmSTSDouble Point found at " << offset << " class " << str2 <<  endl; 
    // reindex the points 
    CbmDetector * trd = fcbm->GetDetector("TRD");
    trd->CopyClones(cl1,cl2,offset);
  } 


  //Rich
  if ( str1.Contains("CbmRichPoint") ) {
    // cout << " -I  CbmRichDouble Point found at " << offset << " class " << str2 <<  endl; 
    // reindex the points 
    CbmDetector * trd = fcbm->GetDetector("RICH");
    trd->CopyClones(cl1,cl2,offset);
  } 

}

//_____________________________________________________________________________
void  CbmRootManager::AddActivatedBranch( const char* fName, TObject* pObj ){
	
   map < TString, TObject*>::iterator p;
   TString BrName=fName;
   
   p=fMap.find(BrName);
   
   if(p!=fMap.end()){
       //  cout << " -E- CbmRootManager::AddActivatedBranch " << BrName << " is already inserted " << endl;
   }else{
      //  cout << " -E- CbmRootManager::AddActivatedBranch " << BrName << " isAdded " << endl;
   	fMap.insert(pair<TString, TObject*> (BrName, pObj));
   }

}

//_____________________________________________________________________________
CbmGeoNode*  CbmRootManager::GetGeoParameter(const char* detname, const char* gname){
 TFolder *detf= NULL;
    CbmGeoNode *node = NULL;
    TList *lgeo=NULL;
    TString lname(detname);
    lname+="GeoPar";
    TFolder *froot =  dynamic_cast<TFolder*> (gROOT->FindObject("cbmroot"));
    if ( froot )  detf = dynamic_cast<TFolder*> (froot->FindObjectAny( detname ));
    else cout << "-E- GetGeoParameter() Main Folder not found ! " << endl;
//    detf->ls();
    if ( detf    )  lgeo = dynamic_cast<TList*> (detf->FindObjectAny( lname.Data() ));
    else cout << "-E- GetGeoParameter() GeoPar: " << lname << endl;
    if ( lgeo    )  node = dynamic_cast<CbmGeoNode*> (lgeo->FindObject(gname));
    else cout << "-E- GetGeoParameter() GeoList not found " << endl;
    return node;

}

//_____________________________________________________________________________
void CbmRootManager::TranicateBranchNames(TTree *fTree, const char *folderName)
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
void CbmRootManager::TranicateBranchNames(TBranch *b, TString ffn)
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



ClassImp(CbmRootManager)







 
