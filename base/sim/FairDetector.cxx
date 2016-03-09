/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    FairDetector source file                   -----
// -----            Created 06/01/04  by M. Al-Turany/ D. Bertini      -----
// -------------------------------------------------------------------------

#include "FairDetector.h"

#include "FairGeoNode.h"                // for FairGeoNode
#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "FairModule.h"                 // for FairModule::svList, etc
#include "FairVolume.h"                 // for FairVolume

#include "TFolder.h"                    // for TFolder
#include "TList.h"                      // for TList
#include "TObject.h"                    // for TObject
#include "TROOT.h"                      // for TROOT, gROOT
#include "TRefArray.h"                  // for TRefArray
#include "TString.h"                    // for TString
#include "TVirtualMC.h"                 // for TVirtualMC, gMC

#include <stddef.h>                     // for NULL
// -------------------------------------------------------------------------

FairDetector::FairDetector(const char* Name, Bool_t Active, Int_t DetId )
  :FairModule(Name, "FAIR Detector", Active),
   fDetId(DetId),
   fLogger(FairLogger::GetLogger())
{
  flGeoPar = new TList();
  TString lname( GetName());
  lname += "GeoPar";
  flGeoPar->SetName(lname.Data());
  kGeoSaved = kFALSE;


}
// -------------------------------------------------------------------------

FairDetector::FairDetector(const FairDetector& rhs)
  :FairModule(rhs),
   fDetId(rhs.fDetId),
   fLogger(rhs.fLogger)
{
}
// -------------------------------------------------------------------------

FairDetector::~FairDetector()
{

  if ( flGeoPar ) { delete flGeoPar; }

}
// -------------------------------------------------------------------------

FairDetector& FairDetector::operator= (const FairDetector& rhs)
{
  // check assignment to self
  if (this == &rhs) return *this;

  // base class assignment
  FairModule::operator=(rhs);

  // assignment operator
  fDetId = rhs.fDetId;
  fLogger = rhs.fLogger;

  return *this;
}

// -------------------------------------------------------------------------

FairDetector::FairDetector()
  :fDetId(0),
   fLogger(FairLogger::GetLogger())
{

}
// -------------------------------------------------------------------------

void   FairDetector::Initialize()
{
// Registers hits collection in Root manager;
// sets sensitive volumes.
// ---
  Int_t NoOfEntries=svList->GetEntries();
  Int_t fMCid;
  FairGeoNode* fN;
  TString cutName;
  TString copysign="#";
  for (Int_t i = 0 ; i < NoOfEntries ; i++ )  {
    FairVolume* aVol = static_cast<FairVolume*>(svList->At(i));
    cutName = aVol->GetName();
    Ssiz_t pos = cutName.Index (copysign, 1);
    if(pos>1) { cutName.Resize(pos); }
    if ( aVol->getModId() == GetModId()  ) {
      fMCid=gMC->VolId(cutName.Data());
      aVol->setMCid(fMCid);
      fN=aVol->getGeoNode();
      if (fN) { fN->setMCid(fMCid); }
    }
  }

}
// -------------------------------------------------------------------------

void FairDetector::SaveGeoParams()
{

  if ( ! kGeoSaved  ) {
    fLogger->Info(MESSAGE_ORIGIN,"Detector: %s Geometry parameters saved ... ", GetName());
    TFolder* mf = dynamic_cast<TFolder*>(gROOT->FindObjectAny("cbmroot")) ;
    TFolder* stsf = NULL;
    if (mf ) { stsf = dynamic_cast<TFolder*> (mf->FindObjectAny(GetName())); }
    if (stsf) {
      TFolder* newf = stsf->AddFolder("Parameters","Detector parameters",NULL);
      newf->Add( flGeoPar ) ;
    }
    kGeoSaved = kTRUE;
  }
}
// -------------------------------------------------------------------------


ClassImp(FairDetector)




