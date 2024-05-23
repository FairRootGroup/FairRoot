/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet2CustomTask.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairTutorialDet2Point.h"

// we include some unit testing here
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>

FairTutorialDet2CustomTask::FairTutorialDet2CustomTask()
    : FairTask("TutorialDetCustomTask", 0)
{}

FairTutorialDet2CustomTask::FairTutorialDet2CustomTask(const char* name, const char* /*title*/)
    : FairTask(name, 0)
{}

FairTutorialDet2CustomTask::~FairTutorialDet2CustomTask() {}

InitStatus FairTutorialDet2CustomTask::Init()
{
    LOG(info) << " FairTutorialDet2CustomTask :: Init() ";

    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        LOG(fatal) << "No FairRootManager";
        return kERROR;
    } else {
        fCustomData = ioman->InitObjectAs<std::vector<CustomClass> const*>("TutorialCustomData");
        if (!fCustomData) {
            LOG(error) << "No input data found!";
            LOG(error) << "Task will be inactive";
            return kERROR;
        }

        // assert that some other queries are null:
        // querying existing data under wrong type
        assert(ioman->InitObjectAs<double const*>("TutorialCustomData") == nullptr);
        // querying non-existing branch
        assert(ioman->InitObjectAs<double const*>("WrongName") == nullptr);
        fCustomData2 = ioman->InitObjectAs<std::vector<CustomClass> const*>("InMemory1");
        assert(fCustomData2);
    }
    return kSUCCESS;
}

void FairTutorialDet2CustomTask::Exec(Option_t* /*option*/)
{
    // Here we print something
    LOG(info) << " I am in FairTutorialDet2CustomTask::Exec";

    LOG(info) << " The custom data input vector has size" << fCustomData->size();
    for (auto& entry : *fCustomData) {
        LOG(info) << " Got entry " << entry.GetX() << " " << entry.GetQ();
    }

    // process data that we got from DigitizerTask
    LOG(info) << " The input vector from DigitizerTask has size" << fCustomData2->size();
    for (auto& entry : *fCustomData2) {
        LOG(info) << " Got entry " << entry.GetX() << " " << entry.GetQ();
    }
}
