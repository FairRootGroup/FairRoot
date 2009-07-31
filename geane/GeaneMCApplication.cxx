#include "GeaneMCApplication.h"
#include "TVirtualMC.h"
#include <iostream>
#include "TSystem.h"

GeaneMCApplication::GeaneMCApplication()
{

  //gMC->Init();
  //gMC->BuildPhysics();

}

void GeaneMCApplication::InitMC(){
  gMC->Init();
  gMC->BuildPhysics();
}

void GeaneMCApplication::Field(const Double_t* x, Double_t* b) const
{
  b[0]=0;
  b[1]=0;
  b[2]=20.;
  std::cout <<"FIELD"<<std::endl;
}


ClassImp(GeaneMCApplication)


