/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    MyCave  file                               -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------
#include "MyCave.h"

#include "FairGeoInterface.h"   // for FairGeoInterface
#include "FairGeoLoader.h"      // for FairGeoLoader
#include "FairGeoNode.h"        // for FairGeoNode
#include "FairGeoVolume.h"      // for FairGeoVolume
#include "FairRun.h"            // for FairRun
#include "FairRuntimeDb.h"      // for FairRuntimeDb
#include "MyGeoCave.h"          // for MyGeoCave

#include <TList.h>       // for TListIter, TList (ptr only)
#include <TObjArray.h>   // for TObjArray
#include <TString.h>     // for TString
#include <stddef.h>      // for NULL

void MyCave::ConstructGeometry()
{
    FairGeoLoader& loader = GetGeometryLoader();
    FairGeoInterface* GeoInterface = loader.getGeoInterface();
    MyGeoCave* MGeo = new MyGeoCave();
    MGeo->setGeomFile(GetGeometryFileName());
    GeoInterface->addGeoModule(MGeo);
    Bool_t rc = GeoInterface->readSet(MGeo);
    if (rc) {
        MGeo->create(loader.getGeoBuilder());
    }
}
MyCave::MyCave()
    : FairModule()
{}

MyCave::~MyCave() {}
MyCave::MyCave(const char* name, const char* Title)
    : FairModule(name, Title)
{
    world[0] = 0;
    world[1] = 0;
    world[2] = 0;
}

MyCave::MyCave(const MyCave& right)
    : FairModule(right)
{
    world[0] = right.world[0];
    world[1] = right.world[1];
    world[2] = right.world[2];
}

FairModule* MyCave::CloneModule() const { return new MyCave(*this); }
