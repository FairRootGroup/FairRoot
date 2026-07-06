/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairRunAna source file                      -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#include "FairRunAna.h"

#include "FairBaseParSet.h"       // for FairBaseParSet
#include "FairEventHeader.h"      // for FairEventHeader
#include "FairField.h"            // for FairField
#include "FairFieldFactory.h"     // for FairFieldFactory
#include "FairFileHeader.h"       // for FairFileHeader
#include "FairFileSource.h"       // ONLY TEMPORARILY, FOR COMPABILITY
#include "FairLogger.h"           // for FairLogger, MESSAGE_ORIGIN
#include "FairMixedSource.h"      // ONLY TEMPORARILY, FOR COMPABILITY
#include "FairParSet.h"           // for FairParSet
#include "FairRootManager.h"      // for FairRootManager
#include "FairRunIdGenerator.h"   // for FairRunIdGenerator
#include "FairRuntimeDb.h"        // for FairRuntimeDb
#include "FairTask.h"             // for FairTask
#include "FairTrajFilter.h"       // for FairTrajFilter
#include "signal.h"

#include <TCollection.h>      // for TRangeDynCast
#include <TDirectory.h>       // for TDirectory::TContext
#include <TFile.h>            // for TFile
#include <TGeoManager.h>      // for gGeoManager, TGeoManager
#include <TKey.h>             // for TKey
#include <TList.h>            // for TList
#include <TObjArray.h>        // for TObjArray
#include <TObject.h>          // for TObject
#include <TROOT.h>            // for TROOT, gROOT
#include <TSeqCollection.h>   // for TSeqCollection
#include <TSystem.h>          // for TSystem, gSystem
#include <iostream>           // for operator<<, basic_ostream, etc
#include <stdlib.h>           // for exit
#include <string.h>           // for strcmp

using std::cout;
using std::endl;

static Bool_t gFRAIsInterrupted;

//_____________________________________________________________________________
static void FRA_handler_ctrlc(int)
{
    LOG(info) << "*********** CTRL C PRESSED *************";
    gFRAIsInterrupted = kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRunAna* FairRunAna::fgRinstance = nullptr;
//_____________________________________________________________________________
FairRunAna* FairRunAna::Instance()
{
    return fgRinstance;
}
//_____________________________________________________________________________
FairRunAna::FairRunAna()
    : FairRun()
    , fRunInfo()
    , fIsInitialized(kFALSE)
    , fInputGeoFile(0)
    , fLoadGeo(kFALSE)
    , fStatic(kFALSE)
    , fField(0)
    , fTimeStamps(kFALSE)
    , fInFileIsOpen(kFALSE)
    , fEventTimeMin(0)
    , fEventTimeMax(0)
    , fEventTime(0)
    , fEventMeanTime(0)
    , fTimeProb(0)
    , fFinishProcessingLMDFile(kFALSE)
    , fFileSource(0)
    , fMixedSource(0)
    , fStoreEventHeader(kTRUE)
{
    fgRinstance = this;
    fAna = kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRunAna::~FairRunAna()
{
    //  delete fFriendFileList;
    delete fField;
    if (gGeoManager) {
        if (gROOT->GetVersionInt() >= 60602) {
            gGeoManager->GetListOfVolumes()->Delete();
            gGeoManager->GetListOfShapes()->Delete();
        }
        delete gGeoManager;
    }
    if (fgRinstance == this) {
        // Do not point to a destructed object!
        fgRinstance = nullptr;
    }
}

//_____________________________________________________________________________

void FairRunAna::SetGeomFile(const char* GeoFileName)
{
    if (fIsInitialized) {
        LOG(fatal) << "Geometry file has to be set before Run::Init !";
        exit(-1);
    } else {
        TDirectory::TContext restorecwd{};
        fInputGeoFile = TFile::Open(GeoFileName);
        if (fInputGeoFile->IsZombie()) {
            LOG(error) << "Error opening Geometry Input file";
            fInputGeoFile = 0;
        }
        LOG(info) << "Opening Geometry input file: " << GeoFileName;
        fLoadGeo = kTRUE;
    }
}

//_____________________________________________________________________________

void FairRunAna::Init()
{
    if (fIsInitialized) {
        LOG(fatal) << "Error Init is already called before!";
        exit(-1);
    } else {
        fIsInitialized = kTRUE;
    }
    fRtdb = GetRuntimeDb();

    // Check if we have an input file to be used
    fInFileIsOpen = fRootManager->InitSource();
    fRootManager->InitSink();

    // Load Geometry from user file
    if (fLoadGeo) {
        SearchForTGeoManagerInGeoFile();
    } else {
        /*** Get the container that normly has the geometry and all the basic stuff from simulation*/
        fRtdb->getContainer("FairGeoParSet");
    }

    if (fInFileIsOpen) {
        // check that the geometry was loaded if not try all connected files!
        if (fLoadGeo && gGeoManager == 0) {
            LOG(info) << "Geometry was not found in the input file we will look in the friends if any!";
            TDirectory::TContext restorecwd{};
            TSeqCollection* fileList = gROOT->GetListOfFiles();
            for (auto nextfile : TRangeDynCast<TFile>(fileList)) {
                if (!nextfile) {
                    continue;
                }
                /// \todo This looks like a leak
                nextfile->Get("FAIRGeom");
                if (gGeoManager) {
                    break;
                }
            }
        }
    } else {   //  if(fInputFile )
        // NO input file but there is a geometry file
        if (fLoadGeo) {
            SearchForTGeoManagerInGeoFile();
        }
    }

    gROOT->GetListOfBrowsables()->Add(fTask);

    // Init the RTDB containers

    FairBaseParSet* par = dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));

    // Assure that basic info is there for the run
    //  if(par && fInputFile) {
    auto* evtHeader = GetEventHeader();
    if (par && fInFileIsOpen) {

        LOG(info) << "Parameter and input file are available, Assure that basic info is there for the run!";
        fRootManager->SpecifyRunId();
        FillEventHeader();
        fRunId = GetEvtHeaderRunId();

        // Copy the Event Header Info to Output
        evtHeader->Register(GetSink() ? fStoreEventHeader : false);

        // Init the containers in Tasks
        LOG(info) << "--- Initialize with RunId  --- " << fRunId;
        if (!fRtdb->initContainers(fRunId)) {
            LOG(error) << "FairRunAna::Init: fRtdb->initContainers failed";
        }
        fTask->SetParTask();
    } else {   // end----- if(fMixedInput)
        LOG(info) << "Initializing without input file or Mixed input";
        evtHeader->Register(GetSink() ? fStoreEventHeader : false);
        FairRunIdGenerator genid;
        fRunId = genid.generateId();
        fRtdb->addRun(fRunId);
        evtHeader->SetRunId(fRunId);
        fTask->SetParTask();
        if (!fRtdb->initContainers(fRunId)) {
            LOG(error) << "FairRunAna::Init: fRtdb->initContainers failed";
        }
    }

    FairFieldFactory* fieldfact = FairFieldFactory::Instance();
    if (fieldfact) {
        fieldfact->SetParm();
    }

    if (!fRtdb->initContainers(fRunId)) {
        LOG(error) << "FairRunAna::Init: fRtdb->initContainers failed";
    }
    fFileHeader->SetRunId(fRunId);

    // create a field
    // <DB>
    // Add test for external FairField settings
    if (fieldfact && !fField) {
        fField = fieldfact->createFairField();
    }

    // Align the geometry when it is avaialble in all cases
    // (read from file, read from container) and before it could
    // be used in the Init() function of a user task
    AlignGeometry();

    // Now call the User initialize for Tasks
    fTask->InitTask();

    // if the vis manager is available then initialize it!
    FairTrajFilter* fTrajFilter = FairTrajFilter::Instance();
    if (fTrajFilter) {
        fTrajFilter->Init();
    }

    // Create a list of time based branches (if any).
    fRootManager->UpdateListOfTimebasedBranches();

    // create the output tree after tasks initialisation
    fRootManager->WriteFolder();
    fRootManager->WriteFileHeader(fFileHeader);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::Run(Int_t Ev_start, Int_t Ev_end)
{
    gFRAIsInterrupted = kFALSE;

    if (fTimeStamps) {
        RunTSBuffers();
    } else {
        //  if (fInputFile==0) {
        if (!fInFileIsOpen) {
            DummyRun(Ev_start, Ev_end);
            return;
        }

        Int_t MaxAllowed = fRootManager->CheckMaxEventNo(Ev_end);
        if (MaxAllowed != -1) {
            if (Ev_end == 0) {
                if (Ev_start == 0) {
                    Ev_end = MaxAllowed;
                } else {
                    Ev_end = Ev_start;
                    if (Ev_end > MaxAllowed) {
                        Ev_end = MaxAllowed;
                    }
                    Ev_start = 0;
                }
            } else {
                if (Ev_end > MaxAllowed) {
                    cout << "-------------------Warning---------------------------" << endl;
                    cout << " -W FairRunAna : File has less events than requested!!" << endl;
                    cout << " File contains : " << MaxAllowed << " Events" << endl;
                    cout << " Requested number of events = " << Ev_end << " Events" << endl;
                    cout << " The number of events is set to " << MaxAllowed << " Events" << endl;
                    cout << "-----------------------------------------------------" << endl;
                    Ev_end = MaxAllowed;
                }
            }
            LOG(info) << "FairRunAna::Run() After checking, the run will run from event " << Ev_start << " to "
                      << Ev_end << ".";
        } else {
            LOG(info) << "FairRunAna::Run() continue running without stop";
        }

        if (fGenerateRunInfo) {
            fRunInfo.Reset();
        }

        for (int i = Ev_start; i < Ev_end || MaxAllowed == -1; i++) {

            gSystem->IgnoreInterrupt();
            //  gFRAIsInterrupted = kFALSE;
            signal(SIGINT, FRA_handler_ctrlc);

            if (gFRAIsInterrupted) {
                LOG(warn) << "FairRunAna::Run() Event loop was interrupted by the user!";
                break;
            }

            auto readEventReturn = fRootManager->ReadEvent(i);

            if (readEventReturn != 0) {
                LOG(warn) << "FairRunAna::Run() fRootManager->ReadEvent(" << i << ") returned " << readEventReturn
                          << ". Breaking the event loop";
                break;
            }

            FillEventHeader();
            CheckRunIdChanged();

            // std::cout << "WriteoutBufferData with time: " << fRootManager->GetEventTime();
            fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());
            fTask->ExecuteTask("");
            Fill();
            fRootManager->DeleteOldWriteoutBufferData();
            fTask->FinishEvent();

            if (fGenerateRunInfo) {
                fRunInfo.StoreInfo();
            }
            if (nullptr != FairTrajFilter::Instance()) {
                FairTrajFilter::Instance()->Reset();
            }
        }

        fRootManager->StoreAllWriteoutBufferData();
        fTask->FinishTask();
        if (fGenerateRunInfo) {
            fRunInfo.WriteInfo();
        }
        fRootManager->LastFill();
        fRootManager->Write();
    }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::RunEventReco(Int_t Ev_start, Int_t Ev_end)
{
    Int_t MaxAllowed = fRootManager->CheckMaxEventNo(Ev_end);
    if (MaxAllowed != -1) {
        if (Ev_end == 0) {
            if (Ev_start == 0) {
                Ev_end = MaxAllowed;
            } else {
                Ev_end = Ev_start;
                if (Ev_end > MaxAllowed) {
                    Ev_end = MaxAllowed;
                }
                Ev_start = 0;
            }
        } else {
            if (Ev_end > MaxAllowed) {
                cout << "-------------------Warning---------------------------" << endl;
                cout << " -W FairRunAna : File has less events than requested!!" << endl;
                cout << " File contains : " << MaxAllowed << " Events" << endl;
                cout << " Requested number of events = " << Ev_end << " Events" << endl;
                cout << " The number of events is set to " << MaxAllowed << " Events" << endl;
                cout << "-----------------------------------------------------" << endl;
                Ev_end = MaxAllowed;
            }
        }
        LOG(info) << "FairRunAna::Run() After checking, the run will run from event " << Ev_start << " to " << Ev_end
                  << ".";
    } else {
        LOG(info) << "FairRunAna::Run() continue running without stop";
    }

    if (fGenerateRunInfo) {
        fRunInfo.Reset();
    }

    for (int i = Ev_start; i < Ev_end; i++) {
        fRootManager->ReadEvent(i);
        /**
         * if we have simulation files then they have MC Event Header and the Run Id is in it, any way it
         * would be better to make FairMCEventHeader a subclass of FairEvtHeader.
         */

        CheckRunIdChanged();

        // FairMCEventHeader* header = dynamic_cast<FairMCEventHeader*>(fRootManager->GetObject("MCEventHeader.");
        //    std::cout << "WriteoutBufferData with time: " << fRootManager->GetEventTime();
        fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());
        fTask->ExecuteTask("");

        FillEventHeader();
        // Fill();
        fTask->FinishEvent();

        if (fGenerateRunInfo) {
            fRunInfo.StoreInfo();
        }
        if (nullptr != FairTrajFilter::Instance()) {
            FairTrajFilter::Instance()->Reset();
        }
    }

    fTask->FinishTask();
    if (fGenerateRunInfo) {
        fRunInfo.WriteInfo();
    }
    fRootManager->LastFill();
    fRootManager->Write();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::Run(Double_t delta_t)
{
    while (fRootManager->ReadNextEvent(delta_t)) {
        fTask->ExecuteTask("");
        FillEventHeader();
        Fill();
        fRootManager->DeleteOldWriteoutBufferData();
        fTask->FinishEvent();
        if (nullptr != FairTrajFilter::Instance()) {
            FairTrajFilter::Instance()->Reset();
        }
    }

    fRootManager->StoreAllWriteoutBufferData();
    fTask->FinishTask();
    fRootManager->LastFill();
    fRootManager->Write();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::RunMQ(Long64_t entry)
{
    /**
   This methode is only needed and used with ZeroMQ
   it read a certain event and call the task exec, but no output is written
   */
    fRootManager->ReadEvent(entry);
    CheckRunIdChanged();
    fTask->ExecuteTask("");
    FillEventHeader();
    fTask->FinishTask();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::RunSingleEntry(Long64_t entry)
{
    fRootManager->ReadEvent(entry);
    CheckRunIdChanged();
    fTask->ExecuteTask("");
    FillEventHeader();
    fTask->FinishTask();
    Fill();
    fRootManager->DeleteOldWriteoutBufferData();
    fRootManager->LastFill();
    fRootManager->Write();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::RunTSBuffers()
{
    Int_t globalEvent = 0;

    bool firstRun = true;
    while (firstRun || !fRootManager->AllDataProcessed()) {
        firstRun = false;
        if (globalEvent < fRootManager->CheckMaxEventNo(
                0)) {   // this step is necessary to load in all data which is not read in via TSBuffers
            fRootManager->ReadNonTimeBasedEventFromBranches(globalEvent++);
        }
        fTask->ExecuteTask("");
        FillEventHeader();
        Fill();
        fRootManager->DeleteOldWriteoutBufferData();
        fTask->FinishEvent();
        if (nullptr != FairTrajFilter::Instance()) {
            FairTrajFilter::Instance()->Reset();
        }
    }
    fRootManager->StoreAllWriteoutBufferData();
    fTask->FinishTask();
    fRootManager->LastFill();
    fRootManager->Write();
}
//_____________________________________________________________________________
//_____________________________________________________________________________

void FairRunAna::RunOnLmdFiles(UInt_t NStart, UInt_t NStop)
{
    if (NStart == 0 && NStop == 0) {
        NStart = 0;
        NStop = 1000000000;
        LOG(info) << " Maximum number of event is set to 1E9";
    }
    for (UInt_t i = NStart; i < NStop; i++) {
        if (fFinishProcessingLMDFile) {
            i = NStop;   /// Same result like break
        }

        fTask->ExecuteTask("");
        FillEventHeader();
        Fill();
    }

    fTask->FinishTask();
    fRootManager->Write();
}
//_____________________________________________________________________________
void FairRunAna::RunOnTBData()
{
    //  std::cout << "FairRunAna::RunOnTBData " << std::endl;
    while (!fRootManager->FinishRun()) {
        fTask->ExecuteTask("");
        Fill();
        fTask->FinishEvent();
    }

    fTask->FinishTask();
    fRootManager->LastFill();
    fRootManager->Write();
}
//_____________________________________________________________________________
void FairRunAna::DummyRun(Int_t Ev_start, Int_t Ev_end)
{
    /** This methode is just for testing, if you are not sure about what you do, don't use it */
    for (int i = Ev_start; i < Ev_end; i++) {
        fTask->ExecuteTask("");
        FillEventHeader();
        Fill();
    }
    fTask->FinishTask();
    fRootManager->Write();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::TerminateRun()
{
    fRootManager->StoreAllWriteoutBufferData();
    fTask->FinishTask();
    //  gDirectory->SetName(fRootManager->GetOutFile()->GetName());
    //  fRunInfo.WriteInfo(); // CRASHES due to file ownership i guess...
    //   cout << ">>> SlaveTerminate fRootManager->GetInChain()->Print()" << endl;
    //   fRootManager->GetInChain()->Print();
    //   cout << ">>>------------------------------------------------<<<" << endl;
    fRootManager->LastFill();
    fRootManager->Write();
}
//_____________________________________________________________________________

/**
 * \sa FairRunOnline::CheckRunIdChanged
 */
void FairRunAna::CheckRunIdChanged()
{
    auto newrunid = GetEvtHeaderRunId();
    if (newrunid == fRunId) {
        return;
    }

    LOG(debug) << "FairRunAna::CheckRunIdChanged() Detected changed RunID from " << fRunId << " to " << newrunid;
    fRunId = newrunid;
    if (fStatic) {
        LOG(debug) << "FairRunAna::CheckRunIdChanged: ReInit not called because initialisation is static.";
        return;
    }
    LOG(debug) << "FairRunAna::CheckRunIdChanged: Call Reinit.";
    Reinit(fRunId);
    fTask->ReInitTask();
}

void FairRunAna::Reinit(UInt_t runId)
{
    // reinit procedure
    if (!fRtdb->initContainers(runId)) {
        LOG(error) << "FairRunAna::Reinit: fRtdb->initContainers failed";
    }
}
//_____________________________________________________________________________

void FairRunAna::RunWithTimeStamps()
{
    if (fIsInitialized) {
        LOG(warn) << "RunWithTimeStamps has to be set before Run::Init !";
        exit(-1);
    } else {
        fTimeStamps = kTRUE;
    }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::SetContainerStatic(Bool_t tempBool)
{
    fStatic = tempBool;
    if (fStatic) {
        LOG(info) << "Parameter Cont. initialisation is static";
    } else {
        LOG(info) << "Parameter Cont. initialisation is NOT static";
    }
}
//_____________________________________________________________________________
void FairRunAna::Fill()
{
    if (fMarkFill) {
        fRootManager->Fill();
    } else {
        fMarkFill = kTRUE;
    }
}
//_____________________________________________________________________________

void FairRunAna::SearchForTGeoManagerInGeoFile()
{
    if (!fInputGeoFile) {   // First check if the user has a separate Geo file!
        return;
    }
    for (auto key : TRangeDynCast<TKey>(fInputGeoFile->GetListOfKeys())) {
        if (!key) {
            continue;
        }
        auto geo = key->ReadObject<TGeoManager>();
        if (!geo) {
            continue;
        }
        gGeoManager = geo;
        break;
    }
}
