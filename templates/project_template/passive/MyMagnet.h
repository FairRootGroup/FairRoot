/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    MyMagnet  file                               -----
// -----                Created 26/03/14  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef MAGNET_H
#define MAGNET_H

#include "FairModule.h"                 // for FairModule
#include "Rtypes.h"                     // for MyMagnet::Class, Bool_t, etc
#include <string>                       // for string

class MyMagnet : public FairModule
{
  public:
    MyMagnet(const char* name, const char* Title="MY Magnet");
    MyMagnet();
    virtual ~MyMagnet();
    void ConstructGeometry();
    ClassDef(MyMagnet,1)

};

#endif //MAGNET_H

