/**
 * FairMQFileSink.cxx
 *
 * @since 2013-06-05
 * @author A. Rybalchenko
 */

#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairTestDetectorHit.h"
#include "FairTestDetectorPayload.h"

#ifdef PROTOBUF
  #include "FairTestDetectorPayload.pb.h"
#endif

#include "FairMQFileSink.h"
#include "FairMQLogger.h"

#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TVector3.h"

template <typename T1, typename T2>
FairMQFileSink<T1,T2>::FairMQFileSink()
{
}

template <typename T1, typename T2>
FairMQFileSink<T1,T2>::~FairMQFileSink()
{
  fTree->Write();
  fOutFile->Close();
}

template <typename T1, typename T2>
void FairMQFileSink<T1,T2>::InitOutputFile(TString defaultId)
{
  fOutput = new TClonesArray("FairTestDetectorHit");

  char out[256];
  sprintf(out, "filesink%s.root", defaultId.Data());

  fOutFile = new TFile(out,"recreate");
  fTree = new TTree("MQOut", "Test output");
  fTree->Branch("Output","TClonesArray", &fOutput, 64000, 99);
}

template <>
void FairMQFileSink<TestDetectorPayload::TestDetectorHit, FairTestDetectorHit>::Run()
{
  LOG(INFO) << ">>>>>>> Run <<<<<<<";

  boost::thread rateLogger(boost::bind(&FairMQDevice::LogSocketRates, this));

  int receivedMsgs = 0;
  bool received = false;

  while ( fState == RUNNING ) {
    FairMQMessage* msg = fTransportFactory->CreateMessage();

    received = fPayloadInputs->at(0)->Receive(msg);

    if (received) {
      Int_t inputSize = msg->GetSize();
      Int_t numInput = inputSize / sizeof(TestDetectorPayload::TestDetectorHit);
      TestDetectorPayload::TestDetectorHit* input = static_cast<TestDetectorPayload::TestDetectorHit*>(msg->GetData());

      fOutput->Delete();

      for (Int_t i = 0; i < numInput; ++i) {
        TVector3 pos(input[i].posX,input[i].posY,input[i].posZ);
        TVector3 dpos(input[i].dposX,input[i].dposY,input[i].dposZ);
        new ((*fOutput)[i]) FairTestDetectorHit(input[i].detID, input[i].mcindex, pos, dpos);
      }

      if (!fOutput) {
        cout << "-W- FairMQFileSink::Run: " << "No Output array!" << endl;
      }

      fTree->Fill();
      received = false;
    }

    delete msg;
  }

  cout << "I've received " << receivedMsgs << " messages!" << endl;

  boost::this_thread::sleep(boost::posix_time::milliseconds(5000));

  rateLogger.interrupt();
  rateLogger.join();
}


#ifdef PROTOBUF

template <>
void FairMQFileSink<TestDetectorProto::HitPayload, FairTestDetectorHit>::Run()
{
  LOG(INFO) << ">>>>>>> Run <<<<<<<";

  boost::thread rateLogger(boost::bind(&FairMQDevice::LogSocketRates, this));

  int receivedMsgs = 0;
  bool received = false;

  while ( fState == RUNNING ) {
    FairMQMessage* msg = fTransportFactory->CreateMessage();

    received = fPayloadInputs->at(0)->Receive(msg);

    if (received) {

      fOutput->Delete();

      TestDetectorProto::HitPayload hp;
      hp.ParseFromArray(msg->GetData(), msg->GetSize());

      int numEntries = hp.hit_size();

      for (int i = 0; i < numEntries; ++i) {
        const TestDetectorProto::Hit& hit = hp.hit(i);
        TVector3 pos(hit.posx(), hit.posy(), hit.posz());
        TVector3 dpos(hit.dposx(), hit.dposy(), hit.dposz());
        new ((*fOutput)[i]) FairTestDetectorHit(hit.detid(), hit.mcindex(), pos, dpos);
      }

      if (!fOutput) {
        cout << "-W- FairMQFileSink::Run: " << "No Output array!" << endl;
      }

      fTree->Fill();
      received = false;
    }

    delete msg;
  }

  cout << "I've received " << receivedMsgs << " messages!" << endl;

  boost::this_thread::sleep(boost::posix_time::milliseconds(5000));

  rateLogger.interrupt();
  rateLogger.join();
}

#endif /* PROTOBUF */