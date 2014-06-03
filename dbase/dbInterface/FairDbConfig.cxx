/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbConfig.h"

#include "FairDbString.h"               // for IsBool, IsFloat, IsInt, etc
#include "FairRegistry.h"               // for FairRegistry, etc

#include "Riosfwd.h"                    // for ostream

#include <cmath>                        // IWYU pragma: keep for rint
// IWYU pragma: no_include <architecture/i386/math.h>
#include <string.h>                     // for strlen, strcpy
#include <cassert>                      // for assert
#include <cstdlib>                      // for atof, atoi
#include <sstream>                      // for operator<<, basic_ostream, etc

void FairDbConfig::RegistryToString(std::string& x, const FairRegistry& r)
{
  FairRegistry::FairRegistryKey rk = r.Key();
  const char* s;

  std::ostringstream ss;
  while ( (s=rk()) ) {
    char        c   = 0;
    const char* cs  = 0;
    int         i   = 0;
    double      d   = 0;
    FairRegistry    reg;
    bool isChar     = r.Get(s,c);
    bool isCharStar = r.Get(s,cs);
    bool isInt      = r.Get(s,i);
    bool isDouble   = r.Get(s,d);
    bool isRegistry = r.Get(s,reg);

    ss << s << "=";
    if      (isChar)     { ss << c;  }
    else if (isCharStar) { ss << "'"<<cs<<"'"; }
    else if (isInt)      { ss << i;  }
    else if (isDouble)   { ss << d; if (rint(d)==d) { ss << ".0"; } }
    else if (isRegistry) { ss << reg; }
    else { assert("Unknown type or bad key in registry"==0); }
    ss << " ";
  }
  x = ss.str();
}


void FairDbConfig::StringToRegistry(FairRegistry& r, const char* s)
{
  int len = strlen(s);
  char* scopy = new char[len+1];
  strcpy(scopy,s);

  char* cKey   = 0;
  char* cEqual = 0;
  char* cValue = 0;
  char* cEnd   = 0;
  for (int i=0; i<len; ++i) {

    if (scopy[i] == '=') {
      cEqual = scopy+i;
      *cEqual = '\0';

      for (cKey=cEqual-1; *cKey==' ' && cKey>scopy; --cKey) { *cKey = '\0'; }
      for (; *cKey!=' ' && *cKey!=',' && *cKey!='\0' && cKey>scopy; --cKey) { ; }
      for (; *cKey==' ' || *cKey=='\0'; ++cKey) { ; }

      for (cValue=cEqual+1; *cValue==' '&&*cValue!='\0'; ++cValue) {
        *cValue = '\0';
      }
      while (*cValue==' ') { ++cValue; }

      bool isString = false;
      if (*cValue=='\'' || *cValue=='\"') {
        isString = true;
        char stringDelim = *cValue;
        ++cValue;
        for (cEnd = cValue; *cEnd!='\0' && *cEnd!=stringDelim; ++cEnd) { ; }
      } else {
        for (cEnd = cValue; *cEnd!='\0'&& *cEnd!=' '&& *cEnd!=','; ++cEnd) { ; }
      }
      *cEnd = '\0';

      if ( isString ) {
        r.Set(cKey,cValue);
      } else if (FairUtilString::IsInt(cValue)) {
        int val = atoi(cValue);
        r.Set(cKey,val);
      } else if (FairUtilString::IsFloat(cValue)) {
        double d = atof(cValue);
        r.Set(cKey,d);
      } else if (FairUtilString::IsBool(cValue)) {
        bool b = FairUtilString::atob(cValue);
        r.Set(cKey,b);
      } else {
        if (strlen(cValue)==1) {
          char c = *cValue;
          r.Set(cKey,c);
        } else {
          r.Set(cKey,cValue);
        }
      }
    }
    cEqual = cEnd+1;
  }

  delete [] scopy;
}
