/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiRingSorter.cxx
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#include "FairTestDetectorDigiRingSorter.h"

#include "FairTestDetectorDigi.h"   // for FairTestDetectorDigi

FairTestDetectorDigiRingSorter::~FairTestDetectorDigiRingSorter()
{
    // TODO Auto-generated destructor stub
}

FairTimeStamp* FairTestDetectorDigiRingSorter::CreateElement(FairTimeStamp* data)
{
    return new FairTestDetectorDigi(*static_cast<FairTestDetectorDigi*>(data));
}
