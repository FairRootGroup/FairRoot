/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveTrack.h
 *
 *  Created on: 23 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVETRACK_H_
#define FAIREVETRACK_H_

#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>  // for Int_t
#include <TEveTrack.h>   // for TEveTrack
#include <TVector3.h>    // for TVector3
class TBuffer;
class TClass;
class TEveTrackPropagator;
class TParticle;

class FairEveTrack : public TEveTrack
{

  public:
    /**
     * default constructor, should not be used
     */
    FairEveTrack();
    FairEveTrack(TParticle *t, Int_t label, TEveTrackPropagator *prop = nullptr);
    /**
     * set properties of first point must be called before calling SetNextPoint
     * @param mom momentum of particle
     * @param pos initiali position of particle
     */
    void SetFirstPoint(const TVector3 &mom, const TVector3 &pos);
    /**
     * add next point to tracjectory
     * @param point
     */
    void SetNextPoint(const TVector3 &point);
    virtual ~FairEveTrack();
    ClassDef(FairEveTrack, 0)
};

#endif /* FAIREVETRACK_H_ */
