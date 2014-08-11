/**
 * O2FLPex.cxx
 *
 * @since 2013-04-23
 * @author D. Klein, A. Rybalchenko, M.Al-Turany, C. Kouzinopoulos
 */

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <sstream>

#include "O2FLPex.h"
#include "FairMQLogger.h"

O2FLPex::O2FLPex() :
  fEventSize(10000),
  fEventRate(1),
  fEventCounter(0)
{
}

O2FLPex::~O2FLPex()
{
}

void O2FLPex::Init()
{
  FairMQDevice::Init();
}

bool O2FLPex::updateIPHeartbeat (string str)
{
  boost::posix_time::ptime currentHeartbeat = boost::posix_time::microsec_clock::local_time();
  
  for (int iOutput = 0; iOutput < fNumOutputs; iOutput++) {
    if ( GetProperty (OutputAddress, "", iOutput) == str ) {
      //mtx_.lock();
      //boost::posix_time::ptime storedHeartbeat = GetProperty (OutputHeartbeat, storedHeartbeat, iOutput);
      //mtx_.unlock();
      //if ( to_simple_string (storedHeartbeat) != "not-a-date-time" ) {
      //  LOG(INFO) << "EPN " << iOutput << " last seen "
      //            << (currentHeartbeat - storedHeartbeat).total_milliseconds()
      //            << " ms ago. Updating heartbeat...";
      //}
      //else {
      //  LOG(INFO) << "IP has no heartbeat associated. Adding heartbeat: " << currentHeartbeat;
      //}

      mtx_.lock();
      SetProperty (OutputHeartbeat, currentHeartbeat, iOutput);
      mtx_.unlock();
      
      return true;
    }
  }
  LOG(ERROR) << "IP " << str << " unknown, not provided at execution time";

  return false;
}

void O2FLPex::SendPayload (Content* payload)
{
  while ( fState == RUNNING ) {
    boost::posix_time::ptime currentHeartbeat = boost::posix_time::microsec_clock::local_time();
    
    for (int iOutput = 0; iOutput < fNumOutputs; iOutput++) {
      mtx_.lock();
      boost::posix_time::ptime storedHeartbeat = GetProperty (OutputHeartbeat, storedHeartbeat, iOutput);
      mtx_.unlock();
      
      if ( to_simple_string (storedHeartbeat) == "not-a-date-time" ||
         (currentHeartbeat - storedHeartbeat).total_milliseconds() > fHeartbeatTimeoutInMs) {
        //LOG(INFO) << "EPN " << iOutput << " has not send a heartbeat, or heartbeat too old";
        continue;
      }
      
      //LOG(INFO) << "Pubishing payload to EPN " << iOutput;
      
      FairMQMessage* msg = fTransportFactory->CreateMessage(fEventSize * sizeof(Content));
      memcpy(msg->GetData(), payload, fEventSize * sizeof(Content));
      
      fPayloadOutputs->at(iOutput)->Send(msg);
      
      delete msg;
    }
    
    --fEventCounter;

    while (fEventCounter == 0) {
      boost::this_thread::sleep (boost::posix_time::milliseconds(1));
    }
  }
}

void O2FLPex::ReceiveHeartbeat()
{
  while ( fState == RUNNING ) {
    FairMQMessage* msg = fTransportFactory->CreateMessage();

    fPayloadInputs->at(0)->Receive(msg);
    
    std::string rpl = std::string(static_cast<char*>(msg->GetData()), msg->GetSize());
    
    //LOG(INFO) << "Message size: " << msg->GetSize() << " Message content: " << rpl;
      
    //Add or update the heartbeat associated with a given EPN
    updateIPHeartbeat (rpl);
    
    delete msg;
  }
}

void O2FLPex::Run()
{
  LOG(INFO) << ">>>>>>> Run <<<<<<<";

  boost::thread rateLogger (boost::bind(&FairMQDevice::LogSocketRates, this));
  boost::thread resetEventCounter (boost::bind(&O2FLPex::ResetEventCounter, this));

  srand(time(NULL));
 
  stringstream ss(fId);
    
  int Flp_id;
  ss >> Flp_id;
    
  Content* payload = new Content[fEventSize];
  for (int i = 0; i < fEventSize; ++i) {
        (&payload[i])->id = Flp_id;
        (&payload[i])->x = rand() % 100 + 1;
        (&payload[i])->y = rand() % 100 + 1;
        (&payload[i])->z = rand() % 100 + 1;
        (&payload[i])->a = (rand() % 100 + 1) / (rand() % 100 + 1);
        (&payload[i])->b = (rand() % 100 + 1) / (rand() % 100 + 1);
        //LOG(INFO) << (&payload[i])->id << " " << (&payload[i])->x << " " << (&payload[i])->y << " " << (&payload[i])->z << " " << (&payload[i])->a << " " << (&payload[i])->b;
  }
    
  boost::thread fReceiveThread (boost::bind(&O2FLPex::SendPayload, this, payload));
  boost::thread fSendThread (boost::bind(&O2FLPex::ReceiveHeartbeat, this));
  
  //Wait for the threads to finish execution
  fReceiveThread.join();
  fSendThread.join();

  delete[] payload;
  
  rateLogger.interrupt();
  resetEventCounter.interrupt();

  rateLogger.join();
  resetEventCounter.join();
}

void O2FLPex::ResetEventCounter()
{
  while ( true ) {
    try {
      fEventCounter = fEventRate / 100;
      boost::this_thread::sleep(boost::posix_time::milliseconds(10));
    } catch (boost::thread_interrupted&) {
      break;
    }
  }
}

void O2FLPex::Log(int intervalInMs)
{
  timestamp_t t0;
  timestamp_t t1;
  unsigned long bytes = fPayloadOutputs->at(0)->GetBytesTx();
  unsigned long messages = fPayloadOutputs->at(0)->GetMessagesTx();
  unsigned long bytesNew = 0;
  unsigned long messagesNew = 0;
  double megabytesPerSecond = 0;
  double messagesPerSecond = 0;

  t0 = get_timestamp();

  while (true) {
    boost::this_thread::sleep(boost::posix_time::milliseconds(intervalInMs));

    t1 = get_timestamp();

    bytesNew = fPayloadOutputs->at(0)->GetBytesTx();
    messagesNew = fPayloadOutputs->at(0)->GetMessagesTx();

    timestamp_t timeSinceLastLog_ms = (t1 - t0) / 1000.0L;

    megabytesPerSecond = ((double) (bytesNew - bytes) / (1024. * 1024.)) / (double) timeSinceLastLog_ms * 1000.;
    messagesPerSecond = (double) (messagesNew - messages) / (double) timeSinceLastLog_ms * 1000.;

    LOG(DEBUG) << "send " << messagesPerSecond << " msg/s, " << megabytesPerSecond << " MB/s";

    bytes = bytesNew;
    messages = messagesNew;
    t0 = t1;
  }
}

void O2FLPex::SetProperty(const int key, const string& value, const int slot/*= 0*/)
{
  switch (key) {
  default:
    FairMQDevice::SetProperty(key, value, slot);
    break;
  }
}

string O2FLPex::GetProperty(const int key, const string& default_/*= ""*/, const int slot/*= 0*/)
{
  switch (key) {
  default:
    return FairMQDevice::GetProperty(key, default_, slot);
  }
}

void O2FLPex::SetProperty(const int key, const int value, const int slot/*= 0*/)
{
  switch (key) {
  case EventSize:
    fEventSize = value;
    break;
  case EventRate:
    fEventRate = value;
    break;
  default:
    FairMQDevice::SetProperty(key, value, slot);
    break;
  }
}

int O2FLPex::GetProperty(const int key, const int default_/*= 0*/, const int slot/*= 0*/)
{
  switch (key) {
  case EventSize:
    return fEventSize;
  case EventRate:
    return fEventRate;
  default:
    return FairMQDevice::GetProperty(key, default_, slot);
  }
}

void O2FLPex::SetProperty(const int key, const boost::posix_time::ptime value, const int slot/*= 0*/)
{
  switch (key) {
  default:
    FairMQDevice::SetProperty(key, value, slot);
    break;
  }
}

boost::posix_time::ptime O2FLPex::GetProperty(const int key, const boost::posix_time::ptime default_, const int slot/*= 0*/)
{
  switch (key) {
  default:
    return FairMQDevice::GetProperty(key, default_, slot);
  }
}
