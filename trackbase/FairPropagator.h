/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * Base abstract class for track propagation
 * @author D. Kresan
 * @version 0.1
 * @since 08.05.2018
 */

#ifndef FAIRPROPAGATOR_H
#define FAIRPROPAGATOR_H

#include <Rtypes.h>
#include <TNamed.h>
#include <TVector3.h>

class FairTrackPar;
class FairTrackParH;
class FairTrackParP;

struct PCAOutputStruct
{
    // OUTPUT STRUCT ----------------------------------------
    // .. PCAStatusFlag 0 by success, else otherwise
    // .. Radius      : radius if the found circle
    // .. OnTrackPCA  : point of closest approach on track
    // .. OnWirePCA   : point of closest approach on wire
    // .. Distance    : distance between track and wire in the PCA
    // .. TrackLength : track length to add to the GEANE one
    PCAOutputStruct()
        : PCAStatusFlag(1)
        , Radius(0.)
        , OnTrackPCA(TVector3(0., 0., 0.))
        , OnWirePCA(TVector3(0., 0., 0.))
        , Distance(0.)
        , TrackLength(0.)
    {}
    int PCAStatusFlag;
    double Radius;
    TVector3 OnTrackPCA;
    TVector3 OnWirePCA;
    double Distance;
    float TrackLength;
};

class FairPropagator : public TNamed
{
  public:
    FairPropagator();

    FairPropagator(const TString& name, const TString& title);

    virtual ~FairPropagator();

    virtual void Init(FairTrackPar* /* TParam */){};

    /**New method to set the plane to propagate particles to
     @v0 v1 v2  Plane defining vectors
    */
    virtual bool SetDestinationPlane([[maybe_unused]] TVector3& /* v0 */,
                                     [[maybe_unused]] TVector3& /* v1 */,
                                     [[maybe_unused]] TVector3& /* v2 */)
    {
        return false;
    }

    /**New method to set the plane to propagate particles from
     @v0 v1     Plane defining vectors
    */
    virtual bool SetOriginPlane([[maybe_unused]] TVector3& /* v0 */, [[maybe_unused]] TVector3& /* v1 */)
    {
        return false;
    }

    /**New method to set the volume to propagate particles to
       @volName Volume name
       @copyNo  Copy number
       @option  Option
    */
    virtual bool SetDestinationVolume([[maybe_unused]] std::string /* volName */,
                                      [[maybe_unused]] int /* copyNo */,
                                      [[maybe_unused]] int /* option */)
    {
        return false;
    }

    /**New method to set the length to propagate particles to
       @length  Track length
    */
    virtual bool SetDestinationLength([[maybe_unused]] float length) { return false; }

    /**New method to set to propagate only parameters
     */
    virtual bool SetPropagateOnlyParameters() { return false; }

    virtual bool Propagate([[maybe_unused]] FairTrackParH* /* TStart */,
                           [[maybe_unused]] FairTrackParH* /* TEnd */,
                           [[maybe_unused]] int /* PDG */)
    {
        return false;
    }
    virtual bool Propagate([[maybe_unused]] FairTrackParP* /* TStart */,
                           [[maybe_unused]] FairTrackParH* /* TEnd */,
                           [[maybe_unused]] int /* PDG */)
    {
        return false;
    }
    virtual bool Propagate([[maybe_unused]] FairTrackParP* /* TStart */,
                           [[maybe_unused]] FairTrackParP* /* TEnd */,
                           [[maybe_unused]] int /* PDG */)
    {
        return false;
    }
    virtual bool Propagate([[maybe_unused]] FairTrackParH* /* TStart */,
                           [[maybe_unused]] FairTrackParP* /* TEnd */,
                           [[maybe_unused]] int /* PDG */)
    {
        return false;
    }
    virtual bool Propagate([[maybe_unused]] float* /* x1 */,
                           [[maybe_unused]] float* /* p1 */,
                           [[maybe_unused]] float* /* x2 */,
                           [[maybe_unused]] float* /* p2 */,
                           [[maybe_unused]] int /* PDG */)
    {
        return false;
    }

    /* ===========================================================================================================================================
     */

    // Set PCA propagation:
    // .. pca = ic = 1 closest approach to point
    //        = 2 closest approach to wire
    //        = 0 no closest approach
    // .. dir = +1 move forward
    //        = -1 move backward
    // .. par = initial track parameters
    virtual bool SetPCAPropagation([[maybe_unused]] int pca,
                                   [[maybe_unused]] int dir = 1,
                                   [[maybe_unused]] FairTrackParP* par = nullptr)
    {
        return kTRUE;
    }

    // INPUT ----------------------------------------
    // .. pca = ic = 1 closest approach to point
    //        = 2 closest approach to wire
    //        = 0 no closest approach
    // .. PDGCode = pdg code of the particle
    // .. point point with respect to which calculate the closest approach
    // .. wire, wire2 line with respect to which calculate the closest approach
    // .. maxdistance = geometrical distance[start - point/wire extr] * 2
    virtual PCAOutputStruct FindPCA([[maybe_unused]] int PCA,
                                    [[maybe_unused]] int PDGCode,
                                    [[maybe_unused]] TVector3 Point,
                                    [[maybe_unused]] TVector3 Wire1,
                                    [[maybe_unused]] TVector3 Wire2,
                                    [[maybe_unused]] double MaxDistance)
    {
        return PCAOutputStruct();
    }

    ClassDef(FairPropagator, 1);
};

#endif
