/*
 * FairTestDetectorDigiWriteoutBuffer.cxx
 *
 *  Created on: May 10, 2011
 *      Author: stockman
 */

#include <FairTestDetectorDigiWriteoutBuffer.h>

#include "FairTestDetectorDigi.h"


ClassImp(FairTestDetectorDigiWriteoutBuffer);


FairTestDetectorDigiWriteoutBuffer::FairTestDetectorDigiWriteoutBuffer():FairWriteoutBuffer()
{

  // TODO Auto-generated constructor stub

}


FairTestDetectorDigiWriteoutBuffer::FairTestDetectorDigiWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance): FairWriteoutBuffer(branchName, "FairTestDetectorDigi", folderName, persistance)
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
  if (fVerbose > 1) {
    std::cout << "Data Inserted: "  <<  *(FairTestDetectorDigi*)(data) << std::endl;
  }
  new ((*myArray)[myArray->GetEntries()]) FairTestDetectorDigi(*(FairTestDetectorDigi*)(data));
}

double FairTestDetectorDigiWriteoutBuffer::FindTimeForData(FairTimeStamp* data)
{
  std::map<FairTestDetectorDigi, double>::iterator it;
  FairTestDetectorDigi myData = *(FairTestDetectorDigi*)data;
  it = fData_map.find(myData);
  if (it == fData_map.end()) {
    return -1;
  } else {
    return it->second;
  }
}

void FairTestDetectorDigiWriteoutBuffer::FillDataMap(FairTimeStamp* data, double activeTime)
{
  FairTestDetectorDigi myData = *(FairTestDetectorDigi*)data;
  fData_map[myData] = activeTime;
}

void FairTestDetectorDigiWriteoutBuffer::EraseDataFromDataMap(FairTimeStamp* data)
{
  FairTestDetectorDigi myData = *(FairTestDetectorDigi*)data;
  if (fData_map.find(myData) != fData_map.end()) {
    fData_map.erase(fData_map.find(myData));
  }
}
