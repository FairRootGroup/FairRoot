/*
 * FairGeoTracksDraw.h
 *
 *  Created on: 23 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIRGEOTRACKSDRAW_H_
#define FAIRGEOTRACKSDRAW_H_
#include "FairEveGeoTracks.h"
#include "FairEventManager.h"

#include <FairTask.h>
#include <Rtypes.h>

/**
 * task that draws the TGeoTracks
 */

class FairGeoTracksDraw : public FairTask
{
    FairEventManager *fEventManager;
    FairEveGeoTracks *fVisualizer;

  public:
    FairGeoTracksDraw();
    virtual void Exec(Option_t *option);
    virtual InitStatus Init();
    virtual ~FairGeoTracksDraw();
    ClassDef(FairGeoTracksDraw, 0)
};

#endif /* FAIRGEOTRACKSDRAW_H_ */
