#ifndef FAIRORARUNINFO_H
#define FAIRORARUNINFO_H

using namespace std;
#include "TNamed.h"
#include <iostream>
#include <iomanip>
#include <fstream>

class FairOraRunInfo : public TNamed {
private:
  Int_t   runId;      // run identifier
  TString startTime;  // start time
  TString endTime;    // stop time
  Int_t   numEvents;  // number of events
public:
  FairOraRunInfo(const char* filename="");
  ~FairOraRunInfo() {}
  void setRunId(Int_t n) {runId=n;}
  void setStartTime(const char* s) {startTime=s;}
  void setEndTime(const char* s) {endTime=s;}
  void setNumEvents(Int_t n) {numEvents=n;}
  Int_t getRunId() {return runId;}
  const char* getStartTime() {return startTime.Data();}
  const char* getEndTime() {return endTime.Data();}
  Int_t getNumEvents() {return numEvents;}
  void print();
  void write(fstream&);
private:
  ClassDef(FairOraRunInfo,0) // Class for run information
};

#endif  /* !FAIRORARUNINFO */
