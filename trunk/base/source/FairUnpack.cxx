// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairUnpack                            -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#include "FairUnpack.h"


FairUnpack::FairUnpack(Int_t type, Int_t subType)
{
  fType = type;
  fSubType = subType;
}


FairUnpack::~FairUnpack()
{
}


ClassImp(FairUnpack)

