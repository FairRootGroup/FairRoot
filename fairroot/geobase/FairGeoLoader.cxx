/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/***************************************************************************
                          FairGeoLoader.cxx  -  description
                             -------------------
    begin                : Thu Jun 17 2004
    copyright            : (C) 2004 by ilse koenig , M. Al-turany
    email                : m.al-turany@gsi.de
 ***************************************************************************/
#include "FairGeoLoader.h"

#include "FairGeoInterface.h"     // for FairGeoInterface
#include "FairGeoRootBuilder.h"   // for FairGeoRootBuilder

#include <TGeoManager.h>   // for TGeoManager
#include <cstdlib>         // for NULL, exit
#include <iostream>        // for cout, endl, operator<<, etc
#include <string.h>        // for strncmp

using std::cout;
using std::endl;

FairGeoLoader* FairGeoLoader::fgInstance = nullptr;

FairGeoLoader* FairGeoLoader::Instance() { return fgInstance; }

static std::unique_ptr<FairGeoBuilder> MakeGeoBuilder(const char* Name)
{
    if (strncmp(Name, "TGeo", 4) == 0) {
        auto geom = std::make_unique<TGeoManager>("FAIRGeom", "FAIR geometry");
        return std::make_unique<FairGeoRootBuilder>("TGeo builder", "geometry builder", std::move(geom));
    }

    if (strncmp(Name, "G3Native", 8) == 0) {
        cout << "-I- FairGeoLoader() : Native G3 Geometry is used: This option is not supported any more!" << endl;
        exit(0);
        //        gGeoManager = NULL;
        //        fGeoBuilder=new FairGeoG3Builder("G3 builder","geometry builder");
    }

    return {};
}

FairGeoLoader::FairGeoLoader()
    : TNamed()
{
    fgInstance = this;
}

FairGeoLoader::FairGeoLoader(const char* Name, const char* title)
    : TNamed(Name, title)
    , fGeoBuilder(MakeGeoBuilder(Name))
{
    if (fgInstance) {
        Fatal("FairGeoLoader", "Singleton instance already exists.");
        return;
    }
    fgInstance = this;

    fInterface.setGeomBuilder(fGeoBuilder.get());
}

FairGeoLoader::~FairGeoLoader()
{
    if (fgInstance == this) {
        // Do not point to a destructed object!
        fgInstance = nullptr;
    }
}
