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

#include <TEveTrack.h>
#include <TEveTrackPropagator.h>
#include <TVector3.h>

class FairEveTrack : public TEveTrack
{
    Int_t fNPoints;
    static Float_t fgWorldSize;

  public:
    /**
     * default constructor, should not be used
     */
    FairEveTrack();
    FairEveTrack(TParticle *t, Int_t label, TEveTrackPropagator *prop = nullptr);
    /**
     * set world size, trajectories are not drawn outside of the world size
     * @param size world size
     */
    static void SetWorldSize(Float_t size) { fgWorldSize = size; };
    /**
     *
     * @return world size
     */
    static Float_t GetWorldSize() { return fgWorldSize; };
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
