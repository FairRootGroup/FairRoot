/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiRingSorter.cxx
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#include "FairTestDetectorDigiRingSorter.h"

#include "FairTestDetectorDigi.h" // for FairTestDetectorDigi

class FairTimeStamp;

ClassImp(FairTestDetectorDigiRingSorter);

FairTestDetectorDigiRingSorter::~FairTestDetectorDigiRingSorter()
{
    // TODO Auto-generated destructor stub
}

FairTimeStamp* FairTestDetectorDigiRingSorter::CreateElement(FairTimeStamp* data)
{
    return new FairTestDetectorDigi(*(FairTestDetectorDigi*)data);
}
