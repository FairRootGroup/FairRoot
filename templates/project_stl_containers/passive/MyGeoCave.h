/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    MyGeoCave  file                               -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------

#ifndef MYGEOCAVE_H
#define MYGEOCAVE_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>    // for MyGeoCave::Class, Bool_t, etc
#include <TString.h>   // for TString
#include <fstream>     // for fstream
#include <iosfwd>      // for fstream

class MyGeoCave : public FairGeoSet
{
  protected:
    TString name;

  public:
    MyGeoCave();
    ~MyGeoCave() override = default;
    const char* getModuleName(Int_t) override { return name.Data(); }
    Bool_t read(std::fstream&, FairGeoMedia*) override;
    void addRefNodes() override;
    void write(std::fstream&) override;
    void print() override;
    ClassDefOverride(MyGeoCave, 0);   // Class for the geometry of CAVE
};

#endif /* !MYGEOCAVE_H */
