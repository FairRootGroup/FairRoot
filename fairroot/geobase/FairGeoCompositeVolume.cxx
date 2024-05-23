/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Modified : 20/04/99

/////////////////////////////////////////////////////////////
// FairGeoCompositeVolume
//
//
/////////////////////////////////////////////////////////////
#include "FairGeoCompositeVolume.h"

#include <TObjArray.h>   // for TObjArray

FairGeoCompositeVolume::FairGeoCompositeVolume(Int_t nComp)
    : FairGeoVolume()
    , components(nullptr)
{
    if (nComp) {
        components = new TObjArray(nComp);
        for (Int_t i = 0; i < nComp; i++) {
            components->AddAt(new FairGeoVolume(), i);
        }
    }
}

FairGeoCompositeVolume::~FairGeoCompositeVolume()
{
    if (components) {
        components->Delete();
    }
    delete components;
}

Int_t FairGeoCompositeVolume::getNumComponents()
{
    if (components) {
        return components->GetSize();
    } else {
        return 0;
    }
}

FairGeoVolume* FairGeoCompositeVolume::getComponent(const Int_t n)
{
    return static_cast<FairGeoVolume*>(components->At(n));
}

void FairGeoCompositeVolume::createComponents(const Int_t n)
{
    if (components) {
        components->Delete();
    } else {
        components = new TObjArray();
    }
    components->Expand(n);
}

void FairGeoCompositeVolume::setComponent(FairGeoVolume* v, const Int_t n)
{
    if (components) {
        components->AddAt(v, n);
    } else {
        Error("FairGeoCompositeVolume::setComponent", "no array of components");
    }
}

void FairGeoCompositeVolume::clear()
{
    FairGeoVolume::clear();
    Int_t n = getNumComponents();
    for (Int_t i = 0; i < n; i++) {
        (static_cast<FairGeoVolume*>(components->At(i)))->clear();
    }
}

void FairGeoCompositeVolume::print()
{
    FairGeoVolume::print();
    FairGeoVolume* v;
    for (Int_t i = 0; i < components->GetSize(); i++) {
        v = static_cast<FairGeoVolume*>(components->At(i));
        if (v) {
            v->print();
        }
    }
}
