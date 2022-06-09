/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairYamlVMCConfig header file                   -----
// -----            Created 2019.02.19 by R. Karabowicz                -----
// -------------------------------------------------------------------------

#ifndef FAIR_YAML_VMC_CONFIG_H
#define FAIR_YAML_VMC_CONFIG_H

#include "FairGenericVMCConfig.h"

// in case system yaml-cpp was compiled with an older boost version where boost::next was defined
// in utility.hpp:
#include <boost/next_prior.hpp>

#include <string>
#include <yaml-cpp/yaml.h>

using namespace std;

class FairYamlVMCConfig : public FairGenericVMCConfig
{
  public:
    FairYamlVMCConfig();
    virtual ~FairYamlVMCConfig() {}

    virtual void Setup(const char* mcEngine);
    virtual void SetupPostInit(const char* mcEngine);

    virtual void UsePostInitConfig(bool useC = true, const char* stringC = "g4ConfigPostInit.yaml") {
        fPostInitFlag = useC;
        fPostInitName = stringC;
    }


  private:
    string ObtainYamlFileName(const char* mcEngine);
    void StoreYamlInfo();

    string fMCEngine;

  protected:
    void SetupGeant3();
    void SetupGeant4();
    virtual void SetupStack() = 0;
    void SetCuts();

    YAML::Node fYamlConfig;
    YAML::Node fYamlConfigPostInit;
};

#endif
