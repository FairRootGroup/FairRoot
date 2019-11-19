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

class FairPropagator : public TNamed
{
  public:
    FairPropagator();

    FairPropagator(const TString& name, const TString& title);

    virtual ~FairPropagator();

    virtual void Init(FairTrackPar* /* TParam */) {};

    //virtual bool Propagate(FairTrackParH* /* TStart */, FairTrackParH* /* TEnd */, int /* PDG */) { return kTRUE; }
    //virtual bool Propagate(FairTrackParP* /* TStart */, FairTrackParH* /* TEnd */, int /* PDG */) { return kTRUE; }
    //virtual bool Propagate(FairTrackParP* /* TStart */, FairTrackParP* /* TEnd */, int /* PDG */) { return kTRUE; }
    //virtual bool Propagate(FairTrackParH* /* TStart */, FairTrackParP* /* TEnd */, int /* PDG */) { return kTRUE; }
    //virtual bool Propagate(float* /* x1 */, float* /* p1 */, float* /* x2 */, float* /* p2 */, int /* PDG */) { return kTRUE; }
    //virtual bool PropagateToPlane(TVector3& /* v0 */, TVector3& /* v1 */, TVector3& /* v2 */) { return kTRUE; }
    //virtual bool PropagateFromPlane(TVector3& /* v1 */, TVector3& /* v2 */) { return kTRUE; }
    //virtual bool PropagateToVolume(TString /* VolName */, int /* CopyNo */, int /* option */) { return kTRUE; }
    //virtual bool PropagateToLength(float /* length */) { return kTRUE; }
    //virtual bool PropagateOnlyParameters() { return kTRUE; }

    virtual bool Propagate(int /* PDG */) { return kTRUE; }

    //    virtual int FindPCA(int /* pca */, int /* PDGCode */, TVector3 /* point */, TVector3 /* wire1 */, TVector3 /* wire2 */, double /* maxdistance */, double& /* Rad */, TVector3& /* vpf */, TVector3& /* vwi */, double& /* Di */, float& /* trklength */) { return 0; }

    /* virtual bool SetWire(TVector3 /\* extremity1 *\/, TVector3 /\* extremity2 *\/) { return kTRUE; } */
    /* virtual bool SetPoint(TVector3 /\* pnt *\/) { return kTRUE; } */
    /* virtual bool PropagateToPCA(int /\* pca *\/) { return kTRUE; } */
    /* virtual bool PropagateToPCA(int /\* pca *\/, int /\* dir *\/) { return kTRUE; } */

    /* virtual TVector3 GetPCAOnWire() { return TVector3(0., 0., 0.); } */
    /* virtual TVector3 GetPCAOnTrack() { return TVector3(0., 0., 0.); } */

    /* virtual float GetLengthAtPCA() { return 0.; } */
    /* virtual float GetTimeAtPCA() { return 0.; } */
    /* virtual bool PropagateToVirtualPlaneAtPCA(int /\* pca *\/) { return kTRUE; } */
    /* virtual bool BackTrackToVertex() { return kTRUE; } */
    /* virtual bool BackTrackToVirtualPlaneAtPCA(int /\* pca *\/) { return kTRUE; } */

    /* virtual bool ActualFindPCA(int /\* pca *\/, FairTrackParP* /\* par *\/, int /\* dir *\/) { return kTRUE; } */

    // transport matrix
    void GetTransportMatrix(double /* trm[5][5] */) {}

    virtual double Step(double /* Charge */, double* /* vecRKIn */, double* /* vecOut */) {return 0.;}

    /**Propagate to closest approach of a point
     @CHARGE    Particle charge
     @STEP      maximum Step size
     @vecRKIn   Initial co-ords,direction cosines,momentum
     @vecOut    Output co-ords,direction cosines,momentum
     */
    virtual void Propagate(double /* Charge */, double* /* vecRKIn */, double* /* Pos */) {}

    /**Propagate to closest approach of a plane
     @CHARGE    Particle charge
     @vecRKIn   Initial co-ords,direction cosines,momentum
     @vec1      vector on the plane
     @vec2      vector on the plane
     @vec3      point on the plane
     @vecOut    Output co-ords,direction cosines,momentum
     */
    virtual void PropagateToPlane(double /* Charge */, double* /* vecRKIn */, double* /* vec1 */, double* /* vec2 */, double* /* vec3 */, double* /* vecOut */) {}

    /* =========================================================================================================================================== */

    /**New method to set the plane to propagate particles to
     @v0 v1 v2  Plane defining vectors
    */
    virtual bool SetDestinationPlane(TVector3& /* v0 */, TVector3& /* v1 */, TVector3& /* v2 */) {return false;}

    /**New method to set the plane to propagate particles from
     @v0 v1     Plane defining vectors
    */
    virtual bool SetOriginPlane(TVector3& /* v0 */, TVector3& /* v1 */) {return false;}

    /**New method to set the volume to propagate particles to
       @volName Volume name
       @copyNo  Copy number
       @option  Option
    */
    virtual bool SetDestinationVolume(std::string /* volName */, int /* copyNo */, int /* option */) {return false;}

    /**New method to set the length to propagate particles to
       @length  Track length
    */
    virtual bool SetDestinationLength(float length) {return false;}

    /**New method to set to propagate only parameters
    */
    virtual bool SetPropagateOnlyParameters() {return false;}

    virtual bool Propagate(FairTrackParH* /* TStart */, FairTrackParH* /* TEnd */, int /* PDG */) { return false; }
    virtual bool Propagate(FairTrackParP* /* TStart */, FairTrackParH* /* TEnd */, int /* PDG */) { return false; }
    virtual bool Propagate(FairTrackParP* /* TStart */, FairTrackParP* /* TEnd */, int /* PDG */) { return false; }
    virtual bool Propagate(FairTrackParH* /* TStart */, FairTrackParP* /* TEnd */, int /* PDG */) { return false; }
    virtual bool Propagate(float* /* x1 */, float* /* p1 */, float* /* x2 */, float* /* p2 */, int /* PDG */) { return false; }

    /**New method to propagate particle to specific plane
     @PDG       Particle code
     @TStart    Start parameter, containing position and momentum with their corresponding errors
     @v0 v1 v2  Plane defining vectors
     @TEnd      End parameter, to be filled by the function
    */
    virtual void PropagateToPlane(int /* PDG */, FairTrackParP* /* TStart */, TVector3& /* v0 */, TVector3& /* v1 */, TVector3& /* v2 */, FairTrackParP* /* TEnd */) {}

    // define wire for PCA extrapolation
    virtual bool SetPCAWire(TVector3 /* extremity1 */, TVector3 /* extremity2 */) { return kTRUE; }
    // define point for PCA extrapolation
    virtual bool SetPCAPoint(TVector3 /* pnt */) { return kTRUE; }
    // .. pca = 1 closest approach to point
    //        = 2 closest approach to wire
    //        = 0 no closest approach
    virtual bool SetPCAPropagation(int pca, int dir = 1, FairTrackParP* = nullptr) { return kTRUE; }

    // get point of closest approach on wire
    virtual TVector3 GetPCAOnWire() { return TVector3(0., 0., 0.); }
    // get point of closest approach on track
    virtual TVector3 GetPCAOnTrack() { return TVector3(0., 0., 0.); }

    // get track length at PCA
    virtual float GetLengthAtPCA() { return 0.; }
    // get track time at PCA
    virtual float GetTimeAtPCA() { return 0.; }
    // ?
    virtual bool PropagateToVirtualPlaneAtPCA(int /* pca */) { return kTRUE; }
    // ?
    virtual bool BackTrackToVertex() { return kTRUE; }
    // ?
    virtual bool BackTrackToVirtualPlaneAtPCA(int /* pca */) { return kTRUE; }

    // INPUT ----------------------------------------
    // .. pca = ic = 1 closest approach to point
    //        = 2 closest approach to wire
    //        = 0 no closest approach
    // .. PDGCode = pdg code of the particle
    // .. point point with respect to which calculate the closest approach
    // .. wire, wire2 line with respect to which calculate the closest approach
    // .. maxdistance = geometrical distance[start - point/wire extr] * 2
    // OUTPUT ----------------------------------------
    // .. Rad radius if the found circle
    // .. vpf: point of closest approach on track
    // .. vwi: point of closest approach on wire
    // .. Di : distance between track and wire in the PCA
    // .. trklength : track length to add to the GEANE one
    virtual int FindPCA(int /* pca */, int /* PDGCode */, TVector3 /* point */, TVector3 /* wire1 */, TVector3 /* wire2 */, double /* maxdistance */, double& /* Rad */, TVector3& /* vpf */, TVector3& /* vwi */, double& /* Di */, float& /* trklength */) { return 0; }


    ClassDef(FairPropagator, 1)
};

#endif
