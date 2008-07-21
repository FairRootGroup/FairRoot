//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004
//*-- Modified: 21/06/2005  Denis bertini

//////////////////////////////////////////////////////////////////////////////
// CbmParRootFileIo
//
// Interface class for parameter I/O from/to ROOT file
// derived from interface base class CbmParIo.
//
// It contains a pointer to the "connection class" of type CbmParRootFile
// inherited from TFile.  CbmParRootFile contains an object of type CbmRtdbRun
// which holds the list of container versions for an event file.
//
// It contains also a list of detector interface classes all having the common
// base type CbmDetParRootFileIo. Every detector has its own interface class.
//////////////////////////////////////////////////////////////////////////////


#include "CbmParRootFileIo.h"

#include "CbmDetParIo.h"
#include "CbmRuntimeDb.h"
#include "CbmRtdbRun.h"

//#include "TDirectory.h"
//#include "TROOT.h"  

//#include <fstream>
//#include "stdio.h"
#include <iostream>
//#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;

ClassImp(CbmParRootFile)
ClassImp(CbmParRootFileIo)

CbmParRootFile::CbmParRootFile(Text_t* fname, Option_t* option,
                           Text_t* ftitle, Int_t compress)
		:TNamed(fname,  ftitle){
//              : TFile(fname,option,ftitle,compress) {
  // constructor opens a ROOT file
  RootFile=new TFile(fname,option,ftitle,compress);
  run=0;
}
CbmParRootFile::CbmParRootFile(TFile *f) 
	:TNamed(f->GetName(), f->GetTitle()){
//	:TFile(f->GetName(),"UPDATE"){
  // constructor opens a ROOT file
  //RootFile=new TFile(f->GetName(),"UPDATE");
  RootFile=f;
  run=0;
}


CbmParRootFile::~CbmParRootFile() {
  // destructor
  if (run) delete run;
  run=0;
}

void CbmParRootFile::readVersions(CbmRtdbRun* currentRun) {
  // finds the current run containing the parameter container versions
  // in the ROOT file
  if (run) delete run;
  run=(CbmRtdbRun*)RootFile->Get(((char*)currentRun->GetName()));
}


CbmParRootFileIo::CbmParRootFileIo() {
  // constructor
    file=0;
    fMerging=kFALSE;

}

CbmParRootFileIo::CbmParRootFileIo(Bool_t merged) {
  // constructor
    file=0;
    fMerging=merged;

}


CbmParRootFileIo::~CbmParRootFileIo() {
  // destructor closes an open file
  close();
}

Bool_t CbmParRootFileIo::open(Text_t* fname, Option_t* option,
                        Text_t* ftitle, Int_t compress) {
  // It opens a ROOT file (default option "READ"). An open file will be closed.
  // The detector I/Os for all detectors defined in the setup are activated.

  //DB, lock file for NFS in case of mulitple access
  //gDirectory->ReadKeys();
    close();
  if (fMerging ){
  // used test merging
  fstream *f = new fstream(fname);
  if (f->good()){
      // check if file already exists
      option = "UPDATE";
  }else{
  // if file doesn't exist recreate option is used
      option = "RECREATE";
  }
  f->close();
   }

  file=new CbmParRootFile(fname,option,ftitle,compress);
  if (file && file->IsOpen()) {
    CbmRuntimeDb::instance()->activateParIo(this);
    return kTRUE;
  }
  cerr << "-E- Could not open input file " << fname << endl;
  Fatal("open","Could not open input file");
  return kFALSE;
}

Bool_t CbmParRootFileIo::open(TFile *f) {
  // It opens a ROOT file (default option "READ"). An open file will be closed.
  // The detector I/Os for all detectors defined in the setup are activated.
//  close();
  file=new CbmParRootFile(f);
  if (file && file->IsOpen()) {
    CbmRuntimeDb::instance()->activateParIo(this);
    return kTRUE;
  }
  return kFALSE;
}

void CbmParRootFileIo::close() {
  // closes an open ROOT file and deletes the detector I/Os
  if (file) {
    file->Close();
    delete file;
    file=0;
  }
  if (detParIoList) detParIoList->Delete();
}

void CbmParRootFileIo::print() {
  // prints the content of a open ROOT file and the list of detector I/Os
  if (file) {
    file->ls();
    TIter next(detParIoList);
    CbmDetParIo* io;
    cout<<"Root file I/O "<<file->GetName()<<" is open\n";
    cout<<"detector I/Os: ";
    while ((io=(CbmDetParIo*)next())) {
      cout<<" "<<io->GetName();
    }
    cout<<'\n';
  }
  else cout<<"No ROOT file open\n";
}

CbmParRootFile* CbmParRootFileIo::getParRootFile() {
  // returns a pointer to the current ROOT file
  return file;
}

void CbmParRootFileIo::readVersions(CbmRtdbRun* currentRun) {
  // reads the parameter container versions for the current run from
  // the ROOT file
  if (file) file->readVersions(currentRun);
}

TList* CbmParRootFileIo::getKeys() {
  // returns the list of keys found in the ROOT file
  if (file) return file->GetListOfKeys();
  return 0;
}
