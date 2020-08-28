/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveTrack.cxx
 *
 *  Created on: 23 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairEveTrack.h"

Float_t FairEveTrack::fgWorldSize = 2000;

FairEveTrack::FairEveTrack()
    : TEveTrack()
    , fNPoints(0)
{}

FairEveTrack::FairEveTrack(TParticle *t, Int_t label, TEveTrackPropagator *prop)
    : TEveTrack(t, label, prop)
    , fNPoints(0)
{}

void FairEveTrack::SetFirstPoint(const TVector3 &mom, const TVector3 &pos)
{
    TEveTrack::SetPoint(fNPoints++, pos.X(), pos.Y(), pos.Z());
    TEvePathMark path;
    Float_t point[3] = {(Float_t)pos.X(), (Float_t)pos.Y(), (Float_t)pos.Z()};
    path.fV = point;
    path.fTime = 0;
    TEveVector Mom(mom.Px(), mom.Py(), mom.Pz());
    path.fP = Mom;
    AddPathMark(path);
}

void FairEveTrack::SetNextPoint(const TVector3 &point)
{
    if (TMath::Abs(point.X()) > fgWorldSize)
        return;
    if (TMath::Abs(point.Y()) > fgWorldSize)
        return;
    if (TMath::Abs(point.Z()) > fgWorldSize)
        return;
    if (TMath::IsNaN(point.X()))
        return;
    TEveTrack::SetPoint(fNPoints++, point.X(), point.Y(), point.Z());
    TEvePathMark path;
    Float_t hit[3] = {(Float_t)point.X(), (Float_t)point.Y(), (Float_t)point.Z()};
    path.fV = hit;
    path.fTime = 0;
    AddPathMark(path);
}

FairEveTrack::~FairEveTrack()
{
    // TODO Auto-generated destructor stub
}
