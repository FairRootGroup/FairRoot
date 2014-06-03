/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

#include "TClonesArray.h"
#include "TMath.h"
#include "TRandom2.h"

#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::fixed;
using std::right;
using std::left;
using std::setw;
using std::setprecision;
using std::set;
using std::map;

using std::sort;
using std::iterator;
using std::vector;

// -----   Default constructor   ------------------------------------------
FairEventBuilderManager::FairEventBuilderManager()
  : FairTask("FairEventBuilderManager", 0),
    fEventBuilders  (),
    fPossibleEvents()
{
}
// -------------------------------------------------------------------------

// -----   Constructor with name   -----------------------------------------
FairEventBuilderManager::FairEventBuilderManager(const char* name, Int_t iVerbose)
  : FairTask(name, iVerbose),
    fEventBuilders  (),
    fPossibleEvents()
{
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairEventBuilderManager::~FairEventBuilderManager()
{
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void FairEventBuilderManager::Exec(Option_t* opt)
{
  if ( fVerbose ) {
    cout << "FairEventBuilderManager::Exec() begin" << endl;
  }

  Double_t maxEventTimeAllowed = FillEventVectors();

  if ( fVerbose ) {
    cout << "++ CAN CREATE EVENTS THAT ARE SMALLER THAN " << maxEventTimeAllowed << " ns" << endl;
  }

  // AnalyzeAndExtractEvents function:
  // - works on fEventBuilders[ieb]
  // - should extract possible events
  // - is implemented by different experiments
  AnalyzeAndExtractEvents(maxEventTimeAllowed);

  return;
}
// -------------------------------------------------------------------------

// -----   Private method FillEventVectors   -------------------------------
Double_t FairEventBuilderManager::FillEventVectors()
{
  // for ( std::vector<FairEventBuilder*>::iterator it = fEventBuilders.begin() ; it != fEventBuilders.end() ; ++it ) {
  //   *it.FindEvents();
  // }
  Double_t maxEventTimeAllowed = 10.e6;
  for ( Int_t ieb = 0 ; ieb < fEventBuilders.size() ; ieb++ ) {
    if ( fVerbose ) { cout << "***** " << fEventBuilders[ieb]->GetName() << " *****" << endl; }
    if ( fVerbose ) { cout << "  there are " << fPossibleEvents[ieb].size() << " possible events" << endl; }
    std::vector<std::pair<double,FairRecoEventHeader*> > tempBuilder = fEventBuilders[ieb]->FindEvents();
    if ( fVerbose ) {
      cout << "  event buffer " << fEventBuilders[ieb]->GetName() << " found " << tempBuilder.size() << " events" << endl;
    }
    std::pair<double,FairRecoEventHeader*> tempPair;
    for ( Int_t ipair = 0 ; ipair < tempBuilder.size() ; ipair++ ) {
      fPossibleEvents[ieb].push_back(tempBuilder[ipair]);
      if ( fVerbose )
        cout << "    added event " << fPossibleEvents[ieb][fPossibleEvents[ieb].size()-1].second
             << " at " << fPossibleEvents[ieb][fPossibleEvents[ieb].size()-1].second->GetEventTime() << " ns." << endl;
    }
    if ( fVerbose ) {
      cout << "  and now " << fPossibleEvents[ieb].size() << " possible events" << endl;
    }

    if ( fEventBuilders[ieb]->AllowedTime() < maxEventTimeAllowed ) {
      maxEventTimeAllowed = fEventBuilders[ieb]->AllowedTime();
    }
  }
  return maxEventTimeAllowed;
}
// -------------------------------------------------------------------------

// -----   Public method CreateAndFillEvents   -----------------------------
void FairEventBuilderManager::CreateAndFillEvent(FairRecoEventHeader* recoEvent)
{

  for ( Int_t ieb = 0 ; ieb < fEventBuilders.size() ; ieb++ ) {
    fEventBuilders[ieb]->StoreEventData(recoEvent);
    fEventBuilders[ieb]->WriteOutAllDeadTimeData();
  }

  FairRootManager::Instance()->Fill();

  for ( Int_t ieb = 0 ; ieb < fEventBuilders.size() ; ieb++ ) {
    fEventBuilders[ieb]->DeleteOldData();
  }
}
// -------------------------------------------------------------------------


// -----   Public method AddEventBuilder   ----------------------------------
void FairEventBuilderManager::AddEventBuilder(FairEventBuilder* eventBuilder)
{
  fEventBuilders  .push_back(eventBuilder);
  std::vector<std::pair<double,FairRecoEventHeader*> > tcArray;
  fPossibleEvents.push_back(tcArray);
  //  if ( fVerbose )
  cout << "*** FairEventBuilderManager. Registered " << eventBuilder->GetName() << endl;
}
// -------------------------------------------------------------------------

// -----   Private method SetParContainers   -------------------------------
void FairEventBuilderManager::SetParContainers()
{

  // Get run and runtime database
  FairRunAna* run = FairRunAna::Instance();
  if ( ! run ) { Fatal("SetParContainers", "No analysis run"); }

  FairRuntimeDb* db = run->GetRuntimeDb();
  if ( ! db ) { Fatal("SetParContainers", "No runtime database"); }
}
// -------------------------------------------------------------------------

// -----   Private method Init   -------------------------------------------
InitStatus FairEventBuilderManager::Init()
{
  // Get input array
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) { Fatal("Init", "No FairRootManager"); }

  cout << "*** FairEventBuilderManager. " << fEventBuilders.size() << " event builders registered." << endl;

  for ( Int_t ieb = 0 ; ieb < fEventBuilders.size() ; ieb++ ) {
    fEventBuilders[ieb]->SetIdentifier(TMath::Power(2,ieb));
    fEventBuilders[ieb]->Init();
  }

  return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Private method ReInit   -------------------------------------------
InitStatus FairEventBuilderManager::ReInit()
{

  return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Private method ReInit   -------------------------------------------
void FairEventBuilderManager::Finish()
{
  AnalyzeAndExtractEvents(-1.);

  cout << "==================== " << fName.Data() << " : Summary ========================" << endl;
  for ( Int_t ieb = 0 ; ieb < fEventBuilders.size() ; ieb++ ) {
    fEventBuilders[ieb]->Finish();
  }
  cout << "=====================================================================" << endl;
}
// -------------------------------------------------------------------------






ClassImp(FairEventBuilderManager)

