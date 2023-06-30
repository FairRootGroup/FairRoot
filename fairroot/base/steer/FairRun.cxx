/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairRun source file                         -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#include "FairRun.h"

#include "FairFileHeader.h"     // for FairFileHeader
#include "FairLogger.h"         // for FairLogger, MESSAGE_ORIGIN
#include "FairRootFileSink.h"   // only temporary, should be removed after the move to FairSink is finished
#include "FairRootManager.h"    // for FairRootManager
#include "FairRuntimeDb.h"      // for FairRuntimeDb
#include "FairTask.h"           // for FairTask

#include <RVersion.h>      // for ROOT_VERSION_CODE and ROOT_VERSION
#include <TFile.h>         // for TFile
#include <TGeoManager.h>   // for gGeoManager, TGeoManager
#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 18, 2) && ROOT_VERSION_CODE <= ROOT_VERSION(6, 22, 6)
#include <TGeoSystemOfUnits.h>   // for TGeoUnit::kTGeoUnits
#endif
#include <TList.h>     // for TList
#include <TObject.h>   // for TObject
#include <TROOT.h>     // fot gROOT
#include <cassert>     // for... well, assert

TMCThreadLocal FairRun* FairRun::fRunInstance = nullptr;

FairRun* FairRun::Instance()
{
    return fRunInstance;
}

FairRun::FairRun(Bool_t isMaster)
    : TNamed()
    , fNTasks(0)
    , fRtdb(FairRuntimeDb::instance())
    , fTask(new FairTask("FairTaskList"))
    , fRootManager(0)
    , fUserOutputFileName()
    , fRunId(0)
    , fAna(kFALSE)
    , fEvtHeader(nullptr)
    , fFileHeader(new FairFileHeader())
    , fGenerateRunInfo(kFALSE)
    , fIsMaster(isMaster)
    , fMarkFill(kTRUE)
{
    if (fRunInstance) {
        Fatal("FairRun", "Singleton instance already exists.");
        return;
    }

    fRunInstance = this;

    // Fix the unit system to the ROOT one which was the default before ROOT v6.18.02.
    // With ROOT v6.18.02 the ROOT team introduced a new unit system (taken from Geant4)
    // for the geometry manager. The change was reverted with ROOT v6.25.1.
    // Unfortunately the way to set the default units to the ROOT one is
    // different for different ROOT versions such that the code needs some
    // preprocessor statements.
    // Before version v6.18.2 and after v6.25.1 the units are correct
    // by default

#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 18, 2) && ROOT_VERSION_CODE <= ROOT_VERSION(6, 22, 6)
    TGeoUnit::setUnitType(TGeoUnit::kTGeoUnits);
#endif

#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 22, 8) && ROOT_VERSION_CODE <= ROOT_VERSION(6, 25, 1)
    TGeoManager::LockDefaultUnits(false);
    TGeoManager::SetDefaultUnits(TGeoManager::EDefaultUnits::kRootUnits);
    TGeoManager::LockDefaultUnits(true);
#endif

    fRootManager = FairRootManager::Instance();
}

FairRun::~FairRun()
{
    LOG(debug) << "Enter Destructor of FairRun";

    // So that FairRootManager does not try to delete these, because we will do that:
    fRootManager->SetSource(nullptr);
    fRootManager->SetSink(nullptr);

    if (fTask) {
        // FairRunAna added it, but let's remove it here, because we own it
        gROOT->GetListOfBrowsables()->Remove(fTask);
        delete fTask;   // There is another tasklist in MCApplication,
    }
    // but this should be independent
    if (fIsMaster) {
        // who is responsible for the RuntimeDataBase?
        delete fRtdb;
    }
    delete fEvtHeader;
    if (fRunInstance == this) {
        // Do not point to a destructed object!
        fRunInstance = nullptr;
    }
    LOG(debug) << "Leave Destructor of FairRun";
}

void FairRun::AddTask(FairTask* task)
{
    fTask->Add(task);
    StoreTaskNames(task);
}

void FairRun::StoreTaskNames(const FairTask* task)
{
    if (task) {
        fFileHeader->AddTaskClassName(task->ClassName());
        fNTasks++;

        const TList* subtasks = task->GetListOfTasks();
        if (subtasks) {
            for (const auto subtask : *subtasks) {
                StoreTaskNames(static_cast<FairTask*>(subtask));
            }
        }
    }
}

void FairRun::SetTask(FairTask* task)
{
    delete fTask;
    fTask = task;
    fNTasks = 0;
    TList* tasklist = fFileHeader->GetListOfTasks();
    if (tasklist) {
        tasklist->Clear();
        StoreTaskNames(task);
    }
}

void FairRun::CreateGeometryFile(const char* geofile)
{
    fRootManager->CreateGeometryFile(geofile);
}

FairTask* FairRun::GetTask(const char* taskName)
{
    TList* taskList = fTask->GetListOfTasks();
    TObject* task = taskList->FindObject(taskName);
    return dynamic_cast<FairTask*>(task);
}

FairEventHeader* FairRun::GetEventHeader()
{
    if (nullptr == fEvtHeader) {
        fEvtHeader = new FairEventHeader();
    }
    return fEvtHeader;
}

void FairRun::SetUseFairLinks(Bool_t val)
{
    fRootManager->SetUseFairLinks(val);
}

void FairRun::SetWriteRunInfoFile(Bool_t write)
{
    LOG(warn) << "Function FairRun::SetWriteRunInfoFile(Bool_t) is deprecated and will vanish in future versions of "
                 "FairRoot.\n";
    LOG(warn) << "Please use FairRun::SetGenerateRunInfo(Bool_t) instead.";

    fGenerateRunInfo = write;
}

Bool_t FairRun::GetWriteRunInfoFile()
{
    LOG(warn)
        << "Function FairRun::GetWriteRunInfoFile() is deprecated and will vanish in future versions of FairRoot.\n";
    LOG(warn) << "Please use FairRun::IsRunInfoGenerated() instead.";

    return fGenerateRunInfo;
}

void FairRun::SetSink(std::unique_ptr<FairSink> newsink)
{
    fSink = std::move(newsink);
    fRootManager->SetSink(fSink.get());
    fUserOutputFileName = fSink->GetFileName();
}

void FairRun::SetSink(FairSink* tempSink)
{
    fSink.reset(tempSink);
    fRootManager->SetSink(fSink.get());
    fUserOutputFileName = fSink->GetFileName();
}

void FairRun::SetOutputFile(const char* fname)
{
    LOG(warning) << "FairRun::SetOutputFile() deprecated. Use FairRootFileSink.";
    fSink = std::make_unique<FairRootFileSink>(fname);
    if (fRootManager)
        fRootManager->SetSink(fSink.get());
    fUserOutputFileName = fname;
}

void FairRun::SetOutputFile(TFile* f)
{
    LOG(warning) << "FairRun::SetOutputFile() deprecated. Use FairRootFileSink.";
    SetSink(std::make_unique<FairRootFileSink>(f));
}

void FairRun::SetOutputFileName(const TString& name)
{
    LOG(warning) << "FairRun::SetOutputFileName() deprecated. Use FairRootFileSink.";
    fSink = std::make_unique<FairRootFileSink>(name);
    if (fRootManager)
        fRootManager->SetSink(fSink.get());
    fUserOutputFileName = name;
}

TFile* FairRun::GetOutputFile()
{
    LOG(warning) << "FairRun::GetOutputFile() deprecated. Use separate file to store additional data.";
    auto sink = GetSink();
    assert(sink->GetSinkType() == kFILESINK);
    auto rootFileSink = static_cast<FairRootFileSink*>(sink);
    return rootFileSink->GetRootFile();
}

void FairRun::SetUserOutputFileName(const TString& name)
{
    fUserOutputFileName = name;
}

TString FairRun::GetUserOutputFileName() const
{
    return fUserOutputFileName;
}

void FairRun::AlignGeometry() const
{
    fAlignmentHandler.AlignGeometry();
}

/**
 * \todo Should we check for `fEvtHeader` being set as well?
 */
void FairRun::FillEventHeader()
{
    if (!fSource) {
        LOG(warning) << "FairRun::FillEventHeader: No Source!";
        return;
    }

    fSource->FillEventHeader(fEvtHeader);
}

void FairRun::AddAlignmentMatrices(const std::map<std::string, TGeoHMatrix>& alignmentMatrices, bool invertMatrices)
{
    fAlignmentHandler.AddAlignmentMatrices(alignmentMatrices, invertMatrices);
}

void FairRun::SetSource(FairSource* othersource)
{
    fRootManager->SetSource(othersource);
    fSource.reset(othersource);
}
