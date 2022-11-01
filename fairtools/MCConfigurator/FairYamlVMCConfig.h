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

#include <string>

// prevent yaml-cpp/node/detail/iterator.h:48:54:
//  error: no member named 'next' in namespace 'boost'
#include <boost/next_prior.hpp>

#include <yaml-cpp/yaml.h>

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
    std::string ObtainYamlFileName(const char* mcEngine);
    void StoreYamlInfo();

    std::string fMCEngine;

  protected:
    void SetupGeant3();
    void SetupGeant4();
    virtual void SetupStack() = 0;
    void SetCuts();

    YAML::Node fYamlConfig;
    YAML::Node fYamlConfigPostInit;

    static constexpr bool fUseFastSimDefault = false;
};

#endif
