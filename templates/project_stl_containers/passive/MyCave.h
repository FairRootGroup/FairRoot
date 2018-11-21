/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    MyCave  file                               -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef Cave_H
#define Cave_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for MyCave::Class, ClassDef, etc

class MyCave : public FairModule
{
  public:
    MyCave(const char* name, const char* Title="Exp Cave");
    MyCave();
    virtual ~MyCave();
    virtual void ConstructGeometry();

    virtual FairModule* CloneModule() const;

  private:
    Double_t world[3];

    MyCave(const MyCave&);
    MyCave& operator=(const MyCave&);

    ClassDef(MyCave,1) //PNDCaveSD
};

#endif //Cave_H

