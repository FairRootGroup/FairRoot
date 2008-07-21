#ifndef CBMORARUNINFO_H
#define CBMORARUNINFO_H

using namespace std;
#include "TNamed.h"
#include <iostream>
#include <iomanip>
#include <fstream>

class CbmOraRunInfo : public TNamed {
private:
  Int_t   runId;      // run identifier
  TString startTime;  // start time
  TString endTime;    // stop time
public:
  CbmOraRunInfo(const char* filename="");
  ~CbmOraRunInfo() {}
  void setRunId(Int_t n) {runId=n;}
  void setStartTime(const char* s) {startTime=s;}
  void setEndTime(const char* s) {endTime=s;}
  Int_t getRunId() {return runId;}
  const char* getStartTime() {return startTime.Data();}
  const char* getEndTime() {return endTime.Data();}
  void print();
  void write(fstream&);
private:
  ClassDef(CbmOraRunInfo,0) // Class for run information
};

#endif  /* !CBMORARUNINFO */
