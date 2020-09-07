/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairGeoTracksDraw.cxx
 *
 *  Created on: 23 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairGeoTracksDraw.h"

#include "FairEveGeoTracks.h"
#include "FairEventManager.h"

#include <TEveManager.h>
#include <TEveSelection.h>

FairGeoTracksDraw::FairGeoTracksDraw(const char* name)
    : FairTask(name)
    , fEventManager(nullptr)
    , fVisualizer(nullptr)
{}

void FairGeoTracksDraw::Exec(Option_t* option) { fVisualizer->Repaint(); }

InitStatus FairGeoTracksDraw::Init()
{
    fEventManager = FairEventManager::Instance();
    fVisualizer = new FairEveGeoTracks();
    fVisualizer->SetRnrChildren(1);
    gEve->AddElement(fVisualizer, FairEventManager::Instance());
    gEve->GetSelection()->SetPickToSelect(TEveSelection::kPS_PableCompound);
    gEve->GetHighlight()->SetPickToSelect(TEveSelection::kPS_PableCompound);
    gEve->Redraw3D(kFALSE);
    return fVisualizer->Init();
}

FairGeoTracksDraw::~FairGeoTracksDraw() {}
