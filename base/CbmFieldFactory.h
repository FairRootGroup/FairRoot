// -------------------------------------------------------------------------
// -----                    CbmFieldFactory header file                  -----
// -----                Created 15/01/07  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef CBMFIELDFACTORY_H
#define CBMFIELDFACTORY_H

#include "CbmField.h"

class CbmFieldFactory {

public:
    static CbmFieldFactory *Instance();
    CbmFieldFactory();
    virtual ~CbmFieldFactory();
    virtual CbmField* createCbmField() {
	CbmField* field=0;
    	if(fCreator) field= fCreator->createCbmField();
	return field;
    };
    virtual void SetParm(){
    	if(fCreator) fCreator->SetParm();
    } 

protected:
    CbmFieldFactory *fCreator;
    static CbmFieldFactory*  fgRinstance;

    ClassDef(CbmFieldFactory,1) 
private:
    CbmFieldFactory(const CbmFieldFactory &M);
    CbmFieldFactory& operator= (const  CbmFieldFactory&) {return *this;}

};
#endif //CBMFIELDFACTORY_H







