/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef Target_H
#define Target_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for FairTarget::Class, ClassDef, etc

class FairTarget : public FairModule
{
  public:
    FairTarget(const char* name, const char* Title="PND Target");
    FairTarget();
    virtual ~FairTarget();
    virtual void ConstructGeometry();

    virtual FairModule* CloneModule() const;

  private:
    FairTarget(const FairTarget& rhs);
    ClassDef(FairTarget,1)
};

#endif //Target_H

