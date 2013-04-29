#ifndef PNDTORINODETECTORHIT_H
#define PNDTORINODETECTORHIT_H 1


//#include "TVector3.h"
#include "FairHit.h"

class TVector3;

class FairTestDetectorHit : public FairHit
{

  public:

    /** Default constructor **/
    FairTestDetectorHit();
    FairTestDetectorHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos);

    /** Destructor **/
    virtual ~FairTestDetectorHit();

  private:

    FairTestDetectorHit(const FairTestDetectorHit&);
    FairTestDetectorHit operator=(const FairTestDetectorHit&);

    ClassDef(FairTestDetectorHit,1);

};
#endif
