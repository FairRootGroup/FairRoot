/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 FairVolumeList  source file                   -----
// -----          Created 12/01/04  by M. Al-Turany                    -----
// -------------------------------------------------------------------------

#include "FairVolumeList.h"

#include "FairVolume.h"                 // for FairVolume
#include "FairLogger.h"                 // for logging

//_____________________________________________________________________________

FairVolumeList::FairVolumeList()
  :TObject(),
   fData(new TObjArray())
{
}

//_____________________________________________________________________________
FairVolumeList::~FairVolumeList()
{
  if (fData) {
    fData->Delete();
    delete fData;
  }
}

//_____________________________________________________________________________
FairVolume* FairVolumeList::getVolume(TString* name)
{

  TObject* obj = findObject(* name);
  if (obj) { 
    LOG(INFO) << "FairVolume getVolume " << name->Data() 
	      << "found" << FairLogger::endl; 
  }

  return static_cast<FairVolume*>(obj);
}

//_____________________________________________________________________________
Int_t FairVolumeList::getVolumeId(TString* name)
{
  FairVolume* vol = getVolume(name);

  if (vol) {
    return vol->getVolumeId();
  } else {
    return -111;
  }
}



//_____________________________________________________________________________
FairVolume* FairVolumeList::findObject(TString name)
{
  FairVolume* obj = NULL;

  for (int i = 0; i < fData->GetEntriesFast(); i++) {
    obj = static_cast<FairVolume*>(fData->At(i));
    if (obj) {
      if (obj->GetName() == name) { 
	return static_cast<FairVolume*>(obj); 
      }
    }
  }

  return NULL;
}

//_____________________________________________________________________________
void FairVolumeList::addVolume(FairVolume* elem)
{

  FairVolume* v= static_cast<FairVolume*>(findObject(elem->GetName()));

  if (v) {
    LOG(ERROR) << "FairVolumeList element: " << elem->GetName() 
	       << " VolId : " << elem->getVolumeId() 
	       << " already defined " << v->getVolumeId() 
	       << FairLogger::endl; 
  } else {
    fData->Add(elem);
  }
}

ClassImp(FairVolumeList)



