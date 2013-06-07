/**
 * TestDetectorDigiLoader.cxx
 *
 *  @since 2012-04-22
 *  @author A. Rybalchenko
 */

#include "TestDetectorDigiLoader.h"
//#include "FairMQLogger.h"

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
    FairTestDetectorDigi* testDigi = (FairTestDetectorDigi*) fInput->At(i);
    if (testDigi != NULL) {
      new(&ptr[i]) TestDetectorPayload::TestDetectorDigi();
      ptr[i] = TestDetectorPayload::TestDetectorDigi();
      ptr[i].fX = testDigi->GetX();
      ptr[i].fY = testDigi->GetY();
      ptr[i].fZ = testDigi->GetZ();
    } else {
      continue;
    }
  }

  FairMQMessage* event = new FairMQMessage(buffer, size, NULL);
  fOutput->push_back(event);
  //std::stringstream logmsg;
  //logmsg << "loaded " << event->Size() << " bytes (" << nTestDetectorDigis << "entries).";
  //FairMQLogger::GetInstance()->Log(FairMQLogger::DEBUG, logmsg.str());
}

//ClassImp(TestDetectorDigiLoader)
