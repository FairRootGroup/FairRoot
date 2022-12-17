/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRHIT_H
#define FAIRHIT_H

#include "FairTimeStamp.h"   // for FairTimeStamp

#include <Rtypes.h>     // for Double_t, Int_t, Double32_t, etc
#include <TVector3.h>   // for TVector3

/**
 * Abstract base class for reconstructed hits in the FAIR detectors.
 **@author V.Friese <v.friese@gsi.de>
 **@author D.Bertini <d.bertini@gsi.de>
 **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairHit : public FairTimeStamp
{
  public:
    /** Default constructor **/
    FairHit();

    /** Constructor with hit parameters **/
    FairHit(Int_t detID, const TVector3& pos, const TVector3& dpos, Int_t index);

    /** Destructor **/
    virtual ~FairHit();

    /** Accessors **/
    Double_t GetDx() const { return fDx; };
    Double_t GetDy() const { return fDy; };
    Double_t GetDz() const { return fDz; };
    Int_t GetRefIndex() const { return fRefIndex; };
    void PositionError(TVector3& dpos) const;
    Int_t GetDetectorID() const { return fDetectorID; };
    Double_t GetX() const { return fX; };
    Double_t GetY() const { return fY; };
    Double_t GetZ() const { return fZ; };
    void Position(TVector3& pos) const;

    /** Modifiers **/
    void SetDx(Double_t dx) { fDx = dx; }
    void SetDy(Double_t dy) { fDy = dy; }
    void SetDz(Double_t dz) { fDz = dz; }
    void SetDxyz(Double_t dx, Double_t dy, Double_t dz);
    void SetPositionError(const TVector3& dpos);
    void SetRefIndex(Int_t index) { fRefIndex = index; }
    void SetDetectorID(Int_t detID) { fDetectorID = detID; }
    void SetX(Double_t x) { fX = x; }
    void SetY(Double_t y) { fY = y; }
    void SetZ(Double_t z) { fZ = z; }
    void SetXYZ(Double_t x, Double_t y, Double_t z);
    void SetPosition(const TVector3& pos);

    /*** Output to screen */
    virtual void Print(const Option_t*) const { ; }

  protected:
    Double32_t fDx, fDy, fDz;   ///< Errors of position [cm]
    Int_t fRefIndex;            ///< Index of FairMCPoint for this hit
    Int_t fDetectorID;          ///< Detector unique identifier
    Double32_t fX, fY, fZ;      ///< Position of hit [cm]

    ClassDef(FairHit, 3);
};

inline void FairHit::PositionError(TVector3& dpos) const { dpos.SetXYZ(fDx, fDy, fDz); }

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

inline void FairHit::Position(TVector3& pos) const { pos.SetXYZ(fX, fY, fZ); }

inline void FairHit::SetXYZ(Double_t x, Double_t y, Double_t z)
{
    fX = x;
    fY = y;
    fZ = z;
}

inline void FairHit::SetPosition(const TVector3& pos)
{
    fX = pos.X();
    fY = pos.Y();
    fZ = pos.Z();
}

#endif   // FAIRHIT_H
