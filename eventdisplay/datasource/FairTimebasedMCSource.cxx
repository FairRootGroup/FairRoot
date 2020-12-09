/*
 * FairTimebasedMCSource.cxx
 *
 *  Created on: 07.12.2020
 *      Author: tstockmanns
 */

#include <FairRootManager.h>
#include <FairTimebasedMCSource.h>

ClassImp(FairTimebasedMCSource);

FairTimebasedMCSource::FairTimebasedMCSource()
{
    // TODO Auto-generated constructor stub
}

FairTimebasedMCSource::~FairTimebasedMCSource()
{
    // TODO Auto-generated destructor stub
}

InitStatus FairTimebasedMCSource::Init()
{
    fEventTime = FairRootManager::Instance()->InitObjectAs<std::vector<double> const*>("EventTimes");
    fBranch = FairRootManager::Instance()->GetInTree()->GetBranch(fBranchName);

    if (fEventTime == nullptr) {
        LOG(error) << "Branch EventTimes not present";
        return kERROR;
    }
    if (fBranch == nullptr) {
        LOG(error) << "Branch " << fBranchName << " not present";
        return kERROR;
    }

    FairDataSourceI::Init();
    return kSUCCESS;
}

void FairTimebasedMCSource::RetrieveData(double time)
{
    Double_t simTime = time;
    Double_t currentEventTime = -1.0;
    auto lower = std::lower_bound(fEventTime->begin(), fEventTime->end(), simTime + 0.01);
    int evtIndex = std::distance(fEventTime->begin(), lower) - 1;
    if (evtIndex > -1) {
        LOG(debug) << "FairTimebasedMCSource::RetrieveData " << simTime << " lower " << *lower << " at index "
                   << evtIndex + 1;
        LOG(debug) << "GetEvent " << evtIndex << " time: " << fEventTime->at(evtIndex) << std::endl;
    }
    if (evtIndex < 0) {
        fCArray->Clear();
    } else {
        fBranch->GetEvent(evtIndex);
        currentEventTime = fEventTime->at(evtIndex);
        fDataHandler.FillTClonesArray(fCArray, evtIndex, currentEventTime, simTime);
    }
}
