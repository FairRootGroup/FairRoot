/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbRollbackTimes.h"
#include "FairDbLogService.h"
#include "FairDb.h"                     // for MakeDateTimeString, etc
#include "FairDbString.h"               // for cmp_wildcard
#include "FairRegistry.h"               // for FairRegistry, etc
#include "ValTimeStamp.h"               // for ValTimeStamp

#include "Riosfwd.h"                    // for ostream
#include "TString.h"                    // for TString, etc

#include <cstring>                      // for strncmp
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <iterator>                     // for reverse_iterator, etc
#include <utility>                      // for pair

using std::cout;
using std::endl;

ClassImp(FairDbRollbackTimes)

FairDbRollbackTimes::FairDbRollbackTimes()
  : fTableToDate(), fTableToType()
{
}

FairDbRollbackTimes::~FairDbRollbackTimes()
{

}

const std::string& FairDbRollbackTimes::GetDate(const std::string& tableName) const
{
  static std::string date;

  name_map_t::const_reverse_iterator itr    = fTableToDate.rbegin();
  name_map_t::const_reverse_iterator itrEnd = fTableToDate.rend();
  for (; itr != itrEnd; ++itr)
    if ( ! FairUtilString::cmp_wildcard(tableName,itr->first)
       ) { return itr->second; }
  return date;
}

const std::string& FairDbRollbackTimes::GetType(const std::string& tableName) const
{

  static std::string type("TIMETRANS");  // The default type

  name_map_t::const_reverse_iterator itr    = fTableToType.rbegin();
  name_map_t::const_reverse_iterator itrEnd = fTableToType.rend();
  for (; itr != itrEnd; ++itr)
    if ( ! FairUtilString::cmp_wildcard(tableName,itr->first)
       ) { return itr->second; }
  return type;
}

void FairDbRollbackTimes::Set(FairRegistry& reg)
{

  FairRegistry::FairRegistryKey keyItr(&reg);

  Bool_t  hasChanged = kFALSE;

  const char* key = keyItr();
  while ( key ) {

    const char* nextKey =  keyItr();

    // Process Rollback keys
    if ( ! strncmp("Rollback:",key,9) ) {
      std::string tableName = key+9;
      std::string date;
      const char* dateChars = 0;
      bool  ok = reg.Get(key,dateChars);
      if ( ok ) {
        date = dateChars;
        ValTimeStamp ts(FairDb::MakeTimeStamp(date,&ok));
        date = FairDb::MakeDateTimeString(ts);
      }
      if ( ok ) {

        // trailing spaces out otherwise SQL
        // will fail expressions involving the date.
        int loc = date.size()-1;
        while ( loc && date[loc] == ' ' ) { date.erase(loc--); }

        fTableToDate[tableName] = date;
        hasChanged = kTRUE;

      } else
        DBLOG("FairDb",FairDbLog::kWarning) << "Illegal Rollback registry item: " << key
                                            << " = " << dateChars << endl;
      reg.RemoveKey(key);
    }

    // Process RollbackType keys

    else if ( ! strncmp("RollbackType:",key,13) ) {
      std::string tableName = key+13;
      TString type;
      const char* typeChars = 0;
      bool  ok = reg.Get(key,typeChars);
      if ( ok ) {
        // Convert to upper case and remove any leading or trailing spaces
        type = typeChars;
        type.ToUpper();
        type = type.Strip(TString::kBoth);
        ok = ! type.CompareTo("TIMETRANS") || ! type.CompareTo("TIMEINCR");
      }
      if ( ok ) {
        fTableToType[tableName] = type.Data();
        hasChanged = kTRUE;
      } else
        DBLOG("FairDb",FairDbLog::kWarning) << "Illegal RollbackType registry item: " << key
                                            << " = " << typeChars << endl;
      reg.RemoveKey(key);
    }
    key = nextKey;
  }

  if ( hasChanged ) { this->Show(); }
}

void FairDbRollbackTimes::Show() const
{
  FairDbLogStream logm = DBLOGSTREAM("FairDb",FairDbLog::kInfo);
  logm << "\n\nRollback Status:  ";
  if ( fTableToDate.size() == 0 ) {  logm <<"Not enabled" << endl; }
  else {
    logm << "\n\n  Times: " << endl;
    name_map_t::const_reverse_iterator itr    = fTableToDate.rbegin();
    name_map_t::const_reverse_iterator itrEnd = fTableToDate.rend();
    for (; itr != itrEnd; ++itr) {
      std::string name = itr->first;
      if ( name.size() < 30 ) { name.append(30-name.size(),' '); }
      logm <<"    " << name << "  " << itr->second << endl;
    }
    logm << "\n  Rollback Type is 'TIMETRANS'";
    if ( fTableToType.size() ) {
      logm << " except as follows: " << endl;
      itr    = fTableToType.rbegin();
      itrEnd = fTableToType.rend();
      for (; itr != itrEnd; ++itr) {
        std::string name = itr->first;
        if ( name.size() < 30 ) { name.append(30-name.size(),' '); }
        logm <<"    " << name << "  " << itr->second << endl;
      }
    }
    logm << endl;
  }
}


