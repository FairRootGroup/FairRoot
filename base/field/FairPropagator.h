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

#ifndef FAIRPROPAGATORH
#define FAIRPROPAGATORH

#include "Rtypes.h"
#include "TNamed.h"
#include "TVector3.h"

class FairTrackPar;
class FairTrackParH;
class FairTrackParP;

class FairPropagator : public TNamed {
public:
    FairPropagator();

    FairPropagator(const TString& name, const TString& title);

    virtual ~FairPropagator();

    virtual void Init(FairTrackPar* /* TParam */) {};

    virtual Bool_t Propagate(FairTrackParH* /* TStart */, FairTrackParH* /* TEnd */, Int_t /* PDG */) { return kTRUE; }
    virtual Bool_t Propagate(FairTrackParP* /* TStart */, FairTrackParH* /* TEnd */, Int_t /* PDG */) { return kTRUE; }
    virtual Bool_t Propagate(FairTrackParP* /* TStart */, FairTrackParP* /* TEnd */, Int_t /* PDG */) { return kTRUE; }
    virtual Bool_t Propagate(FairTrackParH* /* TStart */, FairTrackParP* /* TEnd */, Int_t /* PDG */) { return kTRUE; }
    virtual Bool_t Propagate(Float_t* /* x1 */, Float_t* /* p1 */, Float_t* /* x2 */, Float_t* /* p2 */, Int_t /* PDG */) { return kTRUE; }
    virtual Bool_t PropagateToPlane(TVector3& /* v0 */, TVector3& /* v1 */, TVector3& /* v2 */) { return kTRUE; }
    virtual Bool_t PropagateFromPlane(TVector3& /* v1 */, TVector3& /* v2 */) { return kTRUE; }
    virtual Bool_t PropagateToVolume(TString /* VolName */, Int_t /* CopyNo */, Int_t /* option */) { return kTRUE; }
    virtual Bool_t PropagateToLength(Float_t /* length */) { return kTRUE; }
    virtual Bool_t PropagateOnlyParameters() { return kTRUE; }

    virtual Bool_t Propagate(Int_t /* PDG */) { return kTRUE; }

    virtual Bool_t SetWire(TVector3 /* extremity1 */, TVector3 /* extremity2 */) { return kTRUE; }
    virtual Bool_t SetPoint(TVector3 /* pnt */) { return kTRUE; }
    virtual Bool_t PropagateToPCA(Int_t /* pca */) { return kTRUE; }
    virtual Bool_t PropagateToPCA(Int_t /* pca */, Int_t /* dir */) { return kTRUE; }

    virtual int FindPCA(Int_t /* pca */, Int_t /* PDGCode */, TVector3 /* point */, TVector3 /* wire1 */, TVector3 /* wire2 */, Double_t /* maxdistance */, Double_t& /* Rad */, TVector3& /* vpf */, TVector3& /* vwi */, Double_t& /* Di */, Float_t& /* trklength */) { return 0; }

    virtual TVector3 GetPCAOnWire() { return TVector3(0., 0., 0.); }
    virtual TVector3 GetPCAOnTrack() { return TVector3(0., 0., 0.); }

    virtual Float_t GetLengthAtPCA() { return 0.; }
    virtual Float_t GetTimeAtPCA() { return 0.; }
    virtual Bool_t PropagateToVirtualPlaneAtPCA(Int_t /* pca */) { return kTRUE; }
    virtual Bool_t BackTrackToVertex() { return kTRUE; }
    virtual Bool_t BackTrackToVirtualPlaneAtPCA(Int_t /* pca */) { return kTRUE; }

    virtual Bool_t ActualFindPCA(Int_t /* pca */, FairTrackParP* /* par */, Int_t /* dir */) { return kTRUE; }

    // transport matrix
    void GetTransportMatrix(Double_t /* trm[5][5] */) {}

    virtual void Step(Double_t /* Charge */, Double_t* /* vecRKIn */, Double_t* /* vecOut */) {}

    /**Propagate to closest approach of a point
     @CHARGE    Particle charge
     @STEP      maximum Step size
     @vecRKIn   Initial co-ords,direction cosines,momentum
     @vecOut    Output co-ords,direction cosines,momentum
     */
    virtual void Propagate(Double_t /* Charge */, Double_t* /* vecRKIn */, Double_t* /* Pos */) {}

    /**Propagate to closest approach of a plane
     @CHARGE    Particle charge
     @vecRKIn   Initial co-ords,direction cosines,momentum
     @vec1      vector on the plane
     @vec2      vector on the plane
     @vec3      point on the plane
     @vecOut    Output co-ords,direction cosines,momentum
     */
    virtual void PropagateToPlane(Double_t /* Charge */, Double_t* /* vecRKIn */, Double_t* /* vec1 */, Double_t* /* vec2 */, Double_t* /* vec3 */, Double_t* /* vecOut */) {}

    ClassDef(FairPropagator, 1)
};

#endif
