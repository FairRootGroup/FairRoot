//*-- AUTHOR : Ilse Koenig
//*-- Created : 20/10/2004

/////////////////////////////////////////////////////////////
//  CbmParSet
//
//  Base class for all parameter containers
/////////////////////////////////////////////////////////////

#include "CbmParSet.h"

#include "CbmRuntimeDb.h"

#include <iostream> 
//#include <iomanip>

using std::cout;

ClassImp(CbmParSet)

CbmParSet::CbmParSet(const char* name,const char* title,const char* context)
        : TNamed(name,title) {
  // constructor sets default values of data elements
  paramContext=context;
  for(Int_t i=0;i<3;i++) {versions[i]=-1;}
  status=kFALSE;
  changed=kFALSE;
}

Bool_t CbmParSet::init() {
  // intitializes the container from an input in run time
  // database. If this is not successful it is initialized from
  // the second input. If this failes too, it returns an error.
  // (calls internally the init function in the derived class)
  CbmRuntimeDb* rtdb=CbmRuntimeDb::instance();
  //CbmRunAna* fRun =CbmRunAna::Instance();
// cout << "-I-  CbmParSet::init() " << GetName() << endl;

  Bool_t allFound=kFALSE;
  CbmParIo* io=0;
  if (rtdb) {
    io=rtdb->getFirstInput();
    if (io) allFound=init(io);
    if (!allFound) {
      io=rtdb->getSecondInput();
      //  cout << "-I CbmParSet::init() 2 " << io <<  endl;
      if (io) allFound=init(io);
    } else setInputVersion(-1,2);
  }
  if (allFound) return kTRUE;
  Error("init()","%s not initialized",GetName());
  return kFALSE;
}

Int_t CbmParSet::write() {
  // writes the container to the output defined in the runtime database
  // returns the output version in the ROOT file
  // returns -1 if error occured
  // (calls internally the init function in the derived class)
  CbmParIo* output=CbmRuntimeDb::instance()->getOutput();
  if (output) return write(output);
  Error("write()","%s could not be written to output",GetName());
  return -1;
}

void CbmParSet::print() {
  // prints information about container (versions,status,hasChanged...)
  cout<<"-----  "<<GetName()<<"  -----"<<'\n';
  if (!paramContext.IsNull()) cout<<"Context/Purpose:       "<<paramContext<<'\n';
  if (!author.IsNull()) cout<<"Author:                "<<author<<'\n';
  if (!description.IsNull()) cout<<"Description:           "<<description<<'\n';
  cout<<"first input version:   "<<versions[1]<<'\n';
  cout<<"second input version:  "<<versions[2]<<'\n';
  if (changed) cout<<"has changed"<<'\n';
  else cout<<"has not changed"<<'\n';
  if (status) cout<<"is static"<<'\n';
  else cout<<"is not static"<<'\n';
}

void CbmParSet::resetInputVersions() {
  // resets the input versions if the container is not static
  if (!status) {
    for(Int_t i=0;i<3;i++) {versions[i]=-1;}
    changed=kFALSE;
  }
}
