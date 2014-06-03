/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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

