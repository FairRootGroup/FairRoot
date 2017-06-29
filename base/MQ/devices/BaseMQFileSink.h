/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/* 
 * File:   BaseMQFileSink.h
 * Author: winckler
 *
 * Created on October 7, 2014, 6:06 PM
 */

#ifndef BASEMQFILESINK_H
#define BASEMQFILESINK_H

#include "FairMQDevice.h"
#include "FairMQLogger.h"

/*********************************************************************
 * -------------- NOTES -----------------------
 * All policies must have a default constructor
 * Function to define in (parent) policy classes :
 * 
 *  -------- INPUT POLICY --------
 *                deserialization_type::InitContainer(...)
 * CONTAINER_TYPE deserialization_type::DeserializeMsg(FairMQMessage* msg)
 * 
 * 
 *  -------- OUTPUT POLICY --------
 *                SinkType::AddToFile(CONTAINER_TYPE);
 *                SinkType::InitOutputFile()
 **********************************************************************/

template <typename T, typename U>
class BaseMQFileSink : public FairMQDevice, public T, public U
{
  public:
    typedef T InputPolicy;
    typedef U SinkType;

    BaseMQFileSink()
        : FairMQDevice()
        , InputPolicy()
        , SinkType()
    {}

    virtual ~BaseMQFileSink()
    {}

    template<typename... Args>
    void InitInputData(Args&&... args)
    {
        InputPolicy::Create(std::forward<Args>(args)...);
    }

  protected:
    using InputPolicy::fInput;

    virtual void InitTask()
    {
        SinkType::InitOutputFile();
    }

    typedef typename InputPolicy::deserialization_type DeserializerType;
    virtual void Run()
    {
        int receivedMsg = 0;
        while (CheckCurrentState(RUNNING))
        {
            std::unique_ptr<FairMQMessage> msg(NewMessage());
            if (Receive(msg,"data-in") > 0)
            {
                Deserialize<DeserializerType>(*msg, fInput);
                U::Serialize(fInput); // add fInput to file
                receivedMsg++;
            }
        }

        LOG(INFO) << "Received " << receivedMsg << " messages!";
    }
};

#endif /* BASEMQFILESINK_H */
