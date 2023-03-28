/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveTracks.cxx
 *
 *  Created on: 4 maj 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "FairEveTracks.h"

#include "FairEveRecoTrackList.h"   // for FairEveRecoTrackList
#include "FairEventManager.h"       // for FairEventManager

#include <RtypesCore.h>            // for kFALSE, kTRUE, Bool_t, Color_t
#include <TEveManager.h>           // for TEveManager, gEve
#include <TEveTrackPropagator.h>   // for TEveTrackPropagator
#include <TString.h>               // for TString
#include <algorithm>               // for for_each
#include <list>                    // for __list_iterator, operator!=

FairEveTracks::FairEveTracks(Bool_t acceptCompound)
    : fAcceptCompound(acceptCompound)
{}

void FairEveTracks::ToggleTracks()
{
    std::for_each(BeginChildren(), EndChildren(), [](TEveElement *trackGroup) {
        std::for_each(trackGroup->BeginChildren(), trackGroup->EndChildren(), [](TEveElement *track) {
            if (track->GetRnrSelf()) {
                track->SetRnrSelfChildren(kFALSE, kFALSE);
            } else {
                track->SetRnrSelfChildren(kTRUE, kTRUE);
            }
        });
    });
    gEve->Redraw3D(kFALSE);
}

InitStatus FairEveTracks::Init()
{
    fEventManager = FairEventManager::Instance();
    return kSUCCESS;
}

FairEveTracks::~FairEveTracks() {}

TEveTrackList *FairEveTracks::FindTrackGroup(TString groupName, Color_t color)
{
    auto trackGroup(static_cast<TEveTrackList *>(FindChild(groupName)));

    if (trackGroup == nullptr) {
        TEveTrackPropagator *TrPropagator = new TEveTrackPropagator();
        if (fAcceptCompound) {
            trackGroup = new FairEveRecoTrackList(groupName, TrPropagator);
        } else {
            trackGroup = new TEveTrackList(groupName, TrPropagator);
        }
        AddElement(trackGroup);
        trackGroup->SetRnrLine(kTRUE);
        trackGroup->SetMainColor(color);
    }
    return trackGroup;
}

void FairEveTracks::ToggleGroups()
{
    std::for_each(BeginChildren(), EndChildren(), [](TEveElement *trackGroup) {
        if (trackGroup->GetRnrSelf()) {
            trackGroup->SetRnrSelfChildren(kFALSE, kFALSE);
        } else {
            trackGroup->SetRnrSelfChildren(kTRUE, kTRUE);
        }
    });
    gEve->Redraw3D(kFALSE);
}
