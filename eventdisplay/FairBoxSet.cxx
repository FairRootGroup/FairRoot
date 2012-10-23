// -------------------------------------------------------------------------
// -----                        FairBoxSet source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairBoxSet.h"
#include "FairBoxSetDraw.h"

#include <iostream>
using std::cout;
using std::endl;

// -----   Standard constructor   ------------------------------------------
FairBoxSet::FairBoxSet(FairBoxSetDraw* drawer, const char* name, const char* t)
  : TEveBoxSet(name, t), fDraw(drawer)
{}

ClassImp(FairBoxSet)


