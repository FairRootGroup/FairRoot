/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairFastSimRunConfiguration header file         -----
// -----            Created 2019/01/30  by R. Karabowicz               -----
// -------------------------------------------------------------------------
#ifndef FAIR_FASTSIM_RUN_CONFIGURATION_H
#define FAIR_FASTSIM_RUN_CONFIGURATION_H
#include <TG4RunConfiguration.h>
#include <TString.h>   // for TString
class TG4VUserFastSimulation;

class FairFastSimRunConfiguration : public TG4RunConfiguration
{
  public:
    FairFastSimRunConfiguration(const TString& geometry,
                                const TString& physicsList = "FTFP_BERT",
                                const TString& specialProcess = "stepLimiter",
                                const bool specialStacking = false,
                                const bool isMT = false);
    virtual ~FairFastSimRunConfiguration();

    // methods
    virtual TG4VUserFastSimulation* CreateUserFastSimulation();

    void UseFastSim(bool flag = true) { fUseFastSim = flag; }

  private:
    bool fUseFastSim;
};

#endif   // FAIR_FASTSIM_RUN_CONFIGURATION_H
