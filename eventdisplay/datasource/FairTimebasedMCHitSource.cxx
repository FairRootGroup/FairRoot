/*
 * FairTimebasedMCHitSource.cxx
 *
 * \date 07.12.2020
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 */

#include <FairGetEventTime.h>
#include <FairRootManager.h>
#include <FairTimebasedMCHitSource.h>

ClassImp(FairTimebasedMCHitSource);

FairTimebasedMCHitSource::FairTimebasedMCHitSource()
{
    // TODO Auto-generated constructor stub
}

FairTimebasedMCHitSource::~FairTimebasedMCHitSource()
{
    // TODO Auto-generated destructor stub
}

InitStatus FairTimebasedMCHitSource::Init()
{
    fEventTime = FairRootManager::Instance()->InitObjectAs<std::vector<double> const*>("EventTimes");
    fBranch = FairRootManager::Instance()->GetInTree()->GetBranch(fBranchName);

    if (FairGetEventTime::Instance().Init() != kSUCCESS) {
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

void FairTimebasedMCHitSource::RetrieveData(double simTime)
{
    std::pair<int, double> evt = FairGetEventTime::Instance().GetEvent(simTime);

    if (evt.first < 0) {
        fCArray->Clear();
    } else {
        fBranch->GetEvent(evt.first);
        fDataHandler.FillTClonesArray(fCArray, evt.first, evt.second, simTime);
    }
    FairDataSourceI::RetrieveData(simTime);
}
