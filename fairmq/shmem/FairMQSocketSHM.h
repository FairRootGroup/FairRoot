/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQSOCKETSHM_H_
#define FAIRMQSOCKETSHM_H_

#include <atomic>

#include <memory> // unique_ptr

#include "FairMQSocket.h"
#include "FairMQMessage.h"
#include "FairMQShmManager.h"

class FairMQSocketSHM : public FairMQSocket
{
  public:
    FairMQSocketSHM(const std::string& type, const std::string& name, const std::string& id = "", void* context = nullptr);
    FairMQSocketSHM(const FairMQSocketSHM&) = delete;
    FairMQSocketSHM operator=(const FairMQSocketSHM&) = delete;

    virtual std::string GetId();

    virtual bool Bind(const std::string& address);
    virtual void Connect(const std::string& address);

    virtual int Send(FairMQMessagePtr& msg, const int flags = 0);
    virtual int Receive(FairMQMessagePtr& msg, const int flags = 0);

    virtual int64_t Send(std::vector<std::unique_ptr<FairMQMessage>>& msgVec, const int flags = 0);
    virtual int64_t Receive(std::vector<std::unique_ptr<FairMQMessage>>& msgVec, const int flags = 0);

    virtual void* GetSocket() const;
    virtual int GetSocket(int nothing) const;
    virtual void Close();

    virtual void Interrupt();
    virtual void Resume();

    virtual void SetOption(const std::string& option, const void* value, size_t valueSize);
    virtual void GetOption(const std::string& option, void* value, size_t* valueSize);

    virtual unsigned long GetBytesTx() const;
    virtual unsigned long GetBytesRx() const;
    virtual unsigned long GetMessagesTx() const;
    virtual unsigned long GetMessagesRx() const;

    virtual bool SetSendTimeout(const int timeout, const std::string& address, const std::string& method);
    virtual int GetSendTimeout() const;
    virtual bool SetReceiveTimeout(const int timeout, const std::string& address, const std::string& method);
    virtual int GetReceiveTimeout() const;

    static int GetConstant(const std::string& constant);

    virtual ~FairMQSocketSHM();

  private:
    void* fSocket;
    std::string fId;
    std::atomic<unsigned long> fBytesTx;
    std::atomic<unsigned long> fBytesRx;
    std::atomic<unsigned long> fMessagesTx;
    std::atomic<unsigned long> fMessagesRx;

    static std::atomic<bool> fInterrupted;
};

#endif /* FAIRMQSOCKETSHM_H_ */
