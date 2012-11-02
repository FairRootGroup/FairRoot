#include <map>
#include <sstream>
#include <cassert>
#include <cmath>
#include "FairRegistry.h"
#include "FairDbConf.h"
#include "FairDbString.h"


void FairDbConf::RegistryToString(std::string& x, const FairRegistry& r)
{
  FairRegistry::FairRegistryKey rk = r.Key();
  const char* s;

  std::ostringstream ss;
  while ( (s=rk()) ) {
    // Try to extract the value for this key
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
    else if (isRegistry) { ss << reg; } // Don't think this works...
    else { assert("Unknown type or bad key in registry"==0); }
    ss << " ";
  }
  x = ss.str();
}

//......................................................................

void FairDbConf::StringToRegistry(FairRegistry& r, const char* s)
{
//======================================================================
// Convert the string s to a FairRegistry. Format of s is:
//
// toggle=on pdq=true a=1 b=2.0 name=Mark longstring='some long text'
//
//======================================================================
  // Parse string out into keys and values
  int len = strlen(s);
  char* scopy = new char[len+1];
  strcpy(scopy,s);

  // Skip ahead until we find an equal sign
  char* cKey   = 0;
  char* cEqual = 0;
  char* cValue = 0;
  char* cEnd   = 0;
  for (int i=0; i<len; ++i) {
    // Pick off the equal sign...
    if (scopy[i] == '=') {
      cEqual = scopy+i;
      *cEqual = '\0';

      // Step back to find the start of the key
      for (cKey=cEqual-1; *cKey==' ' && cKey>scopy; --cKey) { *cKey = '\0'; }
      for (; *cKey!=' ' && *cKey!=',' && *cKey!='\0' && cKey>scopy; --cKey) { ; }
      for (; *cKey==' ' || *cKey=='\0'; ++cKey) { ; }

      // Step forward to get the start of the value
      for (cValue=cEqual+1; *cValue==' '&&*cValue!='\0'; ++cValue) {
        *cValue = '\0';
      }
      while (*cValue==' ') { ++cValue; }

      // Handle special case of long strings in single or double quotes
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

      // Convert value to correct data type
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
        // Single character stored at char
        if (strlen(cValue)==1) {
          char c = *cValue;
          r.Set(cKey,c);
        } else {
          // Longer string stored as string
          r.Set(cKey,cValue);
        }
      }
    }
    cEqual = cEnd+1;
  }

  delete [] scopy;
}
