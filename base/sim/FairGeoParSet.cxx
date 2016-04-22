/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                       FairGeoParSet source file              -----
// -----                Created 06/06/13  by M. Al/Turany              -----
// -------------------------------------------------------------------------

#include "FairGeoParSet.h"
#include "TGeoManager.h"                // for TGeoManager
#include "TObjArray.h"                  // for TObjArray
#include "FairParamList.h"              // for FairParamList

ClassImp(FairGeoParSet)

FairGeoParSet::FairGeoParSet(const char* name,const char* title,const char* context)
  : FairParGenericSet(name,title,context),
    fGeoNodes(new TObjArray()),
    fGeom(0)
{


}


FairGeoParSet::~FairGeoParSet(void)
{
}

void FairGeoParSet::clear(void)
{
  //if(fGeoNodes) { delete fGeoNodes; }
// if(fGeom ) delete fGeom;

}

void FairGeoParSet::putParams(FairParamList* l)
{
  if (!l) { return; }
  l->addObject("FairGeoNodes List", fGeoNodes);
  l->addObject("Detector Geometry", fGeom);
}

Bool_t FairGeoParSet::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }
  if (!l->fillObject("FairGeoNodes List", fGeoNodes)) { return kFALSE; }
  if (!l->fillObject("Detector Geometry", fGeom)) { return kFALSE; }
  return kTRUE;
}


