/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    MyPipe file                                -----
// -----                Created by M. Al-Turany  June 2014             -----
// -------------------------------------------------------------------------

#ifndef PIPE_H
#define PIPE_H

#include "FairModule.h"

class MyPipe : public FairModule {
  public:
    MyPipe(const char * name, const char *Title="My Pipe");
    MyPipe();

    virtual ~MyPipe();
    virtual void ConstructGeometry();
   
  ClassDef(MyPipe,1) //MyPIPE

};

#endif //PIPE_H

