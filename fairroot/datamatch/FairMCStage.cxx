/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCStage.cpp
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#include "FairMCStage.h"

FairMCStage::FairMCStage()
    : FairMCObject()
    , fBranchName("")
    , fFileName("")
    , fWeight(1.0)
    , fLoaded(kFALSE)
    , fFill(kFALSE)
{}

FairMCStage::~FairMCStage() {}

FairMCStage::FairMCStage(Int_t id, const std::string& fileName, const std::string& branchName, Double_t weight)
    : FairMCObject(id)
    , fBranchName(branchName)
    , fFileName(fileName)
    , fWeight(weight)
    , fLoaded(kFALSE)
    , fFill(kFALSE)
{}
