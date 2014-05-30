/* 
 * File:   FairTestDetectorMQRecoTask.tpl
 * Author: winckler
 *
 * Created on March 11, 2014, 11:07 AM
 */


////////// Base template class <T1,T2>

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut> 
FairTestDetectorMQRecoTask<TIn,TOut,TPayloadIn,TPayloadOut>::FairTestDetectorMQRecoTask() :  fRecoTask(NULL)
{
    fHasBoostSerialization=true;
    
    #if __cplusplus >= 201103L

    bool checkInputClass=false;
    bool checkOutputClass=false;
    fHasBoostSerialization=false;
    
    
    if(std::is_same<TPayloadIn,boost::archive::binary_iarchive>::value || std::is_same<TPayloadIn,boost::archive::text_iarchive>::value)
    {
        if(has_BoostSerialization<TIn, void(TPayloadIn &, const unsigned int)>::value ==1) 
                checkInputClass=true;
    }
   
    
    
    if(std::is_same<TPayloadOut,boost::archive::binary_oarchive>::value || std::is_same<TPayloadOut,boost::archive::text_oarchive>::value)
    {
        if(has_BoostSerialization<TOut, void(TPayloadOut &, const unsigned int)>::value ==1) 
                checkOutputClass=true;
    }
   
    
    
    if(checkInputClass && checkOutputClass) 
        fHasBoostSerialization=true;
    #endif
    
}


template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut> 
FairTestDetectorMQRecoTask<TIn,TOut,TPayloadIn,TPayloadOut>::FairTestDetectorMQRecoTask(Int_t verbose) :  fRecoTask(NULL)
{
    fHasBoostSerialization=true;
    #if __cplusplus >= 201103L
    bool checkInputClass=false;
    bool checkOutputClass=false;
    fHasBoostSerialization=false;
    
    
    if(std::is_same<TPayloadIn,boost::archive::binary_iarchive>::value || std::is_same<TPayloadIn,boost::archive::text_iarchive>::value)
    {
        if(has_BoostSerialization<TIn, void(TPayloadIn &, const unsigned int)>::value ==1) 
                checkInputClass=true;
        else
            LOG(ERROR) <<"Method 'void serialize(TIn & ar, const unsigned int version)' was not found in input class";
    }
    else
    {
        LOG(ERROR) <<"Output payload is not of supported boost archive type";
        LOG(ERROR) <<"Boost inpput archive type supported : ";
        LOG(ERROR) <<"boost::archive::binary_iarchive and boost::archive::text_iarchive";
    }
    
    
    if(std::is_same<TPayloadOut,boost::archive::binary_oarchive>::value || std::is_same<TPayloadOut,boost::archive::text_oarchive>::value)
    {
        if(has_BoostSerialization<TOut, void(TPayloadOut &, const unsigned int)>::value ==1) 
                checkOutputClass=true;
        else
            LOG(ERROR) <<"Method 'void serialize(TOut & ar, const unsigned int version)' was not found in input class";
    }
    else
    {
        LOG(ERROR) <<"Output payload is not of supported boost archive type";
        LOG(ERROR) <<"Boost output archive type supported : ";
        LOG(ERROR) <<"boost::archive::binary_oarchive and boost::archive::text_oarchive";
    }
    
    
    
    if(checkInputClass && checkOutputClass) 
        fHasBoostSerialization=true;
    
    #endif
}


template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut> 
FairTestDetectorMQRecoTask<TIn,TOut,TPayloadIn,TPayloadOut>::~FairTestDetectorMQRecoTask()
{
        fRecoTask->fDigiArray->Delete();
        fRecoTask->fHitArray->Delete();
        delete fRecoTask;
        if(fDigiVector.size()>0) fDigiVector.clear();
        if(fHitVector.size()>0) fHitVector.clear();
}

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut> 
InitStatus FairTestDetectorMQRecoTask<TIn,TOut,TPayloadIn,TPayloadOut>::Init()
{
        fRecoTask = new FairTestDetectorRecoTask();
        fRecoTask->fDigiArray = new TClonesArray("FairTestDetectorDigi");
        fRecoTask->fHitArray = new TClonesArray("FairTestDetectorHit");

        return kSUCCESS;
}

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut> 
void FairTestDetectorMQRecoTask<TIn,TOut,TPayloadIn,TPayloadOut>::Exec(FairMQMessage* msg, Option_t* opt)
{ 
    if(fHasBoostSerialization)
    {
        int inputSize = msg->GetSize();

        //prepare boost input archive
        std::string msgStr( static_cast<char*>(msg->GetData()), msg->GetSize() );
        std::istringstream ibuffer(msgStr);
        TPayloadIn InputArchive(ibuffer);
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
        TPayloadOut OutputArchive(obuffer); 
        OutputArchive << fHitVector;
        int outputSize=obuffer.str().length();
        msg->Rebuild(outputSize);
        std::memcpy(msg->GetData(), obuffer.str().c_str(), outputSize);
        if(fDigiVector.size()>0) fDigiVector.clear();
        if(fHitVector.size()>0) fHitVector.clear();
    }
    else
    {
        LOG(ERROR) <<" Boost Serialization not ok";
    }
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




