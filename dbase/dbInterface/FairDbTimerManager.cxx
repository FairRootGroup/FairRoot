
#include "FairDbTimer.h"
#include "FairDbTimerManager.h"

ClassImp(FairDbTimerManager)


FairDbTimerManager FairDbTimerManager::gTimerManager;

FairDbTimerManager::FairDbTimerManager() :
  fEnabled(kTRUE),
  fSubWatchEnabled(kFALSE),
  fTimers()
{
}

FairDbTimerManager::~FairDbTimerManager()
{
  while ( this->GetCurrent() ) { this->Pop(); }

}

FairDbTimer* FairDbTimerManager::GetCurrent()
{

  return fTimers.empty() ? 0 : *(fTimers.begin());
}

FairDbTimer* FairDbTimerManager::Pop()
{
  if ( fTimers.empty() ) { return 0; }

  FairDbTimer* timer = this->GetCurrent();
  delete timer;
  timer = 0;
  fTimers.pop_front();
  timer = this->GetCurrent();
  if ( timer ) { timer->Resume(); }
  return timer;

}


FairDbTimer* FairDbTimerManager::Push()
{

  FairDbTimer* timer = this->GetCurrent();
  if ( timer ) { timer->Suspend(); }
  fTimers.push_front(new FairDbTimer);
  return this->GetCurrent();

}

void FairDbTimerManager::RecBegin(string tableName, UInt_t rowSize)
{

  if ( ! fEnabled ) { return; }
  FairDbTimer* timer = this->Push();
  timer->RecBegin(tableName, rowSize);
}

void FairDbTimerManager::RecEnd(UInt_t numRows)
{

  if ( ! fEnabled ) { return; }


  FairDbTimer* timer = this->GetCurrent();
  if ( timer ) { timer->RecEnd(numRows); }
  timer = this->Pop();

}

void FairDbTimerManager::RecFillAgg(Int_t aggno)
{
  if ( ! fEnabled ) { return; }


}


void FairDbTimerManager::RecMainQuery()
{

  if ( ! fEnabled ) { return; }
  FairDbTimer* timer = this->GetCurrent();
  if ( timer ) { timer->RecMainQuery(); }

}


void FairDbTimerManager::StartSubWatch(UInt_t subWatch)
{

  if ( ! fEnabled ) { return; }
  FairDbTimer* timer = this->GetCurrent();
  if ( timer ) { timer->StartSubWatch(subWatch); }

}


