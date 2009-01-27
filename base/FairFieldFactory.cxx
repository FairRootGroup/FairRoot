#include "FairFieldFactory.h"

FairFieldFactory * FairFieldFactory::fgRinstance= 0;


FairFieldFactory::FairFieldFactory()
 :fCreator(0)
{
  
  fgRinstance=this;
}

FairFieldFactory::~FairFieldFactory()
{
}

FairFieldFactory * FairFieldFactory::Instance()
{
         
     return fgRinstance;
}


ClassImp(FairFieldFactory) 







