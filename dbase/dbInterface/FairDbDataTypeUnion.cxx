/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbDataTypeUnion.h"

#include "FairDbString.h"               // for StringTok
#include "FairRegistry.h"               // for FairRegistry, etc
#include "FairDbLogService.h"
#include "Riosfwd.h"                    // for ostream

#include <string.h>                     // for strncmp
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <string>                       // for string, char_traits, etc
#include <utility>                      // for pair
#include <vector>                       // for vector, vector<>::iterator

using std::ostringstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;

ClassImp(FairDbDataTypeUnion)

const FairDbDataTypeUnion* FairDbDataTypeUnion::fgInstance = 0;


ostream& operator<<(ostream& s, const FairDbDataTypeUnion& dataFlagAss)
{
  dataFlagAss.Print(s);
  return s;
}


FairDbDataTypeUnion::FairDbDataTypeUnion()
  : fUnions()
{
  fgInstance = this;
}



FairDbDataTypeUnion::~FairDbDataTypeUnion()
{
  if ( fgInstance == this ) { fgInstance = 0; }
}


FairDbDataTypeUnion::SimList_t
FairDbDataTypeUnion::Get(const DataType::DataType_t value)const
{
  SimMap_t::const_iterator itr = fUnions.find(value);
  if ( itr != fUnions.end() ) { return itr->second; }
  SimList_t l;
  l.push_back(value);
  return l;
}


const FairDbDataTypeUnion& FairDbDataTypeUnion::Instance()
{
  if ( ! fgInstance ) { new FairDbDataTypeUnion; }
  return *fgInstance;
}

void FairDbDataTypeUnion::Print(ostream& s)const
{

  s << "\n\nDataType Union Status:  ";
  if ( fUnions.size() == 0 ) { s <<"Not enabled" << endl; }
  else {
    s << endl;

    SimMap_t::const_iterator mapItr    = fUnions.begin();
    SimMap_t::const_iterator mapItrEnd = fUnions.end();
    while ( mapItr != mapItrEnd ) {

      DataType::DataType_t value = mapItr->first;
      string name = DataType::AsString(value);
      ostringstream buff;
      buff << name << "(" << value << ")";
      name = buff.str();
      if ( name.size() < 20 ) { name.append(20-name.size(),' '); }
      s << name << "maps to: ";

      SimList_t l = mapItr->second;
      SimList_t::const_iterator listItr    = l.begin();
      SimList_t::const_iterator listItrEnd = l.end();
      while ( listItr != listItrEnd ) {
        DataType::DataType_t v = *listItr;
        string n = DataType::AsString(v);
        s << n << "(" << v << ")";
        ++listItr;
        if ( listItr != listItrEnd ) { s << ", "; }
      }
      s << endl;
      ++mapItr;
    }

  }
}


void FairDbDataTypeUnion::Set(FairRegistry& reg)
{

  FairRegistry::FairRegistryKey keyItr(&reg);

  Bool_t  hasChanged = kFALSE;

  const char* key = keyItr();
  while ( key ) {

    const char* nextKey =  keyItr();
    if ( ! strncmp("DataTypeUnion:",key,19) ) {

      // Found a DataTypeUnion key, extract its value.
      string Name = key+19;
      DataType::DataType_t value = DataType::StringToEnum(Name.c_str());
      const char* listChars = 0;
      bool ok = reg.Get(key,listChars) && (value != DataType::kUnknown);
      // Collect the associated list
      SimList_t lv;
      if ( ok ) {
        vector<string> ls;
        FairUtilString::StringTok(ls,listChars,",");
        vector<string>::iterator itr    = ls.begin();
        vector<string>::iterator itrEnd = ls.end();
        for (; itr != itrEnd; ++itr ) {
          DataType::DataType_t v = DataType::StringToEnum(itr->c_str());
          if ( v == DataType::kUnknown) { ok = false; }
          lv.push_back(v);
        }
      }

      if ( ok ) {
        this->Set(value,lv);
        hasChanged = true;
      } else  DBLOG("FairDb",FairDbLog::kWarning) << "Illegal DataTypeUnion registry item: " << key
            << " = " << listChars << endl;

      reg.RemoveKey(key);
    }
    key = nextKey;
  }

  if ( hasChanged ) { this->Show(); }
}


void FairDbDataTypeUnion::Show()
{
}

