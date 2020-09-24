/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIPE_H
#define PIPE_H

#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef

#include "FairModule.h"  // for FairModule

class TBuffer;
class TClass;
class TMemberInspector;

class FairPipe : public FairModule
{
  public:
    FairPipe(const char* name, const char* Title = "PND Pipe");
    FairPipe();

    virtual ~FairPipe();
    virtual void ConstructGeometry();

    virtual FairModule* CloneModule() const;

  private:
    FairPipe(const FairPipe& rhs);

    ClassDef(FairPipe, 1);
};

#endif   // PIPE_H
