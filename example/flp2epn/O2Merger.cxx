/**
 * O2Merger.cxx
 *
 * @since 2012-12-06
 * @author D. Klein, A. Rybalchenko, M. Al-Turany
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQLogger.h"
#include "O2Merger.h"
#include "FairMQPoller.h"


O2Merger::O2Merger()
{
}

O2Merger::~O2Merger()
{
}

void O2Merger::Run()
{
  LOG(INFO) << ">>>>>>> Run <<<<<<<";

  boost::thread rateLogger(boost::bind(&FairMQDevice::LogSocketRates, this));

  FairMQPoller* poller = fTransportFactory->CreatePoller(*fPayloadInputs);

  bool received = false;

  while ( fState == RUNNING ) {
    FairMQMessage* msg = fTransportFactory->CreateMessage();

    poller->Poll(100);

    for(int i = 0; i < fNumInputs; i++) {
      if (poller->CheckInput(i)){
        received = fPayloadInputs->at(i)->Receive(msg);
      }
      if (received) {
        fPayloadOutputs->at(0)->Send(msg);
        received = false;
      }
    }

    delete msg;
  }

  delete poller;

  rateLogger.interrupt();
  rateLogger.join();
}

