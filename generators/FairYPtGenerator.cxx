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
  FairBaseMCGenerator(),
  fYPt(){

}

FairYPtGenerator::FairYPtGenerator(const FairYPtGenerator &copy):
  FairBaseMCGenerator(copy),
  fYPt(*(TH2D*)copy.Clone()){
}

FairYPtGenerator& FairYPtGenerator::operator =(const FairYPtGenerator &other) {
  if (this == &other) return *this;
  FairBaseMCGenerator::operator=(other);
  fYPt = *static_cast<TH2D*>(other.fYPt.Clone());
  return *this;
}

void FairYPtGenerator::SetYPt(const TH2D &yPt) {
  yPt.Copy(fYPt);
  fYPt.SetDirectory(0x0);
}

Bool_t FairYPtGenerator::Init() {
  if(FairBaseMCGenerator::Init()==kFALSE)return kFALSE;
  fYPt.ResetStats();
  for(int i=1;i<=fYPt.GetNbinsX();i++){
    for(int j=1;j<fYPt.GetNbinsY();j++){
      if(fYPt.GetBinContent(i,j)<0){
        LOG(error)<<"FairYPtGenerator negative entries !";
        return kFALSE;
      }
    }
  }
  if(fYPt.GetEntries()==0){
    LOG(error)<<"FairYPtGenerator lack  entries !";
    return kFALSE;
  }
  return kTRUE;
}

Bool_t FairYPtGenerator::ReadEvent(FairPrimaryGenerator *primGen) {
  Double_t pt, y;
  GenerateEventParameters();
  for(int i=0;i<GetMultiplicity();i++){
    fYPt.GetRandom2(y,pt);
    Double_t e = TMath::Sqrt(pt*pt+GetMass2());
    Double_t phi = gRandom->Uniform(-TMath::Pi(),TMath::Pi());
    Double_t pz  = TMath::Sign(e*0.5,y)*TMath::Exp(-y)*(TMath::Exp(2.0*y)-1.0);
    Double_t px = pt*TMath::Cos(phi);
    Double_t py = pt*TMath::Sin(phi);
    primGen->AddTrack(GetPDGType(), px, py, pz, fX, fY, fZ);
  }
  return kTRUE;
}

FairGenerator* FairYPtGenerator::CloneGenerator() const {
  return new FairYPtGenerator(*this);
}

void FairYPtGenerator::GetYPt(Double_t &y, Double_t &pt) {
  fYPt.GetRandom2(y,pt);
}

FairYPtGenerator::~FairYPtGenerator() {
}


