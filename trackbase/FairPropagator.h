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
#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>  // for kTRUE
#include <TNamed.h>      // for TNamed
#include <TString.h>     // for TString
#include <TVector3.h>    // for TVector3
#include <iosfwd>        // for string
#include <string>        // for basic_string
class FairTrackPar;  // lines 22-22
class FairTrackParH;  // lines 23-23
class FairTrackParP;  // lines 24-24
class TBuffer;
class TClass;
class TMemberInspector;

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
    virtual bool SetDestinationPlane([[gnu::unused]] const TVector3& v0,
                                     [[gnu::unused]] const TVector3& v1,
                                     [[gnu::unused]] const TVector3& v2)
    {
        return false;
    }

    /**New method to set the plane to propagate particles from
     @v0 v1     Plane defining vectors
    */
    virtual bool SetOriginPlane([[gnu::unused]] const TVector3& v0, [[gnu::unused]] const TVector3& v1)
    {
        return false;
    }

    /**New method to set the volume to propagate particles to
       @volName Volume name
       @copyNo  Copy number
       @option  Option
    */
    virtual bool SetDestinationVolume([[gnu::unused]] std::string volName,
                                      [[gnu::unused]] int copyNo,
                                      [[gnu::unused]] int option)
    {
        return false;
    }

    /**New method to set the length to propagate particles to
       @length  Track length
    */
    virtual bool SetDestinationLength([[gnu::unused]] float length) { return false; }

    /**New method to set to propagate only parameters
     */
    virtual bool SetPropagateOnlyParameters() { return false; }

    virtual bool Propagate([[gnu::unused]] FairTrackParH* TStart,
                           [[gnu::unused]] FairTrackParH* TEnd,
                           [[gnu::unused]] int PDG)
    {
        return false;
    }
    virtual bool Propagate([[gnu::unused]] FairTrackParP* TStart,
                           [[gnu::unused]] FairTrackParH* TEnd,
                           [[gnu::unused]] int PDG)
    {
        return false;
    }
    virtual bool Propagate([[gnu::unused]] FairTrackParP* TStart,
                           [[gnu::unused]] FairTrackParP* TEnd,
                           [[gnu::unused]] int PDG)
    {
        return false;
    }
    virtual bool Propagate([[gnu::unused]] FairTrackParH* TStart,
                           [[gnu::unused]] FairTrackParP* TEnd,
                           [[gnu::unused]] int PDG)
    {
        return false;
    }
    virtual bool Propagate([[gnu::unused]] float* x1,
                           [[gnu::unused]] float* p1,
                           [[gnu::unused]] float* x2,
                           [[gnu::unused]] float* p2,
                           [[gnu::unused]] int PDG)
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
    virtual bool SetPCAPropagation([[gnu::unused]] int pca,
                                   [[gnu::unused]] int dir = 1,
                                   [[gnu::unused]] FairTrackParP* par = nullptr)
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
    virtual PCAOutputStruct FindPCA([[gnu::unused]] int PCA,
                                    [[gnu::unused]] int PDGCode,
                                    [[gnu::unused]] TVector3 Point,
                                    [[gnu::unused]] TVector3 Wire1,
                                    [[gnu::unused]] TVector3 Wire2,
                                    [[gnu::unused]] double MaxDistance)
    {
        return PCAOutputStruct();
    }

    ClassDef(FairPropagator, 1);
};

#endif
