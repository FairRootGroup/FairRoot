/*
 * FairRecoTracksDraw.h
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIRRECOTRACKSDRAW_H_
#define FAIRRECOTRACKSDRAW_H_

#include "FairEveRecoTracksExample.h"
#include "FairEventManager.h"

#include <FairTask.h>
#include <Rtypes.h>

class FairRecoTracksDraw : public FairTask
{
    FairEventManager *fEventManager;
    FairEveRecoTracksExample *fVisualizer;

  public:
    FairRecoTracksDraw();
    virtual void Exec(Option_t *option);
    virtual InitStatus Init();
    virtual ~FairRecoTracksDraw();
    ClassDef(FairRecoTracksDraw, 1)
};
#endif /* FAIRRECOTRACKSDRAW_H_ */
