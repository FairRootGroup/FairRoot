/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbStopWatch.h"
#include "FairDbLogService.h"
#include "FairDbLogFormat.h"
#include "Riosfwd.h"                    // for ostream
#include <iostream>                     // for operator<<, basic_ostream, etc

using std::cout;
using std::endl;
using std::string;

ClassImp(FairDbStopWatch)

FairDbStopWatch::FairDbStopWatch() :
  fCurSubWatch(0),
  fRowSize(0),
  fQueryStage(kPassive),
  fSubWatches(),
  fTableName(),
  fWatch()
{
  fWatch.Stop();
  for ( int subWatch = 0; subWatch <  kMaxSubWatch; ++subWatch) {
    fSubWatches[subWatch].Stop();
  }
}


FairDbStopWatch::~FairDbStopWatch()
{
}


void FairDbStopWatch::RecBegin(string tableName, UInt_t rowSize)
{

  fQueryStage = kInitialQuery;
  fTableName = tableName;
  fRowSize = rowSize;
  fWatch.Start();
  for ( int subWatch = 0; subWatch <  kMaxSubWatch; ++subWatch) {
    fSubWatches[subWatch].Start();
    fSubWatches[subWatch].Stop();
  }
  if ( fCurSubWatch >= 0 ) { this->StartSubWatch(0); }

}

void FairDbStopWatch::RecEnd(UInt_t numRows)
{

  if ( fQueryStage != kMainQuery ) { return; }

  Float_t tableSize = numRows * fRowSize/1.0e+3;
  string units = "Kb";
  if ( tableSize > 1000. ) {
    tableSize /= 1000.;
    units = "Mb";
  }

  FairDbLogFormat ffmt("%6.1f");

  DBLOG("FairDb",FairDbLog::kInfo)
      << "FairDbStopWatch:" <<  fTableName
      << ": Query done. "  << numRows
      << "rows, " <<  ffmt(tableSize) << units
      << " Cpu" <<  ffmt(fWatch.CpuTime())
      << " , elapsed" << ffmt(fWatch.RealTime())
      << endl;

  fWatch.Stop();
  fQueryStage = kPassive;

  if ( fCurSubWatch >= 0 && fWatch.RealTime() > 5. ) {
    for ( int subWatch = 0; subWatch <  kMaxSubWatch; ++subWatch) {
      static const Char_t* subWatchNames[kMaxSubWatch]
      = { "Query database     ",
          "Create row objects ",
          "Retrieve TSQL rows ",
          "Fill row objects   "
        };
      DBLOG("FairDb",FairDbLog::kInfo)
          << "  Sub. StopWatcher # " <<  subWatchNames[subWatch]
          << ": Cpu" <<  ffmt(fSubWatches[subWatch].CpuTime())
          << " , elapse" << ffmt(fSubWatches[subWatch].RealTime())
          << " , Starts " << ffmt(fSubWatches[subWatch].Counter())
          << endl;
    }
  }
}

void FairDbStopWatch::RecMainQuery()
{
  fQueryStage = kMainQuery;
}

void FairDbStopWatch::RecFillAgg(Int_t /* compNo */)
{
}

void FairDbStopWatch::Resume()
{
  if ( fCurSubWatch >= 0 ) { fSubWatches[fCurSubWatch].Start(kFALSE); }
  fWatch.Start(kFALSE);
}


void FairDbStopWatch::StartSubWatch(UInt_t subWatch)
{
  if (     fCurSubWatch < 0
           || subWatch >= kMaxSubWatch ) { return; }

  fSubWatches[fCurSubWatch].Stop();
  fCurSubWatch = subWatch;
  fSubWatches[fCurSubWatch].Start(kFALSE);

}

void FairDbStopWatch::Suspend()
{
  if ( fCurSubWatch >= 0 ) { fSubWatches[fCurSubWatch].Stop(); }
  fWatch.Stop();
}

