//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

///////////////////////////////////////////////////////////////////////////////
// FairParAsciiFileIo
//
// Interface class for parameter I/O from ASCII file
// derived from the interface base class FairParIo
//
// It contains pointers to the ascii file and to the interface classes for all
// detectors defined in the actual setup.
///////////////////////////////////////////////////////////////////////////////

#include "FairParAsciiFileIo.h"

#include "FairDetParIo.h"
#include "FairRuntimeDb.h"

#include "TString.h"
#include "TObjString.h"
#include "TList.h"
#include "TSystem.h"

//#include <cstring>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::ios;
using std::filebuf;

ClassImp(FairParAsciiFileIo)

FairParAsciiFileIo::FairParAsciiFileIo()
  :FairParIo(),
   file(NULL)
{
  // default destructor
  //  file=0;
}

FairParAsciiFileIo::~FairParAsciiFileIo()
{
  // default destructor closes an open file and deletes list of I/Os
  close();
}

Bool_t FairParAsciiFileIo::open(const Text_t* fname, const Text_t* status)
{
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
  if(strcmp(status,"in")==0) {file->open( fname, ios::in);};
  if(strcmp(status,"out")==0) {file->open( fname, ios::out);};
  filebuf* buf = file->rdbuf();
  if (file && (buf->is_open()==1)) {
    filename=fname;
    FairRuntimeDb::instance()->activateParIo(this);
    return kTRUE;
  }
  cerr << "-E- Could not open input file " << fname << endl;
  Fatal("open","Could not open input file");
  return kFALSE;
}

Bool_t FairParAsciiFileIo::open(const TList* fnamelist, const Text_t* status)
{

  TString outFileName = "all_";
  Int_t pid = gSystem->GetPid();
  outFileName += pid;
  outFileName += ".par";
  TString catCommand = "cat ";
  TObjString* string;
  TListIter myIter(fnamelist);
  while((string = (TObjString*)myIter.Next())) {
    //    cout <<  string->GetString() <<endl;
    catCommand += string->GetString();
    catCommand += " ";
  }
  catCommand += "> ";
  catCommand += outFileName;

  //  cout <<"CAT: "<<catCommand.Data()<<endl;

  gSystem->Exec(catCommand);

  return open(outFileName, status);

}

void FairParAsciiFileIo::close()
{
  // closes the file and deletes the detector I/Os
  if (file) {
    file->close();
    delete file;
    file=0;
    filename="";
  }
  if (detParIoList) { detParIoList->Delete(); }
}

void FairParAsciiFileIo::print()
{
  // prints information about the file and the detector I/Os
  if (check()) {
    cout<<"Ascii I/O "<<filename<<" is open\n";
    TIter next(detParIoList);
    FairDetParIo* io;
    cout<<"detector I/Os: ";
    while ((io=(FairDetParIo*)next())) {
      cout<<" "<<io->GetName();
    }
    cout<<'\n';
  } else { cout<<"No file open\n"; }
}

fstream* FairParAsciiFileIo::getFile()
{
  // returns the file pointer
  return file;
}
