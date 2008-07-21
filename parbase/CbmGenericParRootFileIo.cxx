//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

//////////////////////////////////////////////////////////////////////////////
// CbmGenericParRootFileIo
//
// Interface class to ROOT file for input/output of parameters derived
// from CbmParGenericSet
//////////////////////////////////////////////////////////////////////////////

#include "CbmGenericParRootFileIo.h"

ClassImp(CbmGenericParRootFileIo)

CbmGenericParRootFileIo::CbmGenericParRootFileIo(CbmParRootFile* f) : CbmDetParRootFileIo(f) {
  // constructor
  // sets the name of the I/O class "CbmGenericParIo"
  // gets the pointer to the ROOT file
  fName="CbmGenericParIo";
}

Bool_t CbmGenericParRootFileIo::init(CbmParSet* pPar) {
  // calls CbmDetParRootFileIo"::read(CbmParSet*)
  if (!pFile) return kFALSE;
  return CbmDetParRootFileIo::read(pPar); 
}
