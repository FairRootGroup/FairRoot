#ifndef FAIR_ROOT_MANAGER_H
#define FAIR_ROOT_MANAGER_H
#include "TObject.h"
#include "TString.h"
#include "TFile.h"
#include "TChain.h"
#include <map>
#include <queue>

class FairGeoNode;
class TCollection;
class TClonesarray;
class TFolder;
class TTree;
class TNamed;
class TBranch;
class TList;

/**
 * I/O Manager class
 * @author M. Al-Turany, Denis Bertini
 * @version 0.1
 * @since 12.01.04
 */

//_____________________________________________________________________

class FairRootManager : public TObject
{
  public:
    FairRootManager();
    virtual ~FairRootManager();     
    // static access method
    static FairRootManager* Instance(); 
    // methods
    /**  Set the branch address for a given branch name and return
         a TObject pointer, the user have to cast this pointer to the right type.
    */
    TObject*            ActivateBranch(const char *BrName);
    void                AddFriend( TFile *f );      
    void                CloseInFile() { if(fInFile)fInFile->Close();} 
    void                CloseOutFile() { if(fOutFile)fOutFile->Close();} 
    void                Fill();
    void				ForceFill();
    TList*              GetBranchNameList(){return fBranchNameList;}
    TTree*              GetInTree(){return fInChain->GetTree();}
    TChain*             GetInChain(){return fInChain;}
    TTree*              GetOutTree(){return fOutTree;}
    TFile*              GetInFile(){return  fInFile;}
    TFile*              GetOutFile(){return  fOutFile;}
    /**
      Get the Object (container) for the given branch name,
      this method can be used to access the data of
      a branch that was created from a different
      analysis task, and not written in the tree yet.
      the user have to cast this pointer to the right type.
    */
    FairGeoNode*        GetGeoParameter(const char* detname, const char* gname);
   /**
   Check if Branch persistence or not (Memory branch)
   return value:
   1 : Branch is Persistance
   2 : Memory Branch
   0 : Branch does not exist
   */
   Int_t               CheckBranch(const char* BrName);
   TFile*              OpenInFile(const char* fname="cbmsim.root", Bool_t Connect=kFALSE);
   TFile*              OpenInFile(TFile *f, Bool_t Connect=kFALSE);
   TFile*              OpenOutFile(const char*fname="cbmsim.root");
   TFile*              OpenOutFile(TFile *f);
   void                ReadEvent(Int_t i);
   /**Read all entries from input tree(s) with time stamp from current time to dt (time in ns)*/
   Bool_t              ReadNextEvent(Double_t dt);
   /**create a new branch in the output tree
    *@param name            Name of the branch to create
    *@param Foldername      Folder name containing this branch (e.g Detector name)
    *@param obj             Pointer of type TNamed (e.g. MCStack object)   
    *@param toFile          if kTRUE, branch will be saved to the tree
   */
   void                Register(const char* name, const char* Foldername, TNamed * obj, Bool_t toFile);
     /**create a new branch in the output tree
    *@param name            Name of the branch to create
    *@param Foldername      Folder name containing this branch (e.g Detector name)
    *@param obj             Pointer of type TCollection (e.g. TClonesArray of hits, points)   
    *@param toFile          if kTRUE, branch will be saved to the tree
   */
   void                Register(const char* name,const char* Foldername ,TCollection *obj, Bool_t toFile);

   TClonesArray*		Register(TString branchName, TString className, TString folderName, Bool_t toFile);
   /** Return a pointer to the object (collection) saved in the branch named BrName*/
   TObject*   GetObject(const char* BrName);
  
   void                SetOutTree(TTree *fTree){ fOutTree=fTree;}
   void                Write();
   void                WriteGeometry();
 //  void                CopyClones(TClonesArray* cl1, TClonesArray* cl2, Int_t offset ); 
   void                WriteFolder() ;
   void                AddFile(TString name);
   void                SetWildcard(TString Wildcard);
   void                TranicateBranchNames(TBranch *b, TString ffn);
   void                TranicateBranchNames(TTree *fTree, const char *folderName);
   void                CreateGeometryFile(const char *geofile);
   /**Return branch name by Id*/
   TString             GetBranchName(Int_t id);
   /**Return Id of a branch named */
   Int_t               GetBranchId(TString BrName);
   /**Use time stamps to read data and not tree entries*/
   void                RunWithTimeStamps(){fTimeStamps = kTRUE;}	
   /**Set the branch name list*/
   void                SetBranchNameList(TList *list);

   void			SetCompressData(Bool_t val){fCompressData = val;}

   TClonesArray* GetTClonesArray(TString branchName);
   TClonesArray* GetDataContainer(TString branchName);
   TClonesArray* ForceGetDataContainer(TString branchName);

   Bool_t  DataContainersEmpty(){
	   for(std::map<TString, std::queue<TClonesArray*> >::iterator it = fDataContainer.begin(); it != fDataContainer.end(); it++){
	   		   if (it->second.empty() == false){
	   			   return kFALSE;
	   		   }
	   	   }
	   	   return kTRUE;
   }

   Bool_t	DataContainersFilled(){
	   for(std::map<TString, std::queue<TClonesArray*> >::iterator it = fDataContainer.begin(); it != fDataContainer.end(); it++){
		   if (it->second.empty() == true)
			   return kFALSE;
	   }
	   return kTRUE;
   }
		
private:
   /**private methods*/
   FairRootManager(const FairRootManager &F);
   FairRootManager& operator= (const FairRootManager&) {return *this;}
   /**Add a branch to memory, it will not be written to the output files*/
   void                AddMemoryBranch(const char*, TObject* );

   TObject*            GetMemoryBranch( const char* );


   void	 AssignTClonesArrays();
   void	 AssignTClonesArray(TString branchName);
   void SaveAllContainers();
  
   /** Internal Check if Branch persistence or not (Memory branch)
   return value:
   1 : Branch is Persistance
   2 : Memory Branch
   0 : Branch does not exist
   */
   Int_t               CheckBranchSt(const char* BrName);
   /**Create the Map for the branch persistency status  */
   void                CreatePerMap();

   /**Members*/ 


   /**folder structure of output*/
   TFolder*                            fCbmout;     
   /**folder structure of input*/
   TFolder*                            fCbmroot;
   /** current time in ns*/
   Double_t                            fCurrentTime;
   /**Input file */
   TFile*                              fInFile;   
   /**Input Tree */ 
   TChain*                             fInChain;  
   /**Output file */
   TFile*                              fOutFile;  
   /**Output tree */
   TTree*                              fOutTree;  
   /** list of folders from all input (and friends) files*/
   TObjArray                           fListFolder; //!
  
   TObject**                           fObj2; //!

   Int_t                               fNObj;//!

   std::map < TString , TObject * >    fMap; //!
 
   TTree*                              fPtrTree;//!

   Int_t                               fCurrentEntries;//!
   /**Singleton instance*/
   static FairRootManager*             fgInstance; 
   /**Branch id for this run */
   Int_t                               fBranchSeqId; 
   /**List of branch names as TObjString*/
   TList                               *fBranchNameList; //!

   std::map<TString, std::queue<TClonesArray*> > fDataContainer;
   std::map<TString, TClonesArray*> fActiveContainer;

   /** if kTRUE the entries of a branch are filled from the beginning --> no empty entries*/
   Bool_t								fCompressData;

   /**if kTRUE Read data according to time and not entries*/
   Bool_t                              fTimeStamps;
   /**Flag for creation of Map for branch persistency list  */
   Bool_t                              fBranchPerMap; 
   /** Map for branch persistency list */
   std::map < TString , Int_t >        fBrPerMap; //!
   /**Iterator for the fBrPerMap  Map*/
   std::map < TString, Int_t>::iterator     fBrPerMapIter;


   ClassDef(FairRootManager,3) // Root IO manager
};



#endif //FAIR_ROOT_MANAGER_H   
   

