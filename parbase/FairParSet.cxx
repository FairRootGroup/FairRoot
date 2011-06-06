//*-- AUTHOR : Ilse Koenig
//*-- Created : 20/10/2004

/////////////////////////////////////////////////////////////
//  FairParSet
//
//  Base class for all parameter containers
/////////////////////////////////////////////////////////////

#include "FairParSet.h"

#include "FairRuntimeDb.h"

#include <iostream>

using std::cout;

ClassImp(FairParSet)

FairParSet::FairParSet(const char* name,const char* title,const char* context)
  : TNamed(name,title),
    detName(""),
    status(kFALSE),
    changed(kFALSE),
    paramContext(context),
    author(""),
    description(""),
    fLogger(FairLogger::GetLogger())
{
  for(Int_t i=0; i<3; i++) {versions[i]=-1;}
}

Bool_t FairParSet::init()
{
  // intitializes the container from an input in run time
  // database. If this is not successful it is initialized from
  // the second input. If this failes too, it returns an error.
  // (calls internally the init function in the derived class)
  FairRuntimeDb* rtdb=FairRuntimeDb::instance();
  //FairRunAna* fRun =FairRunAna::Instance();
// cout << "-I-  FairParSet::init() " << GetName() << endl;

  Bool_t allFound=kFALSE;
  FairParIo* io=0;
  if (rtdb) {
    io=rtdb->getFirstInput();
    if (io) { allFound=init(io); }
    if (!allFound) {
      io=rtdb->getSecondInput();
      //cout << "-I FairParSet::init() 2 " << io <<  std::endl;
      if (io) { allFound=init(io); }
    } else { setInputVersion(-1,2); }
  }
  if (allFound) { return kTRUE; }
  fLogger->Error(MESSAGE_ORIGIN, "init() %s  not initialized",GetName());
  return kFALSE;
}

Int_t FairParSet::write()
{
  // writes the container to the output defined in the runtime database
  // returns the output version in the ROOT file
  // returns -1 if error occured
  // (calls internally the init function in the derived class)
  FairParIo* output=FairRuntimeDb::instance()->getOutput();
  if (output) { return write(output); }
  fLogger->Error(MESSAGE_ORIGIN,"write() %s could not be written to output",GetName());
  return -1;
}

void FairParSet::print()
{
  // prints information about container (versions,status,hasChanged...)
  cout<<"-----  "<<GetName()<<"  -----"<<'\n';
  if (!paramContext.IsNull()) { cout<<"Context/Purpose:       "<<paramContext<<'\n'; }
  if (!author.IsNull()) { cout<<"Author:                "<<author<<'\n'; }
  if (!description.IsNull()) { cout<<"Description:           "<<description<<'\n'; }
  cout<<"first input version:   "<<versions[1]<<'\n';
  cout<<"second input version:  "<<versions[2]<<'\n';
  if (changed) { cout<<"has changed"<<'\n'; }
  else { cout<<"has not changed"<<'\n'; }
  if (status) { cout<<"is static"<<'\n'; }
  else { cout<<"is not static"<<'\n'; }
}

void FairParSet::resetInputVersions()
{
  // resets the input versions if the container is not static
  if (!status) {
    for(Int_t i=0; i<3; i++) {versions[i]=-1;}
    changed=kFALSE;
  }
}
