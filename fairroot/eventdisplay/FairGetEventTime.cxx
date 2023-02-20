#include "FairGetEventTime.h"

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

// -----   Public method Init   --------------------------------------------
InitStatus FairGetEventTime::Init()
{
    if (fRunOnce) {
        FairRootManager *ioman = FairRootManager::Instance();
        FairSource *source = ioman->GetSource();
        if (source->GetSourceType() == Source_Type::kFILE) {
            LOG(info) << "Event t0 times:";
            for (int i = 0; i < source->CheckMaxEventNo(); i++) {
                source->ReadEvent(i);
                fEventTime.push_back(((FairFileSource *)source)->GetEventTime());
                LOG(info) << i << " : " << fEventTime.back();
            }
        }
        fRunOnce = false;
        LOG(debug) << "-I- FairGetEventTime: Initialization successful #Times: " << fEventTime.size();
    }
    return kSUCCESS;
}

std::pair<int, double> FairGetEventTime::GetEvent(double simTime) const
{
    auto lower = std::lower_bound(fEventTime.begin(), fEventTime.end(), simTime + 0.01);
    int evtIndex = std::distance(fEventTime.begin(), lower) - 1;
    double evtTime = -1.0;
    if (evtIndex > -1) {
        evtTime = fEventTime.at(evtIndex);
        LOG(debug) << "FairTimebasedMCSource::RetrieveData " << simTime << " lower " << *lower << " at index "
                   << evtIndex + 1;
        LOG(debug) << "GetEvent " << evtIndex << " time: " << evtTime << std::endl;
    }
    return std::make_pair(evtIndex, evtTime);
}

ClassImp(FairGetEventTime);
