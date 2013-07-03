#ifndef FAIRDBLOGSTAT_H
#define FAIRDBLOGSTAT_H
#include "FairDbLog.h"


class FairDbLogStat
{
  public:
    FairDbLogStat();
    ~FairDbLogStat();
    int GetPrintCount(FairDbLog::LogLevel_t lvl) const;
    void Clear();
    void LogPrint(FairDbLog::LogLevel_t lvl);

  private:
    int fPrintCount[FairDbLog::kNLogLevel];
};

#endif // 

