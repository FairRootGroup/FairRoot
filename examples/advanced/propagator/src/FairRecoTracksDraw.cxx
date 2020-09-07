/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairRecoTracksDraw.cxx
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairRecoTracksDraw.h"

#include "FairEveRecoTracksExample.h"
#include "FairEventManager.h"

#include <RtypesCore.h>
#include <TEveManager.h>
#include <TEveSelection.h>

FairRecoTracksDraw::FairRecoTracksDraw(const char* name)
    : FairTask(name)
    , fEventManager(nullptr)
    , fVisualizer(nullptr)
{}

void FairRecoTracksDraw::Exec(Option_t* option) { fVisualizer->Repaint(); }

InitStatus FairRecoTracksDraw::Init()
{
    fEventManager = FairEventManager::Instance();
    fVisualizer = new FairEveRecoTracksExample();
    fVisualizer->SetRnrChildren(1);
    gEve->AddElement(fVisualizer, FairEventManager::Instance());
    gEve->GetSelection()->SetPickToSelect(TEveSelection::kPS_PableCompound);
    gEve->GetHighlight()->SetPickToSelect(TEveSelection::kPS_PableCompound);
    gEve->Redraw3D(kFALSE);
    return fVisualizer->Init();
}

FairRecoTracksDraw::~FairRecoTracksDraw() {}
