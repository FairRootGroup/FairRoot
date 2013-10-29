/**
 * TestDetectorDigiLoader.cxx
 *
 *  @since 2012-04-22
 *  @author A. Rybalchenko
 */

#include "FairTestDetectorDigiLoader.h"
#include "FairMQLogger.h"
#include <iostream>


TestDetectorDigiLoader::TestDetectorDigiLoader() :
  FairMQSamplerTask("Load TestDetectorDigiPixel from rootfile into TestDetectorPayload::TestDetectorDigi")
{
}

TestDetectorDigiLoader::~TestDetectorDigiLoader()
{
}

void TestDetectorDigiLoader::Exec(Option_t* opt)
{
  Int_t nTestDetectorDigis = fInput->GetEntriesFast();
  Int_t size = nTestDetectorDigis * sizeof(TestDetectorPayload::TestDetectorDigi);

  void* buffer = operator new[](size);
  TestDetectorPayload::TestDetectorDigi* ptr = static_cast<TestDetectorPayload::TestDetectorDigi*>(buffer);

  for (Int_t i = 0; i < nTestDetectorDigis; ++i) {
    FairTestDetectorDigi* testDigi = dynamic_cast<FairTestDetectorDigi*>(fInput->At(i));
    if (testDigi != NULL) {
      new(&ptr[i]) TestDetectorPayload::TestDetectorDigi();
      ptr[i] = TestDetectorPayload::TestDetectorDigi();
      ptr[i].fX = testDigi->GetX();
      ptr[i].fY = testDigi->GetY();
      ptr[i].fZ = testDigi->GetZ();
      ptr[i].fTimeStamp = testDigi->GetTimeStamp();
      //std::cout << "Digi: " << ptr[i].fX << "|" << ptr[i].fY << "|" << ptr[i].fZ << "|" << ptr[i].fTimeStamp << ";" << std::endl;
    } else {
      continue;
    }
  }

  fOutput->GetMessage()->rebuild(buffer, size, &FairMQSamplerTask::ClearOutput);

  //std::cout << "Loaded " << fOutput->Size() << " bytes (" << nTestDetectorDigis << " entries)." << std::endl;
}
