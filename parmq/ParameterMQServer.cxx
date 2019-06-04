/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * ParameterMQServer.cxx
 *
 * @since 2015-10-26
 * @author M. Al-Turany, A. Rybalchenko
 */

#include "TGeoManager.h"
#include "RootSerializer.h"
#include "TClass.h"
#include "Rtypes.h"

#include "FairRuntimeDb.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include "FairParGenericSet.h"
#include "FairRunIdGenerator.h"

#include "ParameterMQServer.h"
#include "FairMQLogger.h"

using namespace std;

ParameterMQServer::ParameterMQServer() :
    fRtdb(FairRuntimeDb::instance()),
    fRunId(0),
    fNofSimDevices(0),
    fFirstInputName("first_input.root"),
    fFirstInputType("ROOT"),
    fSecondInputName(""),
    fSecondInputType("ROOT"),
    fOutputName(""),
    fOutputType("ROOT"),
    fRequestChannelName("data"),
    fUpdateChannelName("")
{
}

void ParameterMQServer::Init()
{
    fRequestChannelName = fConfig->GetValue<string>("channel-name");
    fUpdateChannelName = fConfig->GetValue<string>("update-channel-name");

    if (fRequestChannelName != "")
    {
        OnData(fRequestChannelName, &ParameterMQServer::ProcessRequest);
    }
    if (fUpdateChannelName != "")
    {
        OnData(fUpdateChannelName, &ParameterMQServer::ProcessUpdate);
    }
}

void ParameterMQServer::InitTask()
{
    fFirstInputName = fConfig->GetValue<string>("first-input-name");
    fFirstInputType = fConfig->GetValue<string>("first-input-type");
    fSecondInputName = fConfig->GetValue<string>("second-input-name");
    fSecondInputType = fConfig->GetValue<string>("second-input-type");
    fOutputName = fConfig->GetValue<string>("output-name");
    fOutputType = fConfig->GetValue<string>("output-type");

    if (::getenv("DDS_SESSION_ID"))
    {
        std::string ddsSessionId = ::getenv("DDS_SESSION_ID");
        if (fOutputName.length() > 5)
        {
            ddsSessionId = "." + ddsSessionId + ".root";
            fOutputName.replace(fOutputName.length() - 5, 5, ddsSessionId.c_str());
        }
    }

    if (fRtdb != 0)
    {
        // Set first input
        if (fFirstInputName != "")
        {
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
        if (fUpdateChannelName == "")
        {
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
}

bool ParameterMQServer::ProcessRequest(FairMQMessagePtr& req, int /*index*/)
{
    string parameterName = "";
    FairParGenericSet* par = nullptr;

    string reqStr(static_cast<char*>(req->GetData()), req->GetSize());
    LOG(info) << "Received parameter request from client: \"" << reqStr << "\"";

    size_t pos = reqStr.rfind(",");
    string newParameterName = reqStr.substr(0, pos);
    int runId = stoi(reqStr.substr(pos + 1));
    LOG(info) << "Parameter name: " << newParameterName;
    LOG(info) << "Run ID: " << runId;

    LOG(info) << "Retrieving parameter...";
    // Check if the parameter name has changed to avoid getting same container repeatedly
    if (newParameterName != parameterName)
    {
        parameterName = newParameterName;
        par = static_cast<FairParGenericSet*>(fRtdb->getContainer(parameterName.c_str()));
    }
    fRtdb->initContainers(runId);

    LOG(info) << "Sending following parameter to the client:";
    if (par)
    {
        par->print();

        FairMQMessagePtr rep(NewMessage());
        Serialize<RootSerializer>(*rep, par);

        if (Send(rep, fRequestChannelName, 0) < 0)
        {
            LOG(ERROR) << "failed sending reply";
            return false;
        }
    }
    else
    {
        LOG(ERROR) << "Parameter uninitialized! Sending empty message back";
        // Send an empty message back to keep the REQ/REP cycle
        FairMQMessagePtr rep(NewMessage());
        if (Send(rep, fRequestChannelName, 0) < 0)
        {
            LOG(ERROR) << "failed sending reply";
            return false;
        }
    }

    return true;
}

bool ParameterMQServer::ProcessUpdate(FairMQMessagePtr& update, int /*index*/)
{
    gGeoManager = nullptr; // FairGeoParSet update deletes previous geometry because of resetting gGeoManager, so let's NULL it

    std::string* text;

    LOG(info) << "got process update message with size = " << update->GetSize() << " !";
    if (update->GetSize() < 20)
    {
        std::string repString = string(static_cast<char*>(update->GetData()), update->GetSize());
        LOG(info) << "Received string " << repString << " !";
        if (fNofSimDevices == 0)
        {
            FairRunIdGenerator genid;
            fRunId = genid.generateId();
        }
        string messageToSend = to_string(fRunId) + "_" + to_string(fNofSimDevices);
        text = new string(messageToSend);
        fNofSimDevices += 1;
        LOG(info) << "Replying with \"" << messageToSend << "\"";
    }
    else
    {
        // get the run id coded in the description of FairParSet
        FairParGenericSet* newPar = nullptr;
        Deserialize<RootSerializer>(*update, newPar);
        std::string parDescr = std::string(newPar->getDescription());
        uint runId = 0;
        if (parDescr.find("RUNID") != std::string::npos)
        {
            parDescr.erase(0, parDescr.find("RUNID") + 5);
            runId = atoi(parDescr.data());
            if (parDescr.find("RUNID") != std::string::npos)
            {
                parDescr.erase(0, parDescr.find("RUNID") + 5);
            }
        }
        fRtdb->initContainers(runId);

        newPar->setChanged(true); // trigger writing to file
        newPar->setStatic(true); // to get rid of error
        newPar->Print();

        if (fRtdb->addContainer(newPar))
        {
            text = new string("SUCCESS");
        }
        else
        {
            text = new string("FAIL");
        }

        Bool_t kParameterMerged = kTRUE;
        FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
        parOut->open(fOutputName.data());
        fRtdb->setOutput(parOut);
        fRtdb->saveOutput();
        fRtdb->closeOutput();
    }

    FairMQMessagePtr msg(NewMessage(const_cast<char*>(text->c_str()),
                                    text->length(),
                                    [](void* /*data*/, void* object) { delete static_cast<string*>(object); },
                                    text));

    if (Send(msg, fUpdateChannelName) < 0)
    {
        return false;
    }
    return true;
}

ParameterMQServer::~ParameterMQServer()
{
    delete fRtdb;
}
