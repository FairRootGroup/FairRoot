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

#include <yaml-cpp/yaml.h>

class TString;

class FairYamlVMCConfig : public FairGenericVMCConfig
{
  public:
    FairYamlVMCConfig();
    virtual ~FairYamlVMCConfig();

    virtual void Setup(const char* mcEngine);

 private:
    TString ObtainYamlFileName(const char* mcEngine);
    void    StoreYamlInfo();
    
 protected:
    void SetupGeant3();
    void SetupGeant4();
    virtual void SetupStack() = 0;
    void SetCuts();

    YAML::Node fYamlConfig;
};

#endif


