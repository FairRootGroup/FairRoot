/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBBUFFERFILE_H
#define FAIRDBBUFFERFILE_H

#include "Riosfwd.h"                    // for fstream

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                    // for Bool_t, UInt_t, kTRUE, etc  
#endif
#endif

#include <fstream>                      // for fstream, ios_base
#include <string>                       // for string
#include <vector>                       // for vector

class FairDbObjTableMap;
class ValTimeStamp;
class ValInterval;


class FairDbBufferFile
{

  public:

    FairDbBufferFile(const char* fileName= "",
                     Bool_t input = kTRUE);
    ~FairDbBufferFile();

    std::string  GetFileName() const { return fFileName; }
    Bool_t  IsOK() const { return ! fHasErrors;}
    Bool_t  IsReading() const { return this->IsOK() && fReading; }
    Bool_t  IsWriting() const { return this->IsOK() && ! fReading; }

    void Close();

// I/O built-in functions

    FairDbBufferFile& operator >> (Bool_t& num);
    FairDbBufferFile& operator << (const Bool_t& num);
    FairDbBufferFile& operator >> (Int_t& num);
    FairDbBufferFile& operator << (const Int_t& num);
    FairDbBufferFile& operator >> (UInt_t& num);
    FairDbBufferFile& operator << (const UInt_t& num);
    FairDbBufferFile& operator >> (Double_t& num);
    FairDbBufferFile& operator << (const Double_t& num);

// Virtual object I/O.

    FairDbBufferFile& operator >> (ValTimeStamp& ts);
    FairDbBufferFile& operator << (const ValTimeStamp& ts);

    FairDbBufferFile& operator >> (std::string& str);
    FairDbBufferFile& operator << (const std::string& str);

// Validity object I/O.

    FairDbBufferFile& operator >> (ValInterval& vr);
    FairDbBufferFile& operator << (const ValInterval& vr);

// Vector object  I/O used for composite

    FairDbBufferFile& operator >>  (std::vector<FairDbObjTableMap*>& arr);
    FairDbBufferFile& operator <<  (std::vector<FairDbObjTableMap*>& arr);

    char* ReleaseArrayBuffer() {
      char* buff = fArrayBuffer;
      fArrayBuffer = 0;
      return buff;
    }

// Control Cache Storage engine
    static Bool_t CanReadCache()  { return fgWorkDir.size() && fgReadAccess; }
    static Bool_t CanWriteCache() { return fgWorkDir.size() && fgWriteAccess; }
    static   void SetWorkDir(const std::string& dir) {
      fgWorkDir = dir;
      if ( fgWorkDir[fgWorkDir.size()-1] != '/' ) { fgWorkDir += '/'; }
    }
    static   void SetReadAccess(Bool_t access = kTRUE) { fgReadAccess = access; }
    static   void SetWriteAccess(Bool_t access = kTRUE) { fgWriteAccess = access; }

  private:

    FairDbBufferFile(const FairDbBufferFile&);
    FairDbBufferFile operator=(const FairDbBufferFile&);

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

#endif  // FAIRDBBUFFERFILE_H
