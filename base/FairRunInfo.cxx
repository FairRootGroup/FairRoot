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
  // Stores this info together with the timedifference between now
  // and the last call in container arrays for later usage.
  //  gSystem->GetCpuInfo(&cpuInfo, 10);
  //  gSystem->GetMemInfo(&memInfo);


  fLogger->Info(MESSAGE_ORIGIN,"Before GetInfo.");

  GetInfo();

  fLogger->Info(MESSAGE_ORIGIN,"Before CalculateTimeDifference.");

  CalculateTimeDifference();

  fLogger->Info(MESSAGE_ORIGIN,"Before PrintInfo.");

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
  TList* histoList = new TList();
  CreateAndFillHistograms(histoList);
  //  CreateAndFillHistograms(histoList);
  WriteHistosToFile(histoList);
}

void FairRunInfo::CreateAndFillHistograms(TList* histoList)
{
  Int_t entries = fTime.size();
  Int_t timePeriod = fTime.back()-fTime.front();

  TH1F* ResidentMemoryVsEvent = new TH1F("ResidentMemoryVsEvent","Resident Memory as function of Eventnumber;Event;Memory [MB]",entries, 0, entries);
  TH1F* VirtualMemoryVsEvent = new TH1F("VirtualMemoryVsEvent","Virtual Memory as function of Eventnumber;Event;Memory [MB]",entries, 0, entries);
  TH1F* ResidentMemoryVsTime = new TH1F("ResidentMemoryVsTime","Resident memory as function of Runtime;Time [s];Memory [MB]",timePeriod, 0, timePeriod);
  TH1F* VirtualMemoryVsTime = new TH1F("VirtualMemoryVsTime","Virtual memory as function of Runtime;Time [s];Memory [MB]",timePeriod, 0, timePeriod);
  TH1F* EventtimeVsEvent = new TH1F("EventtimeVsEvent","Runtime per Event as function of Event number;Event;Time [s]",(entries-1)*10, 1, entries);

  std::vector<Double_t> timeDiffSorted(fTimeDiff);
  std::vector<Double_t>::iterator it;
  std::sort(timeDiffSorted.begin(), timeDiffSorted.end());

  Int_t minTime = timeDiffSorted.front();
  Int_t maxTime = timeDiffSorted.back();
  timePeriod = maxTime - minTime;

  TH1F* TimePerEvent = new TH1F("TimePerEvent","Runtime;Time [s];Events",(timePeriod+20)*10, minTime-10, maxTime+10);

  Int_t counter = 0;
  std::vector<Long_t>::iterator lit;
  for(lit=fResidentMemory.begin(); lit<fResidentMemory.end(); lit++) {
    ResidentMemoryVsEvent->Fill(counter, *lit);
    counter++;
  }

  counter = 1;
  for(it=fTimeDiff.begin(); it<fTimeDiff.end(); it++) {
    TimePerEvent->Fill(*it);
    EventtimeVsEvent->Fill(counter, *it);
    counter++;
  }


  histoList->AddLast(ResidentMemoryVsEvent);
  histoList->AddLast(TimePerEvent);
  histoList->AddLast(EventtimeVsEvent);
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
  GetInfo();
}

void FairRunInfo::GetInfo()
{
  // Set the TimeStamp to the actual time and store it
  fTimeStamp.Set();
  //  fTime.push_back(fTimeStamp.GetSec());
  fTime.push_back(fTimeStamp.AsDouble());

  gSystem->GetProcInfo(&fProcInfo);
  fResidentMemory.push_back(fProcInfo.fMemResident/1024);
  fVirtualMemory.push_back(fProcInfo.fMemVirtual/1024);
}
