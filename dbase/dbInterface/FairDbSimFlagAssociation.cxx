
#include <iostream>
#include <sstream>
using std::ostringstream;
#include <iostream>
using namespace std;
#include <string>
using std::string;
#include <vector>
using std::vector;


#include "FairDbSimFlagAssociation.h"
#include "FairRegistry.h"
#include "FairDbString.h"

ClassImp(FairDbSimFlagAssociation)

const FairDbSimFlagAssociation* FairDbSimFlagAssociation::fgInstance = 0;


ostream& operator<<(ostream& s, const FairDbSimFlagAssociation& simFlagAss)
{
  simFlagAss.Print(s);
  return s;
}


FairDbSimFlagAssociation::FairDbSimFlagAssociation()
  : fAssociations()
{

  // Connect to global pointer;
  fgInstance = this;

}



FairDbSimFlagAssociation::~FairDbSimFlagAssociation()
{
  // Disconnect from global pointer;
  if ( fgInstance == this ) { fgInstance = 0; }

}
//.....................................................................

FairDbSimFlagAssociation::SimList_t
FairDbSimFlagAssociation::Get(const SimFlag::SimFlag_t value)const
{

  SimMap_t::const_iterator itr = fAssociations.find(value);
  if ( itr != fAssociations.end() ) { return itr->second; }
  SimList_t l;
  l.push_back(value);
  return l;

}


const FairDbSimFlagAssociation& FairDbSimFlagAssociation::Instance()
{

  if ( ! fgInstance ) { new FairDbSimFlagAssociation; }
  // The act of creation will set fgInstance.
  return *fgInstance;

}

void FairDbSimFlagAssociation::Print(ostream& s)const
{

  s << "\n\nSimFlag Association Status:  ";
  if ( fAssociations.size() == 0 ) { s <<"Not enabled" << endl; }
  else {
    s << endl;

    SimMap_t::const_iterator mapItr    = fAssociations.begin();
    SimMap_t::const_iterator mapItrEnd = fAssociations.end();
    while ( mapItr != mapItrEnd ) {

      SimFlag::SimFlag_t value = mapItr->first;
      string name = SimFlag::AsString(value);
      ostringstream buff;
      buff << name << "(" << value << ")";
      name = buff.str();
      if ( name.size() < 20 ) { name.append(20-name.size(),' '); }
      s << name << "maps to: ";

      SimList_t l = mapItr->second;
      SimList_t::const_iterator listItr    = l.begin();
      SimList_t::const_iterator listItrEnd = l.end();
      while ( listItr != listItrEnd ) {
        SimFlag::SimFlag_t v = *listItr;
        string n = SimFlag::AsString(v);
        s << n << "(" << v << ")";
        ++listItr;
        if ( listItr != listItrEnd ) { s << ", "; }
      }
      s << endl;
      ++mapItr;
    }

  }
}


void FairDbSimFlagAssociation::Set(FairRegistry& reg)
{

  FairRegistry::FairRegistryKey keyItr(&reg);

  Bool_t  hasChanged = kFALSE;

  const char* key = keyItr();
  while ( key ) {

    const char* nextKey =  keyItr();
    if ( ! strncmp("SimFlagAssociation:",key,19) ) {

      // Found a SimFlagAssociation key, extract its value.
      string Name = key+19;
      SimFlag::SimFlag_t value = SimFlag::StringToEnum(Name.c_str());
      const char* listChars = 0;
      bool ok = reg.Get(key,listChars) && (value != SimFlag::kUnknown);
      // Collect the associated list
      SimList_t lv;
      if ( ok ) {
        vector<string> ls;
        FairUtilString::StringTok(ls,listChars,",");
        vector<string>::iterator itr    = ls.begin();
        vector<string>::iterator itrEnd = ls.end();
        for (; itr != itrEnd; ++itr ) {
          SimFlag::SimFlag_t v = SimFlag::StringToEnum(itr->c_str());
          if ( v == SimFlag::kUnknown) { ok = false; }
          lv.push_back(v);
        }
      }

      if ( ok ) {
        this->Set(value,lv);
        hasChanged = true;
      } else cout << "Illegal SimFlagAssociation registry item: " << key
                    << " = " << listChars << endl;

      reg.RemoveKey(key);
    }
    key = nextKey;
  }

  if ( hasChanged ) { this->Show(); }
}

//.....................................................................

void FairDbSimFlagAssociation::Show()
{

}

