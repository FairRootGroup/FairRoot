/*
 * FairWriteoutBuffer.cpp
 *
 *  Created on: Jul 30, 2010
 *      Author: stockman
 */

#include "FairWriteoutBuffer.h"
#include "FairRootManager.h"
#include "TClonesArray.h"
#include <iostream>

FairWriteoutBuffer::FairWriteoutBuffer(TString branchName, TString className, TString folderName, Bool_t persistance)
  : TObject(),
    fDeadTime_map(),
    fBranchName(branchName),
    fClassName(className),
    fTreeSave(true),
    fActivateBuffering(kTRUE),
    fVerbose(0)
{
  FairRootManager::Instance()->Register(branchName, className, folderName, persistance);
  if (fBranchName == "" || fClassName == "") {
    fTreeSave = false;
  } else {
    fTreeSave = true;
  }
}

void FairWriteoutBuffer::WriteOutData(double time)
{
  typedef std::multimap<double, std::pair<double, FairTimeStamp*> >::iterator startTimeMapIter;
  if (fActivateBuffering) {
    std::cout << "Before removing: ";
    PrintStartTimeMap();
    startTimeMapIter stopTime = fStartTime_map.lower_bound(time);
    for (startTimeMapIter iter = fStartTime_map.begin(); iter != stopTime; iter++) {
      std::pair<double, FairTimeStamp*> data = iter->second;
      FillDataToDeadTimeMap(data.second, data.first);
    }
    fStartTime_map.erase(fStartTime_map.begin(), stopTime);
    std::cout << "After removing: ";
    PrintStartTimeMap();
    WriteOutDataDeadTimeMap(time);
  } else {
    FairRootManager::Instance()->GetTClonesArray(fBranchName);
  }

}

void FairWriteoutBuffer::WriteOutDataDeadTimeMap(double time)
{
  FairRootManager* ioman = FairRootManager::Instance();
  std::vector<FairTimeStamp*> data;
  if (fActivateBuffering) {
    if (fVerbose > 0) {
      std::cout << "-I- FairWriteoutBuffer::WriteOutData for time: " << time << std::endl;
    }
    data = GetRemoveOldData(time);
    if (fTreeSave && data.size() > 0) {
      TClonesArray* myArray = ioman->GetTClonesArray(fBranchName);
      if (!myArray) {
        std::cout << "-E- FairWriteoutBuffer::WriteOutData " << fBranchName << " array is not available!" << std::endl;
      }
      if (fVerbose > 0) {
        std::cout << "-I- FairWriteoutBuffer::WriteOutData size: " << data.size() << std::endl;
      }
      for (int i = 0; i < data.size(); i++) {
        AddNewDataToTClonesArray(data[i]);
        if (fVerbose > 1) {
          std::cout << i << " : ";
          data[i]->Print();
          std::cout << std::endl;
        }
      }
    }
  } else {
    ioman->GetTClonesArray(fBranchName);
  }
}

void FairWriteoutBuffer::WriteOutAllData()
{
  double ultimateTime = 0;
  if (fStartTime_map.size() > 0) {
    ultimateTime = fStartTime_map.rbegin()->first + 1;
  }
  if (fDeadTime_map.size() > 0) {
    if (fDeadTime_map.rbegin()->first > ultimateTime) {
      ultimateTime = fDeadTime_map.rbegin()->first + 1;
    }
  }
  if (ultimateTime > 0) {
    WriteOutData(ultimateTime);
  }
}

std::vector<FairTimeStamp*> FairWriteoutBuffer::GetRemoveOldData(double time)
{
  typedef std::multimap<double, FairTimeStamp*>::iterator DTMapIter;
  std::vector<FairTimeStamp*> result;
  for(DTMapIter it = fDeadTime_map.begin(); it != fDeadTime_map.lower_bound(time); it++) {
    if (fVerbose > 1) {
      std::cout << "-I- GetRemoveOldData: DeadTime: " << it->first << " Data: " << it->second << std::endl;
    }
    result.push_back(it->second);
    EraseDataFromDataMap(it->second);
  }
  fDeadTime_map.erase(fDeadTime_map.begin(), fDeadTime_map.lower_bound(time));
  return result;
}

std::vector<FairTimeStamp*> FairWriteoutBuffer::GetAllData()
{
  return GetRemoveOldData(fDeadTime_map.rbegin()->first + 1);
}

void FairWriteoutBuffer::FillNewData(FairTimeStamp* data, double startTime, double activeTime)
{
  if (fActivateBuffering) {
    std::cout << "StartTime: " << startTime << std::endl;
    std::pair<double, FairTimeStamp*> timeData(activeTime, data);
    fStartTime_map.insert(std::pair<double, std::pair<double, FairTimeStamp*> >(startTime, timeData));
  } else {
    AddNewDataToTClonesArray(data);
  }

}

void FairWriteoutBuffer::FillDataToDeadTimeMap(FairTimeStamp* data, double activeTime)
{
  if (fActivateBuffering) {
    typedef  std::multimap<double, FairTimeStamp*>::iterator DTMapIter;
    typedef  std::map<FairTimeStamp, double>::iterator DataMapIter;

    double timeOfOldData = FindTimeForData(data);
    if(timeOfOldData > -1) {        //if an older active data object is already present
      if (fVerbose > 1) {
        std::cout << " OldData found! " << std::endl;
      }
      if (fVerbose > 1) {
        std::cout << "New Data: " << activeTime << " : " << data << std::endl;
      }
      double currentdeadtime = timeOfOldData;
      FairTimeStamp* oldData;
      for (DTMapIter it = fDeadTime_map.lower_bound(currentdeadtime); it != fDeadTime_map.upper_bound(currentdeadtime); it++) {
        oldData = it->second;
        if (fVerbose > 1) {
          std::cout << "Check Data: " << it->first << " : " << oldData << std::endl;
        }
        if (oldData->equal(data)) {
          if (fVerbose > 1) {
            std::cout << " oldData == data " << std::endl;
          }
          if (fVerbose > 1) {
            std::cout << it->first << " : " << it->second << std::endl;
          }
          fDeadTime_map.erase(it);
          EraseDataFromDataMap(oldData);
          break;
        }
      }
      std::vector<std::pair<double, FairTimeStamp*> > modifiedData = Modify(std::pair<double, FairTimeStamp*>(currentdeadtime, oldData), std::pair<double, FairTimeStamp*>(-1, data));
      for (int i = 0; i < modifiedData.size(); i++) {
        FillDataToDeadTimeMap(modifiedData[i].second, modifiedData[i].first);
        if (fVerbose > 1) {
          std::cout << i << " :Modified Data: " << modifiedData[i].first << " : " << modifiedData[i].second << std::endl;
        }
      }
    } else {
      if (fVerbose > 1) {
        std::cout << "-I- FairWriteoutBuffer::FillNewData Data Inserted: " << activeTime << " : ";
        data->Print();
        std::cout << std::endl;
      }
      fDeadTime_map.insert(std::pair<double, FairTimeStamp*>(activeTime, data));
      FillDataMap(data, activeTime);
    }
  } else {
    AddNewDataToTClonesArray(data);
  }
}

void FairWriteoutBuffer::PrintStartTimeMap()
{
  typedef std::multimap<double, std::pair<double, FairTimeStamp*> >::iterator startTimeMapIter;
  for (startTimeMapIter iter = fStartTime_map.begin(); iter != fStartTime_map.end(); iter++) {
    std::cout << " | " << iter->first;
  }
  std::cout << " |" << std::endl;
}


ClassImp(FairWriteoutBuffer);
