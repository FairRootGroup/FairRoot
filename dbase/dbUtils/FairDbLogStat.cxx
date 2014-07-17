/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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


