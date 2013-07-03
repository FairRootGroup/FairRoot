#include "FairDbTimer.h"
#include "FairDbLogService.h"
#include "FairDbLogFormat.h"
#include "Riosfwd.h"                    // for ostream
#include <iostream>                     // for operator<<, basic_ostream, etc

using std::cout;
using std::endl;
using std::string;

ClassImp(FairDbTimer)

FairDbTimer::FairDbTimer() :
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


FairDbTimer::~FairDbTimer()
{
}


void FairDbTimer::RecBegin(string tableName, UInt_t rowSize)
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

void FairDbTimer::RecEnd(UInt_t numRows)
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
      << "FairDbTimer:" <<  fTableName
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
          << "      Watcher # " <<  subWatchNames[subWatch]
          << ": Cpu" <<  ffmt(fSubWatches[subWatch].CpuTime())
          << " , elapse" << ffmt(fSubWatches[subWatch].RealTime())
          << " , Starts " << ffmt(fSubWatches[subWatch].Counter())
          << endl;
    }
  }
}

void FairDbTimer::RecMainQuery()
{
  fQueryStage = kMainQuery;
}

void FairDbTimer::RecFillAgg(Int_t /* compNo */)
{
}

void FairDbTimer::Resume()
{
  if ( fCurSubWatch >= 0 ) { fSubWatches[fCurSubWatch].Start(kFALSE); }
  fWatch.Start(kFALSE);
}


void FairDbTimer::StartSubWatch(UInt_t subWatch)
{
  if (     fCurSubWatch < 0
           || subWatch >= kMaxSubWatch ) { return; }

  fSubWatches[fCurSubWatch].Stop();
  fCurSubWatch = subWatch;
  fSubWatches[fCurSubWatch].Start(kFALSE);

}

void FairDbTimer::Suspend()
{
  if ( fCurSubWatch >= 0 ) { fSubWatches[fCurSubWatch].Stop(); }
  fWatch.Stop();
}

