/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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

#include "FairTask.h"   // for FairTask, InitStatus

#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Option_t

class FairEventManager;
class FairEveRecoTracksExample;
class TBuffer;
class TClass;
class TMemberInspector;

class FairRecoTracksDraw : public FairTask
{
    FairEventManager *fEventManager;         //!
    FairEveRecoTracksExample *fVisualizer;   //!

  public:
    FairRecoTracksDraw(const char *name = "reconstructed tracks");
    virtual void Exec(Option_t *option);
    virtual InitStatus Init();
    virtual ~FairRecoTracksDraw();
    ClassDef(FairRecoTracksDraw, 1)
};
#endif /* FAIRRECOTRACKSDRAW_H_ */