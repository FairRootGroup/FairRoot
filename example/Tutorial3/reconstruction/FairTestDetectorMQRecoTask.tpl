/* 
 * File:   FairTestDetectorMQRecoTask.tpl
 * Author: winckler
 *
 * Created on March 11, 2014, 11:07 AM
 */


////////// Base template class <T1,T2>

template <typename TIn, typename TOut, typename TBoostPayloadIn, typename TBoostPayloadOut> 
void FairTestDetectorMQRecoTask<TIn,TOut,TBoostPayloadIn,TBoostPayloadOut>::Exec(FairMQMessage* msg, Option_t* opt)
{ 
    
    int inputSize = msg->GetSize();
    
    //prepare boost input archive
    std::string msgStr( static_cast<char*>(msg->GetData()), msg->GetSize() );
    std::istringstream ibuffer(msgStr);
    TBoostPayloadIn InputArchive(ibuffer);
    try
     {
         InputArchive >> fDigiVector;// get input Archive
     }
     catch (boost::archive::archive_exception e)
     {
         LOG(ERROR) << e.what();
     }
    fRecoTask->fDigiArray->Delete();
    int numInput=fDigiVector.size();

    for (int i = 0; i < numInput; ++i) 
    {
      new ((*fRecoTask->fDigiArray)[i]) TIn(fDigiVector.at(i));
    }

    if (!fRecoTask->fDigiArray) {
      cout << "-W- FairTestDetectorMQRecoTask::Init: " << "No Point array!" << endl;
    }

    fRecoTask->Exec(opt);
    int numOutput = numInput;

    if (inputSize > 0) 
    {
      for (int i = 0; i < numOutput; ++i) 
      {
        TOut* hit = (TOut*) fRecoTask->fHitArray->At(i);
        fHitVector.push_back(*hit);
      }
    }
    
    //prepare boost output archive
    std::ostringstream obuffer;
    TBoostPayloadOut OutputArchive(obuffer); 
    OutputArchive << fHitVector;
    int outputSize=obuffer.str().length();
    msg->Rebuild(outputSize);
    std::memcpy(msg->GetData(), obuffer.str().c_str(), outputSize);
    if(fDigiVector.size()>0) fDigiVector.clear();
    if(fHitVector.size()>0) fHitVector.clear();
   
}


template <>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi,FairTestDetectorHit,TestDetectorPayload::TestDetectorDigi, TestDetectorPayload::TestDetectorHit>::Exec(FairMQMessage* msg, Option_t* opt)
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
#include "FairTestDetectorPayload.pb.h"
template <>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi,FairTestDetectorHit,TestDetectorProto::DigiPayload, TestDetectorProto::HitPayload>::Exec(FairMQMessage* msg, Option_t* opt)
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




