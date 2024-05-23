/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* $Id: */

// -------------------------------------------------------------------------
// -----                    FairEventBuilderManager source file               -----
// -----                  Created 23/09/2013 by R. Karabowicz          -----
// -------------------------------------------------------------------------

/** FairEventBuilderManager
 *@author Radoslaw Karabowicz <r.karabowicz@gsi.de>
 *@since 23.09.2013
 *@version 1.0
 **
 ** FairRoot general task for recreating events in Time-Based reconstruction mode.
 ** Various experiments should implement their own version of the Event Builder Manager.
 ** The main member of the task is vector of reconstructed events fRecoEvents.
 ** It also contains a vector of implementations of FairEventBuilders, that are
 ** responsible for feeding fRecoEvents vector via FindEvents() function.
 **
 ** The heart of the experiment-specific implemenations is
 ** the AnalyzeAndExtractEvents() function, which should interpret
 ** the experimental data to reconstruct events.
 **/

#include "FairEventBuilderManager.h"

#include "FairRecoEventHeader.h"
#include "FairRootManager.h"

#include <TMath.h>
#include <iostream>

using std::cout;
using std::endl;

FairEventBuilderManager::FairEventBuilderManager()
    : FairTask("FairEventBuilderManager", 0)
    , fEventBuilders()
    , fPossibleEvents()
{}

FairEventBuilderManager::FairEventBuilderManager(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fEventBuilders()
    , fPossibleEvents()
{}

FairEventBuilderManager::~FairEventBuilderManager() {}

void FairEventBuilderManager::Exec(Option_t*)
{
    if (fVerbose) {
        cout << "FairEventBuilderManager::Exec() begin" << endl;
    }

    Double_t maxEventTimeAllowed = FillEventVectors();

    if (fVerbose) {
        cout << "++ CAN CREATE EVENTS THAT ARE SMALLER THAN " << maxEventTimeAllowed << " ns" << endl;
    }

    // AnalyzeAndExtractEvents function:
    // - works on fEventBuilders[ieb]
    // - should extract possible events
    // - is implemented by different experiments
    AnalyzeAndExtractEvents(maxEventTimeAllowed);
}

Double_t FairEventBuilderManager::FillEventVectors()
{
    // for (std::vector<FairEventBuilder*>::iterator it = fEventBuilders.begin() ; it != fEventBuilders.end() ; ++it) {
    //   *it.FindEvents();
    // }
    Double_t maxEventTimeAllowed = 10.e6;
    for (UInt_t ieb = 0; ieb < fEventBuilders.size(); ieb++) {
        if (fVerbose) {
            cout << "***** " << fEventBuilders[ieb]->GetName() << " *****" << endl;
        }
        if (fVerbose) {
            cout << "  there are " << fPossibleEvents[ieb].size() << " possible events" << endl;
        }
        std::vector<std::pair<double, FairRecoEventHeader*>> tempBuilder = fEventBuilders[ieb]->FindEvents();
        if (fVerbose) {
            cout << "  event buffer " << fEventBuilders[ieb]->GetName() << " found " << tempBuilder.size() << " events"
                 << endl;
        }
        for (UInt_t ipair = 0; ipair < tempBuilder.size(); ipair++) {
            fPossibleEvents[ieb].push_back(tempBuilder[ipair]);
            if (fVerbose)
                cout << "    added event " << fPossibleEvents[ieb][fPossibleEvents[ieb].size() - 1].second << " at "
                     << fPossibleEvents[ieb][fPossibleEvents[ieb].size() - 1].second->GetEventTime() << " ns." << endl;
        }
        if (fVerbose) {
            cout << "  and now " << fPossibleEvents[ieb].size() << " possible events" << endl;
        }

        if (fEventBuilders[ieb]->AllowedTime() < maxEventTimeAllowed) {
            maxEventTimeAllowed = fEventBuilders[ieb]->AllowedTime();
        }
    }
    return maxEventTimeAllowed;
}

void FairEventBuilderManager::CreateAndFillEvent(FairRecoEventHeader* recoEvent)
{
    for (UInt_t ieb = 0; ieb < fEventBuilders.size(); ieb++) {
        fEventBuilders[ieb]->StoreEventData(recoEvent);
        fEventBuilders[ieb]->WriteOutAllDeadTimeData();
    }

    FairRootManager::Instance()->Fill();

    for (UInt_t ieb = 0; ieb < fEventBuilders.size(); ieb++) {
        fEventBuilders[ieb]->DeleteOldData();
    }
}

void FairEventBuilderManager::AddEventBuilder(FairEventBuilder* eventBuilder)
{
    fEventBuilders.push_back(eventBuilder);
    std::vector<std::pair<double, FairRecoEventHeader*>> tcArray;
    fPossibleEvents.push_back(tcArray);
    //  if (fVerbose)
    cout << "*** FairEventBuilderManager. Registered " << eventBuilder->GetName() << endl;
}

InitStatus FairEventBuilderManager::Init()
{
    // Get input array
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        Fatal("Init", "No FairRootManager");
    }

    cout << "*** FairEventBuilderManager. " << fEventBuilders.size() << " event builders registered." << endl;

    for (UInt_t ieb = 0; ieb < fEventBuilders.size(); ieb++) {
        fEventBuilders[ieb]->SetIdentifier(TMath::Power(2, static_cast<Int_t>(ieb)));
        fEventBuilders[ieb]->Init();
    }

    return kSUCCESS;
}

InitStatus FairEventBuilderManager::ReInit() { return kSUCCESS; }

void FairEventBuilderManager::Finish()
{
    AnalyzeAndExtractEvents(-1.);

    cout << "==================== " << fName.Data() << " : Summary ========================" << endl;
    for (UInt_t ieb = 0; ieb < fEventBuilders.size(); ieb++) {
        fEventBuilders[ieb]->Finish();
    }
    cout << "=====================================================================" << endl;
}
