#ifndef FAIRTUTORIALDERTHIT_H
#define FAIRTUTORIALDETHIT_H 1


#include "FairHit.h"

class TVector3;

class FairTutorialDetHit : public FairHit
{

  public:

    /** Default constructor **/
    FairTutorialDetHit();
    FairTutorialDetHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos);

    /** Destructor **/
    virtual ~FairTutorialDetHit();

  private:

    FairTutorialDetHit(const FairTutorialDetHit&);
    FairTutorialDetHit operator=(const FairTutorialDetHit&);

    ClassDef(FairTutorialDetHit,1);

};
#endif
