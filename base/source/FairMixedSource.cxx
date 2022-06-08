/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

//
//  FairMixedSource.cxx
//  FAIRROOT
//
//  Created by Mohammad Al-Turany on 08/02/14.
//
//
#include "FairMixedSource.h"

#include "FairEventHeader.h"
#include "FairLogger.h"
#include "FairMCEventHeader.h"
#include "FairRootManager.h"

#include <TDirectory.h>   // for TDirectory::TContext
#include <TFolder.h>
#include <TList.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TObject.h>
#include <TROOT.h>
#include <TRandom.h>   // for TRandom, gRandom
#include <TString.h>
#include <cmath>   // floor, fmod

FairMixedSource::FairMixedSource(TFile* f, const char* Title, UInt_t)
    : FairFileSourceBase()
    , fRootManager(0)
    , fInputTitle(Title)
    , fRootFile(f)
    , fFriendFileList()
    , fInputChainList()
    , fFriendTypeList()
    , fInputLevel()
    , fRunIdInfoAll()
    , fListFolder(new TObjArray(16))
    , fCbmout(0)
    , fCbmroot(0)
    , fSourceIdentifier(0)
    , fNoOfEntries(-1)
    , IsInitialized(kFALSE)
    , fMCHeader(0)
    , fEvtHeader(0)
    , fOutHeader(0)
    , fFileHeader(0)
    , fEventTimeInMCHeader(kTRUE)
    , fEvtHeaderIsNew(kFALSE)
    , fCurrentEntryNo(0)
    , fTimeforEntryNo(0)
    , fNoOfBGEntries(0)
    , fCurrentEntry()
    , fEventTimeMin(0.)
    , fEventTimeMax(0.)
    , fEventTime(0.)
    , fBeamTime(-1.)
    , fGapTime(-1.)
    , fEventMeanTime(0.)
    , fSignalBGN()
    , fSBRatiobyN(kFALSE)
    , fSBRatiobyT(kFALSE)
    , fActualSignalIdentifier(0)
    , fNoOfSignals(0)
    , fSignalChainList(nullptr)
    , fBackgroundChain(nullptr)
    , fSignalTypeList()
    , fRunIdFromBG(kFALSE)
    , fRunIdFromSG(kFALSE)
    , fRunIdFromSG_identifier(0)
{
    if ((!fRootFile) || fRootFile->IsZombie()) {
        LOG(fatal) << "Error opening the Input file";
    }
    LOG(info) << "FairMixedSource created------------";

    fRootManager = FairRootManager::Instance();
}

FairMixedSource::FairMixedSource(const TString* RootFileName, const char* Title, UInt_t)
    : FairFileSourceBase()
    , fRootManager(0)
    , fInputTitle(Title)
    , fRootFile(0)
    , fFriendFileList()
    , fInputChainList()
    , fFriendTypeList()
    , fInputLevel()
    , fRunIdInfoAll()
    , fListFolder(new TObjArray(16))
    , fCbmout(0)
    , fCbmroot(0)
    , fSourceIdentifier(0)
    , fNoOfEntries(-1)
    , IsInitialized(kFALSE)
    , fMCHeader(0)
    , fEvtHeader(0)
    , fOutHeader(0)
    , fFileHeader(0)
    , fEventTimeInMCHeader(kTRUE)
    , fEvtHeaderIsNew(kFALSE)
    , fCurrentEntryNo(0)
    , fTimeforEntryNo(0)
    , fNoOfBGEntries(0)
    , fCurrentEntry()
    , fEventTimeMin(0.)
    , fEventTimeMax(0.)
    , fEventTime(0.)
    , fBeamTime(-1.)
    , fGapTime(-1.)
    , fEventMeanTime(0.)
    , fSignalBGN()
    , fSBRatiobyN(kFALSE)
    , fSBRatiobyT(kFALSE)
    , fActualSignalIdentifier(0)
    , fNoOfSignals(0)
    , fSignalChainList(nullptr)
    , fBackgroundChain(nullptr)
    , fSignalTypeList()
    , fRunIdFromBG(kFALSE)
    , fRunIdFromSG(kFALSE)
    , fRunIdFromSG_identifier(0)
{
    fRootFile = TFile::Open(RootFileName->Data());
    if ((!fRootFile) || fRootFile->IsZombie()) {
        LOG(fatal) << "Error opening the Input file";
    }
    fRootManager = FairRootManager::Instance();
    LOG(info) << "FairMixedSource created------------";
}

FairMixedSource::FairMixedSource(const TString RootFileName, const Int_t signalId, const char* Title, UInt_t)
    : FairFileSourceBase()
    , fRootManager(0)
    , fInputTitle(Title)
    , fRootFile(0)
    , fFriendFileList()
    , fInputChainList()
    , fFriendTypeList()
    , fInputLevel()
    , fRunIdInfoAll()
    , fListFolder(new TObjArray(16))
    , fCbmout(0)
    , fCbmroot(0)
    , fSourceIdentifier(0)
    , fNoOfEntries(-1)
    , IsInitialized(kFALSE)
    , fMCHeader(0)
    , fEvtHeader(0)
    , fOutHeader(0)
    , fFileHeader(0)
    , fEventTimeInMCHeader(kTRUE)
    , fEvtHeaderIsNew(kFALSE)
    , fCurrentEntryNo(0)
    , fTimeforEntryNo(0)
    , fNoOfBGEntries(0)
    , fCurrentEntry()
    , fEventTimeMin(0.)
    , fEventTimeMax(0.)
    , fEventTime(0.)
    , fBeamTime(-1.)
    , fGapTime(-1.)
    , fEventMeanTime(0.)
    , fSignalBGN()
    , fSBRatiobyN(kFALSE)
    , fSBRatiobyT(kFALSE)
    , fActualSignalIdentifier(0)
    , fNoOfSignals(0)
    , fSignalChainList(nullptr)
    , fBackgroundChain(nullptr)
    , fSignalTypeList()
    , fRunIdFromBG(kFALSE)
    , fRunIdFromSG(kFALSE)
    , fRunIdFromSG_identifier(0)
{
    fRootFile = TFile::Open(RootFileName.Data());
    if ((!fRootFile) || fRootFile->IsZombie()) {
        LOG(fatal) << "Error opening the Input file";
    }

    if (signalId == 0) {
        SetBackgroundFile(RootFileName);
    } else {
        SetSignalFile(RootFileName, signalId);
    }
    fRootManager = FairRootManager::Instance();
    // fBackgroundFile =  TFile::Open(name);
    // if (fBackgroundFile->IsZombie()) {
    // } else {
    //   fBackgroundChain = new TChain(FairRootManager::GetTreeName(), "/cbmroot");
    //   fBackgroundChain->AddFile(name.Data());
    // }
}

FairMixedSource::~FairMixedSource() = default;

Bool_t FairMixedSource::Init()
{
    fOutHeader = new FairEventHeader();
    LOG(info) << "fSBRatiobyN = " << (fSBRatiobyN ? "true" : "false")
              << " / fSBRatiobyT = " << (fSBRatiobyT ? "true" : "false");

    // LOG(info) << "*********** CHAIN HAS " << fBackgroundChain->GetEntries() << " entries";
    if (IsInitialized) {
        LOG(info) << "FairMixedSource already initialized";
        return kTRUE;
    }
    if (!fBackgroundChain) {
        fBackgroundChain = new TChain(FairRootManager::GetTreeName(), Form("/%s", FairRootManager::GetFolderName()));
        LOG(info) << "FairMixedSource::Init() chain created";
    }

    fBackgroundChain->Add(fRootFile->GetName());
    LOG(info) << "*********** CHAIN HAS " << fBackgroundChain->GetEntries() << " entries";

    // Get the folder structure from file which describes the input tree.
    // There are two different names possible, so check both.
    fCbmroot = fRootFile->Get<TFolder>(FairRootManager::GetFolderName());
    if (!fCbmroot) {
        fCbmroot = fRootFile->Get<TFolder>("cbmroot");
        if (!fCbmroot) {
            fCbmroot = fRootFile->Get<TFolder>("cbmout");
            if (!fCbmroot) {
                fCbmroot = gROOT->GetRootFolder()->AddFolder(FairRootManager::GetFolderName(), "Main Folder");
            } else {
                fCbmroot->SetName(FairRootManager::GetFolderName());
            }
        }
    }
    // Get The list of branches from the input file and add it to the
    // actual list of existing branches.
    // Add this list of branches also to the map of input trees, which
    // stores the information which branches belong to which input tree.
    // There is at least one primary input tree, but there can be many
    // additional friend trees.
    // This information is needed to add new files to the correct friend
    // tree. With this information it is also possible to check if the
    // input files which are added to the input chain all have the same
    // branch structure. Without this check it is possible to add trees
    // with a different branch structure but the same tree name. ROOT
    // probably only checks if the name of the tree is the same.

    auto list = fRootFile->Get<TList>("BranchList");
    if (list == 0)
        LOG(fatal) << "No Branch list in input file";
    TString chainName = fInputTitle;
    fInputLevel.push_back(chainName);
    if (list) {
        TString ObjName;
        TObjString* Obj = 0;
        LOG(info) << "Enteries in the list " << list->GetEntries();
        for (Int_t i = 0; i < list->GetEntries(); i++) {
            Obj = dynamic_cast<TObjString*>(list->At(i));
            if (Obj != 0) {
                ObjName = Obj->GetString();
                LOG(info) << "Branch name " << ObjName.Data();
                fCheckInputBranches[chainName].push_back(ObjName);

                FairRootManager::Instance()->AddBranchToList(ObjName.Data());
            }
        }
    }

    gROOT->GetListOfBrowsables()->Add(fCbmroot);
    fListFolder->Add(fCbmroot);

    // Store the information about the unique runids in the input file
    // together with the filename and the number of events for each runid
    // this information is needed later to check if inconsitencies exist
    // between the main input chain and any of the friend chains.

    //  GetRunIdInfo(fInFile->GetName(), chainName);

    // Add all additional input files to the input chain and do a consitency check
    {
        TDirectory::TContext restorecwd{};

        for (auto fileName : fInputChainList) {
            // Temporarily open the input file to extract information which
            // is needed to bring the friend trees in the correct order
            TFile* inputFile = TFile::Open(fileName);
            if (inputFile->IsZombie()) {
                LOG(fatal) << "Error opening the file " << fileName.Data()
                           << " which should be added to the input chain or as friend chain";
            }

            // Check if the branchlist is the same as for the first input file.
            Bool_t isOk = CompareBranchList(inputFile, chainName);
            if (!isOk) {
                LOG(fatal) << "Branch structure of the input file " << fRootFile->GetName()
                           << " and the file to be added " << fileName.Data();
                return kFALSE;
            }

            // Add the runid information for all files in the chain.
            // GetRunIdInfo(inputFile->GetName(), chainName);
            // Add the file to the input chain
            fBackgroundChain->Add(fileName);

            // Close the temporarly file
            inputFile->Close();
        }
    }
    fNoOfEntries = fBackgroundChain->GetEntries();
    FairRootManager::Instance()->SetInChain(fBackgroundChain, 0);

    for (Int_t i = 0; i < fListFolder->GetEntriesFast(); i++) {
        TFolder* fold = static_cast<TFolder*>(fListFolder->At(i));
        fEvtHeader = static_cast<FairEventHeader*>(fold->FindObjectAny("EventHeader."));
        fMCHeader = static_cast<FairMCEventHeader*>(fold->FindObjectAny("MCEventHeader."));
        if (fEvtHeader) {
            ActivateObject(reinterpret_cast<TObject**>(&fEvtHeader), "EventHeader.");
        }
        if (fMCHeader) {
            ActivateObject(reinterpret_cast<TObject**>(&fMCHeader), "MCEventHeader.");
        }
    }
    FairRootManager::Instance()->SetListOfFolders(fListFolder);

    LOG(info) << "Entries in this Source " << fNoOfEntries << " ------------";
    return kTRUE;
}

Bool_t FairMixedSource::SpecifyRunId()
{
    LOG(debug) << "---FairMixedSource::SpecifyRunId --- ";
    LOG(debug) << "---FairMixedSource::SpecifyRunId  fRunIdFromBG = " << fRunIdFromBG;
    LOG(debug) << "---FairMixedSource::SpecifyRunId  fRunIdFromSG = " << fRunIdFromSG;
    LOG(debug) << "---FairMixedSource::SpecifyRunId  fRunIdFromSG_identifier = " << fRunIdFromSG_identifier;

    if (fRunIdFromBG == fRunIdFromSG) {
        LOG(fatal)
            << "Please specify where to take the from: Signal or Bcckgrand by calling UseRunIdFromBG or UseRunIdFromSG";
        return false;
    }

    if (fRunIdFromBG) {
        fBackgroundChain->GetEntry(0);
        fBackgroundChain->Dump();
        LOG(debug) << "---Get RunId from background chain  --- ";
    } else {
        if (fRunIdFromSG_identifier <= fNoOfSignals) {
            TChain* Sig_chain = fRootManager->GetSignalChainNo(fRunIdFromSG_identifier);
            Sig_chain->GetEntry(0);
            LOG(debug) << "---Get RunId from Signal chain  --- ";
        } else {
            LOG(fatal) << "--- Invalid signal identifier, Max number of signals :  " << fNoOfSignals;
        }
    }
    if (fEvtHeader) {
        fOutHeader->SetRunId(fEvtHeader->GetRunId());
    }
    if (fMCHeader) {
        fOutHeader->SetRunId(fMCHeader->GetRunID());
    }
    return kTRUE;
}

Int_t FairMixedSource::ReadEvent(UInt_t i)
{
    SetEventTime();

    Double_t SBratio = gRandom->Uniform(0, 1);
    Bool_t GetASignal = kFALSE;

    if (fSBRatiobyN || fSBRatiobyT) {
        Double_t ratio = 0;
        for (const auto& mi : fSignalBGN) {
            ratio = mi.second;
            LOG(debug) << "---Check signal no. " << mi.first << " SBratio " << SBratio << " : ratio " << ratio;
            if (SBratio <= ratio) {
                TChain* chain = fSignalTypeList[mi.first];
                UInt_t entry = fCurrentEntry[mi.first];
                chain->GetEntry(entry);
                fOutHeader->SetMCEntryNumber(entry);
                fOutHeader->SetInputFileId(mi.first);
                fOutHeader->SetEventTime(GetEventTime());
                GetASignal = kTRUE;
                fCurrentEntry[mi.first] = entry + 1;
                LOG(debug) << "---Get entry No. " << entry << " from signal chain number --- " << mi.first << " --- ";
                break;
            }
        }
        if (!GetASignal) {
            UInt_t entry = fCurrentEntry[0];
            fBackgroundChain->GetEntry(entry);
            fOutHeader->SetMCEntryNumber(entry);
            fOutHeader->SetInputFileId(0);   // Background files has always 0 as Id
            fOutHeader->SetEventTime(GetEventTime());
            fCurrentEntry[0] = entry + 1;
            LOG(debug) << "---Get entry from background chain  --- ";
        }
    }

    fCurrentEntryNo = i;
    fOutHeader->SetEventTime(GetEventTime());
    LOG(debug) << "--Event number --- " << fCurrentEntryNo << " with time ----" << GetEventTime();

    return 0;
}

void FairMixedSource::Close() {}

void FairMixedSource::FillEventHeader(FairEventHeader* feh)
{
    feh->SetEventTime(fOutHeader->GetEventTime());
    feh->SetMCEntryNumber(fOutHeader->GetMCEntryNumber());
    feh->SetInputFileId(fOutHeader->GetInputFileId());
    feh->SetRunId(fOutHeader->GetRunId());
    LOG(debug) << "FairMixedSource::FillEventHeader() Event " << fCurrentEntryNo << " at " << feh->GetEventTime()
               << " -> Run id = " << fOutHeader->GetRunId() << " event#" << feh->GetMCEntryNumber() << " from file#"
               << fOutHeader->GetInputFileId();
    return;
}

void FairMixedSource::SetSignalFile(TString name, UInt_t identifier)
{
    TFile* SignalInFile = TFile::Open(name.Data());
    if (SignalInFile->IsZombie()) {
        LOG(fatal) << "Error opening the Signal file";
    } else {
        /** Set a signal file of certain type (identifier) if already exist add the file to the chain*/
        if (fSignalTypeList[identifier] == 0) {
            TChain* chain = new TChain(FairRootManager::GetTreeName(), Form("/%s", FairRootManager::GetFolderName()));
            fSignalTypeList[identifier] = chain;
            FairRootManager::Instance()->SetInChain(chain, identifier);
            fCurrentEntry[identifier] = 0;
            fNoOfSignals++;
            fActualSignalIdentifier = identifier;
            chain->AddFile(name.Data());
        } else {
            TChain* CurrentChain = fSignalTypeList[identifier];
            CurrentChain->AddFile(name.Data());
            //      TObjArray* fileElements=CurrentChain->GetListOfFiles();
        }
    }
}

void FairMixedSource::AddSignalFile(TString name, UInt_t identifier) { SetSignalFile(name, identifier); }

TChain* FairMixedSource::GetSignalChainNo(UInt_t i)
{
    if (i << fNoOfSignals) {
        return fSignalTypeList[i];
    } else {
        LOG(info) << "Error signal identifier " << i << " does not exist ";
        return 0;
    }
}

void FairMixedSource::SetBackgroundFile(TString name)
{
    fCurrentEntry[0] = 0;
    if (name.IsNull()) {
        LOG(info) << "No background file defined.";
    }
    fRootFile = TFile::Open(name);
    if (fRootFile->IsZombie()) {
        LOG(fatal) << "Error opening the Background file  " << name.Data();
    }
}

void FairMixedSource::AddBackgroundFile(TString name)
{
    if (name.IsNull()) {
        LOG(info) << "No background file defined.";
    }
    TFile* BGFile = TFile::Open(name);
    if (BGFile->IsZombie()) {
        LOG(fatal) << "Error opening the Background file " << name.Data();
    } else {
        if (fBackgroundChain != 0) {
            fBackgroundChain->AddFile(name.Data());
            //      TObjArray* fileElements=fBackgroundChain->GetListOfFiles();
        } else {
            LOG(fatal) << "Use SetBackGroundFile first, then add files to background";
        }
    }
}

Bool_t FairMixedSource::OpenBackgroundChain()
{
    // Get the folder structure from file which describes the input tree.
    // There are two different names possible, so check both.
    fCbmroot = fRootFile->Get<TFolder>(FairRootManager::GetFolderName());
    if (!fCbmroot) {
        fCbmroot = fRootFile->Get<TFolder>("cbmroot");
        if (!fCbmroot) {
            fCbmroot = fRootFile->Get<TFolder>("cbmout");
            if (!fCbmroot) {
                fCbmroot = gROOT->GetRootFolder()->AddFolder(FairRootManager::GetFolderName(), "Main Folder");
            } else {
                fCbmroot->SetName(FairRootManager::GetFolderName());
            }
        }
    }

    // Get The list of branches from the input file and add it to the
    // actual list of existing branches.
    // Add this list of branches also to the map of input trees, which
    // stores the information which branches belong to which input tree.
    // There is at least one primary input tree, but there can be many
    // additional friend trees.
    // This information is needed to add new files to the correct friend
    // tree. With this information it is also possible to check if the
    // input files which are added to the input chain all have the same
    // branch structure. Without this check it is possible to add trees
    // with a different branch structure but the same tree name. ROOT
    // probably only checks if the name of the tree is the same.

    auto list = fRootFile->Get<TList>("BranchList");
    TString chainName = "BGInChain";
    fInputLevel.push_back(chainName);
    if (list) {
        TObjString* Obj = 0;
        for (Int_t i = 0; i < list->GetEntries(); i++) {
            Obj = dynamic_cast<TObjString*>(list->At(i));
            fCheckInputBranches[chainName].push_back(Obj->GetString());
            FairRootManager::Instance()->AddBranchToList(Obj->GetString().Data());
        }
    }

    gROOT->GetListOfBrowsables()->Add(fCbmroot);
    fListFolder->Add(fCbmroot);
    return kTRUE;
}

Bool_t FairMixedSource::OpenSignalChain()
{
    for (const auto& mi : fSignalTypeList) {
        TChain* currentChain = mi.second;
        // cout << "Signal chain is : " << currentChain->GetName()<< endl;
        //   currentChain->Dump();
        TFile* ChainFirstFile = currentChain->GetFile();
        // cout << "First file in signal chain is : " << ChainFirstFile << endl;
        // Check if the branchlist is the same as for the first input file.
        Bool_t isOk = CompareBranchList(ChainFirstFile, "BGInChain");
        if (!isOk) {
            LOG(fatal) << "Branch structure of the signal chain is different than the back ground one";
        }
    }
    return kTRUE;
}

Bool_t FairMixedSource::ActivateObject(TObject** obj, const char* BrName)
{
    fBackgroundChain->SetBranchStatus(BrName, 1);
    fBackgroundChain->SetBranchAddress(BrName, obj);

    Int_t no = 0;
    for (const auto& mi : fSignalTypeList) {
        TChain* currentChain = mi.second;
        LOG(debug2) << "Set the Branch address for signal file number " << no++ << " and  branch " << BrName;
        currentChain->SetBranchStatus(BrName, 1);
        currentChain->SetBranchAddress(BrName, obj);
    }

    return kTRUE;
}

Bool_t FairMixedSource::ActivateObjectAny(void** obj, const std::type_info& info, const char* BrName)
{

    Bool_t BG_Object = ActivateObjectAnyImpl(fBackgroundChain, obj, info, BrName);

    for (const auto& mi : fSignalTypeList) {
        TChain* currentChain = mi.second;
        if (!(ActivateObjectAnyImpl(currentChain, obj, info, BrName)))
            return false;
    }
    return BG_Object;
}

void FairMixedSource::ReadBKEvent(UInt_t i)
{
    if (0 == i) {
        Int_t totEnt = fBackgroundChain->GetEntries();
        LOG(info) << "The number of entries in background chain is " << totEnt;
    }
    fBackgroundChain->GetEntry(i);
}

void FairMixedSource::BGWindowWidthNo(UInt_t background, UInt_t Signalid)
{
    fSBRatiobyN = kTRUE;
    if (fSBRatiobyT) {
        LOG(fatal) << "Signal rate already set by TIME!!";
    }
    Double_t value = 1.0 / (background + 1.0);
    LOG(debug) << "-- Signal id =  " << Signalid << " with weight = " << value;
    if (background != 0) {
        fSignalBGN[Signalid] = value;
    } else {
        LOG(fatal) << "Background cannot be Zero when setting the signal rate!!";
    }
}

void FairMixedSource::BGWindowWidthTime(Double_t background, UInt_t Signalid)
{
    fSBRatiobyT = kTRUE;
    if (fSBRatiobyN) {
        LOG(fatal) << "Signal rate already set by NUMBER!!";
    }
    if (fEventTimeInMCHeader) {
        LOG(fatal) << "You have to Set the Event mean time before using SetSignalRateTime!";
    }
    if (fEventMeanTime == 0) {
        LOG(fatal) << "Event mean time cannot be zero when using signal rate with time ";
    }
    /**convert to number of event by dividing by the mean time */
    Double_t value = fEventMeanTime / background;
    if (background != 0) {
        fSignalBGN[Signalid] = value;
    } else {
        LOG(fatal) << "Background cannot be Zero when setting the signal rate!!";
    }
}

Int_t FairMixedSource::CheckMaxEventNo(Int_t EvtEnd)
{
    Int_t MaxEventNo = 0;
    if (EvtEnd != 0) {
        MaxEventNo = EvtEnd;
    }
    Int_t localMax = 0;
    Int_t MaxBG = fBackgroundChain->GetEntries();
    Int_t MaxS = 0;
    Double_t ratio = 0.;
    for (const auto& mi : fSignalBGN) {
        TChain* chain = fSignalTypeList[mi.first];
        MaxS = chain->GetEntries();
        LOG(info) << "Signal chain  No " << mi.first << " has  : " << MaxS << " entries ";
        ratio = mi.second;
        if (floor(MaxS / ratio) > MaxBG) {
            localMax = MaxBG + static_cast<Int_t>(floor(MaxBG * ratio));
            LOG(warn) << "No of Event in Background chain is not enough for all signals in chain  " << mi.first;
        } else {
            localMax = static_cast<Int_t>(floor(MaxS / ratio));
            LOG(warn) << "No of Event in signal chain " << mi.first
                      << " is not enough, the maximum event number will be reduced to : " << localMax;
        }
        if (MaxEventNo == 0 || MaxEventNo > localMax) {
            MaxEventNo = localMax;
        }
    }
    LOG(info) << "Maximum No of Event will be set to : " << MaxEventNo;
    return MaxEventNo;
}

void FairMixedSource::SetEventMeanTime(Double_t mean)
{
    fEventMeanTime = mean;
    fTimeProb = std::make_unique<TF1>("TimeProb", "(1/[0])*exp(-x/[0])", 0., mean * 10);
    fTimeProb->SetParameter(0, mean);
    fTimeProb->GetRandom();
    fEventTimeInMCHeader = kFALSE;
}

void FairMixedSource::SetEventTimeInterval(Double_t min, Double_t max)
{
    // disable fTimeProb for the uniform distribution
    fTimeProb.reset();
    fEventTimeMin = min;
    fEventTimeMax = max;
    fEventMeanTime = (fEventTimeMin + fEventTimeMax) / 2;
    fEventTimeInMCHeader = kFALSE;
}

void FairMixedSource::SetBeamTime(Double_t beamTime, Double_t gapTime)
{
    fBeamTime = beamTime;
    fGapTime = gapTime;
}

void FairMixedSource::SetEventTime()
{
    LOG(debug) << "Set event time for Entry = " << fTimeforEntryNo << " , where the current entry is "
               << fCurrentEntryNo << " and eventTime is " << fEventTime;
    if (fBeamTime < 0) {
        fEventTime += GetDeltaEventTime();
    } else {
        do {
            fEventTime += GetDeltaEventTime();
        } while (fmod(fEventTime, fBeamTime + fGapTime) > fBeamTime);
    }
    LOG(debug) << "New time = " << fEventTime;
    fTimeforEntryNo = fCurrentEntryNo;
}

Double_t FairMixedSource::GetDeltaEventTime()
{
    Double_t deltaTime = 0;
    if (fTimeProb) {
        deltaTime = fTimeProb->GetRandom();
        LOG(debug) << "Time set via sampling method : " << deltaTime;
    } else {
        deltaTime = gRandom->Uniform(fEventTimeMin, fEventTimeMax);
        LOG(debug) << "Time set via Uniform Random : " << deltaTime;
    }
    return deltaTime;
}

Double_t FairMixedSource::GetEventTime()
{
    LOG(debug) << "-- Get Event Time --";
    if (!fEvtHeaderIsNew && fEvtHeader != 0) {
        Double_t EvtTime = fEvtHeader->GetEventTime();
        if (!(EvtTime < 0)) {
            return EvtTime;
        }
    }

    if (fEventTimeInMCHeader && !fMCHeader) {
        LOG(debug) << "No MCEventHeader, time is set to 0";
        return 0;
    } else if (fEventTimeInMCHeader && fMCHeader) {
        fEventTime = fMCHeader->GetT();
        LOG(debug) << "Get event time from MCEventHeader : " << fEventTime << " ns";
        return fEventTime;
    } else {

        if (fTimeforEntryNo != fCurrentEntryNo) {
            SetEventTime();
        }
        LOG(debug) << "Calculate event time from user input : " << fEventTime << " ns";
        return fEventTime;
    }
}

void FairMixedSource::ReadBranchEvent(const char* BrName)
{
    /**fill the object with content if the other branches in this tree entry were already read**/
    if (fEvtHeader == 0) {
        return;
    }   // No event header, Reading will start later
    TChain* chain = fSignalTypeList[fEvtHeader->GetInputFileId()];
    if (!chain) {
        return;
    }
    chain->FindBranch(BrName)->GetEntry(fEvtHeader->GetMCEntryNumber());
    return;
}

void FairMixedSource::ReadBranchEvent(const char* BrName, Int_t Entry)
{
    /**fill the object with content if the other branches in this tree entry were already read**/
    if (fEvtHeader == 0) {
        return;
    }   // No event header, Reading will start later
    TChain* chain = fSignalTypeList[fEvtHeader->GetInputFileId()];
    if (!chain) {
        return;
    }
    chain->FindBranch(BrName)->GetEntry(Entry);
    return;
}

void FairMixedSource::UseRunIdFromBG()
{
    /** Use the Backgraund rRunID to initialize the parameter for the run */
    fRunIdFromBG = kTRUE;
}

void FairMixedSource::UseRunIdfromSG(UInt_t identifier)
{
    /** Use the Backgraund rRunID to initialize the parameter for the run
     *@param identifier: Signal file identifier to be used by default we take the first Signal
     */
    fRunIdFromSG = kTRUE;
    fRunIdFromSG_identifier = identifier;
}
ClassImp(FairMixedSource);
