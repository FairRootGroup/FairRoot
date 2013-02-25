
#include "FairDbTimer.h"

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
    // Use Start to reset the counter (Reset doesn't do this).
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

  cout << "FairDbTimer:" <<  fTableName
       << ": Query done. "  << numRows
       << "rows, " <<  tableSize << units
       << " Cpu" <<  fWatch.CpuTime()
       << " , elapse" << fWatch.RealTime()
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

      cout << "      SubWatch " <<  subWatchNames[subWatch]
           << ": Cpu" <<  fSubWatches[subWatch].CpuTime()
           << " , elapse" << fSubWatches[subWatch].RealTime()
           << " , Starts " << fSubWatches[subWatch].Counter()
           << endl;
    }
  }
}
//.....................................................................

void FairDbTimer::RecMainQuery()
{

  fQueryStage = kMainQuery;

}

void FairDbTimer::RecFillAgg(Int_t /* aggNo */)
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

