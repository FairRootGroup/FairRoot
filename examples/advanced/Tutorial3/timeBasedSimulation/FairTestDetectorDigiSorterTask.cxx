/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiSorterTask.cxx
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#include "FairTestDetectorDigiSorterTask.h"

#include "FairLogger.h"
#include "FairRootManager.h"        // for FairRootManager
#include "FairTestDetectorDigi.h"   // for FairTestDetectorDigi, etc
#include "FairTestDetectorDigiRingSorter.h"

#include <TClonesArray.h>   // for TClonesArray

FairTestDetectorDigiSorterTask::FairTestDetectorDigiSorterTask()
{
    // TODO Auto-generated constructor stub
}

FairTestDetectorDigiSorterTask::~FairTestDetectorDigiSorterTask()
{
    // TODO Auto-generated destructor stub
}

void FairTestDetectorDigiSorterTask::AddNewDataToTClonesArray(FairTimeStamp* data)
{
    FairRootManager* ioman = FairRootManager::Instance();
    TClonesArray* myArray = ioman->GetTClonesArray(fOutputBranch);
    if (fVerbose > 1) {
        LOG(info) << "AddNewDataToTClonesArray Data: ";
        LOG(info) << static_cast<FairTestDetectorDigi*>(data)->ToString();
    }
    new ((*myArray)[myArray->GetEntries()]) FairTestDetectorDigi(*static_cast<FairTestDetectorDigi*>(data));
}

FairRingSorter* FairTestDetectorDigiSorterTask::InitSorter(Int_t numberOfCells, Double_t widthOfCells) const
{
    return new FairTestDetectorDigiRingSorter(numberOfCells, widthOfCells);
}
