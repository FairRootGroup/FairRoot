/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIR_ROOT_MANAGER_H
#define FAIR_ROOT_MANAGER_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Bool_t, Int_t, UInt_t, etc
#include "TChain.h"                     // for TChain
#include "TFile.h"                      // for TFile
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString, operator<
#include "TMCtls.h"                     // for multi-threading

#include <stddef.h>                     // for NULL
#include <list>                         // for list
#include <map>                          // for map, multimap, etc
#include <queue>                        // for queue
#include "FairSource.h"
class BinaryFunctor;
class FairEventHeader;
class FairFileHeader;
class FairGeoNode;
class FairLink;
class FairLogger;
class FairTSBufferFunctional;
class FairWriteoutBuffer;
class TArrayI;
class TBranch;
class TClonesArray;
class TCollection;
class TF1;
class TFolder;
class TList;
class TNamed;
class TTree;
class TRefArray;
class TIterator;

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
    /**ctor*/
    FairRootManager();
    /**dtor*/
    virtual ~FairRootManager();
     Bool_t             AllDataProcessed();
    /** Add a branch name to the Branchlist and give it an id*/
    Int_t AddBranchToList(const char* name);
    /**
    Check if Branch persistence or not (Memory branch)
    return value:
    1 : Branch is Persistance
    2 : Memory Branch
    0 : Branch does not exist   */
    Int_t               CheckBranch(const char* BrName);

    
    void                CloseOutFile() { if(fOutFile) { fOutFile->Close(); }}
    /**Create a new file and save the current TGeoManager object to it*/
    void                CreateGeometryFile(const char* geofile);
    void                Fill();
    void                LastFill();
    TClonesArray*       GetEmptyTClonesArray(TString branchName);
    TClonesArray*       GetTClonesArray(TString branchName);
    /**Update the list of Memory branches from the source used*/
    void                UpdateBranches();

    /**Return branch name by Id*/
    TString             GetBranchName(Int_t id);
    /**Return Id of a branch named */
    Int_t               GetBranchId(TString BrName);
    /**Return a TList of TObjString of branch names available in this session*/
    TList*              GetBranchNameList() {return fBranchNameList;}
    /** Return a pointer to the output Tree of type TTree */
    TTree*              GetOutTree() {return fOutTree;}
    /** Return a pointer to the output File of type TFile */
    TFile*              GetOutFile() {return  fOutFile;}
    /**  Get the Object (container) for the given branch name,
         this method can be used to access the data of
         a branch that was created from a different
         analysis task, and not written in the tree yet.
         the user have to cast this pointer to the right type.
         Return a pointer to the object (collection) saved in the fInChain branch named BrName*/
    TObject*            GetObject(const char* BrName);
    /** Return a pointer to the object (collection) saved in the fInTree branch named BrName*/
    Double_t            GetEventTime();
    /** Returns a clone of the data object the link is pointing to. The clone has to be deleted in the calling code! */
    TObject*      GetCloneOfLinkData(const FairLink link);
    /** Get the data of the given branch name,
     *  this method runs over multiple entries
     *  of the tree and selects the data according
     *  to the function and the parameter given.
     */

    TClonesArray* GetCloneOfTClonesArray(const FairLink link);

    void InitTSBuffer(TString branchName, BinaryFunctor* function);
    TClonesArray*     GetData(TString branchName, BinaryFunctor* function, Double_t parameter);
    TClonesArray*     GetData(TString branchName, BinaryFunctor* startFunction, Double_t startParameter, BinaryFunctor* stopFunction, Double_t stopParameter);
    void RegisterTSBuffer(TString branchName, FairTSBufferFunctional* functionalBuffer) {fTSBufferMap[branchName] = functionalBuffer;}
    void TerminateTSBuffer(TString branchName);
    void TerminateAllTSBuffer();
    FairTSBufferFunctional*   GetTSBuffer(TString branchName) {return fTSBufferMap[branchName];}

    /** static access method */
    static FairRootManager* Instance();

    TFile*            OpenOutFile(const char* fname="cbmsim.root");
    TFile*            OpenOutFile(TFile* f);
    /**Read a single entry from background chain*/
    Int_t             ReadEvent(Int_t i=0);
    /** Read a single entry from each branch that is not read via TSBuffers*/
    Int_t             ReadNonTimeBasedEventFromBranches(Int_t i=0);
    /**Read the tree entry on one branch**/
    void              ReadBranchEvent(const char* BrName);
    /**Read all entries from input tree(s) with time stamp from current time to dt (time in ns)*/

    Int_t             GetRunId();

    Bool_t            ReadNextEvent(Double_t dt);
    /**create a new branch in the output tree
     *@param name            Name of the branch to create
     *@param Foldername      Folder name containing this branch (e.g Detector name)
     *@param obj             Pointer of type TNamed (e.g. MCStack object)
     *@param toFile          if kTRUE, branch will be saved to the tree*/
    void                Register(const char* name, const char* Foldername, TNamed* obj, Bool_t toFile);
    /**create a new branch in the output tree
    *@param name            Name of the branch to create
    *@param Foldername      Folder name containing this branch (e.g Detector name)
    *@param obj             Pointer of type TCollection (e.g. TClonesArray of hits, points)
    *@param toFile          if kTRUE, branch will be saved to the tree*/
    void                Register(const char* name,const char* Foldername ,TCollection* obj, Bool_t toFile);

    void                RegisterInputObject(const char* name, TObject* obj);

    TClonesArray*       Register(TString branchName, TString className, TString folderName, Bool_t toFile);
    /** Register a new FairWriteoutBuffer to the map. If a Buffer with the same map key already exists the given buffer will be deleted and the old will be returned!*/
    FairWriteoutBuffer* RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer);
    /**Update the list of time based branches in the output file*/
    void                UpdateListOfTimebasedBranches();
    /**Use time stamps to read data and not tree entries*/
    void                RunWithTimeStamps() {fTimeStamps = kTRUE;}

    /**Set the branch name list*/
    void                SetBranchNameList(TList* list);
    /** Replace the time based branch name list*/
    void SetTimeBasedBranchNameList(TList *list);
  
    void                FillEventHeader(FairEventHeader* feh) { if ( fSource ) fSource->FillEventHeader(feh); } 
   
    /**Set the output tree pointer*/
    void                SetOutTree(TTree* fTree) { fOutTree=fTree;}

    /**Enables a last Fill command after all events are processed to store any data which is still in Buffers*/
    void        SetLastFill(Bool_t val = kTRUE) { fFillLastData=val;}
    /**When creating TTree from TFolder the fullpath of the objects is used as branch names
     * this method truncate the full path from the branch names
    */
    void                TruncateBranchNames(TBranch* b, TString ffn);
    /**When creating TTree from TFolder the fullpath of the objects is used as branch names
     * this method truncate the full path from the branch names
    */
    void                TruncateBranchNames(TTree* fTree, const char* folderName);

    Int_t               Write(const char* name=0, Int_t option=0, Int_t bufsize=0);
    /** Write the current TGeoManager to file*/
    void                WriteGeometry();
    /**Write the file header object to the output file*/
    void                WriteFileHeader(FairFileHeader* f);
    /**Write the folder structure used to create the tree to the output file */
    void                WriteFolder() ;

    /**Check the maximum event number we can run to*/
    Int_t  CheckMaxEventNo(Int_t EvtEnd=0);


    void        StoreWriteoutBufferData(Double_t eventTime);
    void        StoreAllWriteoutBufferData();
    void    DeleteOldWriteoutBufferData();

    Int_t GetEntryNr() {return fEntryNr;}
    void SetEntryNr(Int_t val) {fEntryNr = val;}

    void SetUseFairLinks(Bool_t val) {fUseFairLinks = val;};
    Bool_t GetUseFairLinks() const {return fUseFairLinks;};

    /**
     * @param Status : if  true all inputs are mixed, i.e: each read event will take one entry from each input and put
     * them in one big event and send it to the next step
     */
    /* void SetMixAllInputs(Bool_t Status) { */
    /*    fMixAllInputs=kTRUE; */
    /* } */
   
    
    /** These methods have been moved to the FairFileSource */
    void   SetSource(FairSource* tempSource) { fSource = tempSource; }    
    FairSource* GetSource() { return fSource;}
    Bool_t InitSource();
    
    void                SetListOfFolders(TObjArray* ta){ fListFolder=ta; }
    TChain*             GetInChain ()                  { return fSourceChain;}
    TChain*             GetSignalChainNo(UInt_t i)     { return fSignalChainList[i]; }
    TTree*              GetInTree  ()                  { if ( fSourceChain ) return fSourceChain->GetTree(); return 0; }
    const TFile*        GetRootFile()                  { if ( fSourceChain ) return fSourceChain->GetFile(); return 0; }
    TFile*              GetInFile  ()                  { if ( fSourceChain ) return fSourceChain->GetFile(); return 0; }
    void                SetInChain (TChain* tempChain, Int_t ident=-1);
    /* /\**Set the input tree when running on PROOF worker*\/ */

    void SetFinishRun(Bool_t val = kTRUE){ fFinishRun = val;}
    Bool_t FinishRun() {return fFinishRun;}

    static char* GetTreeName();
  private:
    /**private methods*/
    FairRootManager(const FairRootManager&);
    FairRootManager& operator=(const FairRootManager&);
    /**  Set the branch address for a given branch name and return
        a TObject pointer, the user have to cast this pointer to the right type.*/
    TObject*            ActivateBranch(const char* BrName);
    void                AddFriends( );
    /**Add a branch to memory, it will not be written to the output files*/
    void                AddMemoryBranch(const char*, TObject* );
    /** Internal Check if Branch persistence or not (Memory branch)
    return value:
    1 : Branch is Persistance
    2 : Memory Branch
    0 : Branch does not exist
    */
    Int_t               CheckBranchSt(const char* BrName);
        /**Create the Map for the branch persistency status  */
    void                CreatePerMap();
    TObject*            GetMemoryBranch( const char* );
 //   void                GetRunIdInfo(TString fileName, TString inputLevel);

    FairWriteoutBuffer* GetWriteoutBuffer(TString branchName);


    Int_t       fOldEntryNr;
//_____________________________________________________________________
    /**private Members*/
    /**folder structure of output*/
    TFolder*                            fCbmout;
    /**folder structure of input*/
    TFolder*                            fCbmroot;
    /** current time in ns*/
    Double_t                            fCurrentTime;
    /**Output file */
    TFile*                              fOutFile;
    /**Output tree */
    TTree*                              fOutTree;
    TObject**                           fObj2; //!
    /** Counter for the number of branches activiated */
    Int_t                               fNObj;//!
    /** A list which hold the pointer to the branch 
     * and the name of the branch in memory, it contains all branches (TClonesArrays)
     * persistance and Memory only branches
     */
    std::map < TString , TObject* >     fMap;  //!

    /**Singleton instance*/
#if !defined(__CINT__)
    static TMCThreadLocal FairRootManager*  fgInstance;
#else
    static                FairRootManager*  fgInstance;
#endif

    /**Branch id for this run */
    Int_t                               fBranchSeqId;
    /**List of branch names as TObjString*/
    TList*                               fBranchNameList; //!
    /**List of Time based branchs names as TObjString*/
    TList*                               fTimeBasedBranchNameList; //!
    /** Internally used to compress empty slots in data buffer*/
    std::map<TString, TClonesArray*> fActiveContainer;
    /** Internally used to read time ordered data from branches*/
    std::map<TString, FairTSBufferFunctional*> fTSBufferMap; //!
    std::map<TString, FairWriteoutBuffer* > fWriteoutBufferMap; //!
    std::map<Int_t, TBranch*> fInputBranchMap; //!    //Map of input branch ID with TBranch pointer
    /**if kTRUE Read data according to time and not entries*/
    Bool_t                              fTimeStamps;
    /**Flag for creation of Map for branch persistency list  */
    Bool_t                              fBranchPerMap;
    /** Map for branch persistency list */
    std::map < TString , Int_t >        fBrPerMap; //!
    /**Iterator for the fBrPerMap  Map*/
    std::map < TString, Int_t>::iterator     fBrPerMapIter;
 
    /** for internal use, to return the same event time for the same entry*/
    UInt_t                                  fCurrentEntryNo; //!
    /** for internal use, to return the same event time for the same entry*/
    UInt_t                                  fTimeforEntryNo; //!
    Bool_t  fFillLastData; //!
    Int_t fEntryNr; //!

    TObjArray                           *fListFolder; //!

    FairSource                          *fSource;

    TChain                              *fSourceChain;
    std::map<UInt_t, TChain*>            fSignalChainList;//!

    FairEventHeader                     *fEventHeader;
    
    Bool_t fUseFairLinks; //!
    Bool_t fFinishRun; //!
    /** List of branches from input Chain or Tree*/
    TObjArray* fListOfBranchesFromInput; //!
    /** Iterator for the list of branches from input Chain or Tree */
    TIterator* fListOfBranchesFromInputIter;//!
    /** List of branches used with no-time stamp in time-based session */
    TRefArray* fListOfNonTimebasedBranches; //!
    /** Iterator for the list of branches used with no-time stamp in time-based session */
    TIterator* fListOfNonTimebasedBranchesIter; //!

    ClassDef(FairRootManager,11) // Root IO manager
};


#endif //FAIR_ROOT_MANAGER_H   


