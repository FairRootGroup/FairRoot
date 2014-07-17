/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairRegistry.h"

#include "FairUtilStream.h"             // for read_quoted_string
#include "FairDbLogService.h"
#include "FairRegistryElement.h"           // for FairRegistryElement
#include "FairRegistryElementGeneric.h"        // for FairRegistryElementGeneric

#include "TBuffer.h"                    // for TBuffer, operator<<, etc
#include "TNamed.h"                     // for TNamed

#include <ctype.h>                      // for isspace
#include <string.h>                     // for strcpy, strlen
#include <cassert>                      // for assert
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <map>                          // for _Rb_tree_const_iterator, etc
#include <utility>                      // for pair
#include <sstream>                      // IWYU pragma: keep
// for ostringstream, istringstream

using namespace Util;
using namespace std;

ClassImp(FairRegistry)


FairRegistry::FairRegistry(bool readonly)
  : TNamed(),
    fValuesLocked(readonly),
    fKeysLocked(false),
    fErrorHandler(0),
    fMap(),
    fDirty(true)
{
  this->SetDirty();
}


FairRegistry::FairRegistry(const FairRegistry& rhs)
  : TNamed(rhs),
    fValuesLocked(rhs.fValuesLocked),
    fKeysLocked(rhs.fKeysLocked),
    fErrorHandler(0),
    fMap(),
    fDirty(true)
{
  FairRegistryKey rk = rhs.Key();
  const char* s;

  while ( (s = rk()) ) { fMap[s] = rhs.fMap.find(s)->second->Dup(); }

  //  fValuesLocked = rhs.fValuesLocked;
  //  fKeysLocked   = rhs.fKeysLocked;
  this->SetDirty();
  this->SetName(rhs.GetName());
}

FairRegistry& FairRegistry::operator=(const FairRegistry& rhs)
{
  if (this == &rhs) { return *this; }

  UnLockValues();
  UnLockKeys();

  if (Size() != 0) { Clear(); }

  FairRegistryKey rk = rhs.Key();
  const char* s;

  while ( (s = rk()) ) { fMap[s] = rhs.fMap.find(s)->second->Dup(); }

  fValuesLocked = rhs.fValuesLocked;
  fKeysLocked   = rhs.fKeysLocked;
  this->SetDirty();
  this->SetName(rhs.GetName());

  return *this;
}

void FairRegistry::Merge(const FairRegistry& rhs)
{
  if (this == &rhs) { return; }

  FairRegistryKey rk = rhs.Key();
  const char* s;
  while ( (s = rk()) ) {
    tRegMap::iterator mit = fMap.find(s);
    bool exists = mit != fMap.end();

    if (fKeysLocked && !exists) {

      DBLOG("FairDb",FairDbLog::kWarning)   << "Merge: can't, add new key " << s <<", keys locked."
                                            << "  merger=" << this->GetName()
                                            << ", mergie=" << rhs.GetName() << endl;
      continue;
    }
    if (exists && fValuesLocked) {

      DBLOG("FairDb",FairDbLog::kWarning)<< "Merge: can't, merge key " << s <<", values locked."
                                         << "  merger=" << this->GetName()
                                         << ", mergie=" << rhs.GetName() << endl;
      continue;
    }
    if (exists) { delete mit->second; }
    fMap[s] = rhs.fMap.find(s)->second->Dup();
  }
  this->SetDirty();
}

bool FairRegistry::KeyExists(const char* key) const
{
  return fMap.find(key) != fMap.end();
}

void FairRegistry::RemoveKey(const char* key)
{
  tRegMap::iterator dead = fMap.find(key);
  if (dead == fMap.end()) { return; }
  fMap.erase(dead);
  delete dead->second;
  this->SetDirty();
}

void FairRegistry::Clear(Option_t* /* option */)
{
  if (fValuesLocked || fKeysLocked) {

    DBLOG("FairDb",FairDbLog::kWarning) << "Clear: can't, there are locks in \""
                                        << this->GetName() << "\"\n";
    return;
  }

  tRegMap::iterator mit = fMap.begin();
  while (mit != fMap.end()) {
    delete mit->second;
    ++mit;
  }
  fMap.clear();
  this->SetDirty();
}

void FairRegistry::Dump(void) const
{
  this->TNamed::Dump();
  tRegMap::const_iterator mit = fMap.begin();

  DBLOG("FairDb",FairDbLog::kInfo)<< "FairRegistry: `" << this->GetName() << "', "
                                  << this->Size() << " entries."
                                  << " (Locks: [Keys|Values] `key', `value'):\n";
  while (mit != fMap.end()) {

    DBLOG("FairDb",FairDbLog::kInfo)<< " [" << (fKeysLocked ? 'L' : 'U') << "|"
                                    << (fValuesLocked ? 'L' : 'U') << "] "
                                    << "`" << mit->first << "', `";
    mit->second->Dump();
    DBLOG("FairDb",FairDbLog::kInfo) << "'\n";
    ++mit;
  }

}

ostream& FairRegistry::PrettyPrint(ostream& os) const
{
  static int print_depth = 0;


  tRegMap::const_iterator mit = this->fMap.begin();
  for(int i=0; i<print_depth; ++i) { os << " "; }
  os << "\"" << this->GetName() << "\", "
     << this->Size() << " entries."
     << " keys " << (this->fKeysLocked ? "locked" : "unlocked")
     << ", values " << (this->fValuesLocked ? "locked" : "unlocked")
     << "\n";

  print_depth+=4;
  while (mit != this->fMap.end()) {
    for(int i=0; i<print_depth; ++i) { os << " "; }

    os << mit->first << " = ";
    mit->second->PrintStream(os);
    os << endl;
    ++mit;
  }
  print_depth-=4;
  return os;
}

void FairRegistry::Print(Option_t* ) const
{
  this->PrettyPrint( cout );
}


FairRegistry::~FairRegistry()
{
  tRegMap::iterator mit = fMap.begin();
  while (mit != fMap.end()) {
    delete mit->second;
    ++mit;
  }
}

FairRegistry::FairRegistryKey::FairRegistryKey(const FairRegistry* r) :
  fReg(r),
  fIt()
{
  // CHECKME!
  fIt = const_cast<FairRegistry*>(fReg)->fMap.begin();
}

FairRegistry::FairRegistryKey::FairRegistryKey()
  : fReg(),
    fIt()
{
}

FairRegistry::FairRegistryKey::FairRegistryKey(const FairRegistryKey& rhs)
  : fReg(rhs.fReg),
    fIt(rhs.fIt)
{
}

FairRegistry::FairRegistryKey::~FairRegistryKey()
{
}

const char* FairRegistry::FairRegistryKey::operator()(void)
{
  if (fIt == fReg->fMap.end()) { return 0; }
  const char* s = fIt->first.c_str();
  ++ fIt;
  return s;
}

FairRegistry::FairRegistryKey FairRegistry::Key(void) const
{
  return FairRegistryKey(this);
}

#define REGISTRY_SET(TYPE)                                              \
bool FairRegistry::Set(const char* key, TYPE val)                           \
{                                                                       \
    tRegMap::iterator mit = fMap.find(key);                             \
    if (mit != fMap.end()) {                                            \
        if (fValuesLocked) {                                            \
                DBLOG("FairDb",FairDbLog::kInfo)                           \
               << "Set: Values are locked - not overwriting \""         \
               << key << "\" with \"" << val << "\" in registry \"" << this->GetName() << "\"\n";\
            return false;                                               \
        }                                                               \
        if (!dynamic_cast<FairRegistryElementGeneric<TYPE>*>(mit->second)) {       \
               DBLOG("FairDb",FairDbLog::kInfo)                               \
                << "Set: attempt to overwrite old value for key \""     \
                << key << "\" with different type value "               \
                << val << " in registry \"" << this->GetName() << "\"\n";\
            return false;                                               \
        }                                                               \
        delete mit->second;                                             \
        fMap.erase(mit);                                                \
    }                                                                   \
    else {                                                              \
        if (fKeysLocked) {                                              \
            DBLOG("FairDb",FairDbLog::kWarning)                               \
                 << "Set: Keys are locked - not adding `"               \
                 << key << "' to registry \"" << this->GetName() << "\"\n";\
            return false;                                               \
        }                                                               \
    }                                                                   \
    FairRegistryElement* ri = new FairRegistryElementGeneric< TYPE >(new TYPE (val));     \
    fMap[key] = ri;                                                     \
    this->SetDirty();                                                   \
    return true;                                                        \
}
REGISTRY_SET(char)
REGISTRY_SET(int)
REGISTRY_SET(double)
REGISTRY_SET(FairRegistry)
#undef REGISTRY_SET


// Must treat char* special
bool FairRegistry::Set(const char* key, const char* val)
{
  tRegMap::iterator mit = fMap.find(key);
  if (mit != fMap.end()) {    // Found it
    if (fValuesLocked) {

      DBLOG("FairDb",FairDbLog::kInfo)    << "Set: Values are locked - not overwriting `"
                                          << key << "\" with \"" << val << "\" in registry \"" << this->GetName() << "\"\n";
      return false;
    }
    if (! dynamic_cast<FairRegistryElementGeneric<const char*>*>(mit->second) ) {

      DBLOG("FairDb",FairDbLog::kInfo)   << "Set: attempt to overwrite old value for key \""
                                         << key << "\" with different type value "
                                         << val << " in registry \"" << this->GetName() << "\"\n";
      return false;
    }
    delete mit->second;
    fMap.erase(mit);
  } else {                    // didn't find it
    if (fKeysLocked) {

      DBLOG("FairDb",FairDbLog::kWarning)    << "FairRegistry::Set: Keys are locked - not adding `"
                                             << key << "' in registry \"" << this->GetName() << "\"\n";
      return false;
    }
  }

  char** cpp = new char*;
  (*cpp) = new char [strlen(val)+1];
  strcpy(*cpp,val);
  const char** ccpp = const_cast<const char**>(cpp);
  FairRegistryElement* ri = new FairRegistryElementGeneric< const char* >(ccpp);
  fMap[key] = ri;
  this->SetDirty();
  return true;
}


#define REGISTRY_GET(TYPE)                                      \
bool FairRegistry::Get(const char* key, TYPE & val) const           \
{                                                               \
    tRegMap::const_iterator mit = fMap.find(key);               \
    if (mit == fMap.end()) return false;                        \
    FairRegistryElementGeneric<TYPE>* rix =                                \
        dynamic_cast<FairRegistryElementGeneric<TYPE>*>(mit->second);      \
    if (rix == 0){                                              \
      DBLOG("FairDb",FairDbLog::kInfo) << "Key " << key             \
    << " does not have type "    \
    << #TYPE << " as required"   \
    << endl;                     \
      return false;                                             \
    }                                                           \
    val = *(rix->Get());                                        \
    return true;                                                \
}
REGISTRY_GET(char)
REGISTRY_GET(FairRegistry)
REGISTRY_GET(const char*)
REGISTRY_GET(int)

bool FairRegistry::Get(const char* key, double& val) const
{
  tRegMap::const_iterator mit = fMap.find(key);
  if (mit == fMap.end()) { return false; }
  // try correct type
  FairRegistryElementGeneric<double>* rixd =
    dynamic_cast<FairRegistryElementGeneric<double>*>(mit->second);
  if (rixd) {
    val = *(rixd->Get());
    return true;
  }
  // try int
  FairRegistryElementGeneric<int>* rixi =
    dynamic_cast<FairRegistryElementGeneric<int>*>(mit->second);
  if (rixi) {
    val = *(rixi->Get());
    return true;
  }
  DBLOG("FairDb",FairDbLog::kWarning) << "Key " << key
                                      << " does not have type double or int"
                                      << " as required" << endl;
  return false;
}

#define REGISTRY_GET_TYPE(NAME, RETTYPE, TYPE)                            \
RETTYPE FairRegistry::Get##NAME(const char* key) const                        \
{                                                                         \
    TYPE retval = 0;                                                      \
    if (Get(key,retval)) return retval;                                   \
    if (fErrorHandler) { fErrorHandler(); return 0; }                     \
    else {                                                                \
        DBLOG("FairDb",FairDbLog::kWarning)                                    \
            << "\nFairRegistry::GetTYPE: failed to get value for key \""      \
            << key << "\" from FairRegistry \"" << this->GetName()            \
            << "\".  Aborting\n\n";                                       \
        bool must_get_a_value = false;                                    \
        assert(must_get_a_value);                                         \
        return 0;                                                         \
    }                                                                     \
}

REGISTRY_GET_TYPE(Char, char, char)
REGISTRY_GET_TYPE(CharString, const char*, const char*)
REGISTRY_GET_TYPE(Int, int, int)
REGISTRY_GET_TYPE(Double, double, double)
#undef REGISTRY_GET_TYPE
FairRegistry FairRegistry::GetFairRegistry(const char* key) const
{
  FairRegistry retval;
  if (Get(key,retval)) { return retval; }
  if (fErrorHandler) { fErrorHandler(); return retval; }
  else {

    DBLOG("FairDb",FairDbLog::kError)<< "\nFairRegistry::GetTYPE: failed to get value for key \""
                                     << key << "\" from FairRegistry \"" << this->GetName()
                                     << "\".  Aborting\n\n";
    bool must_get_a_value = false;
    assert(must_get_a_value);
    return retval;
  }
}

const type_info& FairRegistry::GetType(const char* key) const
{
  tRegMap::const_iterator mit = fMap.find(key);
  if (mit == fMap.end()) { return typeid(void); }
  return mit->second->GetType();
}
string FairRegistry::GetTypeAsString(const char* key) const
{
  tRegMap::const_iterator mit = fMap.find(key);
  if (mit == fMap.end()) { return "void"; }
  return mit->second->GetTypeAsString();
}

string FairRegistry::GetValueAsString(const char* key) const
{
  ostringstream os;
  tRegMap::const_iterator mit = fMap.find(key);
  if (mit == fMap.end()) { return ""; }
  mit->second->PrintStream(os);
  return os.str();
}

void FairRegistry::Streamer(TBuffer& b)
{
  int nobjects;

  if (b.IsReading()) {
    Version_t v = b.ReadVersion();
    if (v) {}
    TNamed::Streamer(b);

    b >> nobjects;

    for (int i = 0; i < nobjects; ++i) {

      char tmp[1024];
      b >> tmp;
      string key(tmp);

      FairRegistryElement* ri;
      b >> ri;

      //Set()
      tRegMap::iterator mit = fMap.find(key);
      if (mit != fMap.end()) {
        delete mit->second;
        fMap.erase(mit);
      }
      fMap[key] = ri;

    } //
  } //
  else {
    b.WriteVersion(FairRegistry::IsA());
    TNamed::Streamer(b);

    nobjects = fMap.size();
    b << nobjects;


    DBLOG("FairDb",FairDbLog::kInfo) << "Streamer, Writing "<< nobjects <<" objects\n";

    tRegMap::iterator mit = fMap.begin();
    while (mit != fMap.end()) {
      b << mit->first.c_str();


      DBLOG("FairDb",FairDbLog::kInfo)   << mit->first.c_str() << endl;

      b << mit->second;

      ++mit;
    }
  }
}


std::ostream& FairRegistry::PrintStream(std::ostream& os) const
{
  os << "['" << this->GetName() << "'";

  tRegMap::const_iterator mit, done = fMap.end();
  for (mit = fMap.begin(); mit != done; ++mit) {
    os << " '" << mit->first << "'=(";
    os << mit->second->GetTypeAsString();
    os << ")";
    mit->second->PrintStream(os);
  }

  os << "]";
  return os;
}


static std::istream& bail(std::istream& is)
{

  DBLOG("FairDb",FairDbLog::kWarning) << "FairRegistry::Read(istream&) stream is corrupted !\n";
  return is;
}

std::istream& FairRegistry::ReadStream(std::istream& is)
{
  FairRegistry reg;

  char c;
  if (!is.get(c)) { return bail(is); }
  if (c != '[') {
    is.putback(c);
    return bail(is);
  }
  string name = Util::read_quoted_string(is);
  reg.SetName(name.c_str());

  while (is.get(c)) {
    if (isspace(c)) { continue; }
    if (c == ']') {
      *this = reg;
      return is;
    }
    is.putback(c);


    string key = read_quoted_string(is);
    if (key == "") { return bail(is); }


    if (!is.get(c)) { return bail(is); }


    if (!is.get(c) || c != '(') {
      is.putback(c);
      return bail(is);
    }


    string type;
    while (is.get(c)) {
      if (c == ')') { break; }
      type += c;
    }


    FairRegistryElement* ri = 0;
    if (type == "char") {
      ri = new FairRegistryElementGeneric<char>();
    } else if (type == "int") {
      ri = new FairRegistryElementGeneric<int>();
    } else if (type == "double") {
      ri = new FairRegistryElementGeneric<double>();
    } else if (type == "string") {
      ri = new FairRegistryElementGeneric<const char*>();
    } else if (type == "FairRegistry") {
      ri = new FairRegistryElementGeneric<FairRegistry>();
    } else { return bail(is); }

    ri->ReadStream(is);
    reg.fMap[key] = ri;
  }
  return is;

}
