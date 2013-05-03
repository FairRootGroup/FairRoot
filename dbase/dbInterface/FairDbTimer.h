
#ifndef FAIRDBTIMER
#define FAIRDBTIMER

#include "Rtypes.h"                     // for UInt_t, FairDbTimer::Class, etc
#include "TStopwatch.h"                 // for TStopwatch

#include <string>                       // for string

class FairDbTimer
{

  public:

// Constructors and destructors.
    FairDbTimer();
    virtual ~FairDbTimer();

// State testing member functions

// State changing member functions
    void RecBegin(std::string tableName, UInt_t rowSize);
    void RecEnd(UInt_t numRows);
    void RecFillAgg(Int_t aggNo);
    void RecMainQuery();
    void Resume();
    void StartSubWatch(UInt_t subWatch);
    void Suspend();

// Global timer used for all queries to the Fair DB.

  private:

    enum  QueryStage { kPassive, kInitialQuery, kMainQuery };
    enum { kMaxSubWatch = 4 };  // Must be > 0.

// Data members

    Int_t fCurSubWatch; // Current SubWatch or -1 if disabled.
    UInt_t fRowSize;     // Size of row object
    QueryStage fQueryStage;  // Query stage
    TStopwatch fSubWatches[kMaxSubWatch]; // Partial timers
    std::string fTableName;   // Current table
    TStopwatch fWatch;       // Timer

    ClassDef(FairDbTimer,0)     // Simple query timer

};


#endif // FAIRDBTIMER

