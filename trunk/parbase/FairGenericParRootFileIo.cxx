//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

//////////////////////////////////////////////////////////////////////////////
// FairGenericParRootFileIo
//
// Interface class to ROOT file for input/output of parameters derived
// from FairParGenericSet
//////////////////////////////////////////////////////////////////////////////

#include "FairGenericParRootFileIo.h"

ClassImp(FairGenericParRootFileIo)

FairGenericParRootFileIo::FairGenericParRootFileIo(FairParRootFile* f) : FairDetParRootFileIo(f)
{
  // constructor
  // sets the name of the I/O class "FairGenericParIo"
  // gets the pointer to the ROOT file
  fName="FairGenericParIo";
}

Bool_t FairGenericParRootFileIo::init(FairParSet* pPar)
{
  // calls FairDetParRootFileIo"::read(FairParSet*)
  if (!pFile) { return kFALSE; }
  return FairDetParRootFileIo::read(pPar);
}
