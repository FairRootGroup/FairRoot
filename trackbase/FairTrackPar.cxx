/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
//      Created by M. Al-Turany  06.02.2007
// -------------------------------------------------------------------------

#include "FairTrackPar.h"
#include "TMath.h"
#include "FairLogger.h"
#include "FairRunAna.h"					// for GetFieldValue
#include "FairField.h"

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
    fq  (1)
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
    fq  (q)
{

  Double_t p=TMath::Sqrt(fPx*fPx +fPy*fPy +fPz*fPz );
  if (p!=0) { fQp = q/p; }


}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTrackPar::~FairTrackPar() {}
// -------------------------------------------------------------------------

// -----   Public method Print   -------------------------------------------
void FairTrackPar::Print(Option_t* /*option*/) const
{
  gLogger->Info(MESSAGE_ORIGIN,"Position :(%f,%f,%f)",fX,fY,fZ);
  gLogger->Info(MESSAGE_ORIGIN,"Momentum :(%f,%f,%f)",fPx,fPy,fPz);
}

void FairTrackPar::GetFieldValue(const Double_t point[3], Double_t* bField)
{
	FairRunAna* fRun = FairRunAna::Instance();
	if (fRun->GetField() != 0)
		fRun->GetField()->GetFieldValue(point, bField);
	else {
		bField[0] = .0;
		bField[1] = .0;
		bField[2] = .0;
	}
}

ClassImp(FairTrackPar)






