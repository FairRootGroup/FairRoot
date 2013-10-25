#include <iostream>

#include "FairTestDetectorMQRecoTask.h"

#include "FairTestDetectorHit.h"
#include "FairTestDetectorDigi.h"

#include "FairRootManager.h"
#include "TMath.h"
#include "TClonesArray.h"

// -----   Default constructor   -------------------------------------------
FairTestDetectorMQRecoTask::FairTestDetectorMQRecoTask() :
  fRecoTask(NULL)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairTestDetectorMQRecoTask::FairTestDetectorMQRecoTask(Int_t verbose) :
  fRecoTask(NULL)
{
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
FairTestDetectorMQRecoTask::~FairTestDetectorMQRecoTask()
{
  fRecoTask->fDigiArray->Delete();
  fRecoTask->fHitArray->Delete();
  delete fRecoTask;
}
// -------------------------------------------------------------------------


// -----   Public method Init (abstract in base class)  --------------------
InitStatus FairTestDetectorMQRecoTask::Init()
{
  fRecoTask = new FairTestDetectorRecoTask();
  fRecoTask->fDigiArray = new TClonesArray("FairTestDetectorDigi");
  fRecoTask->fHitArray = new TClonesArray("FairTestDetectorHit");

  return kSUCCESS;

}

// -----   Public method Exec FairMQ interface  --------------------------------------------
void FairTestDetectorMQRecoTask::Exec(FairMQMessage* msg, Option_t* opt)
{
  Int_t inputSize = msg->Size();
  Int_t numInput = inputSize / sizeof(TestDetectorPayload::TestDetectorDigi);
  TestDetectorPayload::TestDetectorDigi* input = static_cast<TestDetectorPayload::TestDetectorDigi*>(msg->GetMessage()->data());

  fRecoTask->fDigiArray->Delete();

  for (Int_t i = 0; i < numInput; ++i) {
    new ((*fRecoTask->fDigiArray)[i]) FairTestDetectorDigi(input[i].fX, input[i].fY ,input[i].fZ, input[i].fTimeStamp);
    //std::cout << "Digi: " << input[i].fX << "|" << input[i].fY << "|" << input[i].fZ << "|" << input[i].fTimeStamp << ";" << std::endl;
  }

  if (!fRecoTask->fDigiArray) {
    std::cout << "-W- FairTestDetectorMQRecoTask::Init: " << "No Point array!" << std::endl;
  }

  fRecoTask->Exec(opt);

  Int_t numOutput = numInput;
  Int_t outputSize = numOutput * sizeof(TestDetectorPayload::TestDetectorHit);
  void* buffer = operator new[](outputSize);
  TestDetectorPayload::TestDetectorHit* output = static_cast<TestDetectorPayload::TestDetectorHit*>(buffer);

  if (inputSize > 0) {

    for (Int_t i = 0; i < numOutput; ++i) {
      FairTestDetectorHit* hit = (FairTestDetectorHit*) fRecoTask->fHitArray->At(i);

      output[i].detID = hit->GetDetectorID();
      output[i].posX = hit->GetX();
      output[i].posY = hit->GetY();
      output[i].posZ = hit->GetZ();
      output[i].dposX = hit->GetDx();
      output[i].dposY = hit->GetDy();
      output[i].dposZ = hit->GetDz();
    }

  }

  msg->GetMessage()->rebuild(buffer, outputSize, &FairMQProcessorTask::ClearOutput);
  //delete[] output;
}

