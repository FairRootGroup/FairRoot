/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----             FairPlutoReactionGenerator header file            -----
// -----          Created 05/07/08  by I. Froehlich                    -----
// -------------------------------------------------------------------------
#include "FairPlutoReactionGenerator.h"

#include "FairPrimaryGenerator.h"       // for FairPrimaryGenerator

#include "PFairGenerator.h"             // for PFairGenerator
#include "PReaction.h"                  // for PReaction

#include "Riosfwd.h"                    // for ostream

#include <stddef.h>                     // for NULL
#include <iostream>                     // for operator<<, basic_ostream, etc

// -----   Default constructor   ------------------------------------------
FairPlutoReactionGenerator::FairPlutoReactionGenerator()
  : FairGenerator(),
    iEvent(0),
#ifdef PLUTOVERSION_FOR_FAIR
    fPlutoFairGenerator(NULL),
#endif
    fReaction(NULL)
{
  /*
  iEvent     = 0;
  fReaction  = NULL;
  #ifdef PLUTOVERSION_FOR_FAIR
  fPlutoFairGenerator = NULL;
  #endif
  */
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
FairPlutoReactionGenerator::FairPlutoReactionGenerator(PReaction* reaction)
  : FairGenerator(),
    iEvent(0),
#ifdef PLUTOVERSION_FOR_FAIR
    fPlutoFairGenerator(new PFairGenerator()),
#endif
    fReaction(reaction)
{
  //  iEvent     = 0;
  //  fReaction  = reaction;
#ifdef PLUTOVERSION_FOR_FAIR
  //  fPlutoFairGenerator = new PFairGenerator();
  if (!reaction) {
    std::cout << "-E FairPlutoReactionGenerator: No PReaction!" << std::endl;
  } else {
    reaction->AddBulk(fPlutoFairGenerator);
    reaction->IsInline();
  }
#else
  std::cout << "-E FairPlutoReactionGenerator: You are using the wrong Pluto version" << std::endl;
#endif
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
FairPlutoReactionGenerator::~FairPlutoReactionGenerator()
{
#ifdef PLUTOVERSION_FOR_FAIR
  if (fPlutoFairGenerator) { delete fPlutoFairGenerator; }
#endif
}
// ------------------------------------------------------------------------



// -----   Public method ReadEvent   --------------------------------------
Bool_t FairPlutoReactionGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{
#ifdef PLUTOVERSION_FOR_FAIR

  // Check for input file
  if ( ! fReaction ) {
    cout << "-E FairPlutoReactionGenerator: No PReaction!" << endl;
    return kFALSE;
  }

  fReaction->InitChannels();
  fReaction->DisableWeightReset();
  if (!fReaction->loop(1,0,0)) { return kFALSE; }


  Double_t px, py, pz, vx, vy, vz;
  Int_t    pdgType;

  while (fPlutoFairGenerator->GetNextParticle(&pdgType, &px, &py, &pz, &vx, &vy, &vz)) {

    if (pdgType) {
      primGen->AddTrack(pdgType, px, py, pz, vx, vy, vz);
    }
  }

  return kTRUE;
#else

  return kFALSE;
#endif
}
// ------------------------------------------------------------------------




ClassImp(FairPlutoReactionGenerator)
