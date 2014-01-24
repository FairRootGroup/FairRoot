#include <iostream>

#include "FairTestDetectorMQRecoTask.h"

#include "FairTestDetectorHit.h"
#include "FairTestDetectorDigi.h"

#include "FairRootManager.h"
#include "TMath.h"
#include "TClonesArray.h"

using std::cout;
using std::endl;

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
  int inputSize = msg->GetSize();
  int numInput = inputSize / sizeof(TestDetectorPayload::TestDetectorDigi);
  TestDetectorPayload::TestDetectorDigi* input = reinterpret_cast<TestDetectorPayload::TestDetectorDigi*>(msg->GetData());

  fRecoTask->fDigiArray->Delete();

  for (int i = 0; i < numInput; ++i) {
    new ((*fRecoTask->fDigiArray)[i]) FairTestDetectorDigi(input[i].fX, input[i].fY ,input[i].fZ, input[i].fTimeStamp);
  }

  if (!fRecoTask->fDigiArray) {
    cout << "-W- FairTestDetectorMQRecoTask::Init: " << "No Point array!" << endl;
  }

  fRecoTask->Exec(opt);

  int numOutput = numInput;
  int outputSize = numOutput * sizeof(TestDetectorPayload::TestDetectorHit);

  msg->Rebuild(outputSize);
  TestDetectorPayload::TestDetectorHit* output = reinterpret_cast<TestDetectorPayload::TestDetectorHit*>(msg->GetData());

  if (inputSize > 0) {
    for (int i = 0; i < numOutput; ++i) {
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
}

