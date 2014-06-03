/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRDBSTOPWATCH
#define FAIRDBSTOPWATCH

#include "Rtypes.h"                     // for UInt_t, FairDbStopWatch::Class, etc
#include "TStopwatch.h"                 // for TStopwatch

#include <string>                       // for string

class FairDbStopWatch
{

  public:
    FairDbStopWatch();
    virtual ~FairDbStopWatch();

    void RecBegin(std::string tableName, UInt_t rowSize);
    void RecEnd(UInt_t numRows);
    void RecFillAgg(Int_t aggNo);
    void RecMainQuery();
    void Resume();
    void StartSubWatch(UInt_t subWatch);
    void Suspend();



  private:

    enum  QueryStage { kPassive, kInitialQuery, kMainQuery };
    enum { kMaxSubWatch = 4 };

// Data members

    Int_t fCurSubWatch;
    UInt_t fRowSize;
    QueryStage fQueryStage;
    TStopwatch fSubWatches[kMaxSubWatch]; // Partial watches
    std::string fTableName;   // Current table
    TStopwatch fWatch;       // StopWatch

    ClassDef(FairDbStopWatch,0)     // Query StopWatch

};


#endif // FAIRDBSTOPWATCH

