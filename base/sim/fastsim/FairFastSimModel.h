/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairFastSimModel header file                    -----
// -----            Created 2019/01/30  by R. Karabowicz               -----
// -------------------------------------------------------------------------
#ifndef FAIR_FASTSIM_MODEL_H_
#define FAIR_FASTSIM_MODEL_H_

#include "G4VFastSimulationModel.hh"

class G4VPhysicalVolume;

class FairFastSimModel : public G4VFastSimulationModel
{
public:
  //-------------------------
  // Constructor, destructor
  //-------------------------
    FairFastSimModel (G4String, G4Region*);
    FairFastSimModel (G4String);
    ~FairFastSimModel ();
    
    virtual G4bool IsApplicable(const G4ParticleDefinition&);
    virtual G4bool ModelTrigger(const G4FastTrack &);
    virtual void DoIt(const G4FastTrack&, G4FastStep&);
};


#endif /* FAIR_FASTSIM_MODEL_H_ */
