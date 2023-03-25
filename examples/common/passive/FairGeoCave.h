/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOCAVE_H
#define FAIRGEOCAVE_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>    // for FairGeoCave::Class, Bool_t, etc
#include <TString.h>   // for TString
#include <iosfwd>      // for fstream

class FairGeoCave : public FairGeoSet
{
  protected:
    TString name;

  public:
    FairGeoCave();
    ~FairGeoCave() override = default;
    const char* getModuleName(Int_t) override { return name.Data(); }
    Bool_t read(std::fstream&, FairGeoMedia*) override;
    void addRefNodes() override;
    void write(std::fstream&) override;
    void print() override;

    ClassDefOverride(FairGeoCave, 0);   // Class for the geometry of CAVE
};

#endif /* !FAIRGEOCAVE_H */
