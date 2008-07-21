//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

///////////////////////////////////////////////////////////////////////////////
// CbmParAsciiFileIo
//
// Interface class for parameter I/O from ASCII file
// derived from the interface base class CbmParIo
// 
// It contains pointers to the ascii file and to the interface classes for all
// detectors defined in the actual setup.
///////////////////////////////////////////////////////////////////////////////

#include "CbmParAsciiFileIo.h"

#include "CbmDetParIo.h"
#include "CbmRuntimeDb.h"

//#include <cstring>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::ios;
using std::filebuf;

ClassImp(CbmParAsciiFileIo)

CbmParAsciiFileIo::CbmParAsciiFileIo() {
  // default destructor
  file=0;
}

CbmParAsciiFileIo::~CbmParAsciiFileIo() {
  // default destructor closes an open file and deletes list of I/Os
  close();
}

Bool_t CbmParAsciiFileIo::open(Text_t* fname, Text_t* status) {
  // opens file
  // if a file is already open, this file will be closed
  // activates detector I/Os
  close();
  if (!((strcmp(status,"in")==0) || (strcmp(status,"out")==0))) {
    cout<<"Put the right stream option for file "<<fname
        <<"\n  writing state : out\n   reading state : in  \nopen  aborted \n"; 
    return kFALSE;
  }
  file=new fstream();
  if(strcmp(status,"in")==0){file->open( fname, ios::in);};
  if(strcmp(status,"out")==0){file->open( fname, ios::out);};
  filebuf* buf = file->rdbuf();
  if (file && (buf->is_open()==1)) {
    filename=fname;
    CbmRuntimeDb::instance()->activateParIo(this);
    return kTRUE;
  }
  cerr << "-E- Could not open input file " << fname << endl;
  Fatal("open","Could not open input file");
  return kFALSE;
}

void CbmParAsciiFileIo::close() {
  // closes the file and deletes the detector I/Os
  if (file) {
    file->close();
    delete file;
    file=0;
    filename="";
  }
  if (detParIoList) detParIoList->Delete();
}

void CbmParAsciiFileIo::print() {
  // prints information about the file and the detector I/Os
  if (check()) {
    cout<<"Ascii I/O "<<filename<<" is open\n";
    TIter next(detParIoList);
    CbmDetParIo* io;
    cout<<"detector I/Os: ";
    while ((io=(CbmDetParIo*)next())) {
      cout<<" "<<io->GetName();
    }
    cout<<'\n';
  }
  else cout<<"No file open\n";
}

fstream* CbmParAsciiFileIo::getFile() {
  // returns the file pointer
  return file;
}
