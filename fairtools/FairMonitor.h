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
 *  Created on: Oct 30, 2014
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

  virtual void Print();
  void Print(TString specString);

  void PrintTask(TTask* tempTask, Int_t taskLevel=0);

  TList* GetHistList() { return fTimerHistList;}

  private:
    static FairMonitor* instance;
    FairMonitor();
    ~FairMonitor();

    Double_t fRunTime;

    Double_t* fTimeArray;

    TList* fTimerHistList;
    TList* fTimerList;

    ClassDef(FairMonitor, 1)
};

extern FairMonitor* gMonitor;

#endif  // BASE_FAIRMONITOR_H_
