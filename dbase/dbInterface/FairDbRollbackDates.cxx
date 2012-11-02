
#include <cstring>

#include "TString.h"

#include "FairDb.h"
#include "FairDbRollbackDates.h"
#include "FairRegistry.h"
#include "FairDbString.h"
#include "ValTimeStamp.h"

ClassImp(FairDbRollbackDates)

FairDbRollbackDates::FairDbRollbackDates()
  : fTableToDate(), fTableToType()
{
}

FairDbRollbackDates::~FairDbRollbackDates()
{

}

const std::string& FairDbRollbackDates::GetDate(const std::string& tableName) const
{
  static std::string date;

  name_map_t::const_reverse_iterator itr    = fTableToDate.rbegin();
  name_map_t::const_reverse_iterator itrEnd = fTableToDate.rend();
  for (; itr != itrEnd; ++itr)
    if ( ! FairUtilString::cmp_wildcard(tableName,itr->first)
       ) { return itr->second; }
  return date;
}

const std::string& FairDbRollbackDates::GetType(const std::string& tableName) const
{

  static std::string type("INSERTDATE");  // The default type

  name_map_t::const_reverse_iterator itr    = fTableToType.rbegin();
  name_map_t::const_reverse_iterator itrEnd = fTableToType.rend();
  for (; itr != itrEnd; ++itr)
    if ( ! FairUtilString::cmp_wildcard(tableName,itr->first)
       ) { return itr->second; }
  return type;
}

void FairDbRollbackDates::Set(FairRegistry& reg)
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

        // Prune away any trailing spaces - they cause SQL
        // to fail expressions involving the date.
        int loc = date.size()-1;
        while ( loc && date[loc] == ' ' ) { date.erase(loc--); }

        fTableToDate[tableName] = date;
        hasChanged = kTRUE;

      } else
        cout << "Illegal Rollback registry item: " << key
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
        ok = ! type.CompareTo("INSERTDATE") || ! type.CompareTo("CREATIONDATE");
      }
      if ( ok ) {
        fTableToType[tableName] = type.Data();
        hasChanged = kTRUE;
      } else
        cout << "Illegal RollbackType registry item: " << key
             << " = " << typeChars << endl;
      reg.RemoveKey(key);
    }
    key = nextKey;
  }

  if ( hasChanged ) { this->Show(); }
}

void FairDbRollbackDates::Show() const
{

  cout << "\n\nRollback Status:  ";
  if ( fTableToDate.size() == 0 ) { cout <<"Not enabled" << endl; }
  else {
    cout << "\n\n  Dates:- " << endl;
    name_map_t::const_reverse_iterator itr    = fTableToDate.rbegin();
    name_map_t::const_reverse_iterator itrEnd = fTableToDate.rend();
    for (; itr != itrEnd; ++itr) {
      std::string name = itr->first;
      if ( name.size() < 30 ) { name.append(30-name.size(),' '); }
      cout <<"    " << name << "  " << itr->second << endl;
    }
    cout << "\n  Rollback Type is 'INSERTDATE'";
    if ( fTableToType.size() ) {
      cout << " except as follows:- " << endl;
      itr    = fTableToType.rbegin();
      itrEnd = fTableToType.rend();
      for (; itr != itrEnd; ++itr) {
        std::string name = itr->first;
        if ( name.size() < 30 ) { name.append(30-name.size(),' '); }
        cout <<"    " << name << "  " << itr->second << endl;
      }
    }
    cout << endl;
  }
}


