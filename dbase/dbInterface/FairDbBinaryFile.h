#ifndef FAIRDBBINARYFILE_H
#define FAIRDBBINARYFILE_H

#include "Riosfwd.h"                    // for fstream

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                    // for Bool_t, UInt_t, kTRUE, etc  
#endif
#endif

#include <fstream>                      // for fstream, ios_base
#include <string>                       // for string
#include <vector>                       // for vector

class FairDbTableRow;
class ValTimeStamp;
class ValRange;


class FairDbBinaryFile
{

  public:

    FairDbBinaryFile(const char* fileName= "",
                     Bool_t input = kTRUE);
    ~FairDbBinaryFile();

    std::string  GetFileName() const { return fFileName; }
    Bool_t  IsOK() const { return ! fHasErrors;}
    Bool_t  IsReading() const { return this->IsOK() && fReading; }
    Bool_t  IsWriting() const { return this->IsOK() && ! fReading; }

    void Close();

// I/O built-in functions

    FairDbBinaryFile& operator >> (Bool_t& num);
    FairDbBinaryFile& operator << (const Bool_t& num);
    FairDbBinaryFile& operator >> (Int_t& num);
    FairDbBinaryFile& operator << (const Int_t& num);
    FairDbBinaryFile& operator >> (UInt_t& num);
    FairDbBinaryFile& operator << (const UInt_t& num);
    FairDbBinaryFile& operator >> (Double_t& num);
    FairDbBinaryFile& operator << (const Double_t& num);

// Virtual object I/O.

    FairDbBinaryFile& operator >> (ValTimeStamp& ts);
    FairDbBinaryFile& operator << (const ValTimeStamp& ts);

    FairDbBinaryFile& operator >> (std::string& str);
    FairDbBinaryFile& operator << (const std::string& str);

// Validity object I/O.

    FairDbBinaryFile& operator >> (ValRange& vr);
    FairDbBinaryFile& operator << (const ValRange& vr);

// Vector object  I/O used for composite

    FairDbBinaryFile& operator >>  (std::vector<FairDbTableRow*>& arr);
    FairDbBinaryFile& operator <<  (std::vector<FairDbTableRow*>& arr);

    char* ReleaseArrayBuffer() {
      char* buff = fArrayBuffer;
      fArrayBuffer = 0;
      return buff;
    }

// Control Cache Storage engine
    static Bool_t CanReadL2Cache()  { return fgWorkDir.size() && fgReadAccess; }
    static Bool_t CanWriteL2Cache() { return fgWorkDir.size() && fgWriteAccess; }
    static   void SetWorkDir(const std::string& dir) {
      fgWorkDir = dir;
      if ( fgWorkDir[fgWorkDir.size()-1] != '/' ) { fgWorkDir += '/'; }
    }
    static   void SetReadAccess(Bool_t access = kTRUE) { fgReadAccess = access; }
    static   void SetWriteAccess(Bool_t access = kTRUE) { fgWriteAccess = access; }

  private:

    FairDbBinaryFile(const FairDbBinaryFile&);
    FairDbBinaryFile operator=(const FairDbBinaryFile&);

// Low-level I/O.

    Bool_t CanRead();
    Bool_t CanWrite();
    void CheckFileStatus();

    Bool_t Read(char* bytes, UInt_t numBytes);
    Bool_t Write(const char* bytes, UInt_t numBytes);


#if !defined(__CINT__)
    fstream*  fFile;
#endif

    Bool_t   fReading;
    Bool_t   fHasErrors;
    char*    fArrayBuffer;
    std::string   fFileName;

    static std::string fgWorkDir;
    static Bool_t fgReadAccess;
    static Bool_t fgWriteAccess;

};

#endif  // FAIRDBBINARYFILE_H
