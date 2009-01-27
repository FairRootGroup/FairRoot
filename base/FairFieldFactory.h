// -------------------------------------------------------------------------
// -----                    FairFieldFactory header file                  -----
// -----                Created 15/01/07  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef CBMFIELDFACTORY_H
#define CBMFIELDFACTORY_H

#include "FairField.h"

class FairFieldFactory {

public:
    static FairFieldFactory *Instance();
    FairFieldFactory();
    virtual ~FairFieldFactory();
    virtual FairField* createFairField() {
	FairField* field=0;
    	if(fCreator) field= fCreator->createFairField();
	return field;
    };
    virtual void SetParm(){
    	if(fCreator) fCreator->SetParm();
    } 

protected:
    FairFieldFactory *fCreator;
    static FairFieldFactory*  fgRinstance;

    ClassDef(FairFieldFactory,1) 
private:
    FairFieldFactory(const FairFieldFactory &M);
    FairFieldFactory& operator= (const  FairFieldFactory&) {return *this;}

};
#endif //CBMFIELDFACTORY_H







