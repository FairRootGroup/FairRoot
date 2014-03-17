#include <iostream>

#include "FairTestDetectorMQRecoTask.h"

#include "FairTestDetectorHit.h"
#include "FairTestDetectorDigi.h"

#include "FairTestDetectorPayload.h"

#ifdef PROTOBUF
  #include "FairTestDetectorPayload.pb.h"
#endif

#include "FairRootManager.h"
#include "TMath.h"
#include "TClonesArray.h"

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
template <typename T1, typename T2>
FairTestDetectorMQRecoTask<T1,T2>::FairTestDetectorMQRecoTask() :
  fRecoTask(NULL)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
template <typename T1, typename T2>
FairTestDetectorMQRecoTask<T1,T2>::FairTestDetectorMQRecoTask(Int_t verbose) :
  fRecoTask(NULL)
{
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
template <typename T1, typename T2>
FairTestDetectorMQRecoTask<T1,T2>::~FairTestDetectorMQRecoTask()
{
  fRecoTask->fDigiArray->Delete();
  fRecoTask->fHitArray->Delete();
  delete fRecoTask;
}
// -------------------------------------------------------------------------


// -----   Public method Init (abstract in base class)  --------------------
template <typename T1, typename T2>
InitStatus FairTestDetectorMQRecoTask<T1, T2>::Init()
{
  fRecoTask = new FairTestDetectorRecoTask();
  fRecoTask->fDigiArray = new TClonesArray("FairTestDetectorDigi");
  fRecoTask->fHitArray = new TClonesArray("FairTestDetectorHit");

  return kSUCCESS;
}

template <>
void FairTestDetectorMQRecoTask<TestDetectorPayload::TestDetectorDigi, TestDetectorPayload::TestDetectorHit>::Exec(FairMQMessage* msg, Option_t* opt)
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

#ifdef PROTOBUF

template <>
void FairTestDetectorMQRecoTask<TestDetectorProto::DigiPayload, TestDetectorProto::HitPayload>::Exec(FairMQMessage* msg, Option_t* opt)
{

  fRecoTask->fDigiArray->Delete();

  TestDetectorProto::DigiPayload dp;
  dp.ParseFromArray(msg->GetData(), msg->GetSize());

  int numEntries = dp.digi_size();

  for (int i = 0; i < numEntries; ++i){
    const TestDetectorProto::Digi& digi = dp.digi(i);
    new ((*fRecoTask->fDigiArray)[i]) FairTestDetectorDigi(digi.fx(), digi.fy(), digi.fz(), digi.ftimestamp());
  }

  if (!fRecoTask->fDigiArray) {
    cout << "-W- FairTestDetectorMQRecoTask::Init: " << "No Point array!" << endl;
  }

  fRecoTask->Exec(opt);

  TestDetectorProto::HitPayload hp;

  for (int i = 0; i < numEntries; ++i) {
    FairTestDetectorHit* hit = (FairTestDetectorHit*) fRecoTask->fHitArray->At(i);
    if (!hit) {
        continue;
    }
    TestDetectorProto::Hit* h = hp.add_hit();
    h->set_detid(hit->GetDetectorID());
    h->set_posx(hit->GetX());
    h->set_posy(hit->GetY());
    h->set_posz(hit->GetZ());
    h->set_dposx(hit->GetDx());
    h->set_dposy(hit->GetDy());
    h->set_dposz(hit->GetDz());
  }

  std::string str;
  hp.SerializeToString(&str);
  size_t size = str.length();

  msg->Rebuild(size);
  memcpy(msg->GetData(), str.c_str(), size);
}

#endif /* PROTOBUF */