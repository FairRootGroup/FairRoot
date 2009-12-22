// -------------------------------------------------------------------------
// -----                       FairHit header file                      -----
// -----          Created 08/09/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

#ifndef FAIRHIT_H
#define FAIRHIT_H


#include "TObject.h"
#include "TVector3.h"

/**
 * Abstract base class for reconstructed hits in the FAIR detectors.
  **@author V.Friese <v.friese@gsi.de>
  **@author D.Bertini <d.bertini@gsi.de>
  **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairHit : public TObject 
{

 public:

  /** Default constructor **/
  FairHit();


  /** Constructor with hit parameters 
   *  @param detID:  Detector id where the hit is
   *  @param pos:    TVector3 of the hit position
   *  @param index:  Index of FairMCPoint for this hit
   */
  FairHit(Int_t detID, TVector3& pos, TVector3& dpos, Int_t index);


  /** Destructor **/
  virtual ~FairHit();


  /** Accessors **/
  /**
   * Return the det ID
   */
  Int_t    GetDetectorID()    const { return fDetectorID;             };
	/**
	 * Return the X coordinate 
     */	
  Double_t GetX()             const { return fX;                      };
	/**
	 * Return the Y coordinate 
     */		
  Double_t GetY()             const { return fY;                      };
	/**
	 * Return the Z coordinate 
     */		
  Double_t GetZ()             const { return fZ;                      };
	/**
	 * Return the error in X coordinate 
     */	
	
  Double_t GetDx()            const { return fDx;                     };
	/**
	 * Return the error in Y coordinate 
     */	
	
  Double_t GetDy()            const { return fDy;                     };
	/**
	 * Return the error in Z coordinate 
     */	
	
  Double_t GetDz()            const { return fDz;                     };
	/**
	 * Return the referance index of this hit 
     */	
	Int_t    GetRefIndex()      const { return fRefIndex;               };
	/**
	 * Return the position vector
     */	
	void Position(TVector3& pos)       const;
	/**
	 * Return the error in position as a vector
     */	
	void PositionError(TVector3& dpos) const;

	
  /** Modifiers **/
 	/**
	 * Set the detector Id for this hit 
     */		
  void SetDetectorID(Int_t detID) { fDetectorID = detID; }
	/**
	 * Set the X coordinates of the position 
     */	
  void SetX(Double_t x) { fX = x; }
	/**
	 * Set the Y coordinates of the position
     */	
  void SetY(Double_t y) { fY = y; }
	/**
	 * Set the Z coordinates of the position
     */	
  void SetZ(Double_t z) { fZ = z; }
	/**
	 * Set X, Y, Z  coordinates of the position
     */		
  void SetXYZ(Double_t x, Double_t y, Double_t z);
	/**
	 * Set the position vector
     */		
  void SetPosition(const TVector3& pos);
	/**
	 * Set the error in X coordinates of the position 
     */		
  void SetDx(Double_t dx) { fDx = dx; }
	/**
	 * Set the error in Y coordinates of the position 
     */	
  void SetDy(Double_t dy) { fDy = dy; }
	/**
	 * Set the error in Z coordinates of the position 
     */	
  void SetDz(Double_t dz) { fDz = dz; }
	/**
	 * Set the error in X, Y,Z coordinates of the position 
     */		
  void SetDxyz(Double_t dx, Double_t dy, Double_t dz);
	/**
	 * Set the error in coordinates as a vector
     */	
	
  void SetPositionError(const TVector3& dpos);
	/**
	 * Set the idex of the referance MC point
     */		
  void SetRefIndex(Int_t index)   { fRefIndex = index; }

  /**
   * Output to screen
   */
  virtual void Print(const Option_t* opt = 0) const {;}



 protected:

  Int_t      fDetectorID;     /// Detector unique identifier
  Double32_t fX, fY, fZ;      /// Position of hit [cm]  
  Double32_t fDx, fDy, fDz;   /// Errors of position [cm]
  Int_t      fRefIndex;       /// Index of FairMCPoint for this hit



  ClassDef(FairHit,1);


};


inline void FairHit::Position(TVector3& pos) const {
  pos.SetXYZ(fX, fY, fZ);
}


inline void FairHit::PositionError(TVector3& dpos) const {
  dpos.SetXYZ(fDx, fDy, fDz); 
}


inline void FairHit::SetXYZ(Double_t x, Double_t y, Double_t z) {
  fX = x;
  fY = y;
  fZ = z;
}


inline void FairHit::SetPosition(const TVector3& pos) {
  fX = pos.X();
  fY = pos.Y();
  fZ = pos.Z();
}


inline void FairHit::SetDxyz(Double_t dx, Double_t dy, Double_t dz) {
  fDx = dx;
  fDy = dy;
  fDz = dz;
}


inline void FairHit::SetPositionError(const TVector3& dpos) {
  fDx = dpos.X();
  fDy = dpos.Y();
  fDz = dpos.Z();
}


#endif
