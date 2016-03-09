/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiWriteoutBuffer.cxx
 *
 *  Created on: May 10, 2011
 *      Author: stockman
 */

#include "FairTestDetectorDigiWriteoutBuffer.h"

#include "FairRootManager.h"      // for FairRootManager
#include "FairTestDetectorDigi.h" // for FairTestDetectorDigi, etc
#include "FairLogger.h"           // for logging

#include "Riosfwd.h"      // for ostream
#include "TClonesArray.h" // for TClonesArray

#include <utility>  // for pair

ClassImp(FairTestDetectorDigiWriteoutBuffer);

FairTestDetectorDigiWriteoutBuffer::FairTestDetectorDigiWriteoutBuffer()
    : FairWriteoutBuffer()
    , fData_map()
{

    // TODO Auto-generated constructor stub
}

FairTestDetectorDigiWriteoutBuffer::FairTestDetectorDigiWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance)
    : FairWriteoutBuffer(branchName, "FairTestDetectorDigi", folderName, persistance)
    , fData_map()
{
}

FairTestDetectorDigiWriteoutBuffer::~FairTestDetectorDigiWriteoutBuffer()
{
    // TODO Auto-generated destructor stub
}

void FairTestDetectorDigiWriteoutBuffer::AddNewDataToTClonesArray(FairTimeStamp* data)
{
    FairRootManager* ioman = FairRootManager::Instance();
    TClonesArray* myArray = ioman->GetTClonesArray(fBranchName);
    if (fVerbose > 1)
    {
      LOG(INFO) << "Data Inserted: " 
		<< static_cast<FairTestDetectorDigi*>(data)->ToString() 
		<< FairLogger::endl;
    }
    new ((*myArray)[myArray->GetEntries()]) FairTestDetectorDigi(*static_cast<FairTestDetectorDigi*>((data)));
}

double FairTestDetectorDigiWriteoutBuffer::FindTimeForData(FairTimeStamp* data)
{
    std::map<FairTestDetectorDigi, double>::iterator it;
    FairTestDetectorDigi myData = *static_cast<FairTestDetectorDigi*>(data);
    it = fData_map.find(myData);
    if (it == fData_map.end())
    {
        return -1;
    }
    else
    {
        return it->second;
    }
}

void FairTestDetectorDigiWriteoutBuffer::FillDataMap(FairTimeStamp* data, double activeTime)
{
    FairTestDetectorDigi myData = *static_cast<FairTestDetectorDigi*>(data);
    fData_map[myData] = activeTime;
}

void FairTestDetectorDigiWriteoutBuffer::EraseDataFromDataMap(FairTimeStamp* data)
{
    FairTestDetectorDigi myData = *static_cast<FairTestDetectorDigi*>(data);
    if (fData_map.find(myData) != fData_map.end())
    {
        fData_map.erase(fData_map.find(myData));
    }
}
