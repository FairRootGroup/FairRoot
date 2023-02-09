/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * MySorterTask.cxx
 *
 *  Created on: Mar 7, 2012
 *      Author: uhlig
 */

#include "MySorterTask.h"

#include "MyDataClass.h"
#include "MyRingSorter.h"

MySorterTask::MySorterTask()
    : FairRingSorterTask()
{}

MySorterTask::~MySorterTask() {}

void MySorterTask::AddNewDataToTClonesArray(FairTimeStamp* data)
{
    FairRootManager* ioman = FairRootManager::Instance();
    TClonesArray* myArray = ioman->GetTClonesArray(fOutputBranch);
    if (fVerbose > 1) {
        std::cout << "-I- MySorterTask::AddNewDataToTClonesArray Data: ";
        std::cout << *(MyDataClass*)(data) << std::endl;
    }
    new ((*myArray)[myArray->GetEntries()]) MyDataClass(*(MyDataClass*)(data));
}

FairRingSorter* MySorterTask::InitSorter(Int_t numberOfCells, Double_t widthOfCells) const
{
    return new MyRingSorter(numberOfCells, widthOfCells);
}
