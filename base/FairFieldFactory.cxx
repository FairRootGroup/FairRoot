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







