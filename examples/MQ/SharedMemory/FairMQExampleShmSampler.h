/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExampleShmSampler.h
 *
 * @since 2016-04-08
 * @author A. Rybalchenko
 */

#ifndef FAIRMQEXAMPLESHMSAMPLER_H_
#define FAIRMQEXAMPLESHMSAMPLER_H_

#include <string>

#include "FairMQDevice.h"
#include "ShmChunk.h"

class FairMQExampleShmSampler : public FairMQDevice
{
  public:
    enum
    {
        MsgSize = FairMQDevice::Last,
        Last
    };

    FairMQExampleShmSampler();
    virtual ~FairMQExampleShmSampler();

    void ListenForAcks();
    void Log(const int intervalInMs);

    virtual void SetProperty(const int key, const std::string& value);
    virtual std::string GetProperty(const int key, const std::string& default_ = "");
    virtual void SetProperty(const int key, const int value);
    virtual int GetProperty(const int key, const int default_ = 0);

    virtual std::string GetPropertyDescription(const int key);
    virtual void ListProperties();

  protected:
    int fMsgSize;

    unsigned long long fBytesOut;
    unsigned long long fMsgOut;
    std::atomic<unsigned long long> fBytesOutNew;
    std::atomic<unsigned long long> fMsgOutNew;

    std::unordered_map<std::string, SharedPtrType> fLocalPtrs;

    std::mutex fContainerMutex;
    std::mutex fAckMutex;
    std::condition_variable fAckCV;

    virtual void Init();
    virtual void Run();
};

#endif /* FAIRMQEXAMPLESHMSAMPLER_H_ */
