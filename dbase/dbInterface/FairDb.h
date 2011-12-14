#ifndef FAIRDB_H
#define FAIRDB_H

#include <map>
#include <string>
#include <iostream>
#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif
#endif
#include "TString.h"
#include "ValContext.h"
#include "ValTimeStamp.h"

using namespace std;

namespace FairDb
{


typedef  Int_t Task;

enum TaskTypes {  kAnyTask     = -1,  // Use to disable task selection in context queries.
                  kDefaultTask = 0
               };

enum TypeRegimes { kRootRegime = 0,
                   kSQLRegime  = 1
                 };



enum DataTypes { kUnknown,
                 kBool,      // concept
                 kChar,      // concept
                 kUChar,     // concept
                 kTiny,
                 kUTiny,
                 kShort,
                 kUShort,
                 kInt,       // concept
                 kUInt,      // concept
                 kLong,
                 kULong,
                 kFloat,     // concept
                 kDouble,
                 kString,    // concept
                 kTString,
                 kDate       // concept
               };


enum DbTypes {  kUnknownDbType = -1,
                kMySQL         = 0,
                kOracle        = 1
             };

enum AbortTest { kDisabled,
                 kTableMissing,
                 kDataMissing
               };

enum {
  // Max local Sequence No
  kMAXLOCALSEQNO   = 99999999,
  // Max. length of a table name
  kMAXTABLENAMELEN = 80
};




// Time gates for each table in secs.
// Used to trim validity searches.
Int_t GetTimeGate(const std::string& tableName);
void SetTimeGate(const  std::string& tableName, Int_t timeGate);


// DateTime conversion utilities.
TString MakeDateTimeString(const ValTimeStamp& timeStamp);
ValTimeStamp MakeTimeStamp(const std::string& sqlDateTime,
                           Bool_t* ok =0);

TString GetValDescr(const char* tableName,
                    Bool_t isTemporary = kFALSE);

Bool_t NotGlobalSeqNo(UInt_t seqNo);
}

#endif  // FAIRDB_H
