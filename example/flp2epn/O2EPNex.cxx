/**
 * O2EPNex.cxx
 *
 * @since 2013-01-09
 * @author D. Klein, A. Rybalchenko, M.Al-Turany
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "O2EPNex.h"
#include "FairMQLogger.h"

O2EPNex::O2EPNex()
{
}

void O2EPNex::Run()
{
  LOG(INFO) << ">>>>>>> Run <<<<<<<";

  boost::thread rateLogger(boost::bind(&FairMQDevice::LogSocketRates, this));

  while ( fState == RUNNING ) {
    FairMQMessage* msg = fTransportFactory->CreateMessage();

    fPayloadInputs->at(0)->Receive(msg);

    int inputSize = msg->GetSize();
    int numInput = inputSize / sizeof(Content);
    Content* input = reinterpret_cast<Content*>(msg->GetData());

    // for (int i = 0; i < numInput; ++i) {
    //     LOG(INFO) << (&input[i])->x << " " << (&input[i])->y << " " << (&input[i])->z << " " << (&input[i])->a << " " << (&input[i])->b;
    // }

    delete msg;
  }

  rateLogger.interrupt();
  rateLogger.join();
}

O2EPNex::~O2EPNex()
{
}
