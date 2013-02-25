
#include <iostream>

#include "TClass.h"
#include "TObject.h"
#include "TSystem.h"


#include "FairDbBinaryFile.h"
#include "FairDbTableRow.h"
#include "ValRange.h"
#include "ValTimeStamp.h"

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
//   Definition of static data members
//   *********************************

string FairDbBinaryFile::fgWorkDir;
Bool_t FairDbBinaryFile::fgReadAccess  = kTRUE;
Bool_t FairDbBinaryFile::fgWriteAccess = kTRUE;

FairDbBinaryFile::FairDbBinaryFile(const char* fileName, Bool_t input )
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
      cout << "Cannot open " << fFileName
           << "; all I/O will fail." << endl;
      fHasErrors = kTRUE;
    }
  }

}
FairDbBinaryFile::~FairDbBinaryFile()
{
  delete[] fArrayBuffer;
  fArrayBuffer = 0;
  this->Close();
  delete fFile;
  fFile = 0;

}
//.....................................................................

void FairDbBinaryFile::Close()
{

  if ( fFile ) { fFile->close(); }
}


#define READ_BUILTIN(t)                                   \
                                                          \
FairDbBinaryFile& FairDbBinaryFile::operator >> (t& v) {        \
  UInt_t numBytes = sizeof(v);                            \
  char* bytes = reinterpret_cast<char*>(&v);              \
  this->Read(bytes,numBytes);                             \
  return *this;                                           \
}
#define WRITE_BUILTIN(t)                                  \
                                                          \
FairDbBinaryFile& FairDbBinaryFile::operator << (const t& v) {  \
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
FairDbBinaryFile& FairDbBinaryFile::operator >> (t& v) {        \
  void* vt = GetVTptr(&v);                                \
  UInt_t numBytes = sizeof(v);                            \
  char* bytes = reinterpret_cast<char*>(&v);              \
  this->Read(bytes,numBytes);                             \
  SetVTptr(&v,vt);                                        \
  return *this;                                           \
}
#define WRITE_SIMPLE(t)                                   \
                                                          \
FairDbBinaryFile& FairDbBinaryFile::operator << (const t& v) {  \
  UInt_t numBytes = sizeof(v);                            \
  const char* bytes = reinterpret_cast<const char*>(&v);  \
  this->Write(bytes,numBytes);                            \
  return *this;                                           \
}

READ_SIMPLE(ValTimeStamp)
WRITE_BUILTIN(ValTimeStamp)


FairDbBinaryFile& FairDbBinaryFile::operator >> (string& str)
{

  if ( this->CanRead() ) {
    getline(*fFile,str,'\0');
    this->CheckFileStatus();
  }
  return *this;
}

FairDbBinaryFile& FairDbBinaryFile::operator << (const string& str)
{

  UInt_t numBytes = str.size()+1;
  this->Write(str.c_str(),numBytes);
  return *this;
}

FairDbBinaryFile& FairDbBinaryFile::operator >> (ValRange& vr)
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
    ValRange tmp(detectorMask,simMask,timeStart,timeEnd,dataSource);
    vr = tmp;
  }
  return *this;
}

FairDbBinaryFile& FairDbBinaryFile::operator << (const ValRange& vr)
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

FairDbBinaryFile& FairDbBinaryFile::operator >> (vector<FairDbTableRow*>& arr)
{
  if ( ! this->CanRead() ) { return *this; }

  if ( arr.size() ) {
    cout << "Attempting to read into non-empty array" << endl;
    return *this;
  }

// Check for start of array marker.

  UInt_t marker = 0;
  (*this) >> marker;
  if ( marker != StartMarker ) {
    cout << "Cannot find start of array marker" << endl;
    this->Close();
    this->CheckFileStatus();
    return *this;
  }

//  Get array size and deal with non-empty arrays.

  Int_t arrSize = 0;
  (*this) >> arrSize;

  if ( arrSize ) {
    Int_t objSize  = 0;
    string objName;
    (*this) >> objName >> objSize;

    //  Ensure that sizes look sensible and use ROOT to instatiate
    //  an example object so that we can get the address of the
    //  virtual table.

    TClass objClass(objName.c_str());
    Int_t objSizefromRoot = objClass.Size();
    void* obj = objClass.New();
    void* vt  = GetVTptr(obj);
    //  This only works if the address of the sub-class object is the same
    //  as the underlying base class, which should be true in this simple case.
    FairDbTableRow* tr = reinterpret_cast<FairDbTableRow*>(obj);
    delete tr;

    cout
        << "Restoring array of " << arrSize << " "
        << objName << " objects"
        << "  VTaddr " << hex << vt << dec
        << " object size "  << objSize << "(from file) "
        << objSizefromRoot << "(from ROOT)"
        << endl;

    if ( arrSize < 0 || objSize != objSizefromRoot ) {
      cout << "Illegal  array size ("<< arrSize
           << ") or object size(" << objSize
           << "," << objSizefromRoot << ")" << endl;
      this->Close();
      this->CheckFileStatus();
      return *this;
    }

//  Allocate buffer and load in array.
    delete[] fArrayBuffer;
    Int_t buffSize = arrSize*objSize;
    fArrayBuffer = new char[buffSize];
    this->Read(fArrayBuffer,buffSize);

//  Fix up VT pointers and populate the vector.

    char* elem = fArrayBuffer;
    arr.reserve(arrSize);
    for (int row = 0; row < arrSize; ++row ) {
      SetVTptr(elem,vt);
      arr.push_back(reinterpret_cast<FairDbTableRow*>(elem));
      elem += objSize;
    }

  }

//  Check for end of array marker.

  (*this) >> marker;
  if ( marker != EndMarker ) {
    cout << "Cannot find end of array marker" << endl;
    this->Close();
    this->CheckFileStatus();
  }

  return *this;

}


FairDbBinaryFile& FairDbBinaryFile::operator << (vector<FairDbTableRow*>& arr)
{

  if ( ! this->CanWrite() ) { return *this; }

  UInt_t marker = StartMarker;
  (*this) << marker;
  Int_t arrSize = arr.size();
  (*this) << arrSize;

  if ( arrSize ) {
    FairDbTableRow* obj = arr[0];
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


Bool_t FairDbBinaryFile::CanRead()
{

  if ( ! fReading ) {
    cout << "Attempting to read from a write-only file" << endl;
    return kFALSE;
  }
  return this->IsOK();

}

Bool_t FairDbBinaryFile::CanWrite()
{

  if ( fReading ) {
    cout << "Attempting to write to a read-only file" << endl;
    return kFALSE;
  }
  return this->IsOK();

}

void FairDbBinaryFile::CheckFileStatus()
{

//  If file was good but has just gone bad, report and close it.
//  Delete it if writing.

  if (    fFile
          && ! fHasErrors
          && ( ! fFile->is_open() || ! fFile->good() ) ) {
    cout << "File not open or has gone bad,"
         << " all further I/O will fail." << endl;
    fHasErrors = kTRUE;
    this->Close();

    //Delete file if writing.
    if ( ! fReading ) {
      cout << "Erasing " << fFileName << endl;
      gSystem->Unlink(fFileName.c_str());
    }

  }

}


Bool_t FairDbBinaryFile::Read(char* bytes, UInt_t numBytes)
{
  if ( ! this->CanRead() ) { return kFALSE; }

  fFile->read(bytes,numBytes);
  this->CheckFileStatus();
  return ! fHasErrors;
}


Bool_t FairDbBinaryFile::Write(const char* bytes, UInt_t numBytes)
{
  if ( ! this->CanWrite() ) { return kFALSE; }

  fFile->write(bytes,numBytes);
  this->CheckFileStatus();
  return ! fHasErrors;
}

