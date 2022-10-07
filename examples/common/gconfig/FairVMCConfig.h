/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairVMCConfig header file                       -----
// -----            Created 2019.02.19 by R. Karabowicz                -----
// -------------------------------------------------------------------------

#ifndef FAIRROOT_SIM_CONFIG_H
#define FAIRROOT_SIM_CONFIG_H

#include "FairXmlVMCConfig.h"

class FairVMCConfig : public FairXmlVMCConfig
{
  public:
    FairVMCConfig();
    virtual ~FairVMCConfig();

  private:
    virtual void SetupStack();
};

#endif
