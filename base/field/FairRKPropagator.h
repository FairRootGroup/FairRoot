/**
* Runge-Kutte Track propagator
* @author M. Al-Turany
* @version 0.1
* @since 22.1.10
*/

#ifndef RKPropagator
#define RKPropagator

#include "FairField.h"

class FairRKPropagator : public TObject
{

  private:
    FairRKPropagator(const FairRKPropagator&);            // Not implemented
    FairRKPropagator& operator=(const FairRKPropagator&); // Not implemented
    Double_t fMaxStep;
    FairField*              fMagField;
  public:
    void Step(Double_t Charge, Double_t* vecRKIn, Double_t* vecOut);
    void OneStepRungeKutta(Double_t charge, Double_t step, Double_t* vect, Double_t* vout);
    FairRKPropagator(FairField* field);
    /**Propagate to closest approach of a point
    @CHARGE    Particle charge
    @STEP      maximum Step size
    @vecRKIn   Initial co-ords,direction cosines,momentum
    @vecOut    Output co-ords,direction cosines,momentum
    */
    void Propagat(Double_t Charge, Double_t* vecRKIn, Double_t* Pos);

    /**Propagate to closest approach of a plane
    @CHARGE    Particle charge
    @vecRKIn   Initial co-ords,direction cosines,momentum
    @vec1      vector on the plane
    @vec2      vector on the plane
    @vec3      point on the plane
    @vecOut    Output co-ords,direction cosines,momentum
    */

    void PropagatToPlane(Double_t Charge, Double_t* vecRKIn, Double_t* vec1, Double_t* vec2, Double_t* vec3, Double_t* vecOut);

    virtual ~FairRKPropagator();
    ClassDef(FairRKPropagator, 1);

};


#endif
