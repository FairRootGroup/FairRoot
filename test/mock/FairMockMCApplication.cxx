# include "FairMockMCApplication.h"

FairMockMCApplication::FairMockMCApplication(const char* name, const char* title)
  :TVirtualMCApplication(name,title)
{
}

FairMockMCApplication::FairMockMCApplication()
  :TVirtualMCApplication()
{
}

FairMockMCApplication::~FairMockMCApplication()
{
  delete gMC;
  gMC=0;
}


ClassImp(FairMockMCApplication)
