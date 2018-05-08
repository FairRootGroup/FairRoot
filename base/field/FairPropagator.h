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

class FairPropagator {
public:
    FairPropagator();
    
    virtual ~FairPropagator();
    
    virtual void Step(Double_t Charge, Double_t* vecRKIn, Double_t* vecOut) = 0;
    
    /**Propagate to closest approach of a point
     @CHARGE    Particle charge
     @STEP      maximum Step size
     @vecRKIn   Initial co-ords,direction cosines,momentum
     @vecOut    Output co-ords,direction cosines,momentum
     */
    virtual void Propagat(Double_t Charge, Double_t* vecRKIn, Double_t* Pos) = 0;
    
    /**Propagate to closest approach of a plane
     @CHARGE    Particle charge
     @vecRKIn   Initial co-ords,direction cosines,momentum
     @vec1      vector on the plane
     @vec2      vector on the plane
     @vec3      point on the plane
     @vecOut    Output co-ords,direction cosines,momentum
     */
    virtual void PropagatToPlane(Double_t Charge, Double_t* vecRKIn, Double_t* vec1, Double_t* vec2, Double_t* vec3, Double_t* vecOut) = 0;
    
    ClassDef(FairPropagator, 0)
};

#endif
