#ifndef FAIRDBTIMERMANAGER
#define FAIRDBTIMERMANAGER

#include "Rtypes.h"                     // for Bool_t, UInt_t, etc

#include <string>
#include <list>

class FairDbTimer;

class FairDbTimerManager
{

  public:

    FairDbTimerManager();
    virtual ~FairDbTimerManager();

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


    static FairDbTimerManager gTimerManager;

  private:

    FairDbTimer* GetCurrent();
    FairDbTimer* Pop();
    FairDbTimer* Push();


    Bool_t fEnabled;
    Bool_t fSubWatchEnabled;
    std::list<FairDbTimer*> fTimers;

    ClassDef(FairDbTimerManager,0)    // Query timer

};


#endif // FAIRDBTIMERMANAGER

