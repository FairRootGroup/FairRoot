/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQMessageZMQ.h
 *
 * @since 2014-01-17
 * @author A. Rybalchenko
 */

#ifndef FAIRMQMESSAGEZMQ_H_
#define FAIRMQMESSAGEZMQ_H_

#include <cstddef>

#include <zmq.h>

#include "FairMQMessage.h"

class FairMQMessageZMQ : public FairMQMessage
{
  public:
    FairMQMessageZMQ();
    FairMQMessageZMQ(size_t size);
    FairMQMessageZMQ(void* data, size_t size, fairmq_free_fn *ffn = &CleanUp, void* hint = NULL);

    virtual void Rebuild();
    virtual void Rebuild(size_t size);
    virtual void Rebuild(void* data, size_t size, fairmq_free_fn *ffn = &CleanUp, void* hint = NULL);

    virtual void* GetMessage();
    virtual void* GetData();
    virtual size_t GetSize();

    virtual void SetMessage(void* data, size_t size);

    virtual void CloseMessage();
    virtual void Copy(FairMQMessage* msg);

    static void CleanUp(void* data, void* hint);

    virtual ~FairMQMessageZMQ();

  private:
    zmq_msg_t fMessage;
};

#endif /* FAIRMQMESSAGEZMQ_H_ */
