#include "FairTutorialDetHit.h"

FairTutorialDetHit::FairTutorialDetHit()
  : FairHit()
{
}

FairTutorialDetHit::FairTutorialDetHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos)
  : FairHit(detID, pos, dpos, mcindex)
{
}

FairTutorialDetHit::~FairTutorialDetHit()
{
}

ClassImp(FairTutorialDetHit)
