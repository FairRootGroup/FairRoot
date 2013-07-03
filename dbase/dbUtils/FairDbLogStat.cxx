#include "FairDbLogStat.h"
#include <cassert>

FairDbLogStat::FairDbLogStat()
{
  this->Clear();
}

FairDbLogStat::~FairDbLogStat()
{
}


int FairDbLogStat::GetPrintCount(FairDbLog::LogLevel_t lvl) const
{
  assert(lvl >= FairDbLog::kMinLogLevel && lvl <= FairDbLog::kNLogLevel);
  return fPrintCount[lvl];
}

void FairDbLogStat::Clear()
{
  for (int i=0; i<FairDbLog::kNLogLevel; ++i) {
    fPrintCount[i] = 0;
  }
}

void FairDbLogStat::LogPrint(FairDbLog::LogLevel_t lvl)
{
  assert(lvl >= FairDbLog::kMinLogLevel && lvl <= FairDbLog::kNLogLevel);
  ++fPrintCount[lvl];
}


