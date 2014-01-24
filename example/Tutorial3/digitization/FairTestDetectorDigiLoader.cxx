/**
 * TestDetectorDigiLoader.cxx
 *
 * @since 2012-04-22
 * @author A. Rybalchenko
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
  int nTestDetectorDigis = fInput->GetEntriesFast();
  int size = nTestDetectorDigis * sizeof(TestDetectorPayload::TestDetectorDigi);

  fOutput = fTransportFactory->CreateMessage(size);
  TestDetectorPayload::TestDetectorDigi* ptr = reinterpret_cast<TestDetectorPayload::TestDetectorDigi*>(fOutput->GetData());

  for (int i = 0; i < nTestDetectorDigis; ++i) {
    FairTestDetectorDigi* testDigi = reinterpret_cast<FairTestDetectorDigi*>(fInput->At(i));
    if (!testDigi) continue;

    new(&ptr[i]) TestDetectorPayload::TestDetectorDigi();
    ptr[i] = TestDetectorPayload::TestDetectorDigi();
    ptr[i].fX = testDigi->GetX();
    ptr[i].fY = testDigi->GetY();
    ptr[i].fZ = testDigi->GetZ();
    ptr[i].fTimeStamp = testDigi->GetTimeStamp();
  }

  //cout << "Loaded " << fOutput->GetSize() << " bytes (" << nTestDetectorDigis << " entries)." << endl;
}
