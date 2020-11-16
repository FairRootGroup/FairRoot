/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                FairConstFieldCreator header file              -----
// -----                Created 12/11/2020  by R. Karabowicz           -----
// -------------------------------------------------------------------------

#ifndef FairConstFieldCreator_H
#define FairConstFieldCreator_H

#include "FairFieldFactory.h"

class FairConstPar;

class FairField;

class FairConstFieldCreator : public FairFieldFactory
{

  public:
    FairConstFieldCreator();
    virtual ~FairConstFieldCreator();
    virtual FairField* createFairField();
    virtual void SetParm();
    ClassDef(FairConstFieldCreator, 1);

  protected:
    FairConstPar* fFieldPar;

  private:
    FairConstFieldCreator(const FairConstFieldCreator&);
    FairConstFieldCreator& operator=(const FairConstFieldCreator&);
};
#endif   // FairConstFieldCreator_H
