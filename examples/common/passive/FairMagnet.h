/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef MAGNET_H
#define MAGNET_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for FairMagnet::Class, Bool_t, etc

#include <string>                       // for string

class FairMagnet : public FairModule
{
  public:
    FairMagnet(const char* name, const char* Title="PND Magnet");
    FairMagnet();
    virtual ~FairMagnet();
    void ConstructGeometry();
    void ConstructASCIIGeometry();
    Bool_t CheckIfSensitive(std::string name);

    virtual FairModule* CloneModule() const;

  private:
    FairMagnet(const FairMagnet& rhs);
    ClassDef(FairMagnet,1)
};

#endif //MAGNET_H

