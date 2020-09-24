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

#include <Rtypes.h>               // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>           // for Double_t, Bool_t
#include <TH2.h>                  // for TH2D

#include "FairBaseMCGenerator.h"  // for FairBaseMCGenerator
#include "TH2D.h"

class FairGenerator;
class FairPrimaryGenerator;
class TBuffer;
class TClass;
class TMemberInspector;

class FairYPtGenerator : public FairBaseMCGenerator
{
  public:
    FairYPtGenerator();
    void SetYPt(const TH2D& yPt);
    virtual Bool_t Init();
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);
    virtual FairGenerator* CloneGenerator() const;
    virtual ~FairYPtGenerator();

  protected:
    FairYPtGenerator(const FairYPtGenerator& base);
    FairYPtGenerator& operator=(const FairYPtGenerator& rhs);
    Double_t GetMass2() const { return GetPDGMass() * GetPDGMass(); };
    void GetYPt(Double_t& y, Double_t& pt);

  private:
    TH2D fYPt;   // Y-Pt distribution
    ClassDef(FairYPtGenerator, 1);
};

#endif /* CBM_NOV_ANALYSIS_CBMFEMTO_HELPERS_FAIRYPTGENERATOR_H_ */
