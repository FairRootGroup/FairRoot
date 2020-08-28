/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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
