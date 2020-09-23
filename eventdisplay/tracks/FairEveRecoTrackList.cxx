/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveRecoTrackList.cxx
 *
 *  Created on: 17 cze 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

 #include "FairEveRecoTrackList.h"
 #include <TEveElement.h>   // for TEveElement::List_i
 #include <TEvePointSet.h>  // for TEvePointSet
 #include <list>            // for operator!=, __list_iterator
 #include "FairEveTrack.h"  // for FairEveTrack
 class TEveTrackPropagator;

FairEveRecoTrackList::FairEveRecoTrackList(TString name, TEveTrackPropagator* prop)
    : TEveTrackList(name, prop)
{
    fChildClass = FairEveRecoTrack::Class();
}

void FairEveRecoTrackList::SetLineColor(Color_t col)
{
    for (List_i i = BeginChildren(); i != EndChildren(); ++i) {
        FairEveRecoTrack* track = (FairEveRecoTrack*)(*i);
        if (track->GetRecoTrack()->GetLineColor() == fLineColor)
            track->GetRecoTrack()->SetLineColor(col);
        if (track->GetMCTrack()) {
            track->GetMCTrack()->SetLineColor(col);
        }
    }
    fLineColor = col;
}

void FairEveRecoTrackList::SetLineStyle(Style_t s)
{
    for (List_i i = BeginChildren(); i != EndChildren(); ++i) {
        FairEveRecoTrack* track = (FairEveRecoTrack*)(*i);
        if (track->GetRecoTrack()->GetLineStyle() == fLineStyle)
            track->GetRecoTrack()->SetLineStyle(s);
        if (track->GetMCTrack()) {
            //     track->GetMCTrack()->SetLineStyle(s);
        }
    }
    fLineStyle = s;
}

void FairEveRecoTrackList::SetLineWidth(Width_t w)
{
    for (List_i i = BeginChildren(); i != EndChildren(); ++i) {
        FairEveRecoTrack* track = (FairEveRecoTrack*)(*i);
        if (track->GetRecoTrack()->GetLineWidth() == fLineWidth)
            track->GetRecoTrack()->SetLineWidth(w);
        if (track->GetMCTrack()) {
            track->GetMCTrack()->SetLineWidth(w);
        }
    }
    fLineWidth = w;
}

void FairEveRecoTrackList::SetMarkerColor(Color_t c)
{
    for (List_i i = BeginChildren(); i != EndChildren(); ++i) {
        FairEveRecoTrack* track = (FairEveRecoTrack*)(*i);
        if (track->GetHits()) {
            if (track->GetHits()->GetMarkerColor() == fMarkerColor) {
                track->GetHits()->SetMarkerColor(c);
            }
        }
    }
    fMarkerColor = c;
}

void FairEveRecoTrackList::SetMarkerSize(Size_t s)
{
    for (List_i i = BeginChildren(); i != EndChildren(); ++i) {
        FairEveRecoTrack* track = (FairEveRecoTrack*)(*i);
        if (track->GetHits()) {
            if (track->GetHits()->GetMarkerSize() == fMarkerSize) {
                track->GetHits()->SetMarkerSize(s);
            }
        }
    }
    fMarkerSize = s;
}

void FairEveRecoTrackList::SetMarkerStyle(Style_t s)
{
    for (List_i i = BeginChildren(); i != EndChildren(); ++i) {
        FairEveRecoTrack* track = (FairEveRecoTrack*)(*i);
        if (track->GetHits()) {
            if (track->GetHits()->GetMarkerStyle() == fMarkerStyle) {
                track->GetHits()->SetMarkerStyle(s);
            }
        }
    }
    fMarkerStyle = s;
}

FairEveRecoTrackList::~FairEveRecoTrackList() {}
