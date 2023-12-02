/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIR_ROOT_MANAGER_H
#define FAIR_ROOT_MANAGER_H

#include "FairMemory.h"
#include "FairSink.h"
#include "FairSource.h"

#include <Rtypes.h>      // for Bool_t, Int_t, UInt_t, etc
#include <TChain.h>      // for TChain
#include <TObject.h>     // for TObject
#include <TRefArray.h>   // for TRefArray
#include <TString.h>     // for TString, operator<
#include <fairlogger/Logger.h>
#include <list>
#include <map>   // for map, multimap, etc
#include <memory>
#include <string>
#include <type_traits>   // is_pointer, remove_pointer, is_const, remove...
#include <typeinfo>

class BinaryFunctor;
class FairEventHeader;
class FairFileHeader;
class FairLink;
class FairTSBufferFunctional;
class FairWriteoutBuffer;
class TBranch;
class TClonesArray;
class TObjArray;
class TCollection;
class TFile;
class TFolder;
class TList;
class TNamed;
class TTree;

/**
 * I/O Manager class
 * \ingroup base_steer
 * @author M. Al-Turany, Denis Bertini
 * @version 0.1
 * @since 12.01.04
 */

class FairRootManager : public TObject
{
    friend class FairRun;

  public:
    /**dtor*/
    ~FairRootManager() override;
    Bool_t AllDataProcessed();
    /** Add a branch name to the Branchlist and give it an id*/
    Int_t AddBranchToList(const char* name);
    /**
    Check if Branch persistence or not (Memory branch)
    return value:
    1 : Branch is Persistance
    2 : Memory Branch
    0 : Branch does not exist   */
    Int_t CheckBranch(const char* BrName);

    void CloseSink()
    {
        if (fSink != nullptr) {
            fSink->Close();
        }
    }
    /**Create a new file and save the current TGeoManager object to it*/
    void CreateGeometryFile(const char* geofile);
    void Fill();
    void LastFill();
    TClonesArray* GetEmptyTClonesArray(TString branchName);
    TClonesArray* GetTClonesArray(TString branchName);
    /**Update the list of Memory branches from the source used*/
    void UpdateBranches();

    /**Return branch name by Id*/
    TString GetBranchName(Int_t id);
    /**Return Id of a branch named */
    Int_t GetBranchId(TString const& BrName);

    /**The MCTrack branch stands out since it is required by the framework algorithms**/
    Int_t GetMCTrackBranchId() const { return fMCTrackBranchId; }

    /**Return a TList of TObjString of branch names available in this session*/
    TList* GetBranchNameList() { return &fBranchNameList; }

    /**  Get the Object (container) for the given branch name,
         this method can be used to access the data of
         a branch that was created from a different
         analysis task, and not written in the tree yet.
         the user have to cast this pointer to the right type.
         Returns a non-owning pointer to the found object
         or nullptr if none found*/
    TObject* GetObject(const char* BrName);

    /// Initializes and returns a default object for a branch or looks it up when it exists already.
    /// Returns nullptr when the branch does not exist or looking up with wrong type.
    /// The name Init indicates that this functions should be called only in Init sections of FairTasks.
    /// The returned default object will be filled with data by the framework.
    template<typename T>
    T InitObjectAs(const char* BrName);

    /** Return a pointer to the object (collection) saved in the fInTree branch named BrName*/
    Double_t GetEventTime();
    /** Returns a clone of the data object the link is pointing to. The clone has to be deleted in the calling code! */
    TObject* GetCloneOfLinkData(const FairLink link);
    /** Get the data of the given branch name,
     *  this method runs over multiple entries
     *  of the tree and selects the data according
     *  to the function and the parameter given.
     */

    TClonesArray* GetCloneOfTClonesArray(const FairLink link);

    void InitTSBuffer(TString branchName, BinaryFunctor* function);
    TClonesArray* GetData(TString branchName, BinaryFunctor* function, Double_t parameter);
    TClonesArray* GetData(TString branchName,
                          BinaryFunctor* startFunction,
                          Double_t startParameter,
                          BinaryFunctor* stopFunction,
                          Double_t stopParameter);
    void RegisterTSBuffer(TString branchName, FairTSBufferFunctional* functionalBuffer)
    {
        fTSBufferMap[branchName] = functionalBuffer;
    }
    void TerminateTSBuffer(TString branchName);
    void TerminateAllTSBuffer();
    FairTSBufferFunctional* GetTSBuffer(TString branchName) { return fTSBufferMap[branchName]; }

    /**
     * \brief Access the singleton
     *
     * Please try avoid using it.
     * It will likely be deprecated at some point.
     * Consider using a getter instead:
     *
     * - FairRun::GetRootManager()
     * - FairDetector::GetRootManager()
     * - FairEventManager::GetRootManager()
     */
    static FairRootManager* Instance();

    /**Read a single entry from background chain*/
    Int_t ReadEvent(const Int_t i = 0);
    /** Read a single entry from each branch that is not read via TSBuffers*/
    Int_t ReadNonTimeBasedEventFromBranches(Int_t i = 0);
    /**Read the tree entry on one branch**/
    void ReadBranchEvent(const char* BrName);
    /**Read the tree entry on one branch for a specific entry**/
    void ReadBranchEvent(const char* BrName, Int_t entry);

    /**Read all entries from input tree(s) with time stamp from current time to dt (time in ns)*/

    Int_t GetRunId();

    Bool_t ReadNextEvent(Double_t dt);
    /**create a new branch in the output tree
     *@param name            Name of the branch to create
     *@param Foldername      Folder name containing this branch (e.g Detector name)
     *@param obj             Pointer of type TNamed (e.g. MCStack object)
     *@param toFile          if kTRUE, branch will be saved to the tree*/
    void Register(const char* name, const char* Foldername, TNamed* obj, Bool_t toFile);
    /**create a new branch in the output tree
     *@param name            Name of the branch to create
     *@param Foldername      Folder name containing this branch (e.g Detector name)
     *@param obj             Pointer of type TCollection (e.g. TClonesArray of hits, points)
     *@param toFile          if kTRUE, branch will be saved to the tree*/
    void Register(const char* name, const char* Foldername, TCollection* obj, Bool_t toFile);

    /** create a new branch based on an arbitrary type T (for which a dictionary must exist) **/
    template<typename T>
    void RegisterAny(const char* name, T*& obj, Bool_t toFile);

    void RegisterInputObject(const char* name, TObject* obj);

    TClonesArray* Register(TString branchName, TString className, TString folderName, Bool_t toFile);
    /** Register a new FairWriteoutBuffer to the map. If a Buffer with the same map key already exists the given buffer
     * will be deleted and the old will be returned!*/
    FairWriteoutBuffer* RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer);
    /**Update the list of time based branches in the output file*/
    void UpdateListOfTimebasedBranches();
    /**Use time stamps to read data and not tree entries
     * \deprecated Deprecated in v18.8, will be removed in v20.
     */
    [[deprecated]] void RunWithTimeStamps() {}

    /**Set the branch name list*/
    void SetBranchNameList(TList* list);
    /** Replace the time based branch name list*/
    void SetTimeBasedBranchNameList(TList* list);

    /** \deprecated Deprecated in v18.8, will be removed in v20. */
    [[deprecated]] void FillEventHeader(FairEventHeader* feh)
    {
        if (fSource)
            fSource->FillEventHeader(feh);
    }

    /**Enables a last Fill command after all events are processed to store any data which is still in Buffers*/
    void SetLastFill(Bool_t val = kTRUE) { fFillLastData = val; }
    /**When creating TTree from TFolder the fullpath of the objects is used as branch names
     * this method truncate the full path from the branch names
     */

    Int_t Write(const char* name = nullptr, Int_t option = 0, Int_t bufsize = 0) override;
    /** Write the current TGeoManager to file*/
    void WriteGeometry();
    /**Write the file header object to the output file*/
    void WriteFileHeader(FairFileHeader* f);
    /**Write the folder structure used to create the tree to the output file */
    void WriteFolder();

    /**Check the maximum event number we can run to*/
    Int_t CheckMaxEventNo(Int_t EvtEnd = 0);

    void StoreWriteoutBufferData(Double_t eventTime);
    void StoreAllWriteoutBufferData();
    void DeleteOldWriteoutBufferData();

    Int_t GetEntryNr() { return fEntryNr; }
    void SetEntryNr(Int_t val) { fEntryNr = val; }

    void SetUseFairLinks(Bool_t val) { fUseFairLinks = val; };
    Bool_t GetUseFairLinks() const { return fUseFairLinks; };

    [[deprecated]] void SetSource(FairSource* source) { fSource = std::unique_ptr<FairSource>{source}; }
    FairSource* GetSource() { return fSource.get(); }
    Bool_t InitSource();

    [[deprecated]] void SetSink(FairSink* sink) { fSink = std::unique_ptr<FairSink>{sink}; }
    FairSink* GetSink() { return fSink.get(); }
    Bool_t InitSink();

    void SetListOfFolders(TObjArray* ta) { fListFolder = ta; }
    TChain* GetInChain() { return fSourceChain; }
    TChain* GetSignalChainNo(UInt_t i) { return fSignalChainList[i]; }
    TTree* GetInTree()
    {
        if (fSourceChain)
            return fSourceChain->GetTree();
        return 0;
    }
    const TFile* GetRootFile()
    {
        if (fSourceChain)
            return fSourceChain->GetFile();
        return 0;
    }
    TFile* GetInFile()
    {
        if (fSourceChain)
            return fSourceChain->GetFile();
        return 0;
    }
    void SetInChain(TChain* tempChain, Int_t ident = -1);
    /* /\**Set the input tree when running on PROOF worker*\/ */

    void SetFinishRun(Bool_t val = kTRUE) { fFinishRun = val; }
    Bool_t FinishRun() { return fFinishRun; }

    static void SetTreeName(const std::string& tname) { fTreeName = tname; }
    static void SetFolderName(const std::string& tname) { fFolderName = tname; }

    const static char* GetTreeName();
    const static char* GetFolderName();

    /**public Members for multi-threading */
    Int_t GetInstanceId() const { return fId; }
    void UpdateFileName(TString& fileName);

    /** Return a pointer to the output File of type TFile */
    TFile* GetOutFile();
    /** Return a pointer to the output tree of type TTree */
    TTree* GetOutTree();

    /**Read one event from source to find out which RunId to use*/
    Bool_t SpecifyRunId();

  private:
    // helper struct since std::pair has problems with type_info
    struct TypeAddressPair
    {
        TypeAddressPair(const std::type_info& oi, const std::type_info& pi, void* a)
            : origtypeinfo(oi)
            , persistenttypeinfo(pi)
            , ptraddr(a)
        {}
        const std::type_info& origtypeinfo;         // type_info of type addr points to
        const std::type_info& persistenttypeinfo;   // type_info of ROOT persistent branch (drops pointers)
        void* ptraddr;                              // address of a pointer (pointing to origtypeinfo);
    };

    /**private methods*/

    /**ctor*/
    FairRootManager();
    FairRootManager(const FairRootManager&);
    FairRootManager& operator=(const FairRootManager&);

    TObject* ListFolderSearch(const char* brname) const;

    /**  Set the branch address for a given branch name and return
        a TObject pointer, the user have to cast this pointer to the right type.*/
    TObject* ActivateBranch(const char* BrName);
    void AddFriends();
    /**Add a branch to memory, it will not be written to the output files*/
    void AddMemoryBranch(const char*, TObject*);

    template<typename T>
    void AddMemoryBranchAny(const char* name, T** obj);
    template<typename T>
    T GetMemoryBranchAny(const char* name) const;

    template<typename T>
    void RegisterImpl(const char* name, const char* Foldername, T* obj, Bool_t toFile);

    /** Internal Check if Branch persistence or not (Memory branch)
    return value:
    1 : Branch is Persistance
    2 : Memory Branch
    0 : Branch does not exist
    */
    Int_t CheckBranchSt(const char* BrName);
    /**Create the Map for the branch persistency status  */
    void CreatePerMap();
    TObject* GetMemoryBranch(const char*) const;
    //   void                GetRunIdInfo(TString fileName, TString inputLevel);

    FairWriteoutBuffer* GetWriteoutBuffer(TString branchName);

    // private helper function to emit a warning
    void EmitMemoryBranchWrongTypeWarning(const char* brname, const char* typen1, const char* typen2) const;

    /**private Members*/

    /** current time in ns*/
    Double_t fCurrentTime;
    std::list<TObject*> fObj2{};   //!
    /** A list which hold the pointer to the branch
     * and the name of the branch in memory, it contains all branches (TClonesArrays)
     * persistance and Memory only branches
     */
    std::map<TString, TObject*> fMap;   //!

    /**folder name variable*/
    static std::string fFolderName;   //!
    /**tree name variable*/
    static std::string fTreeName;   //!
    static std::string GetNameFromFile(const char* namekind);

    /// A map of branchnames to typeinformation + memory address;
    /// used for branches registered with RegisterAny; use of ptr here
    /// since type_info cannot be copied
    std::map<std::string, std::unique_ptr<TypeAddressPair const>> fAnyBranchMap;   //!

    /**Branch id for this run */
    Int_t fBranchSeqId;
    /**List of branch names as TObjString*/
    TList fBranchNameList{};   //!

    /**The branch ID for the special (required) MCTrack branch**/
    Int_t fMCTrackBranchId;   //!

    /**List of Time based branchs names as TObjString*/
    TList* fTimeBasedBranchNameList;   //!
    /** Internally used to compress empty slots in data buffer*/
    std::map<TString, TClonesArray*> fActiveContainer;
    /** Internally used to read time ordered data from branches*/
    std::map<TString, FairTSBufferFunctional*> fTSBufferMap;     //!
    std::map<TString, FairWriteoutBuffer*> fWriteoutBufferMap;   //!
    std::map<Int_t, TBranch*> fInputBranchMap;                   //!    //Map of input branch ID with TBranch pointer
    /**Flag for creation of Map for branch persistency list  */
    Bool_t fBranchPerMap;
    /** Map for branch persistency list */
    std::map<TString, Int_t> fBrPerMap;   //!

    Bool_t fFillLastData;   //!
    Int_t fEntryNr;         //!

    TObjArray* fListFolder{nullptr};   //!

    fairroot::detail::maybe_owning_ptr<FairSource> fSource;   //!

    TChain* fSourceChain = nullptr;
    std::map<UInt_t, TChain*> fSignalChainList;   //!

    FairEventHeader* fEventHeader;

    fairroot::detail::maybe_owning_ptr<FairSink> fSink;   //!

    Bool_t fUseFairLinks;   //!
    Bool_t fFinishRun;      //!
    /** List of branches used with no-time stamp in time-based session */
    TRefArray fListOfNonTimebasedBranches{};   //!

    /**private Members for multi-threading */
    // data members
    Int_t fId{0};   //! This manager ID

    ClassDefOverride(FairRootManager, 0);
};

// FIXME: move to source since we can make it non-template dependent
template<typename T>
void FairRootManager::AddMemoryBranchAny(const char* brname, T** obj)
{
    if (fAnyBranchMap.find(brname) == fAnyBranchMap.end()) {
        auto& ot = typeid(T*);
        auto& pt = typeid(T);
        fAnyBranchMap[brname] = std::unique_ptr<TypeAddressPair const>(new TypeAddressPair(ot, pt, (void*)obj));
    }
}

// try to retrieve an object address from the registered branches/names
template<typename T>
T FairRootManager::GetMemoryBranchAny(const char* brname) const
{
    static_assert(std::is_pointer<T>::value, "Return type of GetMemoryBranchAny has to be a pointer");
    using P = typename std::remove_pointer<T>::type;
    auto iter = fAnyBranchMap.find(brname);
    if (iter != fAnyBranchMap.end()) {
        // verify type consistency
        if (typeid(P) != iter->second->origtypeinfo) {
            EmitMemoryBranchWrongTypeWarning(brname, typeid(P).name(), iter->second->origtypeinfo.name());
            return nullptr;
        }
        return static_cast<T>(iter->second->ptraddr);
    }
    return nullptr;
}

template<typename T>
void FairRootManager::RegisterAny(const char* brname, T*& obj, bool persistence)
{
    AddBranchToList(brname);
    // we are taking the address of the passed pointer
    AddMemoryBranchAny<T>(brname, &obj);
    if (persistence) {
        auto& ot = typeid(T*);
        auto& pt = typeid(T);
        if (fSink)
            fSink->RegisterAny(brname, ot, pt, &obj);
        else
            LOG(fatal) << "The sink does not exist to store persistent branches.";
    }
}

// this function serves as a factory (or lookup) for memory managed
// instances associated to branches
// it returns a pointer to unmodifiable instance of T
template<typename TPtr>
TPtr FairRootManager::InitObjectAs(const char* brname)
{
    static_assert(std::is_pointer<TPtr>::value, "Return type of GetObjectAs has to be a pointer");
    using X = typename std::remove_pointer<TPtr>::type;
    static_assert(std::is_const<X>::value, "Return type of GetObjectAs has to be pointer to const class");
    using T = typename std::remove_const<X>::type;

    // is there already an object associated to the branch in memory??
    // then just return
    T** obj = GetMemoryBranchAny<T**>(brname);
    // obj is some address/instance holding TPtr instances
    if (obj != nullptr)
        return *obj;

    if (!fSource) {
        return nullptr;
    }

    // it does not seem to be the case, let us create the pointer which will be initialized
    // with the data (pointer to T)
    T** addr = new T*;
    // init the pointee to a default obj which we can return
    (*addr) = new T;
    // try to find and activate in the source
    auto succeeded = fSource->ActivateObjectAny((void**)addr, typeid(T), brname);

    if (!succeeded) {
        delete (*addr);
        delete addr;
        return nullptr;
    }
    // add into branch list
    AddMemoryBranchAny<T>(brname, addr);

    // NOTE: ideally we would do proper resource management for addr and *addr
    // since the FairRootManager becomes owner of these pointers/instances; Unfortunately this
    // is quite a difficult task since we would have to store something like std::unique_ptr<T> in a member
    // container which we cannot know a priori; Some solutions we could think of in the future are
    // a) use the Destructor mechanism of ROOT::TClass since we still have the type info.
    // b) investigate if boost::any could be of help here
    // In any case, this problem is not very critical in the sense that FairRootManager is a singleton and hence
    // cannot really leak memory (Assuming that the destructors of T are not doing something non-trivial).
    return *addr;
}

#endif   // FAIR_ROOT_MANAGER_H
