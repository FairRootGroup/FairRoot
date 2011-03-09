// -------------------------------------------------------------------------
// -----                       FairHit header file                      -----
// -----          Created 08/09/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

#ifndef FAIRHIT_H
#define FAIRHIT_H

#include "FairBasePoint.h"
#include "TVector3.h"

/**
 * Abstract base class for reconstructed hits in the FAIR detectors.
  **@author V.Friese <v.friese@gsi.de>
  **@author D.Bertini <d.bertini@gsi.de>
  **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairHit : public FairBasePoint
{

  public:

    /** Default constructor **/
    FairHit();


    /** Constructor with hit parameters **/
    FairHit(Int_t detID, TVector3& pos, TVector3& dpos, Int_t index);


    /** Destructor **/
    virtual ~FairHit();


    /** Accessors **/
    Double_t GetDx()            const { return fDx;                     };
    Double_t GetDy()            const { return fDy;                     };
    Double_t GetDz()            const { return fDz;                     };
    Int_t    GetRefIndex()      const { return fRefIndex;               };
    void PositionError(TVector3& dpos) const;


    /** Modifiers **/
    void SetDx(Double_t dx) { fDx = dx; }
    void SetDy(Double_t dy) { fDy = dy; }
    void SetDz(Double_t dz) { fDz = dz; }
    void SetDxyz(Double_t dx, Double_t dy, Double_t dz);
    void SetPositionError(const TVector3& dpos);
    void SetRefIndex(Int_t index)   { fRefIndex = index; }


    /*** Output to screen */
    virtual void Print(const Option_t* opt = 0) const {;}



  protected:

    Double32_t fDx, fDy, fDz;   // Errors of position [cm]
    Int_t      fRefIndex;       // Index of FairMCPoint for this hit



    ClassDef(FairHit,1);


};


inline void FairHit::PositionError(TVector3& dpos) const
{
  dpos.SetXYZ(fDx, fDy, fDz);
}


inline void FairHit::SetDxyz(Double_t dx, Double_t dy, Double_t dz)
{
  fDx = dx;
  fDy = dy;
  fDz = dz;
}


inline void FairHit::SetPositionError(const TVector3& dpos)
{
  fDx = dpos.X();
  fDy = dpos.Y();
  fDz = dpos.Z();
}


#endif
