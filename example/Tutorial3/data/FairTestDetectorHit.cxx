#include "FairTestDetectorHit.h"

FairTestDetectorHit::FairTestDetectorHit()
  : FairHit()
{
}

FairTestDetectorHit::FairTestDetectorHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos)
  : FairHit(detID, pos, dpos, mcindex)
{
}



FairTestDetectorHit::FairTestDetectorHit(const FairTestDetectorHit &Hit) :
  FairHit(Hit)
{
    
}

FairTestDetectorHit::~FairTestDetectorHit()
{
}

ClassImp(FairTestDetectorHit)
