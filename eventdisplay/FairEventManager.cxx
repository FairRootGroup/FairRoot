//______________________________________________________________________________
/** FairEventManager
*  class for event management and navigation.
*  M. Al-Turany 06.12.2007
**/

#include "FairEventManager.h"

#include "FairRootManager.h"
#include "FairRunAna.h"

#include "TEveManager.h"
#include "TEveGeoNode.h"
#include "TGeoManager.h"
#include "TDatabasePDG.h"

ClassImp(FairEventManager)

FairEventManager* FairEventManager::fgRinstance= 0;
//_____________________________________________________________________________
FairEventManager* FairEventManager::Instance()
{

  return fgRinstance;
}
//______________________________________________________________________________
FairEventManager::FairEventManager()
  :TEveEventManager("FairEventManager", ""),
   fRootManager(FairRootManager::Instance()),
   fEntry(0),
   fRunAna(FairRunAna::Instance()),
   fEvent(0),
   fPriOnly(kFALSE),
   fCurrentPDG(0),
   fMinEnergy(0),
   fMaxEnergy(25),
   fEvtMinEnergy(0),
   fEvtMaxEnergy(10)

{
  fgRinstance=this;
  AddParticlesToPdgDataBase();
}
//______________________________________________________________________________
void FairEventManager::Init()
{
  TEveManager::Create();
  fRunAna->Init();
  if(gGeoManager) {
    TGeoNode* N=  gGeoManager->GetTopNode();
    TEveGeoTopNode* TNod=new  TEveGeoTopNode(gGeoManager, N);
    gEve->AddGlobalElement(TNod);
    gEve->FullRedraw3D(kTRUE);
    fEvent= gEve->AddEvent(this);
  }
}
//______________________________________________________________________________
void FairEventManager::UpdateEditor()
{

}
//______________________________________________________________________________
FairEventManager::~FairEventManager()
{
}
//______________________________________________________________________________
void FairEventManager::Open()
{

}
//______________________________________________________________________________
void FairEventManager::GotoEvent(Int_t event)
{
  fEntry=event;
  fRunAna->Run((Long64_t)event);
}
//______________________________________________________________________________
void FairEventManager::NextEvent()
{
  fEntry+=1;
  fRunAna->Run((Long64_t)fEntry);
}
//______________________________________________________________________________
void FairEventManager::PrevEvent()
{
  fEntry-=1;
  fRunAna->Run((Long64_t)fEntry);
}
//______________________________________________________________________________
void FairEventManager::Close()
{

}

//______________________________________________________________________________

void FairEventManager::DisplaySettings()
{

}

//______________________________________________________________________________
Int_t FairEventManager::Color( int pdg)
{
  switch(pdg) {

  case   22     :
    return  623;    // photon
  case   -2112  :
    return  2 ;   // anti-neutron
  case   -11    :
    return  3;    // e+
  case   -3122  :
    return  4;   // anti-Lambda
  case   11     :
    return  5;    // e-
  case   -3222  :
    return  6;   // Sigma-
  case   12     :
    return  7;    // e-neutrino (NB: flavour undefined by Geant)
  case   -3212  :
    return  8;   // Sigma0
  case   -13    :
    return  9;    // mu+
  case   -3112  :
    return  10;   // Sigma+ (PB)*/
  case   13     :
    return  11;    // mu-
  case   -3322  :
    return  12;   // Xi0
  case   111    :
    return  13;    // pi0
  case   -3312  :
    return  14;   // Xi+
  case   211    :
    return  15;    // pi+
  case   -3334  :
    return  16;   // Omega+ (PB)
  case   -211   :
    return  17;    // pi-
  case   -15    :
    return  18;   // tau+
  case   130    :
    return  19;   // K long
  case   15     :
    return  20;   // tau-
  case   321    :
    return  21;   // K+
  case   411    :
    return  22;   // D+
  case   -321   :
    return  23;   // K-
  case   -411   :
    return  24;   // D-
  case   2112   :
    return  25;   // n
  case   421    :
    return  26;   // D0
  case   2212   :
    return  27;   // p
  case   -421   :
    return  28;   // D0
  case   -2212  :
    return  29;   // anti-proton
  case   431    :
    return  30;   // Ds+
  case   310    :
    return  31;   // K short
  case   -431   :
    return  32;   // anti Ds-
  case   221    :
    return  33;   // eta
  case   4122   :
    return  34;   // Lamba_c+
  case   3122   :
    return  35;   // Lambda
  case   24     :
    return  36;   // W+
  case   3222   :
    return  37;   // Sigma+
  case   -24    :
    return  38;   // W-
  case   3212   :
    return  39;   // Sigma0
  case   23     :
    return  40;   // Z
  case   3112   :
    return  41;   // Sigma-
  case   3322   :
    return  42;   // Xi0
  case   3312   :
    return  43;   // Xi-
  case   3334   :
    return  44;   // Omega- (PB)
  case   50000050   :
    return  801;   // Cerenkov
  case   1000010020  :
    return  45;
  case   1000010030  :
    return  48;
  case   1000020040   :
    return  50;
  case   1000020030   :
    return  55;
  default  :
    return 0;

  }


}
//______________________________________________________________________________

void FairEventManager::AddParticlesToPdgDataBase()
{

//
// Add particles to the PDG data base

  TDatabasePDG* pdgDB = TDatabasePDG::Instance();

  const Double_t kAu2Gev=0.9314943228;
  const Double_t khSlash = 1.0545726663e-27;
  const Double_t kErg2Gev = 1/1.6021773349e-3;
  const Double_t khShGev = khSlash*kErg2Gev;
  const Double_t kYear2Sec = 3600*24*365.25;

// Ions
//

  if ( !pdgDB->GetParticle(1000010020) )
    pdgDB->AddParticle("Deuteron","Deuteron",2*kAu2Gev+8.071e-3,kTRUE,
                       0,3,"Ion",1000010020);

  if ( !pdgDB->GetParticle(1000010030) )
    pdgDB->AddParticle("Triton","Triton",3*kAu2Gev+14.931e-3,kFALSE,
                       khShGev/(12.33*kYear2Sec),3,"Ion",1000010030);

  if ( !pdgDB->GetParticle(1000020040) )
    pdgDB->AddParticle("Alpha","Alpha",4*kAu2Gev+2.424e-3,kTRUE,
                       khShGev/(12.33*kYear2Sec),6,"Ion",1000020040);

  if ( !pdgDB->GetParticle(1000020030) )
    pdgDB->AddParticle("HE3","HE3",3*kAu2Gev+14.931e-3,kFALSE,
                       0,6,"Ion",1000020030);

// Special particles
//
  if ( !pdgDB->GetParticle(50000050) )
    pdgDB->AddParticle("Cherenkov","Cherenkov",0,kFALSE,
                       0,0,"Special",50000050);

  if ( !pdgDB->GetParticle(50000051) )
    pdgDB->AddParticle("FeedbackPhoton","FeedbackPhoton",0,kFALSE,
                       0,0,"Special",50000051);

}
