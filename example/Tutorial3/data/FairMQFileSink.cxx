/*
 * FairMQFileSink.cxx
 *
 *  Created on: 2013-06-05
 *      Author: A. Rybalchenko
 */

#include "FairTestDetectorHit.h"

#include "FairMQFileSink.h"
#include "FairMQLogger.h"

#include "TFile.h"
#include "TTree.h"
#include <iostream>
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

void FairMQFileSink::InitOutput()
{
  fOutput = new TClonesArray("FairTestDetectorHit");

  fOutFile = new TFile("filesink.root","recreate");
  fTree = new TTree("MQOut", "Test output");
  fTree->Branch("Output","TClonesArray", &fOutput, 64000, 99);
}

void FairMQFileSink::Run()
{
  void* status; //necessary for pthread_join
  FairMQLogger::GetInstance()->Log(FairMQLogger::INFO, ">>>>>>> Run <<<<<<<");

  pthread_t logger;
  pthread_create(&logger, NULL, &FairMQDevice::callLogSocketRates, this);

  // Initialize poll set
  zmq_pollitem_t items[] = {
    { *(fPayloadInputs->at(0)->GetSocket()), 0, ZMQ_POLLIN, 0 }
  };

  Bool_t received = false;
  while (true) {
    FairMQMessage msg;

    zmq_poll(items, 1, -1);

    if (items[0].revents & ZMQ_POLLIN) {
      received = fPayloadInputs->at(0)->Receive(&msg);
    }

    if (received) {
      Int_t inputSize = msg.Size();
      Int_t numInput = inputSize / sizeof(TestDetectorPayload::TestDetectorHit);
      TestDetectorPayload::TestDetectorHit* input = static_cast<TestDetectorPayload::TestDetectorHit*>(msg.GetMessage()->data());

      fOutput->Delete();

      for (Int_t i = 0; i < numInput; ++i) {
        TVector3 pos(input[i].posX,input[i].posY,input[i].posZ);
        TVector3 dpos(input[i].dposX,input[i].dposY,input[i].dposZ);
        FairTestDetectorHit* hit = new ((*fOutput)[i]) FairTestDetectorHit(input[i].detID, input[i].mcindex, pos, dpos);
      }

      if (!fOutput) {
        std::cout << "-W- FairMQFileSink::Run: " << "No Output array!" << std::endl;
      }

      fTree->Fill();
    } //if received
  } //while true

  pthread_join(logger, &status);
}
