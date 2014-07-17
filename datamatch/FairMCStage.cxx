/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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

