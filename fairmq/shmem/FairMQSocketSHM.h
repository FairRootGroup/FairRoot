/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQSOCKETSHM_H_
#define FAIRMQSOCKETSHM_H_

#include "FairMQSocket.h"
#include "FairMQMessage.h"

#include <fairmq/shmem/Manager.h>

#include <atomic>
#include <memory> // unique_ptr

class FairMQSocketSHM : public FairMQSocket
{
  public:
    FairMQSocketSHM(fair::mq::shmem::Manager& manager, const std::string& type, const std::string& name, const std::string& id = "", void* context = nullptr);
    FairMQSocketSHM(const FairMQSocketSHM&) = delete;
    FairMQSocketSHM operator=(const FairMQSocketSHM&) = delete;

    std::string GetId() override { return fId; }

    bool Bind(const std::string& address) override;
    void Connect(const std::string& address) override;

    int Send(FairMQMessagePtr& msg) override;
    int SendAsync(FairMQMessagePtr& msg) override;
    int Receive(FairMQMessagePtr& msg) override;
    int ReceiveAsync(FairMQMessagePtr& msg) override;

    int64_t Send(std::vector<std::unique_ptr<FairMQMessage>>& msgVec) override;
    int64_t SendAsync(std::vector<std::unique_ptr<FairMQMessage>>& msgVec) override;
    int64_t Receive(std::vector<std::unique_ptr<FairMQMessage>>& msgVec) override;
    int64_t ReceiveAsync(std::vector<std::unique_ptr<FairMQMessage>>& msgVec) override;

    void* GetSocket() const override;
    int GetSocket(int nothing) const override;
    void Close() override;

    void Interrupt() override;
    void Resume() override;

    void SetOption(const std::string& option, const void* value, size_t valueSize) override;
    void GetOption(const std::string& option, void* value, size_t* valueSize) override;

    unsigned long GetBytesTx() const override;
    unsigned long GetBytesRx() const override;
    unsigned long GetMessagesTx() const override;
    unsigned long GetMessagesRx() const override;

    bool SetSendTimeout(const int timeout, const std::string& address, const std::string& method) override;
    int GetSendTimeout() const override;
    bool SetReceiveTimeout(const int timeout, const std::string& address, const std::string& method) override;
    int GetReceiveTimeout() const override;

    static int GetConstant(const std::string& constant);

    ~FairMQSocketSHM() override;

  private:
    void* fSocket;
    fair::mq::shmem::Manager& fManager;
    std::string fId;
    std::atomic<unsigned long> fBytesTx;
    std::atomic<unsigned long> fBytesRx;
    std::atomic<unsigned long> fMessagesTx;
    std::atomic<unsigned long> fMessagesRx;

    static std::atomic<bool> fInterrupted;

    int Send(FairMQMessagePtr& msg, const int flags);
    int Receive(FairMQMessagePtr& msg, const int flags);
    int64_t Send(std::vector<std::unique_ptr<FairMQMessage>>& msgVec, const int flags);
    int64_t Receive(std::vector<std::unique_ptr<FairMQMessage>>& msgVec, const int flags);
};

#endif /* FAIRMQSOCKETSHM_H_ */
