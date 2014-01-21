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

#include "FairMQFileSink.h"
#include "FairMQLogger.h"

#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TVector3.h"


FairMQFileSink::FairMQFileSink()
{
}

FairMQFileSink::~FairMQFileSink()
{
  fTree->Write();
  fOutFile->Close();
}

void FairMQFileSink::InitOutputFile(TString defaultId)
{
  fOutput = new TClonesArray("FairTestDetectorHit");

  char out[256];
  sprintf(out, "filesink%s.root", defaultId.Data());

  fOutFile = new TFile(out,"recreate");
  fTree = new TTree("MQOut", "Test output");
  fTree->Branch("Output","TClonesArray", &fOutput, 64000, 99);
}

void FairMQFileSink::Run()
{
  FairMQLogger::GetInstance()->Log(FairMQLogger::INFO, ">>>>>>> Run <<<<<<<");

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
        std::cout << "-W- FairMQFileSink::Run: " << "No Output array!" << std::endl;
      }

      fTree->Fill();
      received = false;
    }

    delete msg;
  }

  std::cout << "I've received " << receivedMsgs << " messages!" << std::endl;

  boost::this_thread::sleep(boost::posix_time::milliseconds(5000));

  rateLogger.interrupt();
  rateLogger.join();
}
