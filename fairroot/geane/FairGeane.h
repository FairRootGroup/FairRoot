/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Class for the GEANE initialization
//
// Author: M. Al-Turany
//
#ifndef FAIRGeane_H
#define FAIRGeane_H

#include "FairTask.h"   // for FairTask, InitStatus

#include <Rtypes.h>    // for FairGeane::Class, ClassDef, etc
#include <TString.h>   // for TString

class FairGeaneApplication;
class FairField;

class FairGeane : public FairTask
{
  public:
    /** Default constructor **/
    // FairGeane();

    FairGeane(const char* name, TString UserConfig = "", TString UserCuts = "");

    FairGeane(TString fUserConfig = "", TString fUserCuts = "");

    InitStatus Init();

    void SetParTask();

    virtual ~FairGeane();

    void SetField(FairField* field);

    ClassDef(FairGeane, 1);

  protected:
    FairGeaneApplication* fApp;   //!
    const char* fName;            //!
    TString fUserConfig;          //!
    TString fUserCuts;            //!

  private:
    FairGeane(const FairGeane&);
    FairGeane& operator=(const FairGeane&);
};

#endif
