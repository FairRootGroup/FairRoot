/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairRegistryElementGeneric.h"

#include "FairRegistry.h"               // for FairRegistry
#include "FairRegistryElement.h"           // for FairRegistryElement
#include "FairUtilStream.h"             // for read_quoted_string

#include "TBuffer.h"                    // for TBuffer, operator<<, etc

#include <string.h>                     // for strcpy, strlen
#include <string>                       // for string

using namespace std;

#if (__GNUC__ == 3 && __GNUC_MINOR__ >= 3) || (__GNUC__ >=4 )
template<> const char* FairRegistryElementGeneric<char>::GetTypeAsString(void) const
{ return "char"; }

template<> const char* FairRegistryElementGeneric<int>::GetTypeAsString(void) const
{ return "int"; }

template<> const char* FairRegistryElementGeneric<double>::GetTypeAsString(void) const
{ return "double"; }

template<> const char* FairRegistryElementGeneric<const char*>::GetTypeAsString(void) const
{ return "string"; }

template<> const char* FairRegistryElementGeneric<FairRegistry>::GetTypeAsString(void) const
{ return "FairRegistry"; }

template<> std::ostream& FairRegistryElementGeneric<FairRegistry>::PrintStream(std::ostream& os) const
{ return fData->PrintStream(os); }

template<> std::istream& FairRegistryElementGeneric<FairRegistry>::ReadStream(std::istream& is)
{ if (!fData) { fData = new FairRegistry(); } return fData->ReadStream(is); }
#endif

TBuffer& operator>>(TBuffer& buf, int*& xptr)
{
  int x;
  buf >> x;
  xptr = new int(x);
  return buf;
}
TBuffer& operator>>(TBuffer& buf, double*& xptr)
{
  double x;
  buf >> x;
  xptr = new double(x);
  return buf;
}
TBuffer& operator>>(TBuffer& buf, float*& xptr)
{
  float x;
  buf >> x;
  xptr = new float(x);
  return buf;
}

#if 0
TBuffer& operator>>(TBuffer& buf, bool*& xptr)
{
  int i;
  buf >> i;
  if (i) { xptr = new bool(true); }
  else { xptr = new bool(false); }
  return buf;
}
#endif

//......................................

TBuffer& operator<<(TBuffer& buf, int*& xptr)
{
  buf << *xptr;
  return buf;
}
TBuffer& operator<<(TBuffer& buf, double*& xptr)
{
  buf << *xptr;
  return buf;
}
TBuffer& operator<<(TBuffer& buf, float*& xptr)
{
  buf << *xptr;
  return buf;
}
#if 0
TBuffer& operator<<(TBuffer& buf, bool*& xptr)
{
  buf << (*xptr ? 1 : 0);
  return buf;
}
#endif

#if 0
TBuffer& operator<<(TBuffer& buf, const char*& xptr)
{
  const char* x = xptr;
  --x;
  do {
    ++x;
    buf  << *x;
  } while (*x);
  return buf;
}
#endif

template<>
void FairRegistryElementGeneric<const char*>::Streamer(TBuffer& buf)
{
  if (buf.IsReading()) {
    Version_t v = buf.ReadVersion();
    if (v) { }
    FairRegistryElement::Streamer(buf);

    std::string str = "";
    char x[2];
    x[1] = '\0';

    do {
      buf >> x[0];
      str += x;
    } while (x[0]);

    char** ppchar = new char*;
    *ppchar = new char[str.length() + 1];
    strcpy(*ppchar,str.c_str());
    (*ppchar)[str.length()] = '\0';
    fData = const_cast<const char**>(ppchar);
  } else {
    buf.WriteVersion(IsA());
    FairRegistryElement::Streamer(buf);
    buf << (*fData);
  }
}




template<>
void FairRegistryElementGeneric<char>::Streamer(TBuffer& buf)
{
  if (buf.IsReading()) {
    Version_t v = buf.ReadVersion();
    if (v) { }
    FairRegistryElement::Streamer(buf);

    char c;
    buf >> c;
    fData = new char(c);
  } else {
    buf.WriteVersion(IsA());
    FairRegistryElement::Streamer(buf);
    buf << *fData;
  }
}

template<>
std::ostream& FairRegistryElementGeneric<const char*>::PrintStream(std::ostream& os) const
{
  os << "'" << *fData << "'";
  return os;
}

template<>
std::istream& FairRegistryElementGeneric<const char*>::ReadStream(std::istream& is)
{
  string stot = Util::read_quoted_string(is);

  if (!fData) {
    char** ppchar = new char*;
    *ppchar = 0;
    fData = const_cast<const char**>(ppchar);
  }
  if (*fData) { delete [] *fData; }

  char* pchar = new char[stot.length() + 1];
  strcpy(pchar,stot.c_str());
  *fData = const_cast<const char*>(pchar);
  return is;
}


template<>
FairRegistryElementGeneric<const char*>::~FairRegistryElementGeneric()
{
  if (fData) {
    if (*fData) {
      delete [] *fData;
      *fData = 0;
    }
    delete fData;
    fData = 0;
  }
}

template<>
FairRegistryElement* FairRegistryElementGeneric<const char*>::Dup(void) const
{
  char** ppc = new char*;
  (*ppc) = new char [strlen(*fData)+1];
  strcpy(*ppc,*fData);
  const char** ppcc = const_cast<const char**>(ppc);
  return new FairRegistryElementGeneric< const char* >(ppcc);
}

