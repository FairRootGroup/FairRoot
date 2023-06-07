/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCResult.cpp
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#include "FairMCResult.h"

FairMCResult::FairMCResult()
    : FairMCObject()
    , fStartType(-1)
    , fStopType(-1)
{}

FairMCResult::~FairMCResult() {}

FairMCResult::FairMCResult(Int_t start, Int_t stop)
    : FairMCObject()
    , fStartType(start)
    , fStopType(stop)
{}
