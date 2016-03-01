/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQEXAMPLE9PROCESSOR_H_
#define FAIRMQEXAMPLE9PROCESSOR_H_

#include <string>

#include "FairMQDevice.h"
#include "RootSerializer.h"
#include "TClonesArray.h"
#include "PixelFindHits.h"
#include "PixelDigiPar.h" 

class FairMQEx9Processor : public FairMQDevice
{
  public:
    enum
    {
        InputClassName = FairMQDevice::Last,
        RootParam,
        AsciiParam,
        ParamName,
        Last
    };

    FairMQEx9Processor();
    virtual ~FairMQEx9Processor();

    void SetProperty(const int key, const std::string& value);
    std::string GetProperty(const int key, const std::string& default_ = "");
    void SetProperty(const int key, const int value);
    int GetProperty(const int key, const int default_ = 0);

  protected:

    virtual void Run();
    virtual void Init();
    void UpdateParameter(const std::string& paramName);
    void UpdateParameters();


    static void CustomCleanup(void *data, void *hint);

    template<typename parameter_type>
    parameter_type* UpdateParameter(const std::string& paramName)
    {
        //*

        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

        std::string* reqStr = new std::string(paramName + "," + std::to_string(fCurrentRunId));

        LOG(DEBUG) << "Requesting parameter \"" << paramName << "\" for Run ID " << fCurrentRunId << ".";

        std::unique_ptr<FairMQMessage> req(fTransportFactory->CreateMessage(const_cast<char*>(reqStr->c_str()), reqStr->length(), CustomCleanup, reqStr));
        std::unique_ptr<FairMQMessage> rep(fTransportFactory->CreateMessage());

        if (fChannels.at("data").at(0).Send(req) > 0)
        {
            if (fChannels.at("data").at(0).Receive(rep) > 0)
            {
                parameter_type* param = fParamDeserializer.DeserializeMsg(rep.get());
                LOG(DEBUG) << "Received parameter from the server:";
                return param;
            }
        }


        return nullptr;
        // */
    }



    TClonesArray* fOutput;
    std::string fRootParFileName;
    std::string fAsciiParFileName;
    std::string fInputClassName;
    std::string fParamName;
    std::string fGeoParamName;
    int fCurrentRunId;

    RootSerializer fSerializer;
    RootDeSerializer fDeSerializer;
    base_RootDeSerializer<PixelDigiPar> fParamDeserializer;
    PixelFindHits* fHitFinder;

    
};

#endif /* FAIRMQEXAMPLE9PROCESSOR_H_ */