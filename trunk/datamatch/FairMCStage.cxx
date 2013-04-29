/*
 * FairMCStage.cpp
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#include "FairMCStage.h"

ClassImp(FairMCStage);

FairMCStage::FairMCStage()
  : FairMCObject(),
    fFileName(""),
    fBranchName(""),
    fWeight(1.0),
    fLoaded(kFALSE),
    fFill(kFALSE)
{
}

FairMCStage::~FairMCStage()
{
}

FairMCStage::FairMCStage(Int_t id, std::string fileName, std::string branchName, Double_t weight)
  : FairMCObject(id),
    fFileName(fileName),
    fBranchName(branchName),
    fWeight(weight),
    fLoaded(kFALSE),
    fFill(kFALSE)
{
}

