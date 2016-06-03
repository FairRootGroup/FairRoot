/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExampleShmSink.h
 *
 * @since 2016-04-08
 * @author A. Rybalchenko
 */

#ifndef FAIRMQEXAMPLESHMSINK_H_
#define FAIRMQEXAMPLESHMSINK_H_

#include <atomic>

#include "FairMQDevice.h"

class FairMQExampleShmSink : public FairMQDevice
{
  public:
    FairMQExampleShmSink();
    virtual ~FairMQExampleShmSink();

    void Log(const int intervalInMs);

  protected:
    unsigned long long fBytesIn;
    unsigned long long fMsgIn;
    std::atomic<unsigned long long> fBytesInNew;
    std::atomic<unsigned long long> fMsgInNew;

    virtual void Init();
    virtual void Run();
};

#endif /* FAIRMQEXAMPLESHMSINK_H_ */
