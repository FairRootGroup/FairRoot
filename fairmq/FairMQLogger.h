/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQLogger.h
 *
 * @since 2012-12-04
 * @author D. Klein, A. Rybalchenko
 */

#ifndef FAIRMQLOGGER_H_
#define FAIRMQLOGGER_H_

#include <sstream>
#include <sys/time.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <stdio.h>

class FairMQLogger
{
  public:      
    enum Level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
        STATE,
        NOLOG
    };
    
    FairMQLogger();
    virtual ~FairMQLogger();
    std::ostringstream& Log(int type);

    static void SetLogLevel(int loglevel)
    { 
        FairMQLogger::fMinLogLevel = loglevel; 
    }
    
  private:
    std::ostringstream os;
    int fLogLevel;
    static int fMinLogLevel;
};

typedef unsigned long long timestamp_t;

timestamp_t get_timestamp();

#define LOG(type) FairMQLogger().Log(FairMQLogger::type)
#define MQLOG(type) FairMQLogger().Log(FairMQLogger::type)
#define SET_LOG_LEVEL(loglevel) FairMQLogger::SetLogLevel(FairMQLogger::loglevel)

#endif /* FAIRMQLOGGER_H_ */
