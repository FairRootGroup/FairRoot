/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * MyWriteoutBuffer.cxx
 *
 *  Created on: Mar 7, 2012
 *      Author: uhlig
 */

#include "MyWriteoutBuffer.h"

#include "MyDataClass.h"

MyWriteoutBuffer::MyWriteoutBuffer()
    : FairWriteoutBuffer()
    , fData_map()
{}

MyWriteoutBuffer::MyWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance)
    : FairWriteoutBuffer(branchName, "MyDataClass", folderName, persistance)
    , fData_map()
{}

MyWriteoutBuffer::~MyWriteoutBuffer() {}

std::vector<std::pair<double, MyDataClass*>> MyWriteoutBuffer::Modify(std::pair<double, MyDataClass*> oldData,
                                                                      std::pair<double, MyDataClass*> newData)
{
    std::vector<std::pair<double, MyDataClass*>> result;
    std::pair<double, MyDataClass*> singleResult;
    if (newData.first > 0) {
        singleResult.first = oldData.first + newData.first;
    }
    singleResult.second = oldData.second;
    singleResult.second->AddCharge(newData.second->GetCharge());
    if (fVerbose > 0) {
        std::cout << "Modify hit" << std::endl;
        std::cout << "OldData: " << oldData.first << " : " << oldData.second << " NewData: " << newData.first << " : "
                  << newData.second << std::endl;
        std::cout << "Resulting Data: " << singleResult.first << " : " << singleResult.second << std::endl;
    }

    result.push_back(singleResult);
    return result;
}

void MyWriteoutBuffer::AddNewDataToTClonesArray(FairTimeStamp* data)
{
    FairRootManager* ioman = FairRootManager::Instance();
    TClonesArray* myArray = ioman->GetTClonesArray(fBranchName);
    if (fVerbose > 1) {
        std::cout << "Data Inserted: " << *(MyDataClass*)(data) << std::endl;
    }
    new ((*myArray)[myArray->GetEntries()]) MyDataClass(*(MyDataClass*)(data));
}

double MyWriteoutBuffer::FindTimeForData(FairTimeStamp* data)
{
    std::map<MyDataClass, double>::iterator it;
    MyDataClass myData = *(MyDataClass*)data;
    it = fData_map.find(myData);
    if (it == fData_map.end()) {
        return -1;
    } else {
        return it->second;
    }
}

void MyWriteoutBuffer::FillDataMap(FairTimeStamp* data, double activeTime)
{
    MyDataClass myData = *(MyDataClass*)data;
    fData_map[myData] = activeTime;
}

void MyWriteoutBuffer::EraseDataFromDataMap(FairTimeStamp* data)
{
    MyDataClass myData = *(MyDataClass*)data;
    if (fData_map.find(myData) != fData_map.end()) {
        fData_map.erase(fData_map.find(myData));
    }
}
