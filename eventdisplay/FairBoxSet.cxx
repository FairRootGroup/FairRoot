// -------------------------------------------------------------------------
// -----                        FairBoxSet source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairBoxSet.h"

// -----   Standard constructor   ------------------------------------------
FairBoxSet::FairBoxSet(FairBoxSetDraw* drawer, const char* name, const char* t)
  : TEveBoxSet(name, t), fDraw(drawer)
{}

ClassImp(FairBoxSet)


