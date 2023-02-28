/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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

#include <G4String.hh>   // for G4String
#include <G4Types.hh>    // for G4bool
#include <G4VFastSimulationModel.hh>

class FairFastSimModel : public G4VFastSimulationModel
{
  public:
    //-------------------------
    // Constructor, destructor
    //-------------------------
    FairFastSimModel(G4String, G4Region*);
    FairFastSimModel(G4String);
    ~FairFastSimModel() override;

    G4bool IsApplicable([[gnu::unused]] const G4ParticleDefinition&) override;
    G4bool ModelTrigger([[gnu::unused]] const G4FastTrack&) override;
    void DoIt(const G4FastTrack&, G4FastStep&) override;
};

#endif /* FAIR_FASTSIM_MODEL_H_ */
