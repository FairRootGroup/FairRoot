/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbConfigNotice.h"
#include "FairDbLogService.h"
#include "Riosfwd.h"                    // for istream, ostream

#include <iostream>                     // for operator<<, basic_ostream, etc
#include <string>                       // for operator>>, string

FairDbConfigNotice::FairDbConfigNotice() :
  fCurrent(),
  fDefault(),
  fResult()
{ }

FairDbConfigNotice::FairDbConfigNotice(const FairRegistry& cur, const FairRegistry& defl) :
  fCurrent(cur),
  fDefault(defl),
  fResult()
{ }

FairDbConfigNotice::~FairDbConfigNotice() { }


void FairDbConfigNotice::SetCurrent(const FairRegistry& r)
{
  fCurrent.UnLockValues();
  fCurrent = r;
  fCurrent.LockValues();
}

void FairDbConfigNotice::SetDefault(const FairRegistry& r)
{
  fDefault.UnLockValues();
  fDefault = r;
  fCurrent.LockValues();
}

FairRegistry& FairDbConfigNotice::Query()
{
  FairRegistry::FairRegistryKey rk = fCurrent.Key();

  fResult = fCurrent;
  fResult.UnLockValues();

  const char* k;
  while ( (k=rk()) ) {
    // bool      b;
    char            c;
    const char*     s;
    int             i;
    double          d;
    FairRegistry        r;
    bool isBool   = false;
    bool isChar   = fDefault.Get(k, c);
    bool isString = fDefault.Get(k, s);
    bool isInt    = fDefault.Get(k, i);
    bool isDouble = fDefault.Get(k, d);
    bool isFairRegistry = false;

#define PROMPT(t,c,d) \
 DBLOG("FairDb",FairDbLog::kInfo)  << " "<<t<<" "<<k<<" = ["<<d<<"] "<<c<<" =? ";
    if (isBool) {
    } else if (isChar) {
      char c1, c_in;
      fDefault.Get(k, c1);
      PROMPT("char",c,c1);
      std::cin >> c_in;
      fResult.Set(k, c_in);
    } else if (isString) {
      const char* s1;
      std::string s_in;
      fDefault.Get(k, s1);
      PROMPT("string",s,s1);
      std::cin >> s_in;
      fResult.Set(k, s_in.c_str());
    } else if (isInt) {
      int i1, i_in;
      fDefault.Get(k, i1);
      PROMPT("int",i,i1);
      std::cin >> i_in;
      fResult.Set(k, i_in);
    } else if (isDouble) {
      double d1, d_in;
      fDefault.Get(k, d1);
      PROMPT("double",d,d1);
      std::cin >> d_in;
      fResult.Set(k, d_in);
    } else if (isFairRegistry) {
    }
  }
  return fResult;
}
