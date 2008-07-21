//*-- AUTHOR : Ilse Koenig
//*-- Created : 20/10/2004

///////////////////////////////////////////////////////////////////
//  CbmRun
//
//  class for the parameter versions of an event file
//
//  The name of each run is the run id converted to a string.
//  The run id number identifies the event file.
//  In the parameter ROOT file the valid parameter versions are
//  accessible via the name. 
//  Associated with the run is a list of container
//  names with the versions of the containers in the two
//  possible inputs and the output (class CbmParVersions).
//  The input versions are used during the initialisation
//  used during the initialisation of the containers.
///////////////////////////////////////////////////////////////////

#include "CbmRtdbRun.h"

#include <iostream>
#include <iomanip>

using std::cout;
using std::ios;
using std::setw;

ClassImp(CbmParVersion)
ClassImp(CbmRtdbRun)

CbmParVersion::CbmParVersion(Text_t* name) : TNamed(name,"version info") {
  // constructor with the name of the container
  rootVersion=0;
  for(Int_t i=0;i<3;i++) {inputVersions[i]=-1;}
}

CbmRtdbRun::CbmRtdbRun(Text_t* name,Text_t* refName)
              : TNamed(name,"run parameters") {
  // constructor with the run id and reference run as strings
  parVersions=new TList();
  refRun=refName;
}

CbmRtdbRun::CbmRtdbRun(Int_t r,Int_t rr) {
  // constructor with the run id and reference run as numbers
  parVersions=new TList();
  char name[255];
  sprintf(name,"%i",r);
  SetName(name);
  setRefRun(rr);
}

CbmRtdbRun::CbmRtdbRun(CbmRtdbRun &run) {
  // copy constructor
  SetName(run.GetName());
  parVersions=new TList();
  TList* lv=run.getParVersions();
  TIter next(lv);
  CbmParVersion* pv;
  while ((pv=(CbmParVersion*)next())) {
    parVersions->Add(pv);
  }
  refRun=run.refRun;
}

CbmRtdbRun::CbmRtdbRun() {
  // default Constructor 
  // parVersions has to be set to zero otherwise the 
  // root file is not browsable
  parVersions=0;
}
CbmRtdbRun::~CbmRtdbRun() {
  // destructor
  if (parVersions) {
    parVersions->Delete();
    delete  parVersions;
    parVersions=0;
  }
}

void CbmRtdbRun::addParVersion(CbmParVersion *pv) {
  // adds a container version object to the list
  parVersions->Add(pv);
}

CbmParVersion* CbmRtdbRun::getParVersion(Text_t* name) {
  // return a container version object called by the name of
  // the container
  return (CbmParVersion*)parVersions->FindObject(name);
}

void CbmRtdbRun::resetInputVersions() {
  TIter next(parVersions);
  CbmParVersion* v;
  while ((v=(CbmParVersion*)next())) {
    v->resetInputVersions();
  }
}

void CbmRtdbRun::resetOutputVersions() {
  TIter next(parVersions);
  CbmParVersion* v;
  while ((v=(CbmParVersion*)next())) {
    v->setRootVersion(0);
  }
}

void CbmRtdbRun::print() {
  // prints the list of container versions for this run
  cout<<"run: "<<GetName()<<'\n';
  CbmParVersion* v;
  TIter next(parVersions);
  while ((v=(CbmParVersion*)next())) {
    cout.setf(ios::left,ios::adjustfield);
    cout<<"  "<<setw(45)<<v->GetName();
    cout.setf(ios::right,ios::adjustfield);
    cout<<setw(11)<<v->getInputVersion(1)
        <<setw(11)<<v->getInputVersion(2)
        <<setw(11)<<v->getRootVersion()<<'\n';
  }
}

void CbmRtdbRun::write(fstream& fout) {
  // writes the list of container versions for this run to fstream
  fout<<"run: "<<GetName()<<'\n';
  CbmParVersion* v;
  TIter next(parVersions);
  while ((v=(CbmParVersion*)next())) {
    fout.setf(ios::left,ios::adjustfield);
    fout<<"  "<<setw(45)<<v->GetName();
    fout.setf(ios::right,ios::adjustfield);
    fout<<setw(11)<<v->getInputVersion(1)
        <<setw(11)<<v->getInputVersion(2)
        <<setw(11)<<v->getRootVersion()<<'\n';
  }
}
