/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * ParameterMQServer.cxx
 *
 * @since 2015-10-26
 * @author M. Al-Turany, A. Rybalchenko
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "TMessage.h"
#include "Rtypes.h"

#include "FairRuntimeDb.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"

#include "ParameterMQServer.h"
#include "FairMQLogger.h"
#include "FairParGenericSet.h"

using namespace std;

ParameterMQServer::ParameterMQServer() :
    fRtdb(FairRuntimeDb::instance()),
    fFirstInputName("first_input.root"),
    fFirstInputType("ROOT"),
    fSecondInputName(""),
    fSecondInputType("ROOT"),
    fOutputName(""),
    fOutputType("ROOT")
{
}

void ParameterMQServer::InitTask()
{
    if (fRtdb != 0)
    {
        // Set first input
        if (fFirstInputType == "ROOT")
        {
            FairParRootFileIo* par1R = new FairParRootFileIo();
            par1R->open(fFirstInputName.data(), "UPDATE");
            fRtdb->setFirstInput(par1R);
        }
        else if (fFirstInputType == "ASCII")
        {
            FairParAsciiFileIo* par1A = new FairParAsciiFileIo();
            par1A->open(fFirstInputName.data(), "in");
            fRtdb->setFirstInput(par1A);
        }

        // Set second input
        if (fSecondInputName != "")
        {
            if (fSecondInputType == "ROOT")
            {
                FairParRootFileIo* par2R = new FairParRootFileIo();
                par2R->open(fSecondInputName.data(), "UPDATE");
                fRtdb->setSecondInput(par2R);
            }
            else if (fSecondInputType == "ASCII")
            {
                FairParAsciiFileIo* par2A = new FairParAsciiFileIo();
                par2A->open(fSecondInputName.data(), "in");
                fRtdb->setSecondInput(par2A);
            }
        }

        // Set output
        if (fOutputName != "")
        {
            if (fOutputType == "ROOT")
            {
                FairParRootFileIo* parOut = new FairParRootFileIo(kTRUE);
                parOut->open(fOutputName.data());
                fRtdb->setOutput(parOut);
            }

            fRtdb->saveOutput();
        }
    }
}

void free_tmessage (void* /*data*/, void *hint)
{
    delete static_cast<TMessage*>(hint);
}

void ParameterMQServer::Run()
{
    string parameterName = "";
    FairParGenericSet* par = nullptr;

    while (CheckCurrentState(RUNNING))
    {
        unique_ptr<FairMQMessage> req(fTransportFactory->CreateMessage());

        if (fChannels.at("data").at(0).Receive(req) > 0)
        {
            string reqStr(static_cast<char*>(req->GetData()), req->GetSize());
            LOG(INFO) << "Received parameter request from client: \"" << reqStr << "\"";

            size_t pos = reqStr.rfind(",");
            string newParameterName = reqStr.substr(0, pos);
            int runId = stoi(reqStr.substr(pos + 1));
            LOG(INFO) << "Parameter name: " << newParameterName;
            LOG(INFO) << "Run ID: " << runId;

            LOG(INFO) << "Retrieving parameter...";
            // Check if the parameter name has changed to avoid getting same container repeatedly
            if (newParameterName != parameterName)
            {
                parameterName = newParameterName;
                par = static_cast<FairParGenericSet*>(fRtdb->getContainer(parameterName.c_str()));
            }
            fRtdb->initContainers(runId);

            LOG(INFO) << "Sending following parameter to the client:";
            if (par)
            {
                par->print();

                TMessage* tmsg = new TMessage(kMESS_OBJECT);
                tmsg->WriteObject(par);

                unique_ptr<FairMQMessage> reply(fTransportFactory->CreateMessage(tmsg->Buffer(), tmsg->BufferSize(), free_tmessage, tmsg));

                fChannels.at("data").at(0).Send(reply);
            }
            else
            {
                LOG(ERROR) << "Parameter uninitialized!";
            }
        }
    }
}

void ParameterMQServer::SetProperty(const int key, const string& value)
{
    switch (key)
    {
        case FirstInputName:
            fFirstInputName = value;
            break;
        case FirstInputType:
            fFirstInputType = value;
            break;
        case SecondInputName:
            fSecondInputName = value;
            break;
        case SecondInputType:
            fSecondInputType = value;
            break;
        case OutputName:
            fOutputName = value;
            break;
        case OutputType:
            fOutputType = value;
            break;
        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}

string ParameterMQServer::GetProperty(const int key, const string& default_ /*= ""*/)
{
    switch (key)
    {
        case FirstInputName:
            return fFirstInputName;
        case FirstInputType:
            return fFirstInputType;
        case SecondInputName:
            return fSecondInputName;
        case SecondInputType:
            return fSecondInputType;
        case OutputName:
            return fOutputName;
        case OutputType:
            return fOutputType;
        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}

void ParameterMQServer::SetProperty(const int key, const int value)
{
    switch (key)
    {
        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}

int ParameterMQServer::GetProperty(const int key, const int default_ /*= 0*/)
{
    switch (key)
    {
        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}


ParameterMQServer::~ParameterMQServer()
{
    if (fRtdb)
    {
        delete fRtdb;
    }
}
