/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairHit.h"


// -----   Default constructor   -------------------------------------------
FairHit::FairHit()
  : FairTimeStamp(),
    fDx(0),
    fDy(0),
    fDz(0),
    fRefIndex(-1),
    fDetectorID(-1),
    fX(0),
    fY(0),
    fZ(0)


{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairHit::FairHit(Int_t detID, TVector3& pos, TVector3& dpos, Int_t index)
  :FairTimeStamp(),
   fDx          (dpos.X()),
   fDy          (dpos.Y()),
   fDz          (dpos.Z()),
   fRefIndex    (index),
   fDetectorID  (detID),
   fX           (pos.X()),
   fY           (pos.Y()),
   fZ           (pos.Z())
{
}


// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
FairHit::~FairHit() { }
// -------------------------------------------------------------------------



ClassImp(FairHit)
