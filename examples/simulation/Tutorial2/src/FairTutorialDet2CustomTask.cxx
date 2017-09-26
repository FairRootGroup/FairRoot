/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet2CustomTask.h"
#include "FairTutorialDet2Point.h"
#include "FairRootManager.h"
#include "FairLogger.h"

// we include some unit testing here
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>

// ---- Default constructor -------------------------------------------
FairTutorialDet2CustomTask::FairTutorialDet2CustomTask()
  : FairTask("TutorialDetCustomTask", 0)
{
}
// --------------------------------------------------------------------

// ---- Constructor ----------------------------------------------------
FairTutorialDet2CustomTask::FairTutorialDet2CustomTask(const char* name, const char* /*title*/)
  : FairTask(name, 0)
{
}
// --------------------------------------------------------------------

// ---- Destructor ----------------------------------------------------
FairTutorialDet2CustomTask::~FairTutorialDet2CustomTask()
{
}
// --------------------------------------------------------------------


// ---- Init ----------------------------------------------------------
InitStatus FairTutorialDet2CustomTask::Init()
{
  LOG(INFO) << " FairTutorialDet2CustomTask :: Init() " 
	    << FairLogger::endl;

  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) { 
    LOG(FATAL) << "No FairRootManager" << FairLogger::endl; 
    return kERROR;
  } else {
    fCustomData=ioman->InitObjectAs<std::vector<CustomClass> const*>("TutorialCustomData");
    if ( ! fCustomData ) {
      LOG(ERROR) << "No input data found!" << FairLogger::endl;
      LOG(ERROR) << "Task will be inactive" << FairLogger::endl;
      return kERROR;
    }

    // assert that some other queries are null:
    // querying existing data under wrong type
    assert(ioman->InitObjectAs<double const*>("TutorialCustomData") == nullptr);
    // querying non-existing branch
    assert(ioman->InitObjectAs<double const*>("WrongName") == nullptr);
    fCustomData2=ioman->InitObjectAs<std::vector<CustomClass> const*>("InMemory1");
    assert(fCustomData2);
  }
  return kSUCCESS;
}
// --------------------------------------------------------------------

// ---- Exec ----------------------------------------------------------
void FairTutorialDet2CustomTask::Exec(Option_t* /*option*/)
{
  // Here we print something
  LOG(INFO) <<" I am in FairTutorialDet2CustomTask::Exec" 
	    << FairLogger::endl;

  LOG(INFO) << " The custom data input vector has size" << fCustomData->size() << "\n"; 
  for(auto& entry : *fCustomData) {
    LOG(INFO) << " Got entry " << entry.GetX() << " " << entry.GetQ() << "\n";
  }

  // process data that we got from DigitizerTask
  LOG(INFO) << " The input vector from DigitizerTask has size" << fCustomData2->size() << "\n"; 
  for(auto& entry : *fCustomData2) {
    LOG(INFO) << " Got entry " << entry.GetX() << " " << entry.GetQ() << "\n";
  }

}
// --------------------------------------------------------------------


ClassImp(FairTutorialDet2CustomTask);
