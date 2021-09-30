/********************************************************************************
 * Copyright (C) 2014-2021 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairRunAnaProof source file                 -----
// -----            Created 30/04/13  by R. Karabowicz                 -----
// -------------------------------------------------------------------------

#include "FairRunAnaProof.h"

#include "FairConfig.h"
#include "FairBaseParSet.h"
#include "FairEventHeader.h"
#include "FairFieldFactory.h"
#include "FairFileHeader.h"
#include "FairLogger.h"
#include "FairParIo.h"
#include "FairRunIdGenerator.h"
#include "FairRuntimeDb.h"
#include "FairSink.h"
#include "FairTask.h"
#include "FairTrajFilter.h"

#include <TGeoManager.h>
#include <TKey.h>
#include <TProof.h>
#include <TROOT.h>

FairRunAnaProof* FairRunAnaProof::fRAPInstance = 0;

FairRunAnaProof* FairRunAnaProof::Instance() { return fRAPInstance; }

FairRunAnaProof::FairRunAnaProof(const char* proofName)
    : FairRunAna()
    , fProof(nullptr)
    , fRunOnProofWorker(kFALSE)
    , fProofServerName(proofName)
    , fProofParName(FairConfig::Instance().GetVMCWorkDir() + "/gconfig/libFairRoot.par")
    , fOutputDirectory("")
    , fProofOutputStatus("copy")
    , fProofFileSource(0)
{
    if (strcmp(proofName, "RunOnProofWorker") == 0) {
        fRunOnProofWorker = kTRUE;
    } else {
        LOG(info) << "+++++++ T P R O O F +++++++++++++++++++++++++++++++++";
        LOG(info) << "creating TProof* proof = TProof::Open(\"" << fProofServerName.Data() << "\");";
        TProof::AddEnvVar("LOCALDATASERVER", "file://");
        //    TProof* proof = TProof::Open("lite:///?workers=1");
        fProof = TProof::Open(fProofServerName.Data());
        LOG(info) << "+++++++ C R E A T E D +++++++++++++++++++++++++++++++";
    }

    fRAPInstance = this;
    fAna = kTRUE;
}

FairRunAnaProof::~FairRunAnaProof() {}

void FairRunAnaProof::Init()
{
    fInFileIsOpen = fRootManager->InitSource();

    if (fIsInitialized) {
        LOG(fatal) << "Error Init is already called before!";
        exit(-1);
    } else {
        fIsInitialized = kTRUE;
    }

    if (!fRunOnProofWorker) {
        // Open the input file and add other input files added by AddFile to the
        // input chain. Do a check if the added files are of the same type
        // as the the input file. Same type means check if they contain the
        // same branch.
    }
    // Load Geometry from user file

    if (fLoadGeo) {
        if (fInputGeoFile != 0) {   // First check if the user has a separate Geo file!
            TIter next(fInputGeoFile->GetListOfKeys());
            TKey* key;
            while ((key = static_cast<TKey*>(next()))) {
                if (strcmp(key->GetClassName(), "TGeoManager") != 0) {
                    continue;
                }
                gGeoManager = static_cast<TGeoManager*>(key->ReadObj());
                break;
            }
        }
    } else {
        //    FairGeoParSet* geopar=dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));
        fRtdb->getContainer("FairGeoParSet");
    }

    if (fInFileIsOpen) {
        if (fRunOnProofWorker) {
            if (fLoadGeo && gGeoManager == 0) {
                fProofFileSource->GetInTree()->GetCurrentFile()->Get("FAIRGeom");
            }
        } else {

            // Add all friend files defined by AddFriend to the correct chain
            if (fLoadGeo && gGeoManager == 0) {
                // Check if the geometry in the first file of the Chain
                fProofFileSource->GetInTree()->GetCurrentFile()->Get("FAIRGeom");
            }
            // check that the geometry was loaded if not try all connected files!
            if (fLoadGeo && gGeoManager == 0) {
                LOG(info) << "Geometry was not found in the input file we will look in the friends if any!";
                TFile* currentfile = gFile;
                TFile* nextfile = 0;
                TSeqCollection* fileList = gROOT->GetListOfFiles();
                for (Int_t k = 0; k < fileList->GetEntries(); k++) {
                    nextfile = static_cast<TFile*>(fileList->At(k));
                    if (nextfile) {
                        nextfile->Get("FAIRGeom");
                    }
                    if (gGeoManager) {
                        break;
                    }
                }
                gFile = currentfile;
            }
        }
    } else {   //  if(fInputFile )
        // NO input file but there is a geometry file
        if (fLoadGeo) {
            if (fInputGeoFile != 0) {   // First check if the user has a separate Geo file!
                TIter next(fInputGeoFile->GetListOfKeys());
                TKey* key;
                while ((key = static_cast<TKey*>(next()))) {
                    if (strcmp(key->GetClassName(), "TGeoManager") != 0) {
                        continue;
                    }
                    gGeoManager = static_cast<TGeoManager*>(key->ReadObj());
                    break;
                }
            }
        }
    }
    // Init the Chain ptr
    //  fcurrent = fChainList.begin();
    // fOutFile = fRootManager->OpenOutFile(fOutname);

    if (!fRunOnProofWorker) {
        LOG(warn) << "QUITTING, CAUSE IT'S not running on proof worker";
        return;
    }
    gROOT->GetListOfBrowsables()->Add(fTask);

    // Init the RTDB containers
    fRtdb = GetRuntimeDb();
    FairBaseParSet* par = static_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));

    /**Set the IO Manager to run with time stamps*/
    if (fTimeStamps) {
        fRootManager->RunWithTimeStamps();
    }

    // create the output tree after tasks initialisation
    fRootManager->InitSink();

    // Assure that basic info is there for the run

    if (par && fInFileIsOpen) {

        LOG(info) << "Parameter and input file are available, Assure that basic info is there for the run!";
        fRootManager->ReadEvent(0);

        GetEventHeader();

        fRootManager->FillEventHeader(fEvtHeader);

        fRunId = fEvtHeader->GetRunId();

        // Copy the Event Header Info to Output
        fEvtHeader->Register(kTRUE);

        // Copy the Event Header Info to Output
        fEvtHeader->Register();

        // Init the containers in Tasks

        fRtdb->initContainers(fRunId);
        fTask->SetParTask();

        fRtdb->initContainers(fRunId);
        if (gGeoManager == 0) {}
        //  fRootManager->SetBranchNameList(par->GetBranchNameList());

    } else {
        LOG(info) << "Initializing without input file or Mixed input";
        FairEventHeader* evt = GetEventHeader();
        evt->Register();
        FairRunIdGenerator genid;
        fRunId = genid.generateId();
        fRtdb->addRun(fRunId);
        evt->SetRunId(fRunId);
        fTask->SetParTask();
        fRtdb->initContainers(fRunId);
    }
    FairFieldFactory* fieldfact = FairFieldFactory::Instance();
    if (fieldfact) {
        fieldfact->SetParm();
    }

    fRtdb->initContainers(fRunId);
    fFileHeader->SetRunId(fRunId);

    // create a field
    // <DB>
    // Add test for external FairField settings
    if (fieldfact && !fField) {
        fField = fieldfact->createFairField();
    }
    // Now call the User initialize for Tasks
    fTask->InitTask();
    // if the vis manager is available then initialize it!
    FairTrajFilter* fTrajFilter = FairTrajFilter::Instance();
    if (fTrajFilter) {
        fTrajFilter->Init();
    }

    fRootManager->UpdateListOfTimebasedBranches();

    fRootManager->WriteFolder();
    fRootManager->WriteFileHeader(fFileHeader);
}

void FairRunAnaProof::InitContainers()
{
    fRtdb = GetRuntimeDb();
    FairBaseParSet* par = dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));

    if (par && fInFileIsOpen) {
        fRootManager->ReadEvent(0);

        fEvtHeader = dynamic_cast<FairEventHeader*>(fRootManager->GetObject("EventHeader."));

        if (nullptr == fEvtHeader)
            LOG(fatal) << "Could not read event header.";

        fRootManager->FillEventHeader(fEvtHeader);

        fRunId = fEvtHeader->GetRunId();

        // Copy the Event Header Info to Output
        fEvtHeader->Register();

        // Init the containers in Tasks
        fRtdb->initContainers(fRunId);
        fTask->ReInitTask();
        //    fTask->SetParTask();
        fRtdb->initContainers(fRunId);
        if (gGeoManager == 0) {
            //   par->GetGeometry();
        }
    }
}

void FairRunAnaProof::SetSource(FairSource* tempSource)
{
    // FairRunAnaProof should accept only FairFileSource
    if (strncmp(tempSource->GetName(), "FairFileSource", 14) != 0) {
        LOG(warn) << "FairRunAnaProof. Seems you are trying to set different source than FairFileSource";
    }
    fRootManager->SetSource(tempSource);
    fProofFileSource = static_cast<FairFileSource*>(tempSource);
}

void FairRunAnaProof::Run(Int_t Ev_start, Int_t Ev_end)
{
    RunOnProof(Ev_start, Ev_end);
    return;
}

void FairRunAnaProof::RunOneEvent(Long64_t entry)
{
    if (fTimeStamps) {
        RunTSBuffers();
    } else {
        UInt_t tmpId = 0;
        fRootManager->ReadEvent(entry);

        fRootManager->FillEventHeader(fEvtHeader);

        tmpId = fEvtHeader->GetRunId();
        if (tmpId != fRunId) {
            fRunId = tmpId;
            if (!fStatic) {
                Reinit(fRunId);
                fTask->ReInitTask();
            }
        }
        fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());

        fTask->ExecuteTask("");
        fRootManager->Fill();
        fRootManager->DeleteOldWriteoutBufferData();
        fTask->FinishEvent();
    }
}

void FairRunAnaProof::RunOnProof(Int_t NStart, Int_t NStop)
{
    fProofOutputStatus.ToLower();
    if (!fProofOutputStatus.Contains("copy") && !fProofOutputStatus.Contains("merge")) {
        LOG(warn) << "FairRunAnaProof::RunOnProof. Do not know how to create output \"" << fProofOutputStatus.Data()
                  << "\".";
        LOG(warn) << "FairRunAnaProof::RunOnProof. Please use SetProofOutputStatus to either \"copy\" or \"merge\".";
        LOG(warn) << "FairRunAnaProof::RunOnProof. For the current run using the \"merge\" setting.";
        fProofOutputStatus = "merge";
    }

    //  TChain* inChain = static_cast<TChain*>(fRootManager->GetInChain());
    TChain* inChain = static_cast<TChain*>(fProofFileSource->GetInChain());
    TString par1File = "";
    TString par2File = "";
    if (fRtdb->getFirstInput()) {
        par1File = fRtdb->getFirstInput()->getFilename();
    }
    if (fRtdb->getSecondInput()) {
        par2File = fRtdb->getSecondInput()->getFilename();
    }

    TString outDir = (fOutputDirectory.Length() > 1 ? fOutputDirectory.Data() : gSystem->WorkingDirectory());

    fProof->AddInput(fTask);

    // get file name from FairSink
    TString fileName = fRootManager->GetSink()->GetFileName();
    LOG(info) << " outputFileName = " << fileName.Data();
    if (fileName.Length() < 5)
        fileName = "proofOutput.root";

    fProof->AddInput(new TNamed("FAIRRUNANA_fContainerStatic", (fStatic ? "kTRUE" : "kFALSE")));
    fProof->AddInput(new TNamed("FAIRRUNANA_fProofOutputStatus", fProofOutputStatus.Data()));
    fProof->AddInput(new TNamed("FAIRRUNANA_fOutputDirectory", outDir.Data()));
    fProof->AddInput(new TNamed("FAIRRUNANA_fOutputFileName", fileName.Data()));
    fProof->AddInput(new TNamed("FAIRRUNANA_fParInput1FName", par1File.Data()));
    fProof->AddInput(new TNamed("FAIRRUNANA_fParInput2FName", par2File.Data()));

    Int_t nofChainEntries = inChain->GetEntries();
    LOG(info) << "FairRunAnaProof::RunOnProof(): The chain seems to have " << nofChainEntries << " entries.";

    TObjArray* listOfFiles = inChain->GetListOfFiles();
    LOG(info) << "FairRunAnaProof::RunOnProof(): There are " << listOfFiles->GetEntries() << " files in the chain.";

    inChain->SetProof();

    Int_t nofEventsToAnalyze = NStop - NStart;

    if (nofEventsToAnalyze <= 0) {
        LOG(info) << "You requested to analyze events from " << NStart << " to " << NStop << " that is "
                  << nofEventsToAnalyze << " events!!!";
        nofEventsToAnalyze = nofChainEntries - NStart;
        LOG(info) << "It will be changed to analyze all events from " << NStart << " to the end of chain ("
                  << nofChainEntries << "), that is to analyze " << nofEventsToAnalyze << " events.";
    }

    LOG(info) << "FairRunAnaProof::RunOnProof(): Starting inChain->Process(\"FairAnaSelector\",\"\","
              << nofEventsToAnalyze << "," << NStart << ")";
    inChain->Process("FairAnaSelector", "", nofEventsToAnalyze, NStart);
    LOG(info) << "FairRunAnaProof::RunOnProof(): inChain->Process DONE";

    return;
}

// // void FairRunAnaProof::SetOutputFile(const char* fname)
// {
//   fOutname=fname;
// }
//
// // void FairRunAnaProof::SetOutputFile(TFile* f)
// {
//   if (! fRootManager) return;

//   fOutname=f->GetName();
//   fRootManager->OpenOutFile(f);
//   fOutFile = f;

// }
//
ClassImp(FairRunAnaProof);
