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
#include "FairTask.h"   // for FairTask, InitStatus

#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Bool_t, Int_t, Option_t
class FairEveMCTracks;    // lines 21-21
class FairEventManager;   // lines 22-22
class FairMCTrack;        // lines 23-23
class TBuffer;
class TClass;
class TEveTrackList;   // lines 24-24
class TMemberInspector;

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
