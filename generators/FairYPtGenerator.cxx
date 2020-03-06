/*
 * FairYPtGenerator.cxx
 *
 *  Created on: 6 mar 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairYPtGenerator.h"
#include "FairPrimaryGenerator.h"
#include "FairLogger.h"
#include <TLorentzVector.h>
#include <TDatabasePDG.h>
#include <TParticlePDG.h>
#include <TRandom.h>

FairYPtGenerator::FairYPtGenerator():
  FairGenerator(),
  fPdg(211),fMultiplicity(1),
  fMass2(0.13957018*0.13957018),
  fYPt(){

}

FairYPtGenerator::FairYPtGenerator(const FairYPtGenerator &copy):
  FairGenerator(copy),
  fPdg(copy.fPdg),fMultiplicity(copy.fMultiplicity),
  fMass2(copy.fMass2),
  fYPt(*(TH2D*)copy.Clone()){
}

FairYPtGenerator& FairYPtGenerator::operator =(const FairYPtGenerator &other) {
  if (this == &other) return *this;
  TNamed::operator=(other);
  fPdg = other.fPdg;
  fMultiplicity = other.fMultiplicity;
  fMass2 = other.fMass2;
  fYPt = *static_cast<TH2D*>(other.fYPt.Clone());
  return *this;
}

void FairYPtGenerator::SetYPt(TH2D *yPt) {
  fYPt = *static_cast<TH2D*>(yPt->Clone());
}

Bool_t FairYPtGenerator::Init() {
  fYPt.ResetStats();
  for(int i=1;i<=fYPt.GetNbinsX();i++){
    for(int j=1;j<fYPt.GetNbinsY();j++){
      if(fYPt.GetBinContent(i,j)<0){
        LOG(error)<<"FairYPtGenerator negative entries !";
        return kFALSE;
      }
    }
  }
  if(fMass2<0){
    LOG(error)<<"FairYPtGenerator negative mass !";
    return kFALSE;
  }
  if(fYPt.GetEntries()==0){
    LOG(error)<<"FairYPtGenerator lack  entries !";
    return kFALSE;
  }
  if(fMultiplicity<=0){
    LOG(error)<<"FairYPtGenerator bad multiplicity  !";
    return kFALSE;
  }
  return kTRUE;
}

Bool_t FairYPtGenerator::ReadEvent(FairPrimaryGenerator *primGen) {
  Double_t pt, y;
  for(int i=0;i<fMultiplicity;i++){
    fYPt.GetRandom2(y,pt);
    Double_t e = TMath::Sqrt(pt*pt+fMass2);
    Double_t phi = gRandom->Uniform(-TMath::Pi(),TMath::Pi());
    Double_t pz  = TMath::Sign(e*0.5,y)*TMath::Exp(-y)*(TMath::Exp(2.0*y)-1.0);
    Double_t px = pt*TMath::Cos(phi);
    Double_t py = pt*TMath::Sin(phi);
    primGen->AddTrack(fPdg, px, py, pz, 0, 0, 0);
  }
  return kTRUE;
}

FairGenerator* FairYPtGenerator::CloneGenerator() const {
  return new FairYPtGenerator(*this);
}

void FairYPtGenerator::SetPDGType(Int_t pdg) {
  fPdg = pdg;
  TDatabasePDG *db = TDatabasePDG::Instance();
  TParticlePDG *p = db->GetParticle(pdg);
  if(p==nullptr){
    fMass2 = -1;
  }else{
    fMass2 = p->Mass()*p->Mass();
  }
}

void FairYPtGenerator::GetYPt(Double_t &y, Double_t &pt) {
  fYPt.GetRandom2(y,pt);
}

FairYPtGenerator::~FairYPtGenerator() {
}


