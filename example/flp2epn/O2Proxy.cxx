/**
 * O2Proxy.cxx
 *
 * @since 2013-10-02
 * @author A. Rybalchenko, M.Al-Turany
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQLogger.h"
#include "O2Proxy.h"

O2Proxy::O2Proxy()
{
}

O2Proxy::~O2Proxy()
{
}

void O2Proxy::Run()
{
  LOG(INFO) << ">>>>>>> Run <<<<<<<";

  boost::thread rateLogger(boost::bind(&FairMQDevice::LogSocketRates, this));

    
  FairMQMessage* msg = fTransportFactory->CreateMessage();

    
    
  while ( fState == RUNNING ) {
    
      
    fPayloadInputs->at(0)->Receive(msg);
      
    fPayloadOutputs->at(0)->Send(msg);
  
  }

  delete msg;

  rateLogger.interrupt();
  rateLogger.join();
}
