/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef MAGNET_H
#define MAGNET_H

#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>  // for Bool_t
#include <string>     // for string
#include <iosfwd>        // for string

#include "FairModule.h"  // for FairModule

class TBuffer;
class TClass;
class TMemberInspector;

class FairMagnet : public FairModule
{
  public:
    FairMagnet(const char* name, const char* Title = "PND Magnet");
    FairMagnet();
    virtual ~FairMagnet();
    void ConstructGeometry();
    void ConstructASCIIGeometry();
    Bool_t IsSensitive(const std::string& name);

    virtual FairModule* CloneModule() const;

  private:
    FairMagnet(const FairMagnet& rhs);
    ClassDef(FairMagnet, 1);
};

#endif   // MAGNET_H
