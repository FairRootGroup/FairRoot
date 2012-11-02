#ifndef FAIRDBBINARYFILE_H
#define FAIRDBBINARYFILE_H

#include <fstream>
using std::fstream;
using std::ios_base;

#include <string>
using std::string;

#include <vector>
using std::vector;

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif
#endif

class FairDbTableRow;
class ValTimeStamp;
class ValRange;

class FairDbBinaryFile
{

  public:

    FairDbBinaryFile(const char* fileName= "",
                     Bool_t input = kTRUE);
    ~FairDbBinaryFile();

// State testing.

    string  GetFileName() const { return fFileName; }
    Bool_t  IsOK() const { return ! fHasErrors;}
    Bool_t  IsReading() const { return this->IsOK() && fReading; }
    Bool_t  IsWriting() const { return this->IsOK() && ! fReading; }

// State changing.

    void Close();

// Builtin data type I/O.

    FairDbBinaryFile& operator >> (Bool_t& num);
    FairDbBinaryFile& operator << (const Bool_t& num);
    FairDbBinaryFile& operator >> (Int_t& num);
    FairDbBinaryFile& operator << (const Int_t& num);
    FairDbBinaryFile& operator >> (UInt_t& num);
    FairDbBinaryFile& operator << (const UInt_t& num);
    FairDbBinaryFile& operator >> (Double_t& num);
    FairDbBinaryFile& operator << (const Double_t& num);

// Simple Virtual object I/O.
// (i.e. object with vptr but only built-in data types)

    FairDbBinaryFile& operator >> (ValTimeStamp& ts);
    FairDbBinaryFile& operator << (const ValTimeStamp& ts);

// String I/O.
// Warning: Implimentation assumes that string does not contain
//          a null character.

    FairDbBinaryFile& operator >> (string& str);
    FairDbBinaryFile& operator << (const string& str);

// Compound object I/O.

    FairDbBinaryFile& operator >> (ValRange& vr);
    FairDbBinaryFile& operator << (const ValRange& vr);

// Vector I/O.

    FairDbBinaryFile& operator >>  (vector<FairDbTableRow*>& arr);
    FairDbBinaryFile& operator <<  (vector<FairDbTableRow*>& arr);
    char* ReleaseArrayBuffer() {
      char* buff = fArrayBuffer;
      fArrayBuffer = 0;
      return buff;
    }

// Global control of all created FairDbBinaryFile objects.

    static Bool_t CanReadL2Cache()  { return fgWorkDir.size() && fgReadAccess; }
    static Bool_t CanWriteL2Cache() { return fgWorkDir.size() && fgWriteAccess; }
    static   void SetWorkDir(const string& dir) {
      fgWorkDir = dir;
      if ( fgWorkDir[fgWorkDir.size()-1] != '/' ) { fgWorkDir += '/'; }
    }
    static   void SetReadAccess(Bool_t access = kTRUE) { fgReadAccess = access; }
    static   void SetWriteAccess(Bool_t access = kTRUE) { fgWriteAccess = access; }

  private:

    FairDbBinaryFile(const FairDbBinaryFile&);
    FairDbBinaryFile operator=(const FairDbBinaryFile&);

// The functions that do the low-level I/O.

    Bool_t CanRead();
    Bool_t CanWrite();
    void CheckFileStatus();

    Bool_t Read(char* bytes, UInt_t numBytes);
    Bool_t Write(const char* bytes, UInt_t numBytes);

// CINT does not recognise fstream; only ifstream and ofstream.
#if !defined(__CINT__)

/// Associated file, may be null.
    fstream*  fFile;
#endif

    Bool_t   fReading;
    Bool_t   fHasErrors;
    char*    fArrayBuffer;
    string   fFileName;

    static string fgWorkDir;    //Level 2 Cache directory or null if none.
    static Bool_t fgReadAccess; //Have read access if true.
    static Bool_t fgWriteAccess;//Have write access if true.

};

#endif  // FAIRDBBINARYFILE_H
