#include <iostream>
#include "FairDbConfDialog.h"

//......................................................................

FairDbConfDialog::FairDbConfDialog() :
  fCurrent(),
  fDefault(),
  fResult()
{ }

//......................................................................

FairDbConfDialog::FairDbConfDialog(const FairRegistry& cur, const FairRegistry& defl) :
  fCurrent(cur),
  fDefault(defl),
  fResult()
{ }

//......................................................................

FairDbConfDialog::~FairDbConfDialog() { }

//......................................................................

void FairDbConfDialog::SetCurrent(const FairRegistry& r)
{
//======================================================================
// Copy the registry r to the set of values to display as current
// values
//======================================================================
  fCurrent.UnLockValues();
  fCurrent = r;
  fCurrent.LockValues();
}

//......................................................................

void FairDbConfDialog::SetDefault(const FairRegistry& r)
{
//======================================================================
// Copy the registry r to the set of values to display as default values
//======================================================================
  fDefault.UnLockValues();
  fDefault = r;
  fCurrent.LockValues();
}

//......................................................................

FairRegistry& FairDbConfDialog::Query()
{
//======================================================================
// Conduct the dialog with the user to load new values into the
// registry. Return the registry stuffed with the new values.
//======================================================================
  FairRegistry::FairRegistryKey rk = fCurrent.Key();

  // Setup result registry
  fResult = fCurrent;
  fResult.UnLockValues();

  const char* k; // Key name
  while ( (k=rk()) ) {
    // bool      b; // Temp. bool value
    char            c; // Temp. char value
    const char*     s; // Temp. string value
    int             i; // Temp. int value
    double          d; // Temp. double value
    FairRegistry        r; // Temp. FairRegistry value

    // Use the 'current' registry to divine the types of junk...
    // Currently there's no good way to do this and FairRegistry spits
    // warnings at you for even trying...
    bool isBool   = false;
    // bool isBool   = fDefault.Get(k, b);
    bool isChar   = fDefault.Get(k, c);
    bool isString = fDefault.Get(k, s);
    bool isInt    = fDefault.Get(k, i);
    bool isDouble = fDefault.Get(k, d);
    bool isFairRegistry = false;
    // bool isFairRegistry = fCurrent.Get(k, r);

#define PROMPT(t,c,d) \
std::cout << " "<<t<<" "<<k<<" = ["<<d<<"] "<<c<<" =? ";
    // OK, now get the user's input. One "if" per type...
    if (isBool) {
      // bool b1, b_in;
      // fDefault.Get(k, b1);
      // PROMPT("bool",b,b1);
      // std::cin >> b_in;
      // fResult.Set(k, d_in);
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
      // This is OK, FairRegistry allocates space and stores a copy
      // of the string, not just the pointer
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
      // FairRegistry r1, r_in;
      // std::string rins;
      // fDefault.Get(k, r1);
      // PROMPT("FairRegistry",r,r1);
      // std::cin >> r_ins;
      // r_in << r_ins;
      // fResult.Set(k, r_in);
    }
  } // loop over keys
  return fResult;
}
