/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
* Runge-Kutte Track propagator
* @author M. Al-Turany
* @version 0.2
* @since 22.1.10
*/

#ifndef RKPropagator
#define RKPropagator

#include "FairPropagator.h"

class FairField;
class FairTrackParP;
class TVector3;

class FairRKPropagator : public FairPropagator
{
  private:
    FairRKPropagator(const FairRKPropagator&);            // Not implemented
    FairRKPropagator& operator=(const FairRKPropagator&); // Not implemented
    Double_t fMaxStep;
    FairField* fMagField;

  public:
    void Step(Double_t Charge, Double_t* vecRKIn, Double_t* vecOut);
    Double_t OneStepRungeKutta(Double_t charge, Double_t step, Double_t* vect, Double_t* vout);
    FairRKPropagator(FairField* field);
    /**Propagate to closest approach of a point
    @CHARGE    Particle charge
    @STEP      maximum Step size
    @vecRKIn   Initial co-ords,direction cosines,momentum
    @vecOut    Output co-ords,direction cosines,momentum
    */
    void Propagate(Double_t Charge, Double_t* vecRKIn, Double_t* Pos);

    /**Propagate to closest approach of a plane
    @CHARGE    Particle charge
    @vecRKIn   Initial co-ords,direction cosines,momentum
    @vec1      vector on the plane
    @vec2      vector on the plane
    @vec3      point on the plane
    @vecOut    Output co-ords,direction cosines,momentum
    */

    void PropagateToPlane(Double_t Charge, Double_t* vecRKIn, Double_t* vec1, Double_t* vec2, Double_t* vec3, Double_t* vecOut);

    /**New method to propagate particle to specific plane
     @PDG       Particle code - needed by Geane
     @Charge    Particle charge - needed by RK propagator
     @TStart    Start parameter, containing position and momentum with their corresponding errors
     @v0 v1 v2  Plane defining vectors
     @TEnd      End parameter, to be filled by the function
    */
    virtual void PropagateToPlane(Int_t PDG, Double_t Charge, FairTrackParP* TStart, TVector3& v0, TVector3& v1, TVector3& v2, FairTrackParP* TEnd);

    virtual ~FairRKPropagator();
    ClassDef(FairRKPropagator, 2);
};

#endif
