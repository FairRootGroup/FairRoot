/*
 * FairYPtGenerator.h
 *
 *  Created on: 6 mar 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 *		This generator generates particles by using 2D histogram with distribution of
 *		Y (x-axis) and pt (y-axis).
 */
#ifndef FAIRYPTGENERATOR_H_
#define FAIRYPTGENERATOR_H_

#include "FairGenerator.h"
#include "TH2D.h"

class FairYPtGenerator : public FairGenerator{
  public:
    FairYPtGenerator();
    void SetMultiplicity(Int_t mult) {fMultiplicity = mult;}
    void SetPDGType(Int_t pdg);
    void SetYPt(TH2D *yPt);
    virtual Bool_t Init();
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);
    virtual FairGenerator* CloneGenerator() const;
    virtual ~FairYPtGenerator();
  protected:
    FairYPtGenerator(const FairYPtGenerator &copy);
    FairYPtGenerator& operator=(const FairYPtGenerator &other);
    Int_t GetMultiplicity()const{return fMultiplicity;};
    Int_t GetPDGType()const{return fPdg;};
    Double_t GetMass2()const{return fMass2;};
    void GetYPt(Double_t &y, Double_t &pt);
  private:
    Int_t fPdg; // Particle type
    Int_t fMultiplicity; // Multiplicity
    Double_t fMass2; // M2 of generated particle
    TH2D fYPt;// Y-Pt distribution
    ClassDef(FairYPtGenerator,1)
};

#endif /* CBM_NOV_ANALYSIS_CBMFEMTO_HELPERS_FAIRYPTGENERATOR_H_ */
