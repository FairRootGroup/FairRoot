/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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

#include "FairDetParIo.h"               // for FairDetParIo
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairLogger.h"

#include "TCollection.h"                // for TIter
#include "TList.h"                      // for TList, TListIter
#include "TObjString.h"                 // for TObjString
#include "TString.h"                    // for TString, operator<<
#include "TSystem.h"                    // for TSystem, gSystem

#include <string.h>                     // for strcmp, NULL
#include <iostream>                     // for cout, cerr

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
  file=new std::fstream();
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
  TString outFileName = gSystem->WorkingDirectory();

  outFileName += "/all_";
  Int_t pid = gSystem->GetPid();
  outFileName += pid;
  outFileName += ".par";
  TString catCommand = "cat ";
  TObjString* string;
  TListIter myIter(fnamelist);
  while((string = static_cast<TObjString*>(myIter.Next()))) {
    // check if the file exist
    // if file exist return value is false
    if ( gSystem->AccessPathName(string->GetString())) {
      LOG(FATAL) << "Parameter file " << string->GetString() << " does not exist." << FairLogger::endl;
    }
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
    while ((io=static_cast<FairDetParIo*>(next()))) {
      cout<<" "<<io->GetName();
    }
    cout<<'\n';
  } else { cout<<"No file open\n"; }
}

std::fstream* FairParAsciiFileIo::getFile()
{
  // returns the file pointer
  return file;
}
