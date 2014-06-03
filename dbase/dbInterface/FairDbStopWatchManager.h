/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBSTOPWATCHMANAGER
#define FAIRDBSTOPWATCHMANAGER

#include "Rtypes.h"                     // for Bool_t, UInt_t, etc

#include <string>
#include <list>

class FairDbStopWatch;

class FairDbStopWatchManager
{

  public:

    FairDbStopWatchManager();
    virtual ~FairDbStopWatchManager();

    void Enable(Bool_t flag=kTRUE,
                Bool_t enableSubWatch = kFALSE) {
      fEnabled = flag;
      fSubWatchEnabled = enableSubWatch;
    }
    void RecBegin(std::string tableName, UInt_t rowSize);
    void RecEnd(UInt_t numRows);
    void RecFillAgg(Int_t aggNo);
    void RecMainQuery();
    void StartSubWatch(UInt_t subWatch);


    static FairDbStopWatchManager gStopWatchManager;

  private:

    FairDbStopWatch* GetCurrent();
    FairDbStopWatch* Pop();
    FairDbStopWatch* Push();


    Bool_t fEnabled;
    Bool_t fSubWatchEnabled;
    std::list<FairDbStopWatch*> fStopWatchs;

    ClassDef(FairDbStopWatchManager,0)    // Query StopWatch

};


#endif // FAIRDBSTOPWATCHMANAGER

