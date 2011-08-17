#include "FairRunInfo.h"
#include "FairLogger.h"

#include "TSystem.h"
#include "TList.h"
#include "TH1.h"
#include "TDirectory.h"

#include <iostream>

ClassImp(FairRunInfo)

//_____________________________________________________________________________
FairRunInfo::FairRunInfo()
  :TObject(),
   fTimeStamp(),
   fCpuInfo(),
   fMemInfo(),
   fProcInfo(),
   fTimeDiff(),
   fResidentMemory(),
   fVirtualMemory(),
   fLogger(FairLogger::GetLogger())
{
}

FairRunInfo::~FairRunInfo()
{
}

void FairRunInfo::StoreInfo()
{
  // Extract the Information about the used memory from the system.
  // Stores this infor together with the timedifference between now
  // and the last call in container arrays for later usage.
  //  gSystem->GetCpuInfo(&cpuInfo, 10);
  //  gSystem->GetMemInfo(&memInfo);

  // Set the TimeStamp to the actual time
  fTimeStamp.Set();
  fTime.push_back(fTimeStamp.GetSec());

  gSystem->GetProcInfo(&fProcInfo);
  fResidentMemory.push_back(fProcInfo.fMemResident/1024);
  fVirtualMemory.push_back(fProcInfo.fMemVirtual/1024);

  CalculateTimeDifference();

  PrintInfo();
}

void FairRunInfo::PrintInfo()
{

  fLogger->Info(MESSAGE_ORIGIN,"Time to execute 1 event: %d s",
                fTimeDiff.back());
  fLogger->Info(MESSAGE_ORIGIN,"Used resident memory: %i MB",
                fResidentMemory.back());
  fLogger->Info(MESSAGE_ORIGIN,"Used virtual memory: %i MB",
                fVirtualMemory.back());
}

void FairRunInfo::CalculateTimeDifference()
{
  // Calculates the time difference between now and the last call

  Int_t lastElement = fTime.size()-1;
  fTimeDiff.push_back( fTime.at(lastElement) -
                       fTime.at(lastElement-1) );
}


void FairRunInfo::WriteInfo()
{
  TList* histoList = NULL;
  CreateAndFillHistograms(histoList);
  //  WriteHistosToFile(histoList);
}

void FairRunInfo::CreateAndFillHistograms(TList* histoList)
{
  fLogger->Info(MESSAGE_ORIGIN,"Size of fTime: %i",
                fTime.size());
  fLogger->Info(MESSAGE_ORIGIN,"Size of fTimeDiff: %i",
                fTimeDiff.size());
  fLogger->Info(MESSAGE_ORIGIN,"Size of fResidentMemory: %i",
                fResidentMemory.size());
  fLogger->Info(MESSAGE_ORIGIN,"Size of fVirtualMemory: %i",
                fVirtualMemory.size());

  Int_t entries = fTime.size();
  Int_t timePeriod = fTime.back()-fTime.front();

  TH1F* memResVsEvent = new TH1F("memResVsEvent","Resident Memory as function of Eventnumber;Event;Memory [MB]",entries, 0, entries);
  TH1F* memVirtVsEvent = new TH1F("memVirtVsEvent","Virtual Memory as function of Eventnumber;Event;Memory [MB]",entries, 0, entries);
  TH1F* memResVsTime = new TH1F("memResVsTime","Resident memory as function of Runtime;Time [s];Memory [MB]",timePeriod, 0, timePeriod);
  TH1F* memVirtVsTime = new TH1F("memVirtVsTime","Virtual memory as function of Runtime;Time [s];Memory [MB]",timePeriod, 0, timePeriod);
  TH1F* eventtimeVsEvent = new TH1F("eventtimeVsEvent","Runtime per Event as function of Event number;Event;Time [s]",entries-1, 1, entries);

  std::vector<Int_t> timeDiffSorted(fTimeDiff);
  std::vector<Int_t>::iterator it;
  std::sort(timeDiffSorted.begin(), timeDiffSorted.end());

  Int_t minTime = timeDiffSorted.front();
  Int_t maxTime = timeDiffSorted.back();
  timePeriod = maxTime - minTime;

  TH1F* timePerEvent = new TH1F("timePerEvent","Runtime;Time [s];Events",timePeriod+20, minTime-10, maxTime+10);

  Int_t counter = 0;
  std::vector<Long_t>::iterator lit;
  for(lit=fResidentMemory.begin(); lit<fResidentMemory.end(); lit++) {
    memResVsEvent->Fill(counter, *lit);
    counter++;
  }
  for(it=fTimeDiff.begin(); it<fTimeDiff.end(); it++) {
    timePerEvent->Fill(*it);
  }
  counter = 1;
  for(it=fTimeDiff.begin(); it<fTimeDiff.end(); it++) {
    eventtimeVsEvent->Fill(counter, *it);
    counter++;
  }
  //  histoList->AddLast(memVsEvent);
  // create a new subdirectory in the output file and
  // write all histograms
  TDirectory* currentDir = gDirectory;

  gDirectory->cd();
  gDirectory->mkdir("FairRunInfo");
  gDirectory->cd("FairRunInfo");

  memResVsEvent->Write();
  timePerEvent->Write();
  eventtimeVsEvent->Write();

  gDirectory=currentDir;
}

void FairRunInfo::WriteHistosToFile(TList* histoList)
{
  // create a new subdirectory in the output file and
  // write all histograms
  TDirectory* currentDir = gDirectory;

  gDirectory->cd();
  gDirectory->mkdir("FairRunInfo");
  gDirectory->cd("FairRunInfo");

  TIterator* listIter=histoList->MakeIterator();
  listIter->Reset();
  TObject* obj = NULL;
  while((obj=listIter->Next())) {
    obj->Write();
  }

  gDirectory=currentDir;
}

void FairRunInfo::Reset()
{
  // Set the TimeStamp to the actual time and store it
  fTimeStamp.Set();
  fTime.push_back(fTimeStamp.GetSec());

  gSystem->GetProcInfo(&fProcInfo);
  fResidentMemory.push_back(fProcInfo.fMemResident/1024);
  fVirtualMemory.push_back(fProcInfo.fMemVirtual/1024);
}
