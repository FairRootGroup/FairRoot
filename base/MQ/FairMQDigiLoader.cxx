/**
 * FairMQDigiLoader.cxx
 *
 *  @since 2012-04-22
 *  @author A. Rybalchenko
 */


/*
#include "FairMQDigiLoader.h"
#include "FairMQLogger.h"
#include <iostream>


FairMQDigiLoader::FairMQDigiLoader() :
  FairMQSamplerTask("Load Detector Digis from rootfile into FairMQPayload::TestDetectorDigi")
{
}

FairMQDigiLoader::~FairMQDigiLoader()
{
}

void FairMQDigiLoader::Exec(Option_t* opt)
{
  int nDigis = fInput->GetEntriesFast();
  int size = nDigis * sizeof(FairMQPayload::TestDetectorDigi);
  
  fOutput = fTransportFactory->CreateMessage(size);
  FairMQPayload::TestDetectorDigi* ptr = reinterpret_cast<FairMQPayload::TestDetectorDigi*>(fOutput->GetData());

  for (Int_t i = 0; i < nDigis; ++i) 
  {
    FairMQDigi* digi = reinterpret_cast<FairMQDigi*>(fInput->At(i));
    if (!digi) continue;

    new(&ptr[i]) FairMQPayload::TestDetectorDigi();
    ptr[i] = FairMQPayload::TestDetectorDigi();
    ptr[i].fX = digi->GetX();
    ptr[i].fY = digi->GetY();
    ptr[i].fZ = digi->GetZ();
    ptr[i].fTimeStamp = digi->GetTimeStamp();
  }

  //std::cout << "Loaded " << fOutput->Size() << " bytes (" << NDigis << " entries)." << std::endl;
}


 */
 