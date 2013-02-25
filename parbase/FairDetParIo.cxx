//*-- AUTHOR : Ilse Koenig
//*-- Created : 20/10/2004
#include "FairDetParIo.h"
/////////////////////////////////////////////////////////////
//  FairDetParIo
//
//  Abstract class for parameter input/output needed by a
//  detector
/////////////////////////////////////////////////////////////
FairDetParIo::FairDetParIo()
  :TNamed(),
   inputNumber(0)
{
}

ClassImp(FairDetParIo)

