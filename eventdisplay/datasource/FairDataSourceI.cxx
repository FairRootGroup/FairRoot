/*
 * FairDataSourceI.cxx
 *
 *  Created on: 07.12.2020
 *      Author: tstockmanns
 */

#include "FairTask.h"

#include <FairDataSourceI.h>
#include <FairRootManager.h>
#include <fairlogger/Logger.h>

ClassImp(FairDataSourceI);

FairDataSourceI::FairDataSourceI()
{
    // TODO Auto-generated constructor stub
}

FairDataSourceI::~FairDataSourceI()
{
    // TODO Auto-generated destructor stub
}

InitStatus FairDataSourceI::Init()
{
    fCArray = static_cast<TClonesArray*>(FairRootManager::Instance()->GetObject(fBranchName));
    if (fCArray != nullptr) {
        return kSUCCESS;
    }
    LOG(error) << "Branch " << fBranchName << " not found!";
    return kERROR;
}
