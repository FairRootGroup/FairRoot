/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----              FairFieldFactory source file                     -----
// -----          Created 12/01/04  by   M. Al-Turany                  -----
// -------------------------------------------------------------------------


#include "FairFieldFactory.h"

FairFieldFactory* FairFieldFactory::fgRinstance= 0;


FairFieldFactory::FairFieldFactory()
  :fCreator(0)
{

  fgRinstance=this;
}

FairFieldFactory::~FairFieldFactory()
{
}

FairFieldFactory* FairFieldFactory::Instance()
{

  return fgRinstance;
}


ClassImp(FairFieldFactory)







