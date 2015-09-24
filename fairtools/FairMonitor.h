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

class TList;
class TTask;

class FairMonitor : public TNamed
{
  public:
  static FairMonitor* GetMonitor();

  void StartTimer(const TTask* tTask, const char* identStr);
  void StopTimer (const TTask* tTask, const char* identStr);

  void RecordRegister(const char* name, const char* folderName, Bool_t toFile);
  void RecordGetting(const char* name);

  void SetCurrentTask(TTask* tTask) { fCurrentTask = tTask; }

  virtual void Print(Option_t* option = "");
  virtual void Draw (Option_t* option = "");

  void Print(TString specString);

  void DrawHist(TString specString);

  void PrintTask(TTask* tempTask, Int_t taskLevel=0);

  TList* GetHistList() { return fTimerHistList;}

  void EnableMonitor(Bool_t tempBool = kTRUE) { fRunMonitor = tempBool; }

  private:
    static FairMonitor* instance;
    FairMonitor();
    ~FairMonitor();

    Bool_t fRunMonitor;

    Double_t fRunTime;

    Double_t* fTimeArray;

    TList* fTimerHistList;
    TList* fTimerList;

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

    ClassDef(FairMonitor, 1)
};

extern FairMonitor* gMonitor;

#endif  // BASE_FAIRMONITOR_H_
