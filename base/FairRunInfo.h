#ifndef FAIRRUNINFO_H
#define FAIRRUNINFO_H


#include "TObject.h"
#include "TSystem.h"
#include "TTimeStamp.h"

#include <vector>

class FairLogger;
class TList;

class FairRunInfo : public TObject
{

  public:

    FairRunInfo();

    ~FairRunInfo();

    void StoreInfo();

    void WriteInfo();

    void Reset();

  private:

    TTimeStamp  fTimeStamp;//!
    CpuInfo_t   fCpuInfo;//!
    MemInfo_t   fMemInfo;//!
    ProcInfo_t  fProcInfo;//!
    std::vector<Int_t> fTimeDiff;//!
    std::vector<Int_t> fTime;//!
    std::vector<Long_t> fResidentMemory;//!
    std::vector<Long_t> fVirtualMemory;//!
    FairLogger* fLogger;

    void CalculateTimeDifference();

    void PrintInfo();

    void CreateAndFillHistograms(TList* histoList);

    void WriteHistosToFile(TList* histoList);

    ClassDef(FairRunInfo,1)

};
#endif
