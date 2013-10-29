/*
 * FairMQFileSink.cxx
 *
 *  Created on: 2013-06-05
 *      Author: A. Rybalchenko
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

  // Initialize poll set
  zmq_pollitem_t items[] = {
    { *(fPayloadInputs->at(0)->GetSocket()), 0, ZMQ_POLLIN, 0 }
  };

  int receivedMsgs = 0;
  Bool_t received = false;

  while ( fState == RUNNING ) {
    FairMQMessage msg;

    zmq_poll(items, 1, 100); // TODO: can timeout be avoided?

    if (items[0].revents & ZMQ_POLLIN) {
      received = fPayloadInputs->at(0)->Receive(&msg);
      receivedMsgs++;
    }

    if (received) {
      Int_t inputSize = msg.Size();
      Int_t numInput = inputSize / sizeof(TestDetectorPayload::TestDetectorHit);
      TestDetectorPayload::TestDetectorHit* input = static_cast<TestDetectorPayload::TestDetectorHit*>(msg.GetMessage()->data());

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
    } //if received
  } //while true

  std::cout << "I've received " << receivedMsgs << " messages!" << std::endl;

  boost::this_thread::sleep(boost::posix_time::milliseconds(5000));

  rateLogger.interrupt();
  rateLogger.join();
}
