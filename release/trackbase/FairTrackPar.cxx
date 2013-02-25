// -------------------------------------------------------------------------
//      Created by M. Al-Turany  06.02.2007
// -------------------------------------------------------------------------

#include "FairTrackPar.h"
#include "TMath.h"
#include "FairLogger.h"

using namespace std;

// -----   Default constructor   -------------------------------------------
FairTrackPar::FairTrackPar()
  : TObject(),
    fX (0.),
    fY (0.),
    fZ (0.),
    fDX (0.),
    fDY (0.),
    fDZ (0.),
    fPx (0.),
    fPy (0.),
    fPz (0.),
    fDPx (0.),
    fDPy (0.),
    fDPz (0.),
    fQp (0.),
    fDQp (0.),
    fq  (1),
    fLogger(FairLogger::GetLogger())
{


}
// -------------------------------------------------------------------------

// -----   Constructor with parameters   -----------------------------------
FairTrackPar::FairTrackPar(Double_t x, Double_t y, Double_t z,
                           Double_t px, Double_t py, Double_t pz, Int_t q)

  : TObject(),
    fX (x),
    fY (y),
    fZ (z),
    fDX (x),
    fDY (y),
    fDZ (z),
    fPx (px),
    fPy (py),
    fPz (pz),
    fDPx (px),
    fDPy (py),
    fDPz (pz),
    fQp (0.),
    fDQp (0.),
    fq  (q),
    fLogger(FairLogger::GetLogger())
{

  Double_t p=TMath::Sqrt(fPx*fPx +fPy*fPy +fPz*fPz );
  if (p!=0) { fQp = q/p; }


}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTrackPar::~FairTrackPar() {}
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void FairTrackPar::Print(Option_t* option) const
{
  fLogger->Info(MESSAGE_ORIGIN,"Position :(%f,%f,%f)",fX,fY,fZ);
  fLogger->Info(MESSAGE_ORIGIN,"Momentum :(%f,%f,%f)",fPx,fPy,fPz);
}

ClassImp(FairTrackPar)






