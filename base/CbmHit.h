// -------------------------------------------------------------------------
// -----                       CbmHit header file                      -----
// -----          Created 08/09/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

#ifndef CBMHIT_H
#define CBMHIT_H


#include "TObject.h"
#include "TVector3.h"

/**
 * Abstract base class for reconstructed hits in the CBM detectors.
  **@author V.Friese <v.friese@gsi.de>
  **@author D.Bertini <d.bertini@gsi.de>
  **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class CbmHit : public TObject 
{

 public:

  /** Default constructor **/
  CbmHit();


  /** Constructor with hit parameters **/
  CbmHit(Int_t detID, TVector3& pos, TVector3& dpos, Int_t index);


  /** Destructor **/
  virtual ~CbmHit();


  /** Accessors **/
  Int_t    GetDetectorID()    const { return fDetectorID;             };
  Double_t GetX()             const { return fX;                      };
  Double_t GetY()             const { return fY;                      };
  Double_t GetZ()             const { return fZ;                      };
  Double_t GetDx()            const { return fDx;                     };
  Double_t GetDy()            const { return fDy;                     };
  Double_t GetDz()            const { return fDz;                     };
  Int_t    GetRefIndex()      const { return fRefIndex;               };
  void Position(TVector3& pos)       const;
  void PositionError(TVector3& dpos) const;


  /** Modifiers **/
  void SetDetectorID(Int_t detID) { fDetectorID = detID; }
  void SetX(Double_t x) { fX = x; }
  void SetY(Double_t y) { fY = y; }
  void SetZ(Double_t z) { fZ = z; }
  void SetXYZ(Double_t x, Double_t y, Double_t z);
  void SetPosition(const TVector3& pos);
  void SetDx(Double_t dx) { fDx = dx; }
  void SetDy(Double_t dy) { fDy = dy; }
  void SetDz(Double_t dz) { fDz = dz; }
  void SetDxyz(Double_t dx, Double_t dy, Double_t dz);
  void SetPositionError(const TVector3& dpos);
  void SetRefIndex(Int_t index)   { fRefIndex = index; }


  /*** Output to screen */
  virtual void Print(const Option_t* opt = 0) const {;}



 protected:

  Int_t      fDetectorID;     // Detector unique identifier
  Double32_t fX, fY, fZ;      // Position of hit [cm]  
  Double32_t fDx, fDy, fDz;   // Errors of position [cm]
  Int_t      fRefIndex;       // Index of CbmMCPoint for this hit



  ClassDef(CbmHit,1);


};


inline void CbmHit::Position(TVector3& pos) const {
  pos.SetXYZ(fX, fY, fZ);
}


inline void CbmHit::PositionError(TVector3& dpos) const {
  dpos.SetXYZ(fDx, fDy, fDz); 
}


inline void CbmHit::SetXYZ(Double_t x, Double_t y, Double_t z) {
  fX = x;
  fY = y;
  fZ = z;
}


inline void CbmHit::SetPosition(const TVector3& pos) {
  fX = pos.X();
  fY = pos.Y();
  fZ = pos.Z();
}


inline void CbmHit::SetDxyz(Double_t dx, Double_t dy, Double_t dz) {
  fDx = dx;
  fDy = dy;
  fDz = dz;
}


inline void CbmHit::SetPositionError(const TVector3& dpos) {
  fDx = dpos.X();
  fDy = dpos.Y();
  fDz = dpos.Z();
}


#endif
