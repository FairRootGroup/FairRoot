#include "CbmFieldFactory.h"

CbmFieldFactory * CbmFieldFactory::fgRinstance= 0;


CbmFieldFactory::CbmFieldFactory()
 :fCreator(0)
{
  
  fgRinstance=this;
}

CbmFieldFactory::~CbmFieldFactory()
{
}

CbmFieldFactory * CbmFieldFactory::Instance()
{
         
     return fgRinstance;
}


ClassImp(CbmFieldFactory) 







