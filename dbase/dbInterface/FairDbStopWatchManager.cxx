/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbStopWatchManager.h"

#include "FairDbStopWatch.h"

using std::string;

ClassImp(FairDbStopWatchManager)


FairDbStopWatchManager FairDbStopWatchManager::gStopWatchManager;

FairDbStopWatchManager::FairDbStopWatchManager() :
  fEnabled(kTRUE),
  fSubWatchEnabled(kFALSE),
  fStopWatchs()
{
}

FairDbStopWatchManager::~FairDbStopWatchManager()
{
  while ( this->GetCurrent() ) { this->Pop(); }

}

FairDbStopWatch* FairDbStopWatchManager::GetCurrent()
{

  return fStopWatchs.empty() ? 0 : *(fStopWatchs.begin());
}

FairDbStopWatch* FairDbStopWatchManager::Pop()
{
  if ( fStopWatchs.empty() ) { return 0; }

  FairDbStopWatch* timer = this->GetCurrent();
  delete timer;
  timer = 0;
  fStopWatchs.pop_front();
  timer = this->GetCurrent();
  if ( timer ) { timer->Resume(); }
  return timer;

}


FairDbStopWatch* FairDbStopWatchManager::Push()
{

  FairDbStopWatch* timer = this->GetCurrent();
  if ( timer ) { timer->Suspend(); }
  fStopWatchs.push_front(new FairDbStopWatch);
  return this->GetCurrent();

}

void FairDbStopWatchManager::RecBegin(string tableName, UInt_t rowSize)
{

  if ( ! fEnabled ) { return; }
  FairDbStopWatch* timer = this->Push();
  timer->RecBegin(tableName, rowSize);
}

void FairDbStopWatchManager::RecEnd(UInt_t numRows)
{

  if ( ! fEnabled ) { return; }


  FairDbStopWatch* timer = this->GetCurrent();
  if ( timer ) { timer->RecEnd(numRows); }
  timer = this->Pop();

}

void FairDbStopWatchManager::RecFillAgg(Int_t aggno)
{
  if ( ! fEnabled ) { return; }


}


void FairDbStopWatchManager::RecMainQuery()
{

  if ( ! fEnabled ) { return; }
  FairDbStopWatch* timer = this->GetCurrent();
  if ( timer ) { timer->RecMainQuery(); }

}


void FairDbStopWatchManager::StartSubWatch(UInt_t subWatch)
{

  if ( ! fEnabled ) { return; }
  FairDbStopWatch* timer = this->GetCurrent();
  if ( timer ) { timer->StartSubWatch(subWatch); }

}


