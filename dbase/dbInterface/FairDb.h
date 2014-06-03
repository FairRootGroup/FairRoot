/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDB_H
#define FAIRDB_H

#include "ValTimeStamp.h"               // for ValTimeStamp

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                     // for Bool_t, Int_t, kFALSE, etc
#endif
#endif

#include "TString.h"                    // for TString

#include <string>                       // for string

// IWYU pragma: no_include "Rtypes.h"

namespace FairDb
{


typedef  Int_t Version;

enum VersionTypes {  kAnyVersion     = -1,  // Use to disable versioning select in ext. context queries.
                     kDefaultVersion = 0,
                     kOtherVersion = 1      
                  };

enum TypeRegimes { kRootRegime = 0,
                   kSQLRegime  = 1
                 };



enum DataTypes { kUnknown,
                 kBool,
                 kChar,
                 kUChar,
                 kTiny,
                 kUTiny,
                 kShort,
                 kUShort,
                 kInt,
                 kUInt,
                 kLong,
                 kULong,
                 kFloat,
                 kDouble,
                 kString,
                 kTString,
                 kDate,
                 kBinary
               };


enum DbTypes {  kUnknownDbType = -1,
                kMySQL         = 0,
                kOracle        = 1,
                kPostgreSQL    = 2,
                kSQLite        = 3
             };

enum AbortTest { kDisabled,
                 kTableMissing,
                 kDataMissing
               };

enum {
  kMAXLOCALSEQNO   = 99999999,
  kMAXTABLENAMELEN = 80
};


// Time intervals for  table in secs.
Int_t GetTimeWindow(const std::string& tableName);
void SetTimeWindow(const  std::string& tableName, Int_t timeGate);

TString GetValDefinition(const char* tableName,
                         Bool_t isTemporary = kFALSE);
Bool_t NotGlobalSeqNo(UInt_t seqNo);

// Complex type  conversion utility functions
TString MakeDateTimeString(const ValTimeStamp& timeStamp);
ValTimeStamp MakeTimeStamp(const std::string& sqlDateTime,Bool_t* ok =0);

TString StreamAsString(const Int_t* arr, Int_t size);
TString StreamAsString(const UInt_t* arr, Int_t size);
TString StreamAsString(const Short_t* arr, Int_t size);
TString StreamAsString(const UShort_t* arr, Int_t size);
TString StreamAsString(const Bool_t* arr, Int_t size);
TString StreamAsString(const Float_t* arr, Int_t size);
TString StreamAsString(const Double_t* arr, Int_t size);
TString StreamAsString(const TObject* obj, Int_t& size);

// Logging System
void SetLogLevel(Int_t level);
}

#endif  // FAIRDB_H
