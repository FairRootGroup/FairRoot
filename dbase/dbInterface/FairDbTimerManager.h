#ifndef FAIRDBTIMERMANAGER
#define FAIRDBTIMERMANAGER

#include "Rtypes.h"                     // for Bool_t, UInt_t, etc

#include <string>
#include <list>

class FairDbTimer;

class FairDbTimerManager
{

  public:

// Constructors and destructors.
    FairDbTimerManager();
    virtual ~FairDbTimerManager();

// State testing member functions

// State changing member functions
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

// Global timer manager used for all queries to the DB.

    static FairDbTimerManager gTimerManager;

  private:

    FairDbTimer* GetCurrent();
    FairDbTimer* Pop();
    FairDbTimer* Push();

// Data members

    Bool_t fEnabled;     // Enable/disable
    Bool_t fSubWatchEnabled;
    // SubWatch Enable/disable (not used now).
    std::list<FairDbTimer*> fTimers;      // Push-down stack of timers.

    ClassDef(FairDbTimerManager,0)    // Simple query timer

};


#endif // FAIRDBTIMERMANAGER

