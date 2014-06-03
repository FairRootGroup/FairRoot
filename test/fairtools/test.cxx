/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairLogger.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <numeric>
#include "TStopwatch.h"

//std::cout<<"Value: "<<val<<std::endl;

//gLogger->Info(MESSAGE_ORIGIN, "Value: %i", val);

/*
std::cout<<"Das sollte schwarz sein."<<std::endl;
*/

//    LOG(INFO) << "Value: "<< val <<" "<< FairLogger::endl;

/*
std::cout<<"Das sollte wieder schwarz sein."<<std::endl;
LOG_IF(WarningLog, true) << "Das sollte man sehen."<< FairLogger::endl;
LOG_IF(WarningLog, false) << "Das sollte man nicht sehen."<< FairLogger::endl;
LOG_IF(WarningLog, i%2) << "Jedes zweite mal."<< FairLogger::endl;
std::cout<<"Das sollte wieder schwarz sein."<<std::endl;
*/
//  }

void logToPrintf(int iterations)
{
  for (int i=0; i < iterations; i++) {
    Int_t val = i * i - (i-1);
    printf("Value: %i\n",val);
  }
}

void logToCout(int iterations)
{
  for (int i=0; i < iterations; i++) {
    Int_t val = i * i - (i-1);
    std::cout<<"Value: "<<val<<std::endl;
  }
}

void logToCerr(int iterations)
{
  for (int i=0; i < iterations; i++) {
    Int_t val = i * i - (i-1);
    std::cerr<<"Value: "<<val<<std::endl;
  }
}

void logToLoggerPrintf(int iterations)
{

  for (int i=0; i < iterations; i++) {
    Int_t val = i * i - (i-1);
    gLogger->Info(MESSAGE_ORIGIN, "Value: %i", val);
  }
}

void logToLoggerCout(int iterations)
{
  for (int i=0; i < iterations; i++) {
    Int_t val = i * i - (i-1);
    LOG(INFO) << "Value: "<< val <<" "<< FairLogger::endl;
  }
}

void logToLoggerCoutTest(int iterations)
{
  for (int i=0; i < iterations; i++) {
    Int_t val = i * i - (i-1);
    LOG(INFO) << "Value: "<< val <<" "<< FairLogger::endl;
    LOG(DEBUG) << "Value: "<< val <<" "<< FairLogger::endl;
  }
}

void logTo(int iterations)
{

  for (int i=0; i < iterations; i++) {
    Int_t val = i * i - (i-1);
  }
}

void setSyncOutput(bool decision)
{
  std::ios_base::sync_with_stdio(decision);
}

void PrintHelpAndExit()
{
  std::cerr<<"Please call the program with the number of the test to run."<<std::endl;
  std::cerr<<"The following tests are implemented:"<<std::endl;
  std::cerr<<" 1. printf"<<std::endl;
  std::cerr<<" 2. cout syncronised"<<std::endl;
  std::cerr<<" 3. cout not synchronised"<<std::endl;
  std::cerr<<" 4. cerr syncronised"<<std::endl;
  std::cerr<<" 5. cerr not synchronised"<<std::endl;
  std::cerr<<" 6. FairLogger printf implemetation"<<std::endl;
  std::cerr<<" 7. FairLogger streamer implemetation"<<std::endl;
  exit(-1);
}

void doCalculation(std::vector<Double_t> rtime, std::vector<Double_t> ctime)
{
  // Remove smallest and largest value
  sort (rtime.begin(), rtime.end());
  rtime.erase(rtime.begin());
  rtime.pop_back();
  sort (ctime.begin(), ctime.end());
  ctime.erase(ctime.begin());
  ctime.pop_back();

  Double_t ctime_sum;
  Double_t ctime_avg;
  Double_t rtime_sum;
  Double_t rtime_avg;
  for(int i = 0; i < rtime.size(); i++) {
    rtime_sum += rtime.at(i);
    ctime_sum += ctime.at(i);
  }

  rtime_avg = rtime_sum/rtime.size();
  ctime_avg = ctime_sum/ctime.size();

  Double_t ctime_min = *min_element(ctime.begin(),ctime.end());
  Double_t ctime_max = *max_element(ctime.begin(),ctime.end());

  //  Double_t rtime_sum = accumulate(rtime.begin(), rtime.end(), 0);
  //  Double_t rtime_avg = rtime_sum/rtime.size();
  Double_t rtime_min = *min_element(rtime.begin(),rtime.end());
  Double_t rtime_max = *max_element(rtime.begin(),rtime.end());
  std::cout<<"Discarding the lowest and highest value the"<<std::endl;
  std::cout<<"average of "<<rtime.size()<<" measurements is calculated."<<std::endl;
  std::cout << "Real time (min, average, max): " <<
            rtime_min<<", "<<rtime_avg<<", "<<rtime_max<<std::endl;
  std::cout << "CPU time (min, average, max): " <<
            ctime_min<<", "<<ctime_avg<<", "<<ctime_max<<std::endl;

}


int main(int argc, char* argv[])
{

  //gLogger->SetLogScreenLevel("BLA");
  //gLogger->SetLogToFile(false);
  //gLogger->SetLogToScreen(false);
  //gLogger->Fatal(MESSAGE_ORIGIN, "This is a fatal message.");
  //LOG(INFO) << "This message should never be printed." << FairLogger::endl;
  //LOG(FATAL) << "This is a fatal message" << FairLogger::endl;
  //exit(-42);

  int iterations = 1000000;
  int time_measurements = 12;

  /*
  for (int i=0; i < iterations; i++) {
    Int_t val = i * i - (i-1);
    printf("Value: %i\n",val);
  }
  exit(0);
  */

  if (1 == argc) {
    logToPrintf(iterations);
    std::cout << "Using printf for output"<<std::endl;
    exit(0);
  }

  if (2 < argc) {
    PrintHelpAndExit();
  }

  int x = atoi(argv[1]);

  TStopwatch timer;
  std::vector<Double_t> rtime;
  std::vector<Double_t> ctime;

  switch (x) {
  case 1:
    for (int meas = 0; meas < time_measurements; meas++) {
      timer.Start();
      logToPrintf(iterations);
      timer.Stop();
      rtime.push_back(timer.RealTime());
      ctime.push_back(timer.CpuTime());
      sleep(4);
    }
    doCalculation(rtime, ctime);
    std::cout << "Using printf for output"<<std::endl;
    break;
  case 2:
    for (int meas = 0; meas < time_measurements; meas++) {
      timer.Start();
      logToCout(iterations);
      timer.Stop();
      rtime.push_back(timer.RealTime());
      ctime.push_back(timer.CpuTime());
      sleep(4);
    }
    doCalculation(rtime, ctime);
    std::cout << "Using syncronised cout for output"<<std::endl;
    break;
  case 3:
    setSyncOutput(false);
    for (int meas = 0; meas < time_measurements; meas++) {
      timer.Start();
      logToCout(iterations);
      timer.Stop();
      rtime.push_back(timer.RealTime());
      ctime.push_back(timer.CpuTime());
      sleep(4);
    }
    doCalculation(rtime, ctime);
    std::cout << "Using non syncronised cout for output"<<std::endl;
    break;
  case 4:
    for (int meas = 0; meas < time_measurements; meas++) {
      timer.Start();
      logToCerr(iterations);
      timer.Stop();
      rtime.push_back(timer.RealTime());
      ctime.push_back(timer.CpuTime());
      sleep(4);
    }
    doCalculation(rtime, ctime);
    std::cout << "Using syncronised cerr for output"<<std::endl;
    break;
  case 5:
    setSyncOutput(false);
    for (int meas = 0; meas < time_measurements; meas++) {
      timer.Start();
      logToCerr(iterations);
      timer.Stop();
      rtime.push_back(timer.RealTime());
      ctime.push_back(timer.CpuTime());
      sleep(4);
    }
    doCalculation(rtime, ctime);
    std::cout << "Using non syncronised cerr for output"<<std::endl;
    break;
  case 6:
    for (int meas = 0; meas < time_measurements; meas++) {
      timer.Start();
      logToLoggerPrintf(iterations);
      timer.Stop();
      rtime.push_back(timer.RealTime());
      ctime.push_back(timer.CpuTime());
      sleep(4);
    }
    doCalculation(rtime, ctime);
    std::cout << "Using logger printf output"<<std::endl;
    break;
  case 7:
    for (int meas = 0; meas < time_measurements; meas++) {
      timer.Start();
      logToLoggerCout(iterations);
      timer.Stop();
      rtime.push_back(timer.RealTime());
      ctime.push_back(timer.CpuTime());
      sleep(4);
    }
    doCalculation(rtime, ctime);
    std::cout << "Using logger cout output"<<std::endl;
    break;
  case 8:
    setSyncOutput(false);
    for (int meas = 0; meas < time_measurements; meas++) {
      timer.Start();
      logToLoggerPrintf(iterations);
      timer.Stop();
      rtime.push_back(timer.RealTime());
      ctime.push_back(timer.CpuTime());
      sleep(4);
    }
    doCalculation(rtime, ctime);
    std::cout << "Using logger printf output"<<std::endl;
    break;
  case 9:
    setSyncOutput(false);
    for (int meas = 0; meas < time_measurements; meas++) {
      timer.Start();
      logToLoggerCout(iterations);
      timer.Stop();
      rtime.push_back(timer.RealTime());
      ctime.push_back(timer.CpuTime());
      sleep(4);
    }
    doCalculation(rtime, ctime);
    std::cout << "Using logger cout output"<<std::endl;
    break;
  case 10:
    setSyncOutput(false);
    for (int meas = 0; meas < time_measurements; meas++) {
      timer.Start();
      logToLoggerCoutTest(iterations/2);
      timer.Stop();
      rtime.push_back(timer.RealTime());
      ctime.push_back(timer.CpuTime());
      sleep(4);
    }
    doCalculation(rtime, ctime);
    std::cout << "Using logger cout output"<<std::endl;
    break;
  default:
    std::cout << "Option Unknown"<<std::endl;
    PrintHelpAndExit();
  }


  //std::ios_base::sync_with_stdio(false);
  //gLogger->SetColoredLog(false);
  //gLogger->SetLogToFile(true);
  //gLogger->SetLogToScreen(false);



}
