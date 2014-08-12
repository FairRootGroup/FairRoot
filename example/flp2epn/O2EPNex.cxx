/**
 * O2EPNex.cxx
 *
 * @since 2013-01-09
 * @author D. Klein, A. Rybalchenko, M.Al-Turany, C. Kouzinopoulos
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "O2EPNex.h"
#include "FairMQLogger.h"

O2EPNex::O2EPNex()
{
}

void O2EPNex::ReceivePayload()
{
  while ( fState == RUNNING ) {
    FairMQMessage* msg = fTransportFactory->CreateMessage();

    fPayloadInputs->at(0)->Receive(msg);
    
    //LOG(INFO) << "Received payload from FLP";

    int inputSize = msg->GetSize();
    int numInput = inputSize / sizeof(Content);
    Content* input = reinterpret_cast<Content*>(msg->GetData());

    // for (int i = 0; i < numInput; ++i) {
    //     LOG(INFO) << (&input[i])->x << " " << (&input[i])->y << " " << (&input[i])->z << " " << (&input[i])->a << " " << (&input[i])->b;
    // }

    delete msg;
  }
}

void O2EPNex::SendHeartbeat()
{
  while ( fState == RUNNING ) {
    
    for (int iOutput = 0; iOutput < fNumOutputs; iOutput++) {
      FairMQMessage* msg = fTransportFactory->CreateMessage (strlen (fInputAddress.at(0).c_str()));
      memcpy(msg->GetData(), fInputAddress.at(0).c_str(), strlen (fInputAddress.at(0).c_str()));
    
      fPayloadOutputs->at(iOutput)->Send(msg);
      
      delete msg;
    }
    
    //LOG(INFO) << "Publishing identification string";
    
    boost::this_thread::sleep(boost::posix_time::milliseconds(fHeartbeatIntervalInMs));
  }
}

void O2EPNex::Run()
{
  LOG(INFO) << ">>>>>>> Run <<<<<<<";

  boost::thread rateLogger(boost::bind(&FairMQDevice::LogSocketRates, this));

  boost::thread fReceiveThread (boost::bind(&O2EPNex::ReceivePayload, this));
  boost::thread fSendThread (boost::bind(&O2EPNex::SendHeartbeat, this));
    
  //Wait for the threads to finish execution
  fReceiveThread.join();
  fSendThread.join();

  rateLogger.interrupt();
  rateLogger.join();
}

O2EPNex::~O2EPNex()
{
}
