/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMonitor.cxx
 *
 *  Created on: Oct 30, 2014
 *      Author: r.karabowicz
 */

#include "FairMonitor.h"
#include "FairLogger.h"

#include "TAxis.h"
#include "TH1F.h"
#include "TList.h"
#include "TNamed.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TString.h"
#include "TTask.h"

#include <iomanip>
#include <iostream>
#include <iterator>
#include <utility>

FairMonitor* FairMonitor::instance = NULL;

//_____________________________________________________________________________
FairMonitor::FairMonitor()
  : TNamed("FairMonitor","Monitor for FairRoot")
  , fRunTime(0.)
  , fTimeArray(new Double_t[1000])
  , fTimerHistList(new TList())
  , fTimerList(new TList())
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairMonitor::~FairMonitor()
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairMonitor* FairMonitor::GetMonitor()
{
  if (!instance) {
    instance = new FairMonitor();
  }
  return instance;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairMonitor::StartTimer(const TTask* tTask, const char* identStr) {
  TString tempString = Form("hist_%X_%s_%s",tTask,tTask->GetName(),identStr);

  Int_t nofHists = fTimerHistList->GetEntries();
  Int_t ihist = 0;
  for ( ihist = 0 ; ihist < nofHists ; ihist++ ) {
    if ( !tempString.CompareTo(fTimerHistList->At(ihist)->GetName()) ) {
      break;
    }
  }
  if ( ihist == nofHists ) {
    fTimerList->Add(new TStopwatch()); 
    TString titleString = Form("Time distribution for %s, %s",tTask->GetName(),identStr);
    fTimerHistList->Add(new TH1F(tempString,titleString,1000,0.,0.0001));
    fTimeArray[nofHists] = 0.;
  }
  ((TStopwatch*)(fTimerList->At(ihist)))->Start();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairMonitor::StopTimer(const TTask* tTask, const char* identStr) {
  TString tempString = Form("hist_%X_%s_%s",tTask,tTask->GetName(),identStr);

  Int_t nofHists = fTimerHistList->GetEntries();
  Int_t ihist = 0;
  for ( ihist = 0 ; ihist < nofHists ; ihist++ ) {
    if ( !tempString.CompareTo(fTimerHistList->At(ihist)->GetName()) ) {
      break;
    }
  }
  if ( ihist == nofHists ) {
    LOG(INFO) << "FairMonitor::StopTimer() called without matching StartTimer()" << FairLogger::endl;
    return;
  }
  ((TStopwatch*)(fTimerList->At(ihist)))->Stop();
  Double_t time = ((TStopwatch*)(fTimerList->At(ihist)))->RealTime();
  TH1F* tempHist = ((TH1F*)(fTimerHistList->At(ihist)));
  Double_t histXmax = tempHist->GetXaxis()->GetXmax();
  while ( histXmax < time ) 
    {
      tempHist->Rebin(10);
      tempHist->SetBins(1000,0.,histXmax*10);
      histXmax = tempHist->GetXaxis()->GetXmax();
    }
  fRunTime += time;
  fTimeArray[ihist] += time;
  ((TH1F*)(fTimerHistList->At(ihist)))->Fill(time);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairMonitor::PrintTask(TTask* tempTask, Int_t taskLevel) {

  TString tempString = Form("hist_%X_%s_%s",tempTask,tempTask->GetName(),"EXEC");
  Int_t nofHists = fTimerHistList->GetEntries();
  Int_t ihist = 0;
  Int_t longestName = 0;
  for ( ihist = 0 ; ihist < nofHists ; ihist++ ) {
    if ( longestName < strlen(fTimerHistList->At(ihist)->GetName()) ) 
      longestName = strlen(fTimerHistList->At(ihist)->GetName());
  }
  for ( ihist = 0 ; ihist < nofHists ; ihist++ ) {
    if ( !tempString.CompareTo(fTimerHistList->At(ihist)->GetName()) ) {
      for ( Int_t ilev = 0 ; ilev < taskLevel ; ilev++ )
	LOG(INFO) << "  " << FairLogger::flush;
      LOG(INFO) << "\"" << tempTask->GetName() << "\"" << FairLogger::flush;
      for ( Int_t ilen = strlen(fTimerHistList->At(ihist)->GetName()) ; ilen < longestName+10-taskLevel*2 ; ilen++ )
	LOG(INFO) << " " << FairLogger::flush;
      LOG(INFO) << ((TH1F*)(fTimerHistList->At(ihist)))->GetMean() << " s/ev [" << (Int_t)(fTimeArray[ihist]/fRunTime*100.) << "%]" << FairLogger::endl;
    }
  }

  TList* subTaskList = tempTask->GetListOfTasks();
  if ( !subTaskList ) return;
  for ( Int_t itask = 0 ; itask < subTaskList->GetEntries() ; itask++ ) {
    TTask* subTask = (TTask*)subTaskList->At(itask);
    if ( subTask ) 
      PrintTask(subTask,taskLevel+1);
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairMonitor::Print(TString specString) {
  Int_t nofHists = fTimerHistList->GetEntries();
  for ( Int_t ihist = 0 ; ihist < nofHists ; ihist++ ) {
    TString histString = Form("%s",fTimerHistList->At(ihist)->GetName());
    if ( !histString.Contains("EXEC") && histString.Contains(specString) ) {
      LOG(INFO) << histString.Data() << " " << ((TH1F*)(fTimerHistList->At(ihist)))->GetMean() << " s/ev [" << (Int_t)(fTimeArray[ihist]/fRunTime*100.) << "%]" << FairLogger::endl;
    }
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairMonitor::Print() {

  TTask* mainFairTask = (TTask*)(gROOT->GetListOfBrowsables()->FindObject("FairTaskList"));
  if ( mainFairTask ) 
    PrintTask(mainFairTask,0);

  LOG(INFO) << "-------------------------------------------------------------------------------------" << FairLogger::endl;
  Print("");

}
//_____________________________________________________________________________


ClassImp(FairMonitor)
