#include "FairGetEventTimeTask.h"

#include <iostream>

// Root includes
#include "TBranch.h"
#include "TClonesArray.h"
#include "TParticlePDG.h"
#include "TROOT.h"
#include "TString.h"
#include "TTree.h"

// framework includes
#include "FairFileSource.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairTimeStamp.h"

#include <fairlogger/Logger.h>

FairGetEventTimeTask::FairGetEventTimeTask()
    : FairTask("Pnd Get Event Time")
    , fEventTime(new std::vector<double>)
{}

FairGetEventTimeTask::~FairGetEventTimeTask() {}

InitStatus FairGetEventTimeTask::ReInit()
{
    InitStatus stat = kSUCCESS;
    return stat;
}

// -----   Public method Init   --------------------------------------------
InitStatus FairGetEventTimeTask::Init()
{
    FairRootManager *ioman = FairRootManager::Instance();
    FairSource *source = ioman->GetSource();
    if (source->GetSourceType() == Source_Type::kFILE) {
        LOG(info) << "Event t0 times:";
        for (int i = 0; i < source->CheckMaxEventNo(); i++) {
            source->ReadEvent(i);
            fEventTimeCopy.push_back(((FairFileSource *)source)->GetEventTime());
            LOG(info) << i << " : " << fEventTimeCopy.back();
        }
    }

    ioman->RegisterAny("EventTimes", fEventTime, kFALSE);

    LOG(debug) << "-I- FairGetEventTimeTask: Initialization successful #Times: " << fEventTimeCopy.size();
    return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void FairGetEventTimeTask::Exec(Option_t *)
{
    *fEventTime = fEventTimeCopy;   // todo Check if a faster way exists to preserve the data between events
}

void FairGetEventTimeTask::FinishEvent()
{
    delete (fEventTime);
    fEventTime = nullptr;
}

ClassImp(FairGetEventTimeTask);
