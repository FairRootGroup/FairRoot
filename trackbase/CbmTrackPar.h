#ifndef CBMSTSTRACKPAR
#define CBMSTSTRACKPAR 1

#include "TObject.h"


class CbmTrackPar : public TObject
{
   
 public:

  /** Constructor **/
  CbmTrackPar();

  /** Constructor with all variables **/
  CbmTrackPar(Double_t x,  Double_t y,  Double_t z,
		Double_t fx, Double_t fy, Double_t fz, Double_t q);

  /** Destructor **/
  virtual ~CbmTrackPar();

  /** Output to screen **/
  virtual void Print();

  /** Accessors **/
  virtual Double_t GetX()   { return fX; };
  virtual Double_t GetY()   { return fY; };
  virtual Double_t GetZ()   { return fZ; };
  Double_t GetQ()  const { return fq; };

  virtual Double_t GetDX()  const { return fDX; };
  virtual Double_t GetDY()  const { return fDY; };
  virtual Double_t GetDZ()  const { return fDZ; };

  virtual Double_t GetPx() const { return fPx; };
  virtual Double_t GetPy() const { return fPy; };
  virtual Double_t GetPz() const { return fPz; };
  virtual Double_t GetQp() const { return fQp; };

  virtual Double_t GetDPx() const { return fDPx; };
  virtual Double_t GetDPy() const { return fDPy; };
  virtual Double_t GetDPz() const { return fDPz; };
  virtual Double_t GetDQp() const { return fDQp; };

  

  virtual void SetX(Double_t x)   { fX  = x;  };
  virtual void SetY(Double_t y)   { fY  = y;  };
  virtual void SetZ(Double_t z)   { fZ  = z;  };

  virtual void SetDX(Double_t dx)   { fDX  = dx;  };
  virtual void SetDY(Double_t dy)   { fDY  = dy;  };
  virtual void SetDZ(Double_t dz)   { fDZ  = dz;  };

  virtual void SetPx(Double_t px) { fPx = px; };
  virtual void SetPy(Double_t py) { fPy = py; };
  virtual void SetPz(Double_t pz) { fPz = pz; };
 
  virtual void SetDPx(Double_t dpx) { fDPx = dpx; };
  virtual void SetDPy(Double_t dpy) { fDPy = dpy; };
  virtual void SetDPz(Double_t dpz) { fDPz = dpz; };

  void SetQp(Double_t qp) { fQp = qp; };


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
  Double_t fq;

  ClassDef(CbmTrackPar,1);

};
#endif
