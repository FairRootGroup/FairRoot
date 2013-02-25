#ifndef FAIR_ROOT_MANAGER_H
#define FAIR_ROOT_MANAGER_H

#include "TObject.h"
#include "TString.h"
#include "TArrayI.h"
#include "TObjArray.h"
#include "TFile.h"
#include "TChain.h"
#include <map>
#include <list>
#include <queue>

class FairGeoNode;
class FairFileHeader;
class FairMCEventHeader;
class FairEventHeader;
class FairFileHeader;
class FairLogger;
class FairTSBufferFunctional;
class BinaryFunctor;
class FairWriteoutBuffer;
class FairLink;
class TCollection;
class TClonesarray;
class TFolder;
class TTree;
class TNamed;
class TBranch;
class TList;
class TF1;


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
    void                AddSignalFile(TString name, UInt_t identifier );
    /**Add input background file by name*/
    void                AddBackgroundFile(TString name);
    void                AddFile(TString name);
    void                AddFriend(TString Name);
    void                AddFriendsToChain();

    Bool_t             AllDataProcessed();

    /**
    Check if Branch persistence or not (Memory branch)
    return value:
    1 : Branch is Persistance
    2 : Memory Branch
    0 : Branch does not exist   */
    Int_t               CheckBranch(const char* BrName);

    void                CloseInFile() { if(fInFile) { fInFile->Close(); }}

    void                CloseOutFile() { if(fOutFile) { fOutFile->Close(); }}
    /**Create a new file and save the current TGeoManager object to it*/
    void                CreateGeometryFile(const char* geofile);
    Bool_t              DataContainersEmpty();
    Bool_t              DataContainersFilled();
    void                Fill();
    void                ForceFill();
    void                LastFill();
    TClonesArray*       ForceGetDataContainer(TString branchName);
    TClonesArray*       GetEmptyTClonesArray(TString branchName);
    TClonesArray*       GetTClonesArray(TString branchName);
    TClonesArray*       GetDataContainer(TString branchName);
    /**Return branch name by Id*/
    TString             GetBranchName(Int_t id);
    /**Return Id of a branch named */
    Int_t               GetBranchId(TString BrName);
    /**Return a TList of TObjString of branch names */
    TList*              GetBranchNameList() {return fBranchNameList;}

    TTree*              GetInTree() {return fInChain->GetTree();}
    TChain*             GetInChain() {return fInChain;}
    TChain*             GetBGChain() { return  fBackgroundChain;}
    TChain*             GetSignalChainNo(UInt_t i);
    TTree*              GetOutTree() {return fOutTree;}
    TFile*              GetInFile() {return  fInFile;}
    TFile*              GetOutFile() {return  fOutFile;}
    /**  Get the Object (container) for the given branch name,
         this method can be used to access the data of
         a branch that was created from a different
         analysis task, and not written in the tree yet.
         the user have to cast this pointer to the right type.*/
    FairGeoNode*        GetGeoParameter(const char* detname, const char* gname);
    /** Return a pointer to the object (collection) saved in the fInChain branch named BrName*/
    TObject*            GetObject(const char* BrName);
    /** Return a pointer to the object (collection) saved in the fInTree branch named BrName*/
    TObject*            GetObjectFromInTree(const char* BrName);
    Double_t            GetEventTime();
    /** Returns a clone of the data object the link is pointing to. The clone has to be deleted in the calling code! */
    TObject*      GetCloneOfLinkData(const FairLink link);
    /** Get the data of the given branch name,
     *  this method runs over multiple entries
     *  of the tree and selects the data according
     *  to the function and the parameter given.
     */

    TClonesArray* GetCloneOfTClonesArray(const FairLink link);

    TClonesArray*     GetData(TString branchName, BinaryFunctor* function, Double_t parameter);
    TClonesArray*     GetData(TString branchName, BinaryFunctor* startFunction, Double_t startParameter, BinaryFunctor* stopFunction, Double_t stopParameter);
    void RegisterTSBuffer(TString branchName, FairTSBufferFunctional* functionalBuffer) {fTSBufferMap[branchName] = functionalBuffer;}
    FairTSBufferFunctional*   GetTSBuffer(TString branchName) {return fTSBufferMap[branchName];}

    /** static access method */
    static FairRootManager* Instance();

    Bool_t            OpenInChain();

    /** Open and prepare the input tree when running on PROOF worker*/
    Bool_t            OpenInTree();

    Bool_t            OpenBackgroundChain();
    Bool_t            OpenSignalChain();
    TFile*            OpenOutFile(const char* fname="cbmsim.root");
    TFile*            OpenOutFile(TFile* f);
    /**Read a single entry from background chain*/
    void                ReadBKEvent(Int_t i);
    void              ReadEvent(Int_t i);
    /**Read all entries from input tree(s) with time stamp from current time to dt (time in ns)*/
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

    TClonesArray*       Register(TString branchName, TString className, TString folderName, Bool_t toFile);
    /** Register a new PndWriteoutBuffer to the map. If a Buffer with the same map key already exists the given buffer will be deleted and the old will be returned!*/
    FairWriteoutBuffer* RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer);
    /**Use time stamps to read data and not tree entries*/
    void                RunWithTimeStamps() {fTimeStamps = kTRUE;}

    /**Set the input signal file
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file
     */
    void                  SetSignalFile(TString name, UInt_t identifier );
    /**Set the input background file by name*/
    void                  SetBackgroundFile(TString name);
    /**Add signal file to input
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file to which this signal should be added
     */

    /**Set the status of the EvtHeader
     *@param Status:  True: The header was creatged in this session and has to be filled
              FALSE: We use an existing header from previous data level
     */
    void                SetEvtHeaderNew(Bool_t Status) {fEvtHeaderIsNew = Status;}
    Bool_t              IsEvtHeaderNew() {return fEvtHeaderIsNew;}

    /**Set the branch name list*/
    void                SetBranchNameList(TList* list);
    void                SetCompressData(Bool_t val) {fCompressData = val;}
    /**Set the name of the input file*/
    void                SetInputFile(TString name);

    /**Set the input tree when running on PROOF worker*/
    void                SetInTree (TTree*  tempTree)  {fInTree = NULL; fInTree  = tempTree;}

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

    void                Write();
    /** Write the current TGeoManager to file*/
    void                WriteGeometry();
    /**Write the file header object to the output file*/
    void                WriteFileHeader(FairFileHeader* f);
    /**Write the folder structure used to create the tree to the output file */
    void                WriteFolder() ;
    /** Set the min and max limit for event time in ns */
    void                SetEventTimeInterval(Double_t min, Double_t max);
    /** Set the mean time for the event in ns */
    void                SetEventMeanTime(Double_t mean);
    void                SetEventTime();
    void                SetFileHeader(FairFileHeader* f) {fFileHeader =f;}

    /**Set the signal to background ratio in event units
    *@param background :  Number of background Events for one signal
    *@param Signalid :    Signal file Id, used when adding (setting) the signal file
    */
    void BGWindowWidthNo(UInt_t background, UInt_t Signalid);
    /**Set the signal to background rate in time units
    *@param background :  Time of background Events before one signal
    *@param Signalid :    Signal file Id, used when adding (setting) the signal file
    */
    void BGWindowWidthTime(Double_t background, UInt_t Signalid);

    /**Check the maximum event number we can run to*/
    Int_t  CheckMaxEventNo(Int_t EvtEnd=0);


    void        StoreWriteoutBufferData(Double_t eventTime);
    void        StoreAllWriteoutBufferData();
    void    DeleteOldWriteoutBufferData();

    Int_t GetEntryNr() {return fEntryNr;}
    void SetEntryNr(Int_t val) {fEntryNr = val;}

  private:
    /**private methods*/
    FairRootManager(const FairRootManager&);
    FairRootManager& operator=(const FairRootManager&);
    /**  Set the branch address for a given branch name and return
        a TObject pointer, the user have to cast this pointer to the right type.*/
    TObject*            ActivateBranch(const char* BrName);
    TObject*            ActivateBranchInInTree(const char* BrName);
    void                AddFriends( );
    /**Add a branch to memory, it will not be written to the output files*/
    void                AddMemoryBranch(const char*, TObject* );
    void                AssignTClonesArrays();
    void                AssignTClonesArray(TString branchName);
    /** Internal Check if Branch persistence or not (Memory branch)
    return value:
    1 : Branch is Persistance
    2 : Memory Branch
    0 : Branch does not exist
    */
    Int_t               CheckBranchSt(const char* BrName);
    void                CheckFriendChains();
    Bool_t              CompareBranchList(TFile* fileHandle, TString inputLevel);
    void                CreateNewFriendChain(TString inputFile, TString inputLevel);
    /**Create the Map for the branch persistency status  */
    void                CreatePerMap();
    TObject*            GetMemoryBranch( const char* );
    void                GetRunIdInfo(TString fileName, TString inputLevel);
    void                PrintFriendList();
    void                SaveAllContainers();
    /**Read a single entry*/
    void                ReadMixedEvent(Int_t i);
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
    /**Input file */
    TFile*                              fInFile;
    /**Input Chain */
    TChain*                             fInChain;
    /**Input Tree */
    TTree*                              fInTree;
    /**Output file */
    TFile*                              fOutFile;
    /**Output tree */
    TTree*                              fOutTree;
    /** list of folders from all input (and friends) files*/
    TObjArray                           fListFolder; //!
    TObject**                           fObj2; //!
    Int_t                               fNObj;//!
    std::map < TString , TObject* >     fMap;  //!
    TTree*                              fPtrTree;//!
    Int_t                               fCurrentEntries;//!
    /**Singleton instance*/
    static FairRootManager*             fgInstance;
    /**Branch id for this run */
    Int_t                               fBranchSeqId;
    /**List of branch names as TObjString*/
    TList*                               fBranchNameList; //!
    /** Internally used to compress empty slots in data buffer*/
    std::map<TString, std::queue<TClonesArray*> > fDataContainer;
    /** Internally used to compress empty slots in data buffer*/
    std::map<TString, TClonesArray*> fActiveContainer;
    /** Internally used to read time ordered data from branches*/
    std::map<TString, FairTSBufferFunctional*> fTSBufferMap; //!
    std::map<TString, FairWriteoutBuffer* > fWriteoutBufferMap; //!
    std::map<Int_t, TBranch*> fInputBranchMap; //!    //Map of input branch ID with TBranch pointer

    /** if kTRUE the entries of a branch are filled from the beginning --> no empty entries*/
    Bool_t                              fCompressData;
    /**if kTRUE Read data according to time and not entries*/
    Bool_t                              fTimeStamps;
    /**Flag for creation of Map for branch persistency list  */
    Bool_t                              fBranchPerMap;
    /** Map for branch persistency list */
    std::map < TString , Int_t >        fBrPerMap; //!
    /**Iterator for the fBrPerMap  Map*/
    std::map < TString, Int_t>::iterator     fBrPerMapIter;
    /** List of all files added with AddFriend */
    std::list<TString>                      fFriendFileList; //!

    TString                             fInputFileName; //!
    std::list<TString>                  fInputChainList;//!
    std::map<TString, TChain*>          fFriendTypeList;//!

    std::map<TString, std::list<TString>* > fCheckInputBranches; //!
    std::list<TString>                      fInputLevel; //!
    std::map<TString, std::multimap<TString, TArrayI> > fRunIdInfoAll; //!

    FairLogger*                         fLogger;//!
    /**True if signal and background mixing is used*/
    Bool_t                              fMixedInput;//!
    /**Actual identifier of the added signals, this is used to identify how many signals are added*/
    UInt_t                              fActualSignalIdentifier; //!
    /** Total number of signals added (Types and not files!)*/
    UInt_t                              fNoOfSignals; //!
    /** list of chains which has to be created for the different signals*/
    std::list<TString>*                  fSignalChainList; //!
    /**Chain containing the background*/
    TChain*                              fBackgroundChain; //!
    TFile*                               fBackgroundFile; //!
    std::map<UInt_t, TChain*>            fSignalTypeList;//!

    /** min time for one event (ns) */
    Double_t                                fEventTimeMin;  //!
    /** max time for one Event (ns) */
    Double_t                                fEventTimeMax;  //!
    /** Time of event since th start (ns) */
    Double_t                                fEventTime;     //!
    /** EventMean time used (P(t)=1/fEventMeanTime*Exp(-t/fEventMeanTime) */
    Double_t                                fEventMeanTime; //!
    /** used to generate random numbers for event time; */
    TF1*                                    fTimeProb;      //!
    /** MC Event header */
    FairMCEventHeader*                      fMCHeader; //!

    /**Event Header*/
    FairEventHeader*                        fEvtHeader; //!

    /**File Header*/
    FairFileHeader*                        fFileHeader; //!

    /**holds the SB ratio by number*/
    std::map<UInt_t, Double_t>              fSignalBGN;//!
    /** This is true if the event time used, came from simulation*/
    Bool_t                                  fEventTimeInMCHeader; //!
    /**True for background window in entry units*/
    Bool_t                                  fSBRatiobyN;  //!
    /**True for background window in time units (ns) */
    Bool_t                                  fSBRatiobyT;  //!
    /** for internal use, to return the same event time for the same entry*/
    UInt_t                                  fCurrentEntryNo; //!
    /** for internal use, to return the same event time for the same entry*/
    UInt_t                                  fTimeforEntryNo; //!
    /**No of entries in BG Chain*/
    UInt_t                                  fNoOfBGEntries; //!
    /**Hold the current entry for each input chain*/
    std::map<UInt_t, UInt_t>                fCurrentEntry; //!
    /**This flag is true if the event header was created in this session
    * otherwise it is false which means the header was created in a previous data
    * level and used here (e.g. in the digi)
    */
    Bool_t      fEvtHeaderIsNew; //!
    Bool_t  fFillLastData; //!
    Int_t fEntryNr; //!


    ClassDef(FairRootManager,7) // Root IO manager
};



#endif //FAIR_ROOT_MANAGER_H   


