/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRSTSTRACKPAR
#define FAIRSTSTRACKPAR 1
#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>  // for Double_t, Int_t, Option_t
#include <TObject.h>     // for TObject
#include <TVector3.h>    // for TVector3
class TBuffer;
class TClass;
class TMemberInspector;

class FairTrackPar : public TObject
{
  public:
    /** Constructor **/
    FairTrackPar();

    /** Constructor with all variables **/
    FairTrackPar(Double_t x, Double_t y, Double_t z, Double_t px, Double_t py, Double_t pz, Int_t q);

    FairTrackPar(Double_t x,
                 Double_t y,
                 Double_t z,
                 Double_t dx,
                 Double_t dy,
                 Double_t dz,
                 Double_t px,
                 Double_t py,
                 Double_t pz,
                 Double_t dpx,
                 Double_t dpy,
                 Double_t dpz,
                 Int_t q);

    /** Destructor **/
    virtual ~FairTrackPar();

    /** Output to screen **/
    virtual void Print(Option_t* option = "") const;
    /** Accessors **/
    virtual TVector3 GetPosition() const { return TVector3(fX, fY, fZ); }

    virtual Double_t GetX() { return fX; }
    virtual Double_t GetY() { return fY; }
    virtual Double_t GetZ() { return fZ; }
    Int_t GetQ() const { return fq; }

    virtual Double_t GetDX() const { return fDX; }
    virtual Double_t GetDY() const { return fDY; }
    virtual Double_t GetDZ() const { return fDZ; }

    virtual TVector3 GetMomentum() const { return TVector3(fPx, fPy, fPz); }

    virtual Double_t GetPx() const { return fPx; }
    virtual Double_t GetPy() const { return fPy; }
    virtual Double_t GetPz() const { return fPz; }
    virtual Double_t GetQp() const { return fQp; }

    virtual Double_t GetDPx() const { return fDPx; }
    virtual Double_t GetDPy() const { return fDPy; }
    virtual Double_t GetDPz() const { return fDPz; }
    virtual Double_t GetDQp() const { return fDQp; }

    virtual void GetFieldValue(const Double_t point[3], Double_t* bField);

    virtual void SetX(Double_t x) { fX = x; }
    virtual void SetY(Double_t y) { fY = y; }
    virtual void SetZ(Double_t z) { fZ = z; }

    virtual void SetDX(Double_t dx) { fDX = dx; }
    virtual void SetDY(Double_t dy) { fDY = dy; }
    virtual void SetDZ(Double_t dz) { fDZ = dz; }

    virtual void SetPx(Double_t px) { fPx = px; }
    virtual void SetPy(Double_t py) { fPy = py; }
    virtual void SetPz(Double_t pz) { fPz = pz; }

    virtual void SetDPx(Double_t dpx) { fDPx = dpx; }
    virtual void SetDPy(Double_t dpy) { fDPy = dpy; }
    virtual void SetDPz(Double_t dpz) { fDPz = dpz; }

    void SetQp(Double_t qp) { fQp = qp; }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int)
    {
        ar& fX;
        ar& fY;
        ar& fZ;
        ar& fDX;
        ar& fDY;
        ar& fDZ;
        ar& fPx;
        ar& fPy;
        ar& fPz;
        ar& fDPx;
        ar& fDPy;
        ar& fDPz;
        ar& fQp;
        ar& fDQp;
        ar& fq;
    }

  protected:
    /** Position of track [cm] **/
    Double_t fX, fY, fZ;

    /** Error in position of track [cm] **/
    Double_t fDX, fDY, fDZ;

    /** momentum  [GeV]**/
    Double_t fPx, fPy, fPz;

    /** Error in momentum  [GeV]**/
    Double_t fDPx, fDPy, fDPz;

    /** Charge over momentum [1/GeV] **/
    Double_t fQp;

    /** Error in charge over momentum [1/GeV] **/
    Double_t fDQp;

    /** charge*/
    Int_t fq;

    ClassDef(FairTrackPar, 2);
};

#endif
