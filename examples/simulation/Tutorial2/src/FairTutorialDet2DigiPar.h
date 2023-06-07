/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairTutorialDetDigiPar header file              -----
// -----                 Created 15/05/08  by F. Uhlig                 -----
// -------------------------------------------------------------------------

#ifndef FAIRTUTORIALDET2DIGIPAR_H
#define FAIRTUTORIALDET2DIGIPAR_H

#include "FairParGenericSet.h"

#include <Rtypes.h>
#include <TArrayF.h>
#include <TArrayI.h>

class FairParamList;

class FairTutorialDet2DigiPar : public FairParGenericSet
{
  public:
    /** Standard constructor **/
    FairTutorialDet2DigiPar(const char* name = "FairTutorialDet2DigiPar",
                            const char* title = "Tutorial Det digi parameters",
                            const char* context = "Default");

    FairTutorialDet2DigiPar(const FairTutorialDet2DigiPar&) = delete;
    FairTutorialDet2DigiPar& operator=(const FairTutorialDet2DigiPar&) = delete;
    /** Destructor **/
    ~FairTutorialDet2DigiPar() override;

    virtual void printparams();

    /** Reset all parameters **/
    void clear() override;

    void putParams(FairParamList*) override;
    Bool_t getParams(FairParamList*) override;

  private:
    TArrayF ftutdetdigipar{10};     //
    TArrayI ftutdetdigiparsector;   //
    Int_t ftutdetdigiparstation;    //

    ClassDefOverride(FairTutorialDet2DigiPar, 1);
};

#endif
