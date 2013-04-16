#include "FairTutorialDet4Hit.h"

FairTutorialDet4Hit::FairTutorialDet4Hit()
  : FairHit()
{
}

FairTutorialDet4Hit::FairTutorialDet4Hit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos)
  : FairHit(detID, pos, dpos, mcindex)
{
}

FairTutorialDet4Hit::~FairTutorialDet4Hit()
{
}

ClassImp(FairTutorialDet4Hit)
