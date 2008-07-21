// ------------------------------------------------------------------------
// -----                  CbmMCEventHeader source file                -----
// -----                                                              -----
// -----    Created 08/12/05                      V. Friese           -----
// ------------------------------------------------------------------------


#include "CbmMCEventHeader.h"



// -----   Default constructor   ------------------------------------------
CbmMCEventHeader::CbmMCEventHeader() 
: TNamed("MCEvent", "MC"), 
  fRunId(0),
  fEventId(0), 
  fX (0.), 
  fY (0.), 
  fZ (0.), 
  fT (0.), 
  fB (0.),
  fNPrim(0),
  fIsSet(kFALSE)

{
}
// ------------------------------------------------------------------------



// -----   Constructor with run identifier   ------------------------------
CbmMCEventHeader::CbmMCEventHeader(UInt_t runId) 
  : TNamed("MCEvent", "MC"), 
    fRunId(runId),
    fEventId(0), 
    fX (0.), 
    fY (0.), 
    fZ (0.), 
    fT (0.), 
    fB (0.),
    fNPrim(0),
    fIsSet(kFALSE)
  
{
}
// ------------------------------------------------------------------------



// -----   Standard constructor   -----------------------------------------
CbmMCEventHeader::CbmMCEventHeader(Int_t iEvent, Double_t x, Double_t y, 
				   Double_t z, Double_t t,Double_t b, 
				   Int_t nPrim)
  : TNamed("MCEvent", "MC"), 
    fRunId(0),
    fEventId(iEvent), 
    fX (x), 
    fY (y), 
    fZ (z), 
    fT (t), 
    fB (b),
    fNPrim(nPrim),
    fIsSet(kFALSE)

{
}
// ------------------------------------------------------------------------



// -----   Destructor   ---------------------------------------------------
CbmMCEventHeader::~CbmMCEventHeader() { }
// ------------------------------------------------------------------------



// -----   Public method Reset   ------------------------------------------
void CbmMCEventHeader::Reset() {
  fEventId = fNPrim = 0;
  fX = fY = fZ = fT = fB = 0.;
  fIsSet = kFALSE;
}
// ------------------------------------------------------------------------

  

ClassImp(CbmMCEventHeader)
