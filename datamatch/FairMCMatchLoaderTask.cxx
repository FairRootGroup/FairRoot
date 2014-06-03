/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairMCMatchLoaderTask source file             -----
// -----                  Created 18/07/08  by T.Stockmanns        -----
// -------------------------------------------------------------------------
#include "FairMCMatchLoaderTask.h"

#include "FairMCMatch.h"                // for FairMCMatch
#include "FairRootManager.h"            // for FairRootManager

#include "Riosfwd.h"                    // for ostream
#include "TClonesArray.h"               // for TClonesArray

#include <stddef.h>                     // for NULL
#include <iostream>                     // for operator<<, basic_ostream, etc

// -----   Default constructor   -------------------------------------------
FairMCMatchLoaderTask::FairMCMatchLoaderTask()
  : FairTask("Creates FairMCMatch"),
    fMCLink(NULL),
    fEventNr(0),
    fMCMatch(NULL)
{
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
FairMCMatchLoaderTask::~FairMCMatchLoaderTask()
{
}

// -----   Public method Init   --------------------------------------------
InitStatus FairMCMatchLoaderTask::Init()
{
  fMCMatch = new FairMCMatch("FairMCMatch", "FairMCMatch");

  InitDataStages();

  /*
  fMCMatch->InitStage("MVDPoint");
  fMCMatch->InitStage("MVDStripDigis");
  fMCMatch->InitStage("MVDPixelDigis");
  fMCMatch->InitStage("MVDHitsPixel");
  fMCMatch->InitStage("MVDHitsStrip");
  fMCMatch->InitStage("MVDPixelClusterCand");
  fMCMatch->InitStage("MVDStripClusterCand");

  fMCMatch->InitStage("EmcCluster");
  fMCMatch->InitStage("EmcBump");
  fMCMatch->InitStage("EmcDigi");
  fMCMatch->InitStage("EmcHit");
  fMCMatch->InitStage("EmcPoint");
  fMCMatch->InitStage("EmcRecoHit");
  fMCMatch->InitStage("EmcSharedDigi");
  fMCMatch->InitStage("EmcWaveform");

  fMCMatch->InitStage("STTPoint");
  fMCMatch->InitStage("STTHit");
  fMCMatch->InitStage("SttHelixHit");
  fMCMatch->InitStage("STTTrack");
  fMCMatch->InitStage("STTTrackCand");

  fMCMatch->InitStage("PndTpcPoint");
  fMCMatch->InitStage("PndTpcPrimaryCluster");
  fMCMatch->InitStage("PndTpcDriftedElectron");
  fMCMatch->InitStage("PndTpcAvalanche");
  fMCMatch->InitStage("PndTpcSignal");
  fMCMatch->InitStage("PndTpcDigi");
  fMCMatch->InitStage("PndTpcCluster");


  fMCMatch->InitStage("GEMPoint");
  fMCMatch->InitStage("GEMDigi");
  fMCMatch->InitStage("GEMHit");

  fMCMatch->InitStage("PndDchPoint");
  fMCMatch->InitStage("PndDchDigi");
  fMCMatch->InitStage("PndDchCylinderHit");

  fMCMatch->InitStage("MdtPoint");
  fMCMatch->InitStage("MdtHit");
  fMCMatch->InitStage("MdtTrk");

  fMCMatch->InitStage("LheHit");
  fMCMatch->InitStage("LheCandidate");
  fMCMatch->InitStage("LheTrack");
  fMCMatch->InitStage("MVDIdealTrackCand");
  fMCMatch->InitStage("MVDRiemannTrackCand");
  //fMCMatch->InitStage("PndTrack");
  fMCMatch->InitStage("LheGenTrack");
  fMCMatch->InitStage("PidChargedCand");
  fMCMatch->InitStage("PidNeutralCand");
  */

  FairRootManager* ioman = FairRootManager::Instance();
  if (!ioman) {
    std::cout << "-E- FairMCMatchLoaderTask::Init: "
              << "RootManager not instantiated!" << std::endl;
    return kFATAL;
  }

  fMCLink = (TClonesArray*)ioman->GetObject("MCLink");
  ioman->Register("MCMatch", "MCInfo", fMCMatch, kFALSE);

  return kSUCCESS;
}


// -------------------------------------------------------------------------
void FairMCMatchLoaderTask::SetParContainers()
{
}


// -----   Public method Exec   --------------------------------------------
void FairMCMatchLoaderTask::Exec(Option_t* opt)
{

  if (!fMCLink) { Fatal("Exec", "No fMCLink"); }
  fMCMatch->ClearMCList();

  fMCMatch->LoadInMCLists(fMCLink);
  fMCMatch->CreateArtificialStage("MCTrack");

  fMCMatch->Print();
  std::cout << std::endl;
}

void FairMCMatchLoaderTask::Finish()
{
}


ClassImp(FairMCMatchLoaderTask);
