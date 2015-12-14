/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * FairMonitor.h
 *
 *  Created on: Aug 01, 2015
 *      Author: r.karabowicz
 */

#ifndef BASE_FAIRMONITOR_H_
#define BASE_FAIRMONITOR_H_

#include <list>
#include <map>

#include "TNamed.h"
#include "TStopwatch.h"

class TCanvas;
class TFile;
class TList;
class TTask;

class FairMonitor : public TNamed
{
  public:
  static FairMonitor* GetMonitor();

  void EnableMonitor(Bool_t tempBool = kTRUE) { fRunMonitor = tempBool; }

  void StartMonitoring(const TTask* tTask, const char* identStr) {
    StartTimer        (tTask,identStr);
    StartMemoryMonitor(tTask,identStr);
  }
  void  StopMonitoring(const TTask* tTask, const char* identStr) {
    StopTimer        (tTask,identStr);
    StopMemoryMonitor(tTask,identStr);
  }

  void StartTimer(const TTask* tTask, const char* identStr);
  void  StopTimer(const TTask* tTask, const char* identStr);

  void StartMemoryMonitor(const TTask* tTask, const char* identStr);
  void  StopMemoryMonitor(const TTask* tTask, const char* identStr);

  void RecordInfo(const TTask* tTask, const char* identStr, Double_t value);

  void RecordRegister(const char* name, const char* folderName, Bool_t toFile);
  void RecordGetting(const char* name);

  void SetCurrentTask(TTask* tTask) { fCurrentTask = tTask; }

  virtual void Print(Option_t* option = "") const;
  virtual void Draw (Option_t* option = "");

  void PrintTask(TString specString) const;
  void PrintTask(TTask* tempTask, Int_t taskLevel=0) const;
  void DrawHist(TString specString);

  TList* GetHistList() { return fHistList; }

  void StoreHistograms(TFile* tfile);

  private:
    static FairMonitor* instance;
    FairMonitor();
    ~FairMonitor();
    FairMonitor(const FairMonitor&);
    FairMonitor& operator=(const FairMonitor&);

    Bool_t fRunMonitor;

    Double_t fRunTime; 
    Double_t fRunMem;

    std::map<TString, TStopwatch> fTimerMap;
    std::map<TString, Int_t> fMemoryMap;

    TList* fHistList;
    TCanvas* fCanvas;

    Int_t fNoTaskRequired;
    Int_t fNoTaskCreated;

    TTask* fCurrentTask;
    std::multimap<TString, TString> fTaskRequired;
    std::multimap<TString, TString> fTaskCreated;
    std::multimap<TString, TString> fTaskCreatedTemp;
    
    std::map<TString, Int_t> fObjectMap;
    std::map<TString, Int_t> fTaskMap;

    std::map<TString, std::pair<Double_t, Double_t> > fObjectPos;
    std::map<TString, std::pair<Double_t, Double_t> > fTaskPos;
 
    void GetTaskMap(TTask* tempTask);
    void AnalyzeObjectMap(TTask* tempTask);

    ClassDef(FairMonitor, 0)
};

extern FairMonitor* gMonitor;

#endif  // BASE_FAIRMONITOR_H_
