/*
 * FairTimebasedSource.cxx
 *
 * \date 07.12.2020
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 */

#include <FairRootManager.h>
#include <FairTimebasedSource.h>

FairTimebasedSource::FairTimebasedSource()
{
    // TODO Auto-generated constructor stub
}

FairTimebasedSource::~FairTimebasedSource()
{
    delete (fStartFunctor);
    delete (fStopFunctor);
}

void FairTimebasedSource::RetrieveData(double time)
{
    fCArray = FairRootManager::Instance()->GetData(
        fBranchName, fStartFunctor, time - fTimeWindowMinus, fStopFunctor, time + fTimeWindowPlus);
    FairDataSourceI::RetrieveData(time);
}
