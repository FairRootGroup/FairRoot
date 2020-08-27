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

#include "FairEveMCTracks.h"
#include "FairEventManager.h"
#include "FairTask.h"

class FairMCTracksDraw : public FairTask
{
    FairEventManager *fEventManager;
    FairEveMCTracks *fVisualizer;

  protected:
    Bool_t CheckCuts(FairMCTrack *tr);
    void DrawTrack(Int_t id);
    TEveTrackList *GetTrackGroup(void *tr);

  public:
    FairMCTracksDraw();
    virtual void Exec(Option_t *opt = "");
    virtual InitStatus Init();
    virtual ~FairMCTracksDraw();
    ClassDef(FairMCTracksDraw, 0)
};

#endif /* FAIRMCTRACKSDRAW_H_ */
