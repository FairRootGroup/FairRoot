// -------------------------------------------------------------------------
// -----                      FairRadLenPoint source file                   -----
// -----                  Created 14/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------


#include "FairRadLenPoint.h"


// -----   Default constructor   -------------------------------------------
FairRadLenPoint::FairRadLenPoint()
  : FairMCPoint(),
    fA(0),
    fZmat(0),
    fDensity(0),
    fRadLen(0),
    fXOut(0),
    fYOut(0),
    fZOut(0),
    fPxOut(0),
    fPyOut(0),
    fPzOut(0)


{
  /**default ctor*/
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairRadLenPoint::FairRadLenPoint(Int_t trackID, Int_t detID, TVector3 pos,
                                 TVector3 mom, Double_t tof, Double_t length, Double_t eLoss,
                                 TVector3 posOut, TVector3 momOut,
                                 Float_t  A, Float_t  Z, Float_t Density, Float_t   RadLen)
  : FairMCPoint(trackID, detID, pos, mom, tof, length, eLoss),
    fA(A),
    fZmat(Z),
    fDensity(Density),
    fRadLen(RadLen),
    fXOut ( posOut.X()),
    fYOut ( posOut.Y()),
    fZOut ( posOut.Z()),
    fPxOut ( momOut.Px()),
    fPyOut ( momOut.Py()),
    fPzOut ( momOut.Pz())
{
  /**std ctor*/

}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
FairRadLenPoint::~FairRadLenPoint() { }
// -------------------------------------------------------------------------

void  FairRadLenPoint::Print(const Option_t*) const
{
  /**to be implimented*/


}
ClassImp(FairRadLenPoint)

