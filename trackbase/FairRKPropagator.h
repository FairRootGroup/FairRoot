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
#include "FairPropagator.h"   // for FairPropagator, PCAOutputStruct

#include <Rtypes.h>     // for THashConsistencyHolder, ClassDef
#include <TVector3.h>   // for TVector3
#include <iosfwd>       // for string
class FairField;        // lines 20-20
class FairTrackParH;
class FairTrackParP;   // lines 21-21
class TBuffer;
class TClass;
class TMemberInspector;

enum PropagationFlag
{
    NONE,
    TOPLANE,
    TOVOLUME,
    TOLENGTH
};

class FairRKPropagator : public FairPropagator
{
  private:
    FairRKPropagator(const FairRKPropagator&);              // Not implemented
    FairRKPropagator& operator=(const FairRKPropagator&);   // Not implemented
    double fMaxStep;
    FairField* fMagField;

    PropagationFlag fPropagationFlag;
    TVector3 fDefPlaneV0;
    TVector3 fDefPlaneV1;
    TVector3 fDefPlaneV2;

    int fPCAPropagationType;
    int fPCAPropagationDir;
    FairTrackParP* fPCAPropagationPar;

    double GetChargeFromPDG(int pdg);
    double CalculatePointToWireDistance(TVector3 point, TVector3 wire1, TVector3 wire2, TVector3& vwi);

  public:
    double Step(double Charge, double* vecRKIn, double* vecOut);
    double OneStepRungeKutta(double charge, double step, double* vect, double* vout);
    FairRKPropagator(FairField* field);
    /**Propagate to closest approach of a point
    @CHARGE    Particle charge
    @STEP      maximum Step size
    @vecRKIn   Initial co-ords,direction cosines,momentum
    @vecOut    Output co-ords,direction cosines,momentum
    */
    void Propagate(double Charge, double* vecRKIn, double* Pos);

    /**Propagate to closest approach of a plane
    @CHARGE    Particle charge
    @vecRKIn   Initial co-ords,direction cosines,momentum
    @vec1      vector on the plane
    @vec2      vector on the plane
    @vec3      point on the plane
    @vecOut    Output co-ords,direction cosines,momentum
    */

    void PropagateToPlane(double Charge, double* vecRKIn, double* vec1, double* vec2, double* vec3, double* vecOut);

    /* ===========================================================================================================================================
     */

    /**New method to set the plane to propagate particles to
     @v0 v1 v2  Plane defining vectors
    */
    virtual bool SetDestinationPlane(const TVector3& v0, const TVector3& v1, const TVector3& v2);

    /**New method to set the plane to propagate particles from
     @v0 v1     Plane defining vectors
    */
    virtual bool SetOriginPlane(const TVector3& v0, const TVector3& v1);

    /**New method to set the volume to propagate particles to
       @volName Volume name
       @copyNo  Copy number
       @option  Option
    */
    virtual bool SetDestinationVolume(std::string volName, int copyNo, int option);

    /**New method to set the length to propagate particles to
       @length  Track length
    */
    virtual bool SetDestinationLength(float length);

    /**New method to set to propagate only parameters
     */
    virtual bool SetPropagateOnlyParameters() { return true; }

    virtual bool Propagate(FairTrackParH* TStart, FairTrackParH* TEnd, int PDG);
    virtual bool Propagate(FairTrackParP* TStart, FairTrackParH* TEnd, int PDG);
    virtual bool Propagate(FairTrackParP* TStart, FairTrackParP* TEnd, int PDG);
    virtual bool Propagate(FairTrackParH* TStart, FairTrackParP* TEnd, int PDG);
    virtual bool Propagate(float* x1, float* p1, float* x2, float* p2, int PDG);

    virtual bool SetPCAPropagation(int pca, int dir = 1, FairTrackParP* par = nullptr);

    virtual PCAOutputStruct FindPCA(int PCA,
                                    int PDGCode,
                                    TVector3 Point,
                                    TVector3 Wire1,
                                    TVector3 Wire2,
                                    double MaxDistance);

    virtual ~FairRKPropagator();
    ClassDef(FairRKPropagator, 2);
};

#endif
