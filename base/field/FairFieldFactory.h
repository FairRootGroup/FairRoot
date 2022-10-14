/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    FairFieldFactory header file                  -----
// -----                Created 15/01/07  by M. Al-Turany              -----
// -------------------------------------------------------------------------

#ifndef FAIRFIELDFACTORY_H
#define FAIRFIELDFACTORY_H

#include <Rtypes.h>   // for FairFieldFactory::Class, etc

class FairField;

class FairFieldFactory
{
  public:
    static FairFieldFactory* Instance();
    FairFieldFactory();
    virtual ~FairFieldFactory();
    virtual FairField* createFairField() = 0;
    virtual void SetParm() {}

  protected:
    /**
     * \deprecated Deprecated in v19, will be removed in v20.
     */
    [[deprecated]] FairFieldFactory* fCreator;
    static FairFieldFactory* fgRinstance;

    ClassDef(FairFieldFactory, 1);

  private:
    FairFieldFactory(const FairFieldFactory& M);
    FairFieldFactory& operator=(const FairFieldFactory&) { return *this; }
};

#endif   // FAIRFIELDFACTORY_H
