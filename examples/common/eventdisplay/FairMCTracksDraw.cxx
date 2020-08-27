/*
 * FairMCTracksDraw.cxx
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include <TEveManager.h>
#include <TEveSelection.h>

#include "FairMCTracksDraw.h"

FairMCTracksDraw::FairMCTracksDraw() :fEventManager(nullptr),fVisualizer(nullptr){
}

void FairMCTracksDraw::Exec(Option_t * /*option*/) {
    fVisualizer->Repaint();
}

InitStatus FairMCTracksDraw::Init() {
    fEventManager = FairEventManager::Instance();
    fVisualizer = new FairEveMCTracks();
    fVisualizer->SetRnrChildren(1);
    gEve->AddElement(fVisualizer, FairEventManager::Instance());
    gEve->GetSelection()->SetPickToSelect(TEveSelection::kPS_PableCompound);
    gEve->GetHighlight()->SetPickToSelect(TEveSelection::kPS_PableCompound);
    gEve->Redraw3D(kFALSE);
    return fVisualizer->Init();
}

FairMCTracksDraw::~FairMCTracksDraw() {
}
