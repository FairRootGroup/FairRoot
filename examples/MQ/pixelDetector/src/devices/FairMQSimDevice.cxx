/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSimDevice.cxx
 *
 * @since 2017.10.24
 * @author R. Karabowicz
 */

#include "FairMQSimDevice.h"

#include "FairModule.h"
#include "FairParSet.h"
#include "FairPrimaryGenerator.h"
#include "FairRunSim.h"
#include "FairRuntimeDb.h"

#include <FairMQDevice.h>
#include <TCollection.h>
#include <TList.h>
#include <TObjArray.h>
#include <cstdio>   // printf
#include <fairlogger/Logger.h>

using namespace std;

FairMQSimDevice::FairMQSimDevice()
    : FairMQRunDevice()
    , fSimDeviceId(0)
    , fUpdateChannelName("updateChannel")
    , fRunSim(nullptr)
    , fNofEvents(1)
    , fTransportName("TGeant3")
    , fMaterialsFile("")
    , fMagneticField(nullptr)
    , fDetectorArray(nullptr)
    , fPrimaryGenerator(nullptr)
    , fStoreTrajFlag(false)
    , fTaskArray(nullptr)
    , fFirstParameter(nullptr)
    , fSecondParameter(nullptr)
    , fSink(nullptr)
{}

void FairMQSimDevice::InitTask()
{
    fRunSim = new FairRunSim();

    fRunSim->SetSink(fSink);

    if (fFirstParameter || fSecondParameter) {
        FairRuntimeDb* rtdb = fRunSim->GetRuntimeDb();
        if (fFirstParameter)
            rtdb->setFirstInput(fFirstParameter);
        if (fSecondParameter)
            rtdb->setSecondInput(fSecondParameter);
    }

    fRunSim->SetName(fTransportName.data());
    //  fRunSim->SetSimulationConfig(new FairVMCConfig());
    fRunSim->SetIsMT(kFALSE);

    if (fUserConfig.Length() > 0)
        fRunSim->SetUserConfig(fUserConfig);
    if (fUserCuts.Length() > 0)
        fRunSim->SetUserCuts(fUserCuts);

    // -----   Create media   -------------------------------------------------
    fRunSim->SetMaterials(fMaterialsFile.data());

    // -----   Magnetic field   -------------------------------------------
    if (fMagneticField)
        fRunSim->SetField(fMagneticField);

    // -----   Create geometry   ----------------------------------------------
    for (int idet = 0; idet < fDetectorArray->GetEntries(); idet++) {
        fRunSim->AddModule((FairModule*)(fDetectorArray->At(idet)));
    }

    // -----   Negotiate the run number   -------------------------------------
    // -----      via the fUpdateChannelName   --------------------------------
    // -----      ask the fParamMQServer   ------------------------------------
    // -----      receive the run number and sampler id   ---------------------
    std::string* askForRunNumber = new string("ReportSimDevice");
    FairMQMessagePtr req(NewMessage(
        const_cast<char*>(askForRunNumber->c_str()),
        askForRunNumber->length(),
        [](void* /*data*/, void* object) { delete static_cast<string*>(object); },
        askForRunNumber));
    FairMQMessagePtr rep(NewMessage());

    unsigned int runId = 0;
    if (Send(req, fUpdateChannelName) > 0) {
        if (Receive(rep, fUpdateChannelName) > 0) {
            std::string repString = string(static_cast<char*>(rep->GetData()), rep->GetSize());
            LOG(info) << " -> " << repString.data();
            runId = stoi(repString);
            repString = repString.substr(repString.find_first_of('_') + 1, repString.length());
            fSimDeviceId = stoi(repString);
            LOG(info) << "runId = " << runId << "  ///  fSimDeviceId = " << fSimDeviceId;
        }
    }

    if (fPrimaryGenerator) {
        fPrimaryGenerator->SetEventNr(fSimDeviceId
                                      * fNofEvents);   // run n simulations with same run id - offset the event number
        fRunSim->SetGenerator(fPrimaryGenerator);
    }

    fRunSim->SetStoreTraj(fStoreTrajFlag);

    // -----   Set tasks   ----------------------------------------------------
    if (fTaskArray) {
        for (int itask = 0; itask < fTaskArray->GetEntries(); itask++) {
            fRunSim->AddTask((FairTask*)(fTaskArray->At(itask)));
        }
    }

    // -----   Initialize simulation run   ------------------------------------
    fRunSim->SetRunId(runId);   // run n simulations with same run id - offset the event number
    fRunSim->Init();
}

bool FairMQSimDevice::ConditionalRun()
{
    if (fSimDeviceId == 0)
        UpdateParameterServer();
    fRunSim->Run(fNofEvents);
    return false;
}

void FairMQSimDevice::UpdateParameterServer()
{
    FairRuntimeDb* rtdb = fRunSim->GetRuntimeDb();

    printf("FairMQSimDevice::UpdateParameterServer() (%d containers)\n", rtdb->getListOfContainers()->GetEntries());

    // send the parameters to be saved
    TIter next(rtdb->getListOfContainers());
    FairParSet* cont;
    while ((cont = static_cast<FairParSet*>(next()))) {
        std::string ridString = std::string("RUNID") + std::to_string(fRunSim->GetRunId()) + std::string("RUNID")
                                + std::string(cont->getDescription());
        cont->setDescription(ridString.data());
        FairMQRunDevice::SendObject(cont, fUpdateChannelName);
    }

    printf("FairMQSimDevice::UpdateParameterServer() finished\n");
}

void FairMQSimDevice::SendBranches()
{
    if (NewStatePending()) {
        fRunSim->StopMCRun();
    }
    FairMQRunDevice::SendBranches();
}
