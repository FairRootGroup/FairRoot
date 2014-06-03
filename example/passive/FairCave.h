/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef Cave_H
#define Cave_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for FairCave::Class, ClassDef, etc

class FairCave : public FairModule
{
  public:
    FairCave(const char* name, const char* Title="Exp Cave");
    FairCave();
    virtual ~FairCave();
    virtual void ConstructGeometry();


  private:
    Double_t world[3];
    ClassDef(FairCave,1) //PNDCaveSD
};

#endif //Cave_H

