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

#include "TMessage.h"
#include "Rtypes.h"

#include "FairRuntimeDb.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include "FairParGenericSet.h"

#include "ParameterMQServer.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"

using namespace std;

ParameterMQServer::ParameterMQServer() :
    fRtdb(FairRuntimeDb::instance()),
    fFirstInputName("first_input.root"),
    fFirstInputType("ROOT"),
    fSecondInputName(""),
    fSecondInputType("ROOT"),
    fOutputName(""),
    fOutputType("ROOT"),
    fChannelName("data")
{
}

void ParameterMQServer::InitTask()
{
    fFirstInputName = fConfig->GetValue<string>("first-input-name");
    fFirstInputType = fConfig->GetValue<string>("first-input-type");
    fSecondInputName = fConfig->GetValue<string>("second-input-name");
    fSecondInputType = fConfig->GetValue<string>("second-input-type");
    fOutputName = fConfig->GetValue<string>("output-name");
    fOutputType = fConfig->GetValue<string>("output-type");
    fChannelName = fConfig->GetValue<string>("channel-name");

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

void ParameterMQServer::Run()
{
    string parameterName = "";
    FairParGenericSet* par = nullptr;

    while (CheckCurrentState(RUNNING))
    {
        FairMQMessagePtr req(NewMessage());

        if (Receive(req, fChannelName, 0) > 0)
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

                FairMQMessagePtr rep(NewMessage(tmsg->Buffer(),
                                                tmsg->BufferSize(),
                                                [](void* /*data*/, void* object){ delete static_cast<TMessage*>(object); },
                                                tmsg));

                if (Send(rep, fChannelName, 0) < 0)
                {
                    LOG(ERROR) << "failed sending reply";
                    break;
                }
            }
            else
            {
                LOG(ERROR) << "Parameter uninitialized!";
                // Send an empty message back to keep the REQ/REP cycle
                FairMQMessagePtr rep(NewMessage());
                if (Send(rep, fChannelName, 0) < 0)
                {
                    LOG(ERROR) << "failed sending reply";
                    break;
                }
            }
        }
    }
}

ParameterMQServer::~ParameterMQServer()
{
    delete fRtdb;
}
