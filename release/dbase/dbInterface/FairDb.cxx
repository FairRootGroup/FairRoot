#include "FairDb.h"
#include <sstream>

static std::map<std::string,Int_t> fgTimegateTable;

Int_t FairDb::GetTimeGate(const std::string& tableName)
{

  // Set default if looking up table for the first time.
  std::map<std::string,Int_t>::iterator
  tablePtr = fgTimegateTable.find(tableName);
  if ( tablePtr == fgTimegateTable.end()
     ) { FairDb::SetTimeGate(tableName,10*24*60*60); }

  cout << "-I- FairDb:: Returning time gate " << fgTimegateTable[tableName]
       << " for " << tableName << endl;
  return fgTimegateTable[tableName];

}

TString FairDb::GetValDescr(const char* tableName,
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
  sql += "  DETECTORMASK tinyint,";
  sql += "  SIMMASK tinyint,";
  sql += "  TASK integer,";
  sql += "  AGGREGATENO integer,";
  sql += "  CREATIONDATE datetime not null,";
  sql += "  INSERTDATE datetime not null ) ";
  return sql;
}

//.....................................................................

TString FairDb::MakeDateTimeString(const ValTimeStamp& timeStamp)
{
  return timeStamp.AsString("s");

}
//.....................................................................

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

  istringstream in(sqlDateTime);
  in >> input.year >> dummy >> input.month >> dummy >> input.day
     >> input.hour >> dummy >> input.min   >> dummy >> input.sec;

  if ( ok ) { *ok = kTRUE; }
  if (  sqlDateTime < lo || sqlDateTime > hi ) {
    if ( ok ) { *ok = kFALSE; }
    else {
      static int bad_date_count = 0;
      if ( ++bad_date_count <= 20 ) {
        const char* last = (bad_date_count == 20) ? "..Last Message.. " : "";

        cout<< "-I- FairDB:: Bad date string: " << sqlDateTime
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

void FairDb::SetTimeGate(const std::string& tableName, Int_t timeGate)
{

  if ( timeGate > 15 && timeGate <= 100*24*60*60 ) {
    fgTimegateTable[tableName] = timeGate;
    cout << "-I- FairDb:: Setting time gate " << timeGate
         << " for " << tableName << endl;
  } else {
    cout << "-I- FairDb:: Ignoring  invalid time gate setting "
         << timeGate
         << " for " << tableName << endl;
  }
}

Bool_t FairDb::NotGlobalSeqNo(UInt_t seqNo)
{
  return seqNo <= kMAXLOCALSEQNO;
}

