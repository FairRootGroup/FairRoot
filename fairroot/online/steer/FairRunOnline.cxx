/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairRunOnline source file                   -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#include "FairRunOnline.h"

#include "FairBaseParSet.h"
#include "FairEventHeader.h"
#include "FairField.h"
#include "FairFileHeader.h"
#include "FairGeoParSet.h"
#include "FairParSet.h"   // for FairParSet
#include "FairRootManager.h"
#include "FairRunIdGenerator.h"
#include "FairRuntimeDb.h"
#include "FairSource.h"   // for FairSource, kONLINE
#include "FairTask.h"

#include <TCollection.h>   // for TIter
#include <TGeoManager.h>
#include <THttpServer.h>
#include <TList.h>        // for TList
#include <TObjArray.h>    // for TObjArray
#include <TObjString.h>   // for TObjString
#include <TObject.h>      // for TObject
#include <TROOT.h>
#include <TSystem.h>
#include <fairlogger/Logger.h>
#include <iostream>
#include <signal.h>
#include <stdlib.h>

using std::cout;
using std::endl;

FairRunOnline* FairRunOnline::fgRinstance = nullptr;

FairRunOnline* FairRunOnline::Instance()
{
    return fgRinstance;
}

FairRunOnline::FairRunOnline()
    : FairRun()
    , fAutomaticFinish(kTRUE)
    , fIsInitialized(kFALSE)
    , fStatic(kFALSE)
    , fField(0)
    , fNevents(0)
    , fServer(nullptr)
    , fServerRefreshRate(0)
{
    fgRinstance = this;
    fAna = kTRUE;
    LOG(info) << "FairRunOnline constructed at " << this;
}

FairRunOnline::FairRunOnline(FairSource* source)
    : FairRun()
    , fAutomaticFinish(kTRUE)
    , fIsInitialized(kFALSE)
    , fStatic(kFALSE)
    , fField(0)
    , fNevents(0)
    , fServer(nullptr)
    , fServerRefreshRate(0)
{
    SetSource(source);
    fgRinstance = this;
    fAna = kTRUE;
    LOG(info) << "FairRunOnline constructed at " << this;
}

FairRunOnline::~FairRunOnline()
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
    delete fServer;
    if (fgRinstance == this) {
        // Do not point to a destructed object!
        fgRinstance = nullptr;
    }
}

static Bool_t gIsInterrupted;

static void handler_ctrlc(int)
{
    gIsInterrupted = kTRUE;
}

void FairRunOnline::Init()
{
    LOG(info) << "FairRunOnline::Init";
    if (fIsInitialized) {
        LOG(fatal) << "Error Init is already called before!";
        exit(-1);
    } else {
        fIsInitialized = kTRUE;
    }

    fRootManager->InitSink();
    fRootManager->InitSource();

    //  FairGeoLoader* loader = new FairGeoLoader("TGeo", "Geo Loader");
    //  FairGeoInterface* GeoInterFace = loader->getGeoInterface();
    //  GeoInterFace->SetNoOfSets(ListOfModules->GetEntries());
    //  GeoInterFace->setMediaFile(MatFname.Data());
    //  GeoInterFace->readMedia();

    // Add a Generated run ID to the FairRunTimeDb for input data which contain a FairMCEventHeader
    // The call doesn't make sense for online sources which doesn't contain a  FairMCEventHeader

    if (kONLINE != GetSource()->GetSourceType()) {
        fRootManager->ReadEvent(0);
    }

    // --- Get event header from Run
    auto* evtHeader = GetEventHeader();
    FillEventHeader();
    if (0 == fRunId)   // Run ID was not set in run manager
    {
        if (0 == GetEvtHeaderRunId())   // Run ID was not set in source
        {
            // Generate unique Run ID
            FairRunIdGenerator genid;
            fRunId = genid.generateId();
            GetSource()->SetRunId(fRunId);
        } else {
            // Use Run ID from source
            fRunId = GetEvtHeaderRunId();
        }
    } else {
        // Run ID was set in the run manager - propagate to source
        GetSource()->SetRunId(fRunId);
    }

    fRtdb->addRun(fRunId);
    fFileHeader->SetRunId(fRunId);
    FairBaseParSet* par = dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));
    FairGeoParSet* geopar = dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));
    if (geopar) {
        geopar->SetGeometry(gGeoManager);
    }
    if (fField) {
        fField->Init();
        fField->FillParContainer();
    }
    TList* containerList = fRtdb->getListOfContainers();
    TIter next(containerList);
    FairParSet* cont;
    TObjArray* ContList = new TObjArray();
    while ((cont = dynamic_cast<FairParSet*>(next()))) {
        ContList->Add(new TObjString(cont->GetName()));
    }
    if (par) {
        par->SetContListStr(ContList);
        par->setChanged();
        par->setInputVersion(fRunId, 1);
    }
    if (geopar) {
        geopar->setChanged();
        geopar->setInputVersion(fRunId, 1);
    }

    fRootManager->WriteFileHeader(fFileHeader);

    GetSource()->SetParUnpackers();
    fTask->SetParTask();
    if (!fRtdb->initContainers(fRunId)) {
        LOG(error) << "FairRunOnline::Init: fRtdb->initContainers failed";
    }

    LOG(info) << "FairRunOnline::Init() Event header at " << evtHeader;
    fRootManager->Register("EventHeader.", "Event", evtHeader, (nullptr != GetSink()));
    evtHeader->SetRunId(fRunId);

    if (!GetSource()->InitUnpackers()) {
        LOG(fatal) << "FairRunOnline->Init() InitUnpackers() failed!";
        return;
    }

    // Now call the User initialize for Tasks
    fTask->InitTask();

    // create the output tree after tasks initialisation
    fRootManager->InitSink();
    fRootManager->WriteFolder();
    fRootManager->WriteFileHeader(fFileHeader);
}

Int_t FairRunOnline::EventLoop()
{
    gSystem->IgnoreInterrupt();
    signal(SIGINT, handler_ctrlc);

    FillEventHeader();
    if (!CheckRunIdChanged()) {
        return 1;
    }

    fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());
    fTask->ExecuteTask("");
    // TODO: Fill the event header again? Is this necessary?
    FillEventHeader();
    Fill();
    fRootManager->DeleteOldWriteoutBufferData();
    fTask->FinishEvent();
    fNevents += 1;
    if (fServer && 0 == (fNevents % fServerRefreshRate)) {
        fServer->ProcessRequests();
    }

    if (gIsInterrupted) {
        return 1;
    }

    return 0;
}

void FairRunOnline::Run(Int_t Ev_start, Int_t Ev_end)
{
    fNevents = 0;

    gIsInterrupted = kFALSE;

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
    }
    Int_t status;
    if (Ev_start < 0) {
        while (kTRUE) {
            status = fRootManager->ReadEvent();
            if (0 == status) {
                status = EventLoop();
            }
            if (1 == status) {
                break;
            } else if (2 == status) {
                continue;
            }
            if (gIsInterrupted) {
                break;
            }
        }
    } else {
        for (Int_t i = Ev_start; i < Ev_end; i++) {
            status = fRootManager->ReadEvent(i);
            if (0 == status) {
                status = EventLoop();
            }
            if (1 == status) {
                break;
            } else if (2 == status) {
                i -= 1;
                continue;
            }

            if (gIsInterrupted) {
                break;
            }
        }
    }

    fRootManager->StoreAllWriteoutBufferData();
    if (fAutomaticFinish) {
        Finish();
    }
}

void FairRunOnline::Finish()
{
    fTask->FinishTask();
    fRootManager->LastFill();
    fRootManager->Write();
}

void FairRunOnline::ActivateHttpServer(Int_t refreshRate, Int_t httpServer)
{
    TString serverAddress = "http:";
    serverAddress += httpServer;
    fServer = new THttpServer(serverAddress);
    fServerRefreshRate = refreshRate;
}

void FairRunOnline::RegisterHttpCommand(TString name, TString command)
{
    if (fServer) {
        TString path = "/Objects/HISTO";
        fServer->RegisterCommand(name, path + command);
    }
}

/**
 * \sa FairRunAna::CheckRunIdChanged
 */
bool FairRunOnline::CheckRunIdChanged()
{
    auto const tmpId = GetEvtHeaderRunId();
    if (tmpId == fRunId) {
        return true;
    }

    LOG(info) << "FairRunOnline::CheckRunIdChanged: Detected changed RunID from " << fRunId << " to " << tmpId;
    fRunId = tmpId;
    if (fStatic) {
        LOG(info) << "FairRunOnline::CheckRunIdChanged: ReInit not called because initialisation is static.";
        return true;
    }
    LOG(info) << "FairRunOnline::CheckRunIdChanged: Call Reinit.";
    Reinit(fRunId);
    if (!GetSource()->ReInitUnpackers()) {
        LOG(fatal) << "FairRunOnline::CheckRunIdChanged: ReInitUnpackers() failed!";
        return false;
    }
    fTask->ReInitTask();
    return true;
}

void FairRunOnline::Reinit(UInt_t runId)
{
    // reinit procedure
    if (!fRtdb->initContainers(runId)) {
        LOG(error) << "FairRunOnline::Reinit: fRtdb->initContainers failed";
    }
}

void FairRunOnline::SetContainerStatic(Bool_t tempBool)
{
    fStatic = tempBool;
    if (fStatic) {
        LOG(info) << "Parameter Cont. initialisation is static";
    } else {
        LOG(info) << "Parameter Cont. initialisation is NOT static";
    }
}

void FairRunOnline::AddObject(TObject* object)
{
    if (nullptr == object) {
        return;
    }
    if (fServer) {
        TString classname = TString(object->ClassName());
        if (classname.EqualTo("TCanvas")) {
            fServer->Register("CANVAS", object);
        } else if (classname.EqualTo("TFolder")) {
            fServer->Register("/", object);
        } else if (classname.Contains("TH1") || classname.Contains("TH2")) {
            fServer->Register("HISTO", object);
        } else {
            LOG(warn) << "FairRunOnline::AddObject : unrecognized object type : " << classname;
        }
    }
}

void FairRunOnline::Fill()
{
    if (fMarkFill) {
        fRootManager->Fill();
    } else {
        fMarkFill = kTRUE;
    }
}
