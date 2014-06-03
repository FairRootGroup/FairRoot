/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairDbBufferFile.h"
#include "FairDbLogService.h"
#include "FairDbObjTableMap.h"             // for FairDbObjTableMap
#include "ValInterval.h"                   // for ValInterval
#include "ValTimeStamp.h"               // for ValTimeStamp

#include "TClass.h"                     // for TClass
#include "TString.h"                    // for TString
#include "TSystem.h"                    // for TSystem, gSystem

#include <string.h>                     // for memcpy
#include <iostream>                     // for cout

using std::cout;
using std::endl;
using std::hex;
using std::dec;
using std::string;
using std::ios_base;
using std::vector;

enum Markers { StartMarker = 0xaabbccdd,
               EndMarker   = 0xddbbccaa
             };

void* GetVTptr(const void* obj)
{
  void* ptr;
  memcpy(&ptr,obj,4);
  return ptr;

}
void SetVTptr(void* obj, const void* vt)
{
  memcpy(obj,&vt,4);
}

string FairDbBufferFile::fgWorkDir;
Bool_t FairDbBufferFile::fgReadAccess  = kTRUE;
Bool_t FairDbBufferFile::fgWriteAccess = kTRUE;

FairDbBufferFile::FairDbBufferFile(const char* fileName, Bool_t input )
  :
  fFile(0),
  fReading(input),
  fHasErrors(kFALSE),
  fArrayBuffer(0),
  fFileName(fileName)
{

  // Complete the file name.
  //  fFileName = fileName;
  if ( fFileName != "" ) {
    Bool_t access = input ? fgReadAccess : fgWriteAccess;
    if ( fgWorkDir == "" || ! access ) { fFileName = ""; }
    else { fFileName = fgWorkDir +  fFileName; }
  }

  // Open the file.
  ios_base::openmode mode = ios_base::in|ios_base::binary;
  if ( ! input ) { mode = ios_base::out|ios_base::binary; }

  if ( fFileName == "" ) { fHasErrors = kTRUE; }
  else {
    fFile = new fstream(fFileName.c_str(),mode);
    if ( ! fFile->is_open() || ! fFile->good() ) {
      DBLOG("FairDb",FairDbLog::kWarning) << "Cannot open the file# " << fFileName
                                          << "; all I/O will then fail. !!!" << endl;
      fHasErrors = kTRUE;
    }
  }

}

FairDbBufferFile::~FairDbBufferFile()
{
  delete[] fArrayBuffer;
  fArrayBuffer = 0;
  this->Close();
  delete fFile;
  fFile = 0;

}


void FairDbBufferFile::Close()
{

  if ( fFile ) { fFile->close(); }
}


#define READ_BUILTIN(t)                                   \
                                                          \
FairDbBufferFile& FairDbBufferFile::operator >> (t& v) {        \
  UInt_t numBytes = sizeof(v);                            \
  char* bytes = reinterpret_cast<char*>(&v);              \
  this->Read(bytes,numBytes);                             \
  return *this;                                           \
}
#define WRITE_BUILTIN(t)                                  \
                                                          \
FairDbBufferFile& FairDbBufferFile::operator << (const t& v) {  \
  UInt_t numBytes = sizeof(v);                            \
  const char* bytes = reinterpret_cast<const char*>(&v);  \
  this->Write(bytes,numBytes);                            \
  return *this;                                           \
}

READ_BUILTIN(Bool_t)
WRITE_BUILTIN(Bool_t)
READ_BUILTIN(Int_t)
WRITE_BUILTIN(Int_t)
READ_BUILTIN(UInt_t)
WRITE_BUILTIN(UInt_t)
READ_BUILTIN(Double_t)
WRITE_BUILTIN(Double_t)



#define READ_SIMPLE(t)                                    \
                                                          \
FairDbBufferFile& FairDbBufferFile::operator >> (t& v) {        \
  void* vt = GetVTptr(&v);                                \
  UInt_t numBytes = sizeof(v);                            \
  char* bytes = reinterpret_cast<char*>(&v);              \
  this->Read(bytes,numBytes);                             \
  SetVTptr(&v,vt);                                        \
  return *this;                                           \
}
#define WRITE_SIMPLE(t)                                   \
                                                          \
FairDbBufferFile& FairDbBufferFile::operator << (const t& v) {  \
  UInt_t numBytes = sizeof(v);                            \
  const char* bytes = reinterpret_cast<const char*>(&v);  \
  this->Write(bytes,numBytes);                            \
  return *this;                                           \
}

READ_SIMPLE(ValTimeStamp)
WRITE_BUILTIN(ValTimeStamp)


FairDbBufferFile& FairDbBufferFile::operator >> (string& str)
{

  if ( this->CanRead() ) {
    getline(*fFile,str,'\0');
    this->CheckFileStatus();
  }
  return *this;
}

FairDbBufferFile& FairDbBufferFile::operator << (const string& str)
{

  UInt_t numBytes = str.size()+1;
  this->Write(str.c_str(),numBytes);
  return *this;
}

FairDbBufferFile& FairDbBufferFile::operator >> (ValInterval& vr)
{

  if ( this->CanRead() ) {
    Int_t        detectorMask;
    Int_t        simMask;
    ValTimeStamp timeStart;
    ValTimeStamp timeEnd;
    string str;
    (*this) >> detectorMask
            >> simMask
            >> timeStart
            >> timeEnd
            >> str;
    TString dataSource(str.c_str());
    ValInterval tmp(detectorMask,simMask,timeStart,timeEnd,dataSource);
    vr = tmp;
  }
  return *this;
}

FairDbBufferFile& FairDbBufferFile::operator << (const ValInterval& vr)
{

  if ( this->CanWrite() ) {
    string str(vr.GetDataSource().Data());
    (*this) << vr.GetDetectorMask()
            << vr.GetSimMask()
            << vr.GetTimeStart()
            << vr.GetTimeEnd()
            << str;
  }
  return *this;
}

FairDbBufferFile& FairDbBufferFile::operator >> (vector<FairDbObjTableMap*>& arr)
{
  if ( ! this->CanRead() ) { return *this; }

  if ( arr.size() ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20)  << "Attempting to read into non-empty array" << endl;
    return *this;
  }



  UInt_t marker = 0;
  (*this) >> marker;
  if ( marker != StartMarker ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20)  << "Cannot find start of array marker" << endl;
    this->Close();
    this->CheckFileStatus();
    return *this;
  }


  Int_t arrSize = 0;
  (*this) >> arrSize;

  if ( arrSize ) {
    Int_t objSize  = 0;
    string objName;
    (*this) >> objName >> objSize;


    TClass objClass(objName.c_str());
    Int_t objSizefromRoot = objClass.Size();
    void* obj = objClass.New();
    void* vt  = GetVTptr(obj);

    FairDbObjTableMap* tr = reinterpret_cast<FairDbObjTableMap*>(obj);
    delete tr;

    DBLOG("FairDb",FairDbLog::kInfo)
        << "Restoring array of " << arrSize << " "
        << objName << " objects"
        << "  VTaddr " << hex << vt << dec
        << " object size "  << objSize << "(from file) "
        << objSizefromRoot << "(from ROOT)"
        << endl;

    if ( arrSize < 0 || objSize != objSizefromRoot ) {
      MAXDBLOG("FairDb",FairDbLog::kError,20) << "Illegal  array size ("<< arrSize
                                              << ") or object size(" << objSize
                                              << "," << objSizefromRoot << ")" << endl;
      this->Close();
      this->CheckFileStatus();
      return *this;
    }

//  Allocate buffer
    delete[] fArrayBuffer;
    Int_t buffSize = arrSize*objSize;
    fArrayBuffer = new char[buffSize];
    this->Read(fArrayBuffer,buffSize);

    char* elem = fArrayBuffer;
    arr.reserve(arrSize);
    for (int row = 0; row < arrSize; ++row ) {
      SetVTptr(elem,vt);
      arr.push_back(reinterpret_cast<FairDbObjTableMap*>(elem));
      elem += objSize;
    }

  }

  (*this) >> marker;
  if ( marker != EndMarker ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "Cannot find end of array marker" << endl;
    this->Close();
    this->CheckFileStatus();
  }

  return *this;

}


FairDbBufferFile& FairDbBufferFile::operator << (vector<FairDbObjTableMap*>& arr)
{

  if ( ! this->CanWrite() ) { return *this; }

  UInt_t marker = StartMarker;
  (*this) << marker;
  Int_t arrSize = arr.size();
  (*this) << arrSize;

  if ( arrSize ) {
    FairDbObjTableMap* obj = arr[0];
    Int_t objSize  = obj->IsA()->Size();
    string objName = obj->ClassName();
    (*this) << objName << objSize;
    for (int row = 0; row < arrSize; ++row ) {
      obj = arr[row];
      const char* p = reinterpret_cast<const char*>(arr[row]);
      this->Write(p,objSize);
    }

  }

  marker = EndMarker;
  (*this) << marker;

  return *this;

}


Bool_t FairDbBufferFile::CanRead()
{

  if ( ! fReading ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "Attempting to read from a write-only file" << endl;
    return kFALSE;
  }
  return this->IsOK();

}

Bool_t FairDbBufferFile::CanWrite()
{

  if ( fReading ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20)  << "Attempting to write to a read-only file" << endl;
    return kFALSE;
  }
  return this->IsOK();

}

void FairDbBufferFile::CheckFileStatus()
{
  // File Status

  if (    fFile
          && ! fHasErrors
          && ( ! fFile->is_open() || ! fFile->good() ) ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20)  << "File not open or has gone bad,"
        << " all further I/O will fail." << endl;
    fHasErrors = kTRUE;
    this->Close();

    //Delete file if writing.
    if ( ! fReading ) {
      MAXDBLOG("FairDb",FairDbLog::kError,20)  << "Erasing " << fFileName << endl;
      gSystem->Unlink(fFileName.c_str());
    }

  }

}


Bool_t FairDbBufferFile::Read(char* bytes, UInt_t numBytes)
{
  if ( ! this->CanRead() ) { return kFALSE; }

  fFile->read(bytes,numBytes);
  this->CheckFileStatus();
  return ! fHasErrors;
}


Bool_t FairDbBufferFile::Write(const char* bytes, UInt_t numBytes)
{
  if ( ! this->CanWrite() ) { return kFALSE; }

  fFile->write(bytes,numBytes);
  this->CheckFileStatus();
  return ! fHasErrors;
}

