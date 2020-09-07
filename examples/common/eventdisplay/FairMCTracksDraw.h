/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCTracksDraw.h
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIRMCTRACKSDRAW_H_
#define FAIRMCTRACKSDRAW_H_

#include "FairTask.h"

class FairEveMCTracks;
class FairEventManager;
class FairMCTrack;
class TEveTrackList;

class FairMCTracksDraw : public FairTask
{
    FairEventManager *fEventManager;   //!
    FairEveMCTracks *fVisualizer;      //!

  protected:
    Bool_t CheckCuts(FairMCTrack *tr);
    void DrawTrack(Int_t id);
    TEveTrackList *GetTrackGroup(void *tr);

  public:
    FairMCTracksDraw(const char *name = "MC tracks");
    virtual void Exec(Option_t *opt = "");
    virtual InitStatus Init();
    virtual ~FairMCTracksDraw();
    ClassDef(FairMCTracksDraw, 0)
};

#endif /* FAIRMCTRACKSDRAW_H_ */
