#ifndef FAIR_ROOT_MANAGER_H
#define FAIR_ROOT_MANAGER_H
#include "TObject.h"
#include "TString.h"
#include "TFile.h"
#include "TChain.h"
#include <map>

class FairGeoNode;
class FairGenericStack;
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
    void                AddAndMerge( TFile *f ); 
    void                CloseInFile() { if(fInFile)fInFile->Close();} 
    void                CloseOutFile() { if(fOutFile)fOutFile->Close();} 
    void                Fill();
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
    /**
       create a new branch in the output tree
    */
    void                Register(const char* name, const char* Foldername, TNamed * obj, Bool_t toFile);
    void                Register(const char* name,const char* Foldername ,TCollection *obj, Bool_t toFile);
    TObject*		    GetObject(const char* BrName);
    void                SetOutTree(TTree *fTree){ fOutTree=fTree;}
    void                Write();
    void                WriteGeometry();
    void                CopyClones(TClonesArray* cl1, TClonesArray* cl2, Int_t offset ); 
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
	void                SetBranchNameList(TList *list);
		
private:
	/**private methods*/
	FairRootManager(const FairRootManager &F);
    FairRootManager& operator= (const FairRootManager&) {return *this;}
	TObject*            GetMergedObject(const char* BrName) ;     
	void                ReindexStack(); 
	void                AddMemoryBranch(const char*, TObject* );
	TObject*            GetMemoryBranch( const char* );   
	/**Members*/ 
	TFolder*                            cbmout;     /**folder structure of output*/
	TFolder*                            cbmroot;    /**folder structure of input*/
	TFile*                              fInFile;    /**Input file */
	TChain*                             fInChain;    /**Input Tree */ 
	TFile*                              fOutFile;   /**Output file */
	TTree*                              fOutTree;   /**Output tree */
	TObjArray                           listFolder; //!
	TObjArray                           fListOfTrees; //!
	TObjArray                           fListOfClones; //!
	TObjArray                           fListOfStack; //!
	Bool_t                              isMerging; //! 
	FairGenericStack*                   fMergedStack; //!
	TObjArray                           fListOfMergedClones; //!
	TObject**                           fObj2; //!
	Int_t                               fNObj;//!
	std::map < TString , TObject * >    fMap; //!
	TTree*                              tmpPtrTree;//!
	TTree*                              fPtrTree;//!
	Int_t                               fCurrentEntries;//!
	static FairRootManager*             fgInstance; /**Singleton instance*/
	Int_t                               fBranchSeqId; /**Branch id for this run */
	TList                               *fBranchNameList; //! /**List of branch names as TObjString*/
	ClassDef(FairRootManager,1) // Root IO manager
};



#endif //FAIR_ROOT_MANAGER_H   
   

