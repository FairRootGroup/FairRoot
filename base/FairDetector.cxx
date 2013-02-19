// -------------------------------------------------------------------------
// -----                    FairDetector source file                   -----
// -----            Created 06/01/04  by M. Al-Turany/ D. Bertini      -----
// -------------------------------------------------------------------------



#include "FairDetector.h"


#include "FairModule.h"
#include "FairVolume.h"
#include "FairGeoNode.h"
#include "FairLogger.h"


#include "TVirtualMC.h"
#include "TString.h"
#include "TFolder.h"
#include "TROOT.h"
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

FairDetector::~FairDetector()
{

  if ( flGeoPar ) { delete flGeoPar; }

}
// -------------------------------------------------------------------------

FairDetector::FairDetector()
  :fDetId(0)
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
    FairVolume* aVol = (FairVolume*) svList->At(i);
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
    TFolder* mf = (TFolder*) gROOT->FindObjectAny("cbmroot");
    TFolder* stsf = NULL;
    if (mf ) { stsf = (TFolder*) mf->FindObjectAny(GetName()); }
    if (stsf) {
      TFolder* newf = stsf->AddFolder("Parameters","Detector parameters",NULL);
      newf->Add( flGeoPar ) ;
    }
    kGeoSaved = kTRUE;
  }
}
// -------------------------------------------------------------------------


ClassImp(FairDetector)




