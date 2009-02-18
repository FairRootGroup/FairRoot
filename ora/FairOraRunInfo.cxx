///*-- AUTHOR : Ilse Koenig
//*-- Created : 26/11/2004 by I.Koenig

//////////////////////////////////////////////////////////////////////////////
//
// FairOraRunInfo
//
// Class for run information (filled by Oracle interface)
//
//////////////////////////////////////////////////////////////////////////////

#include "FairOraRunInfo.h"

ClassImp(FairOraRunInfo)

FairOraRunInfo::FairOraRunInfo(const char* filename) {
  SetName(filename);
  runId=numEvents=-1;
}

void FairOraRunInfo::print() {
  cout.setf(ios::left,ios::adjustfield);
  cout<<setw(50)<<GetName()<<setw(12)<<runId<<"\n    "<<startTime<<"  "
      <<setw(25)<<endTime;
  cout.setf(ios::right,ios::adjustfield);
  cout<<setw(12)<<numEvents<<'\n';
}

void FairOraRunInfo::write(fstream& fout) {
  fout.setf(ios::left,ios::adjustfield);
  fout<<setw(50)<<GetName()<<setw(12)<<runId<<"  "<<startTime<<"  "
      <<setw(25)<<endTime;
  fout.setf(ios::right,ios::adjustfield);
  fout<<setw(12)<<numEvents<<'\n';
}
