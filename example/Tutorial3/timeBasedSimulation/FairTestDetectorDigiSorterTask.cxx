/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiSorterTask.cxx
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#include <FairTestDetectorDigiSorterTask.h>

#include "FairRootManager.h"      // for FairRootManager
#include "FairTestDetectorDigi.h" // for FairTestDetectorDigi, etc
#include "FairTestDetectorDigiRingSorter.h"

#include "Riosfwd.h"      // for ostream
#include "TClonesArray.h" // for TClonesArray

#include <iostream> // for ostream, cout, operator<<, etc

class FairRingSorter;
class FairTimeStamp;

ClassImp(FairTestDetectorDigiSorterTask);

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
    if (fVerbose > 1)
    {
        std::cout << "-I- FairTestDetectorDigiSorterTask::AddNewDataToTClonesArray Data: ";
        std::cout << *(FairTestDetectorDigi*)(data) << std::endl;
    }
    new ((*myArray)[myArray->GetEntries()]) FairTestDetectorDigi(*(FairTestDetectorDigi*)(data));
}

FairRingSorter* FairTestDetectorDigiSorterTask::InitSorter(Int_t numberOfCells, Double_t widthOfCells) const
{
    return new FairTestDetectorDigiRingSorter(numberOfCells, widthOfCells);
}
