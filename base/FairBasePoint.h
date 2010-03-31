#ifndef FAIRBASEPOINT_H
#define FAIRBASEPOINT_H

#include "FairMultiLinkedData.h"
#include "TVector3.h"

#include <vector>

/**
 * Abstract base class for 3D hit information in the FAIR detectors.
  **@author V.Friese <v.friese@gsi.de>
  **@author D.Bertini <d.bertini@gsi.de>
  **@author M.Al-Turany <m.al-turany@gsi.de>
  **@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 */
class FairBasePoint : public FairMultiLinkedData
{

 public:

  /** Default constructor **/
  FairBasePoint();


  /** Constructor with hit parameters **/
  FairBasePoint(Int_t detID, TVector3& pos);

  /** Destructor **/
  virtual ~FairBasePoint();


  /** Accessors **/
  Int_t    GetDetectorID()   const { return fDetectorID;             };
  Double_t GetX()             const { return fX;                      };
  Double_t GetY()             const { return fY;                      };
  Double_t GetZ()             const { return fZ;                      };
  void Position(TVector3& pos)       const;


  /** Modifiers **/
  void SetDetectorID(Int_t detID) { fDetectorID = detID; }
  void SetX(Double_t x) { fX = x; }
  void SetY(Double_t y) { fY = y; }
  void SetZ(Double_t z) { fZ = z; }
  void SetXYZ(Double_t x, Double_t y, Double_t z);
  void SetPosition(const TVector3& pos);

  /*** Output to screen */
  virtual void Print(std::ostream& out = std::cout){
		out << *this;
  }

  friend std::ostream& operator<< (std::ostream& out, const FairBasePoint& data){
	  out << "BasePoint in: " << data.GetDetectorID() << " at ";
	  out << "(" << data.GetX() << "," << data.GetY() << "," << data.GetZ() << ")" << std::endl;

	  return out;
  }

 protected:

  Int_t      fDetectorID;     ///< Detector unique identifier
  Double32_t fX, fY, fZ;      ///< Position of hit [cm]



  ClassDef(FairBasePoint,1);


};


inline void FairBasePoint::Position(TVector3& pos) const {
  pos.SetXYZ(fX, fY, fZ);
}


inline void FairBasePoint::SetXYZ(Double_t x, Double_t y, Double_t z) {
  fX = x;
  fY = y;
  fZ = z;
}


inline void FairBasePoint::SetPosition(const TVector3& pos) {
  fX = pos.X();
  fY = pos.Y();
  fZ = pos.Z();
}


#endif
