/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    FairFieldFactory header file                  -----
// -----                Created 15/01/07  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef FAIRFIELDFACTORY_H
#define FAIRFIELDFACTORY_H

#include "Rtypes.h"                     // for FairFieldFactory::Class, etc

class FairField;

class FairFieldFactory
{

  public:
    static FairFieldFactory* Instance();
    FairFieldFactory();
    virtual ~FairFieldFactory();
    virtual FairField* createFairField() {
      FairField* field=0;
      if(fCreator) { field= fCreator->createFairField(); }
      return field;
    };
    virtual void SetParm() {
      if(fCreator) { fCreator->SetParm(); }
    }

  protected:
    FairFieldFactory* fCreator;
    static FairFieldFactory*  fgRinstance;

    ClassDef(FairFieldFactory,1)
  private:
    FairFieldFactory(const FairFieldFactory& M);
    FairFieldFactory& operator= (const  FairFieldFactory&) {return *this;}

};
#endif //FAIRFIELDFACTORY_H







