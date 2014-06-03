/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDb.h"

#include "Riosfwd.h"                    // for ostream

#include "TBufferFile.h"
#include "TVirtualStreamerInfo.h"

#include "FairUtilStream.h"
#include "FairDbLogService.h"

#include <map>                          // for map, _Rb_tree_iterator, etc
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <sstream>                      // IWYU pragma: keep
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::hex;
using std::map;
using std::endl;
using std::istringstream;

static std::map<std::string,Int_t> fgTimegateTable;

Int_t FairDb::GetTimeWindow(const std::string& tableName)
{

  std::map<std::string,Int_t>::iterator
  tablePtr = fgTimegateTable.find(tableName);
  if ( tablePtr == fgTimegateTable.end()
     ) { FairDb::SetTimeWindow(tableName,10*24*60*60); }

  DBLOG("FairDb",FairDbLog::kInfo) << " Return time window " << fgTimegateTable[tableName]
                                   << " for " << tableName << endl;

  return fgTimegateTable[tableName];

}

TString FairDb::GetValDefinition(const char* tableName,
                                 Bool_t isTemporary)
{

  TString sql;
  sql += "create ";
  if ( isTemporary ) { sql += "temporary "; }
  sql += "table ";
  sql += tableName;
  sql += "VAL ( ";
  sql += "  SEQNO integer not null primary key,";
  sql += "  TIMESTART datetime not null,";
  sql += "  TIMEEND datetime not null,";
  sql += "  DETID tinyint,";
  sql += "  DATAID tinyint,";
  sql += "  VERSION integer,";
  sql += "  COMPOSITEID integer,";
  sql += "  TIMEINCR datetime not null,";
  sql += "  TIMETRANS datetime not null ) ";
  return sql;
}


ValTimeStamp FairDb::MakeTimeStamp(const std::string& sqlDateTime,
                                   Bool_t* ok)
{

  struct date {
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
  };
  char dummy;

  static string lo = "1970-01-01 00:00:00";
  static string hi = "2038-01-19 03:14:07";

  // Set up defaults from 0:0am today.
  ValTimeStamp nowTS;
  int nowDate = nowTS.GetDate();
  date defaultDate = {nowDate/10000, nowDate/100%100, nowDate%100,0,0,0};
  date input       = defaultDate;

  //  istringstream in(sqlDateTime);
  // in >> input.year >> dummy >> input.month >> dummy >> input.day
  //   >> input.hour >> dummy >> input.min   >> dummy >> input.sec;

  sscanf(sqlDateTime.c_str(),"%d-%d-%d %d:%d:%d",&input.year,&input.month,&input.day,&input.hour,&input.min,&input.sec);

  if ( ok ) { *ok = kTRUE; }
  
  if (  sqlDateTime < lo || sqlDateTime > hi ) {
    if ( ok ) { *ok = kFALSE; }
    else {
      static int bad_date_count = 0;
      if ( ++bad_date_count <= 20 ) {
        const char* last = (bad_date_count == 20) ? "..Last Message.. " : "";

        DBLOG("FairDb",FairDbLog::kError)   << "Bad date string: " << sqlDateTime
                                            << " parsed as "
                                            << input.year  << " "
                                            << input.month << " "
                                            << input.day   << " "
                                            << input.hour  << " "
                                            << input.min   << " "
                                            << input.sec
                                            << "\n    Outside range " << lo
                                            << " to " << hi << last << endl;
      }
    }

    input = defaultDate;
  }
  
  return ValTimeStamp(input.year,input.month,input.day,
                      input.hour,input.min,input.sec);

}

void FairDb::SetLogLevel(Int_t level)
{
  FairDbLogService::Instance()->GetStream("FairDb")->SetLogLevel(level);
}

void FairDb::SetTimeWindow(const std::string& tableName, Int_t timeGate)
{

  if ( timeGate > 15 && timeGate <= 100*24*60*60 ) {
    fgTimegateTable[tableName] = timeGate;
    DBLOG("FairDb",FairDbLog::kInfo) << "Set time window: " << timeGate
                                     << " for: " << tableName << endl;
  } else {
    DBLOG("FairDb",FairDbLog::kWarning) << "Ignore  invalid time window setting "
                                        << timeGate
                                        << " for:" << tableName << endl;
  }
}

Bool_t FairDb::NotGlobalSeqNo(UInt_t seqNo)
{
  return seqNo <= kMAXLOCALSEQNO;
}


TString FairDb::MakeDateTimeString(const ValTimeStamp& timeStamp)
{
  return timeStamp.AsString("s");

}

TString FairDb::StreamAsString(const Int_t* arr, Int_t size)
{
  // ROOT IO is used to create a packed
  // hexadecimal string out of the object

  TBufferFile b_write(TBuffer::kWrite);
  b_write.WriteFastArray(arr,size);
  Char_t* buff =  b_write.Buffer();
  Int_t   ll   = b_write.Length();

  static std::string astr;
  Util::BinToHex(buff,ll,astr);
  return astr.c_str();
}


TString FairDb::StreamAsString(const UInt_t* arr, Int_t size)
{
  // ROOT IO is used to create a packed
  // hexadecimal string out of the object

  TBufferFile b_write(TBuffer::kWrite);
  b_write.WriteFastArray(arr,size);
  Char_t* buff =  b_write.Buffer();
  Int_t   ll   = b_write.Length();

  static std::string astr;
  Util::BinToHex(buff,ll,astr);
  return astr.c_str();
}


TString FairDb::StreamAsString(const Short_t* arr, Int_t size)
{
  // ROOT IO is used to create a packed
  // hexadecimal string out of the object

  TBufferFile b_write(TBuffer::kWrite);
  b_write.WriteFastArray(arr,size);
  Char_t* buff =  b_write.Buffer();
  Int_t   ll   = b_write.Length();

  static std::string astr;
  Util::BinToHex(buff,ll,astr);
  return astr.c_str();
}



TString FairDb::StreamAsString(const UShort_t* arr, Int_t size)
{
  // ROOT IO is used to create a packed
  // hexadecimal string out of the object

  TBufferFile b_write(TBuffer::kWrite);
  b_write.WriteFastArray(arr,size);
  Char_t* buff =  b_write.Buffer();
  Int_t   ll   = b_write.Length();

  static std::string astr;
  Util::BinToHex(buff,ll,astr);
  return astr.c_str();
}



TString FairDb::StreamAsString(const Bool_t* arr, Int_t size)
{
  // ROOT IO is used to create a packed
  // hexadecimal string out of the object

  TBufferFile b_write(TBuffer::kWrite);
  b_write.WriteFastArray(arr,size);
  Char_t* buff =  b_write.Buffer();
  Int_t   ll   = b_write.Length();

  static std::string astr;
  Util::BinToHex(buff,ll,astr);
  return astr.c_str();
}


TString FairDb::StreamAsString(const Float_t* arr, Int_t size)
{
  // ROOT IO is used to create a packed
  // hexadecimal string out of the object

  TBufferFile b_write(TBuffer::kWrite);
  b_write.WriteFastArray(arr,size);
  Char_t* buff =  b_write.Buffer();
  Int_t   ll   = b_write.Length();

  static std::string astr;
  Util::BinToHex(buff,ll,astr);
  return astr.c_str();
}


TString FairDb::StreamAsString(const Double_t* arr, Int_t size)
{
  // ROOT IO is used to create a packed
  // hexadecimal string out of the object

  TBufferFile b_write(TBuffer::kWrite);
  b_write.WriteFastArray(arr,size);
  Char_t* buff =  b_write.Buffer();
  Int_t   ll   = b_write.Length();

  static std::string astr;
  Util::BinToHex(buff,ll,astr);

  return astr.c_str();
}



TString FairDb::StreamAsString(const TObject* obj, Int_t& size)
{
  // ROOT IO is used to create a packed
  // hexadecimal string out of the object

  TObject* cobj = obj->Clone();
  TBufferFile b_write(TBuffer::kWrite);
  cobj->Streamer(b_write);

  Char_t* buff =  b_write.Buffer();
  Int_t   ll   = b_write.Length();

  // Generate Hex from bin
  static std::string str_hex;
  Util::BinToHex(buff,ll,str_hex);

  // Compute the size
  size = ll;
  return str_hex.c_str();
}


