/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveRecoTrackList.h
 *
 *  Created on: 17 cze 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVERECOTRACKLIST_H_
#define FAIREVERECOTRACKLIST_H_

#include "FairEveRecoTrack.h"

#include <TEveTrack.h>

class FairEveRecoTrackList : public TEveTrackList
{
  public:
    FairEveRecoTrackList() { fChildClass = FairEveRecoTrack::Class(); };
    FairEveRecoTrackList(TString name, TEveTrackPropagator* prop = 0);
    void SetLineColor(Color_t col);
    void SetLineStyle(Style_t s);
    void SetLineWidth(Width_t w);
    void SetMarkerColor(Color_t c);
    void SetMarkerSize(Size_t s);
    void SetMarkerStyle(Style_t s);
    virtual ~FairEveRecoTrackList();
    ClassDef(FairEveRecoTrackList, 0)
};

#endif /* FAIREVERECOTRACKLIST_H_ */
