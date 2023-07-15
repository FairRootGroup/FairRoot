/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairRootManager source file                 -----
// -----            Created 06/01/04  by M. Al-Turany/D. Bertini       -----
// -------------------------------------------------------------------------

// Class FairRootManager
// ------------------
// Class that takes care of Root IO.
#include "FairRootManager.h"

#include "FairEventHeader.h"   // for FairEventHeader
#include "FairFileHeader.h"    // for FairFileHeader
#include "FairFileSource.h"
#include "FairLink.h"                 // for FairLink
#include "FairLinkManager.h"          // for FairLinkManager
#include "FairLogger.h"               // for FairLogger, MESSAGE_ORIGIN
#include "FairMonitor.h"              // for FairMonitor
#include "FairRootFileSink.h"         // to enable GetOutFile()
#include "FairRun.h"                  // for FairRun
#include "FairTSBufferFunctional.h"   // for FairTSBufferFunctional, etc
#include "FairWriteoutBuffer.h"       // for FairWriteoutBuffer

#include <TBranch.h>        // for TBranch
#include <TClonesArray.h>   // for TClonesArray
#include <TCollection.h>    // for TCollection, TIter
#include <TDirectory.h>     // for TDirectory::TContext
#include <TFile.h>          // for TFile
#include <TFolder.h>        // for TFolder
#include <TGeoManager.h>    // for TGeoManager, gGeoManager
#include <TList.h>          // for TList
#include <TNamed.h>
#include <TObjArray.h>    // for TObjArray
#include <TObjString.h>   // for TObjString
#include <TTree.h>        // for TTree
#include <algorithm>      // for find
#include <atomic>
#include <cassert>
#include <cstdio>
#include <cstring>    // for strcmp
#include <iostream>   // for operator<<, basic_ostream, etc
#include <list>       // for _List_iterator, list, etc
#include <map>        // for map, _Rb_tree_iterator, etc
#include <memory>     // for unique_ptr
#include <set>        // for set, set<>::iterator
#include <stdlib.h>   // for exit
#include <utility>    // for pair
#include <vector>     // for vector

using std::list;
using std::map;
using std::pair;
using std::set;

static std::atomic<int> FRM_fgCounter{0};
std::string FairRootManager::fFolderName = "";
std::string FairRootManager::fTreeName = "";

FairRootManager* FairRootManager::Instance()
{
    // Returns singleton instance.
    // ---
    static thread_local FairRootManager instance;
    return &instance;
}

FairRootManager::FairRootManager()
    : TObject()
    , fCurrentTime(0)
    , fBranchSeqId(0)
    , fMCTrackBranchId(-1)
    , fTimeBasedBranchNameList(new TList())
    , fActiveContainer()
    , fTSBufferMap()
    , fWriteoutBufferMap()
    , fInputBranchMap()
    , fBranchPerMap(kFALSE)
    , fBrPerMap()
    , fFillLastData(kFALSE)
    , fEntryNr(0)
    , fSource(0)
    , fSignalChainList()
    , fEventHeader(new FairEventHeader())
    , fSink(nullptr)
    , fUseFairLinks(kFALSE)
    , fFinishRun(kFALSE)
{
    // Set Id
    fId = FRM_fgCounter.fetch_add(1, std::memory_order_relaxed);

    LOG(debug) << "FairRootManager::FairRootManager #" << fId << " at " << this;

    fBranchNameList.SetOwner(kTRUE);
}

FairRootManager::~FairRootManager()
{
    LOG(debug) << "Enter Destructor of FairRootManager";

    delete fEventHeader;
    delete fSourceChain;
    if (fSink)
        delete fSink;
    if (fSource)
        delete fSource;

    // Global cleanup

    FRM_fgCounter.fetch_sub(1, std::memory_order_relaxed);

    LOG(debug) << "FairRootManager::~FairRootManager done #" << fId << " at " << this;
}

Bool_t FairRootManager::InitSource()
{
    // creating fSourceChain now, to give the user chance to change the tree and folder name
    fSourceChain = new TChain(GetTreeName(), Form("/%s", GetFolderName()));

    LOG(debug) << "Call the initialiazer for the FairSource in FairRootManager ";
    if (fSource) {
        Bool_t sourceInitBool = fSource->Init();
        TObjArray* listofbranchesfrominput = fSourceChain->GetListOfBranches();
        TObject* obj;
        if (listofbranchesfrominput) {
            TIter branchiter{listofbranchesfrominput};
            while ((obj = branchiter())) {
                if ((fTimeBasedBranchNameList->FindObject(obj->GetName())) == 0)
                    fListOfNonTimebasedBranches.Add(obj);
            }
        }
        LOG(debug) << "Source is intialized and the list of branches is created in FairRootManager ";
        return sourceInitBool;
    }
    return kFALSE;
}

Bool_t FairRootManager::InitSink()
{
    if (fSink) {
        fSink->InitSink();
        return true;
    }
    LOG(info) << "The output sink is not set. No branches will be stored.";
    return false;
}

template<typename T>
void FairRootManager::RegisterImpl(const char* name, const char* folderName, T* obj, Bool_t toFile)
{
    /// a common implementation for Register
    FairMonitor::GetMonitor()->RecordRegister(name, folderName, toFile);

    // Security check. If the the name is equal the folder name there are problems with reading
    // back the data. Instead of the object inside the folder the RootManger will return a pointer
    // to the folder. To avoid such problems we check here if both strings are equal and stop the
    // execution with some error message if this is the case.
    if (strcmp(name, folderName) == 0) {
        LOG(fatal) << "The names for the object name " << name << " and the folder name " << folderName
                   << " are equal. This isn't allowed. So we stop the execution at this point. Pleae change either the "
                      "name or the folder name.";
    }

    if (toFile) { /**Write the Object to the Tree*/
        obj->SetName(name);
        if (fSink) {
            fSink->RegisterImpl(name, folderName, obj);
        } else {
            LOG(warning) << "The sink does not exist to store persistent branches (" << name << ").";
        }
    }
    AddMemoryBranch(name, obj);
    AddBranchToList(name);

    if (!toFile) {
        FairLinkManager::Instance()->AddIgnoreType(GetBranchId(name));
    }
}

void FairRootManager::Register(const char* name, const char* folderName, TNamed* obj, Bool_t toFile)
{
    RegisterImpl(name, folderName, obj, toFile);
}

Int_t FairRootManager::AddBranchToList(const char* name)
{
    if (fBranchNameList.FindObject(name) == 0) {
        fBranchNameList.AddLast(new TObjString(name));
        // check if we are setting the MCTrack Branch
        if (strcmp(name, "MCTrack") == 0) {
            fMCTrackBranchId = fBranchSeqId;
        }
        fBranchSeqId++;
    }
    return fBranchSeqId;
}

void FairRootManager::Register(const char* name, const char* foldername, TCollection* obj, Bool_t toFile)
{
    RegisterImpl(name, foldername, obj, toFile);
}

void FairRootManager::RegisterInputObject(const char* name, TObject* obj)
{
    AddMemoryBranch(name, obj);
    AddBranchToList(name);
}

TClonesArray* FairRootManager::Register(TString branchName, TString className, TString folderName, Bool_t toFile)
{
    FairMonitor::GetMonitor()->RecordRegister(branchName, folderName, toFile);

    TClonesArray* outputArray;
    if (fActiveContainer.find(branchName) == fActiveContainer.end()) {
        fActiveContainer[branchName] = new TClonesArray(className);
        outputArray = fActiveContainer[branchName];
        Register(branchName, folderName, outputArray, toFile);
    }

    return fActiveContainer[branchName];
}

TClonesArray* FairRootManager::GetEmptyTClonesArray(TString branchName)
{
    if (fActiveContainer.find(branchName)
        != fActiveContainer.end()) {               // if a TClonesArray is registered in the active container
        if (fActiveContainer[branchName] == 0) {   // the address of the TClonesArray is still valid
            std::cout << "-E- FairRootManager::GetEmptyTClonesArray: Container deleted outside FairRootManager!"
                      << std::endl;
        } else {
            fActiveContainer[branchName]->Delete();
        }
        return fActiveContainer[branchName];   // return the container
    } else {
        std::cout << "-E- Branch: " << branchName << " not registered!"
                  << std::endl;   // error if the branch is not registered
    }
    return 0;
}

TClonesArray* FairRootManager::GetTClonesArray(TString branchName)
{
    if (fActiveContainer.find(branchName) != fActiveContainer.end()) {
        return fActiveContainer[branchName];   // return the container
    } else {
        LOG(info) << "Branch: " << branchName.Data() << " not registered!";
    }
    // error if the branch is not registered
    return 0;
}

TString FairRootManager::GetBranchName(Int_t id)
{
    /**Return the branch name from the id*/
    if (id < fBranchSeqId) {
        TObjString* ObjStr = static_cast<TObjString*>(fBranchNameList.At(id));
        return ObjStr->GetString();
    } else {
        TString NotFound("Branch not found");
        return NotFound;
    }
}

Int_t FairRootManager::GetBranchId(TString const& BrName)
{
    /**Return the branch id from the name*/
    TObjString* ObjStr;
    Int_t Id = -1;
    for (Int_t t = 0; t < fBranchNameList.GetEntries(); t++) {
        ObjStr = static_cast<TObjString*>(fBranchNameList.TList::At(t));
        if (BrName == ObjStr->GetString()) {
            Id = t;
            break;
        }
    }
    return Id;
}

void FairRootManager::InitTSBuffer(TString branchName, BinaryFunctor* function)
{
    fTSBufferMap[branchName] = new FairTSBufferFunctional(branchName, GetInTree(), function);
}

TClonesArray* FairRootManager::GetData(TString branchName, BinaryFunctor* function, Double_t parameter)
{
    if (fTSBufferMap[branchName] == 0) {
        fTSBufferMap[branchName] = new FairTSBufferFunctional(branchName, GetInTree(), function);
    }
    fTSBufferMap[branchName]->SetStopFunction(function);
    return fTSBufferMap[branchName]->GetData(parameter);
}

TClonesArray* FairRootManager::GetData(TString branchName,
                                       BinaryFunctor* startFunction,
                                       Double_t startParameter,
                                       BinaryFunctor* stopFunction,
                                       Double_t stopParameter)
{
    if (fTSBufferMap[branchName] == 0) {
        fTSBufferMap[branchName] = new FairTSBufferFunctional(branchName, GetInTree(), stopFunction, startFunction);
    }
    fTSBufferMap[branchName]->SetStopFunction(stopFunction);
    fTSBufferMap[branchName]->SetStartFunction(startFunction);
    return fTSBufferMap[branchName]->GetData(startParameter, stopParameter);
}

void FairRootManager::TerminateTSBuffer(TString branchName)
{
    if (fTSBufferMap.count(branchName) > 0) {
        fTSBufferMap[branchName]->Terminate();
    }
}

void FairRootManager::TerminateAllTSBuffer()
{
    for (auto& mi : fTSBufferMap) {
        mi.second->Terminate();
    }
}

Bool_t FairRootManager::AllDataProcessed()
{
    for (auto& mi : fTSBufferMap) {
        if (!mi.second->AllDataProcessed() && !mi.second->TimeOut()) {
            return false;
        }
    }
    return kTRUE;
}

void FairRootManager::Fill()
{
    if (fSink)
        fSink->Fill();
}

void FairRootManager::LastFill()
{
    //  FairMonitor::GetMonitor()->StoreHistograms(); MOVED TO FairRootFileSink
    if (fFillLastData) {
        if (fSink)
            fSink->Fill();
    }
}

Int_t FairRootManager::Write(const char*, Int_t, Int_t)
{
    /** Writes the tree in the file.*/

    LOG(debug) << "FairRootManager::Write " << this;

    if (fSink)
        return (fSink->Write());

    return 0;
}

void FairRootManager::WriteGeometry()
{
    /** Writes the geometry in the current output file.*/
    if (fSink)
        fSink->WriteGeometry();
}

void FairRootManager::CreateGeometryFile(const char* geofile)
{
    /** Writes the geometry in a separate file.
     *  This is only to have a file which can be read without the
     *  framework. The geomanager used by the framework is still
     *  stored in the parameter file or database
     */
    TDirectory::TContext restorecwd{};
    std::unique_ptr<TFile> file{TFile::Open(geofile, "RECREATE")};
    file->WriteTObject(gGeoManager);
    file->Close();
}

void FairRootManager::WriteFolder()
{
    if (fSink) {
        fSink->WriteFolder();
        fSink->WriteObject(&fBranchNameList, "BranchList", TObject::kSingleKey);
        fSink->WriteObject(fTimeBasedBranchNameList, "TimeBasedBranchList", TObject::kSingleKey);
    }
}
Bool_t FairRootManager::SpecifyRunId()
{
    if (!fSource) {
        LOG(fatal) << "No Source available";
        return false;
    }
    Bool_t Result = fSource->SpecifyRunId();
    fSource->FillEventHeader(fEventHeader);
    LOG(info) << "---FairRootManager::SpecifyRunId --- ";
    return Result;
}
Int_t FairRootManager::ReadEvent(const Int_t i)
{
    if (!fSource)
        return 0;

    fSource->Reset();

    SetEntryNr(i);

    if (!fSource) {
        LOG(fatal) << "No Source available";
        return -1;
    }

    Int_t readEventResult = fSource->ReadEvent(i);

    fSource->FillEventHeader(fEventHeader);
    fCurrentTime = fEventHeader->GetEventTime();

    LOG(debug) << "--Event number --- " << i << " with t0 time ---- " << fCurrentTime;

    return readEventResult;
}

void FairRootManager::ReadBranchEvent(const char* BrName, Int_t entry)
{
    if (!fSource)
        return;
    fSource->Reset();
    SetEntryNr(entry);

    fSource->ReadBranchEvent(BrName, entry);
    fSource->FillEventHeader(fEventHeader);
    fCurrentTime = fEventHeader->GetEventTime();
}

Int_t FairRootManager::GetRunId()
{
    if (fSource) {
        fSource->FillEventHeader(fEventHeader);
        return fEventHeader->GetRunId();
    }
    return -1;
}

void FairRootManager::ReadBranchEvent(const char* BrName)
{
    if (fSource) {
        fSource->ReadBranchEvent(BrName);
        fSource->FillEventHeader(fEventHeader);
        fCurrentTime = fEventHeader->GetEventTime();
    }
}

Int_t FairRootManager::ReadNonTimeBasedEventFromBranches(Int_t Entry)
{
    if (fSource) {
        TObject* Obj;
        TIter branchiter{&fListOfNonTimebasedBranches};
        while ((Obj = branchiter())) {
            fSource->ReadBranchEvent(Obj->GetName(), Entry);
            fSource->FillEventHeader(fEventHeader);
            fCurrentTime = fEventHeader->GetEventTime();
        }
    } else {
        return 0;
    }
    return 1;
}

Bool_t FairRootManager::ReadNextEvent(Double_t)
{
    Bool_t readentry = kFALSE;
    /// TODO
    return readentry;
}

TObject* FairRootManager::GetObject(const char* BrName)
{
    /**Get Data object by name*/
    LOG(debug2) << " Try to find if the object " << BrName << " is already activated by another task or call";
    /**Get object from memory or source*/
    TObject* Obj = ActivateBranch(BrName);
    if (Obj != nullptr)
        FairMonitor::GetMonitor()->RecordGetting(BrName);
    return Obj;
}

TObject* FairRootManager::GetCloneOfLinkData(const FairLink link)
{
    TObject* result = 0;

    //  std::cout << "GetCloneOfLinkData: Link " << link << std::endl;
    Int_t fileId = link.GetFile();
    Int_t entryNr = link.GetEntry();
    Int_t type = link.GetType();
    Int_t index = link.GetIndex();

    Int_t oldEntryNr = GetEntryNr();

    //  std::cout << "OldEntryNr: " << GetEntryNr();

    //  std::cout << "GetLinkData: " << link << std::endl;

    TTree* dataTree;   // get the correct Tree
    if (fileId < 0) {
        dataTree = GetInTree();
    } else if (fileId == 0) {
        dataTree = GetInChain();
    } else {
        dataTree = GetSignalChainNo(fileId);
    }

    if (dataTree == 0) {
        dataTree = GetInTree();
    }

    if (type < 0) {
        return 0;
    }

    TBranch* dataBranch = 0;

    //  std::cout << "DataType: " << GetBranchName(type) << std::endl;

    if (fileId < 0 && fInputBranchMap[type] != 0) {
        dataBranch = fInputBranchMap[type];
    } else if (fileId < 0) {
        fInputBranchMap[type] = dataTree->GetBranch(GetBranchName(type));
        dataBranch = fInputBranchMap[type];
    } else {
        dataBranch = dataTree->GetBranch(GetBranchName(type));
    }

    if (dataBranch == 0) {
        return 0;
    }

    if (entryNr > -1) {   // get the right entry (if entryNr < 0 then the current entry is taken
        if (entryNr < dataBranch->GetEntries()) {
            dataBranch->GetEntry(entryNr);
        } else {
            return 0;
        }
    } else {   // the link entry nr is negative --> take the actual one

        //    std::cout << "EntryNr: " << GetEntryNr() << std::endl;
        //    dataBranch->GetEntry(GetEntryNr());
    }

    if (index < 0) {   // if index is -1 then this is not a TClonesArray so only the Object is returned
        result = GetObject(GetBranchName(type))->Clone();
    } else {
        TClonesArray* dataArray = static_cast<TClonesArray*>(GetObject(GetBranchName(type)));

        //  std::cout << "FairRootManager::GetCloneOfLinkData() dataArray size: " << dataArray->GetEntriesFast()
        //            << std::endl;
        if (index < dataArray->GetEntriesFast()) {
            //      std::cout << "DataArray at index " << index << " has Link: " <<
            //      ((FairMultiLinkedData*)dataArray->At(index))->GetNLinks() << std::cout;
            result = dataArray->At(index)->Clone();
            //      std::cout << "Result: " << *((FairMultiLinkedData*)result) << std::endl;
        }
    }
    if (entryNr > -1) {
        dataBranch->GetEntry(oldEntryNr);   // reset the dataBranch to the original entry
    }
    return result;
}

TClonesArray* FairRootManager::GetCloneOfTClonesArray(const FairLink link)
{
    TClonesArray* result = 0;

    //  std::cout << "GetCloneOfLinkData: Link " << link << std::endl;
    Int_t fileId = link.GetFile();
    Int_t entryNr = link.GetEntry();
    Int_t type = link.GetType();
    Int_t index = link.GetIndex();

    Int_t oldEntryNr = GetEntryNr();

    //  std::cout << "OldEntryNr: " << GetEntryNr();

    //  std::cout << "GetLinkData: " << link << std::endl;

    TTree* dataTree;   // get the correct Tree
    if (fileId < 0) {
        dataTree = GetInTree();
    } else if (fileId == 0) {
        dataTree = GetInChain();
    } else {
        dataTree = GetSignalChainNo(fileId);
    }

    if (dataTree == 0) {
        dataTree = GetInTree();
    }

    if (type < 0) {
        return 0;
    }

    TBranch* dataBranch = 0;

    //  std::cout << "DataType: " << GetBranchName(type) << std::endl;

    if (fileId < 0 && fInputBranchMap[type] != 0) {
        dataBranch = fInputBranchMap[type];
    } else if (fileId < 0) {
        fInputBranchMap[type] = dataTree->GetBranch(GetBranchName(type));
        dataBranch = fInputBranchMap[type];
    } else {
        dataBranch = dataTree->GetBranch(GetBranchName(type));
    }

    if (dataBranch == 0) {
        return 0;
    }

    if (entryNr > -1) {   // get the right entry (if entryNr < 0 then the current entry is taken
        if (entryNr < dataBranch->GetEntries()) {
            dataBranch->GetEntry(entryNr);
        } else {
            return 0;
        }
    } else {   // the link entry nr is negative --> take the actual one

        //    std::cout << "EntryNr: " << GetEntryNr() << std::endl;
        //    dataBranch->GetEntry(GetEntryNr());
    }

    if (index < 0) {   // if index is -1 then this is not a TClonesArray so only the Object is returned
        result = 0;
    } else {
        result = static_cast<TClonesArray*>(GetObject(GetBranchName(type))->Clone());
    }
    if (entryNr > -1) {
        dataBranch->GetEntry(oldEntryNr);   // reset the dataBranch to the original entry
    }
    return result;
}

Int_t FairRootManager::CheckBranch(const char* BrName)
{
    /**The first time this method is called the map is generated and then used*/
    if (!fBranchPerMap) {
        CreatePerMap();
        return CheckBranchSt(BrName);
    } else {
        auto brpermapiter = fBrPerMap.find(BrName);
        if (brpermapiter != fBrPerMap.end()) {
            return brpermapiter->second;
        } else {
            return 0;
        }
    }
}

void FairRootManager::SetBranchNameList(TList* list)
{
    if (list == nullptr)
        return;
    // otherwise clear existing and add via the standard interface
    fBranchNameList.Clear();
    fMCTrackBranchId = -1;
    for (Int_t t = 0; t < list->GetEntries(); t++) {
        AddBranchToList(static_cast<TObjString*>(list->At(t))->GetString().Data());
    }
}

void FairRootManager::SetInChain(TChain* tempChain, Int_t ident)
{
    if (ident <= 0)
        fSourceChain = tempChain;
    else
        fSignalChainList[ident] = tempChain;
}

Double_t FairRootManager::GetEventTime()
{
    return fCurrentTime;
}

void FairRootManager::UpdateBranches()
{
    for (auto& iobj : fObj2) {
        if (iobj) {
            const char* objname = iobj->GetName();
            LOG(info) << "FairRootManager::UpdateBranches \"" << objname << "\" (\"" << iobj->GetTitle() << "\")";
            fSource->ActivateObject(&iobj, objname);
        }
    }
}

/** Private functions*/

TObject* FairRootManager::ListFolderSearch(const char* brname) const
{
    if (!fListFolder) {
        return nullptr;
    }
    for (auto const* fold : TRangeDynCast<TFolder>(fListFolder)) {
        if (!fold) {
            continue;
        }
        TObject* obj = fold->FindObjectAny(brname);
        if (obj) {
            return obj;
        }
    }
    return nullptr;
}

TObject* FairRootManager::ActivateBranch(const char* BrName)
{
    /** Set the branch address for a given branch name and return a TObject pointer,
   the user have to cast this pointer to the right type.
   The function has been revisited ! Now it test if in the task init() mutilple
   calls to activate branch is done , and then just forward the pointer.
   <DB>
   **/
    auto& newentry = fObj2.emplace_back(GetMemoryBranch(BrName));
    if (newentry) {
        return newentry;
    }
    /**try to find the object decribing the branch in the folder structure in file*/
    LOG(debug) << "Try to find an object " << BrName << " describing the branch in the folder structure in file";
    newentry = ListFolderSearch(BrName);

    if (!newentry) {
        /** if we do not find an object corresponding to the branch in the folder structure
         *  then we have no idea about what type of object is this and we cannot set the branch address
         */
        LOG(info) << " Branch: " << BrName << " not found in Tree.";
        // Fatal(" No Branch in the tree", BrName );
        return nullptr;
    } else {
        if (fSource)
            fSource->ActivateObject(&newentry, BrName);
    }

    AddMemoryBranch(BrName, newentry);
    return newentry;
}

void FairRootManager::AddMemoryBranch(const char* fName, TObject* pObj)
{
    /**branch will be available ionly in Memory, will not be written to disk */
    TString BrName = fName;
    auto p = fMap.find(BrName);
    if (p == fMap.end()) {
        fMap.emplace(std::move(BrName), pObj);
    }
}

Int_t FairRootManager::CheckBranchSt(const char* BrName)
{
    // cout <<"FairRootManager::CheckBranchSt  :  " << BrName << endl;

    TObject* Obj1 = ListFolderSearch(BrName);
    TObject* Obj2 = GetMemoryBranch(BrName);   // Branch in Memory

    Int_t returnvalue = 0;
    if (Obj1 != 0) {
        returnvalue = 1;
    } else if (Obj2 != 0) {
        returnvalue = 2;
    } else {
        returnvalue = 0;
    }

    /**  1 : Branch is Persistance
       2 : Memory Branch
       0 : Branch does not exist
  */
    return returnvalue;
}

void FairRootManager::CreatePerMap()
{
    // cout << " FairRootManager::CreatePerMap() " << endl;
    fBranchPerMap = kTRUE;
    for (Int_t i = 0; i < fBranchSeqId; i++) {
        TObjString* name = static_cast<TObjString*>(fBranchNameList.At(i));
        // cout << " FairRootManager::CreatePerMap() Obj At " << i << "  is "  << name->GetString() << endl;
        TString BrName = name->GetString();
        fBrPerMap.insert(pair<TString, Int_t>(BrName, CheckBranchSt(BrName.Data())));
    }
}

TObject* FairRootManager::GetMemoryBranch(const char* fName) const
{
    // return fMap[BrName];
    const TString BrName = fName;
    auto p = fMap.find(BrName);

    if (p != fMap.end()) {
        return p->second;
    } else {
        return nullptr;
    }
}

void FairRootManager::WriteFileHeader(FairFileHeader* f)
{
    if (fSink)
        fSink->WriteObject(f, "FileHeader", TObject::kSingleKey);
}

Int_t FairRootManager::CheckMaxEventNo(Int_t EvtEnd)
{
    if (fSource)
        return fSource->CheckMaxEventNo(EvtEnd);
    return 0;
}

FairWriteoutBuffer* FairRootManager::RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer)
{
    if (fWriteoutBufferMap[branchName] == 0) {
        fWriteoutBufferMap[branchName] = buffer;
    } else {
        LOG(warn) << "Branch " << branchName.Data() << " is already registered in WriteoutBufferMap";
        delete buffer;
    }

    return fWriteoutBufferMap[branchName];
}

void FairRootManager::UpdateListOfTimebasedBranches()
{
    /**
     * Add branches that are time based to the proper list
     */

    for (auto& mi : fWriteoutBufferMap) {
        if (mi.second->IsBufferingActivated())
            fTimeBasedBranchNameList->AddLast(new TObjString(mi.first.Data()));
    }
}

void FairRootManager::SetTimeBasedBranchNameList(TList* list)
{
    /**
     * Replace the list
     */

    if (list != 0) {
        fTimeBasedBranchNameList->Delete();
        delete fTimeBasedBranchNameList;
        fTimeBasedBranchNameList = list;
    }
}

FairWriteoutBuffer* FairRootManager::GetWriteoutBuffer(TString branchName)
{
    if (fWriteoutBufferMap.count(branchName) > 0) {
        return fWriteoutBufferMap[branchName];
    } else {
        return 0;
    }
}

void FairRootManager::StoreWriteoutBufferData(Double_t eventTime)
{
    for (auto& mi : fWriteoutBufferMap) {
        mi.second->WriteOutData(eventTime);
    }
}

void FairRootManager::StoreAllWriteoutBufferData()
{
    Bool_t dataInBuffer = kFALSE;
    for (auto& mi : fWriteoutBufferMap) {
        if (mi.second->GetNData() > 0) {
            dataInBuffer = kTRUE;
        }
        mi.second->WriteOutAllData();
    }
    fFillLastData = dataInBuffer;
}

void FairRootManager::DeleteOldWriteoutBufferData()
{
    for (auto& mi : fWriteoutBufferMap) {
        mi.second->DeleteOldData();
    }
}

std::string FairRootManager::GetNameFromFile(const char* namekind)
{
    std::string default_name = "";

    if (strcmp(namekind, "treename=") && strcmp(namekind, "foldername=")) {
        LOG(fatal) << "FairRootManager, requested " << namekind << ", while only treename= and foldername= available.";
        return default_name;
    }

    char* workdir = getenv("VMCWORKDIR");
    if (nullptr == workdir) {
        return default_name;
    }

    // Open file with output tree name
    std::ifstream file(Form("%s/config/rootmanager.dat", workdir));
    // If file does not exist -> default
    if (!file.is_open()) {
        return default_name;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind(namekind, 0) == 0) {
            line.replace(0, strlen(namekind), "");
            file.close();
            return line;
        }
    }

    file.close();
    return default_name;
}

const char* FairRootManager::GetTreeName()
{
    if (fTreeName.length() > 0) {
        return Form("%s", fTreeName.c_str());
    }

    std::string nameFromFile = GetNameFromFile("treename=");
    if (nameFromFile.length() > 0) {
        return Form("%s", nameFromFile.c_str());
    }

    return "cbmsim";
}

const char* FairRootManager::GetFolderName()
{
    if (fFolderName.length() > 0) {
        return Form("%s", fFolderName.c_str());
    }

    std::string nameFromFile = GetNameFromFile("foldername=");
    if (nameFromFile.length() > 0) {
        return Form("%s", nameFromFile.c_str());
    }

    if (!FairRun::Instance()->IsAna()) {
        return "cbmroot";
    }
    return "cbmout";
}

void FairRootManager::EmitMemoryBranchWrongTypeWarning(const char* brname, const char* type1, const char* type2) const
{
    LOG(warn) << "Trying to read from memory branch " << brname << " with wrong type " << type1
              << " (expexted: " << type2 << " )";
}

void FairRootManager::UpdateFileName(TString& fileName)
{
    TString tid = "_t";
    tid += GetInstanceId();
    fileName.Insert(fileName.Index(".root"), tid);
}

TFile* FairRootManager::GetOutFile()
{
    auto sink = GetSink();
    assert(sink->GetSinkType() == kFILESINK);
    auto rootFileSink = static_cast<FairRootFileSink*>(sink);
    return rootFileSink->GetRootFile();
}

TTree* FairRootManager::GetOutTree()
{
    auto sink = GetSink();
    assert(sink->GetSinkType() == kFILESINK);
    auto rootFileSink = static_cast<FairRootFileSink*>(sink);
    return rootFileSink->GetOutTree();
}
