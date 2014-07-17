/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRREGISTRYELEMENTGENERIC_H
#define FAIRREGISTRYELEMENTGENERIC_H

#include "FairRegistryElement.h"           // for FairRegistryElement

#include "TBuffer.h"                    // for TBuffer
#include "Riosfwd.h"                    // for ostream, istream
#include "Rtypeinfo.h"                  // for type_info
#include "Rtypes.h"                     // for FairRegistryElement::Streamer, etc

#include <iostream>                     // IWYU pragma: keep
#include <typeinfo>                     // for type_info
class FairRegistry;

template<class T> class FairRegistryElementGeneric : public FairRegistryElement
{
  public:

    friend class FairRegistry;

    FairRegistryElementGeneric();
    ~FairRegistryElementGeneric();

    void Dump() const { std::cerr << *fData; }
    void Print(Option_t* opt ="") const { std::cout << *fData; }

    virtual std::ostream& PrintStream(std::ostream& os) const {
      return os << *fData;
    }
    virtual std::istream& ReadStream(std::istream& is) {
      if (!fData) { fData = new T; }
      return is >> *fData;
    }

    virtual const type_info& GetType() const { return typeid(T); }
    virtual const char* GetTypeAsString() const { return "void"; }

  private:

    FairRegistryElementGeneric(T* data);
    T* Get(void);               //
    void Set(T* data);          //
    FairRegistryElement* Dup(void) const;

    T* fData;

    FairRegistryElementGeneric(const FairRegistryElementGeneric&);
    FairRegistryElementGeneric operator=(const FairRegistryElementGeneric&);

    ClassDefT(FairRegistryElementGeneric<T>,1)
};
ClassDefT2(FairRegistryElementGeneric,T)


TBuffer& operator>>(TBuffer& buf, int*& xptr);
TBuffer& operator>>(TBuffer& buf, double*& xptr);
TBuffer& operator>>(TBuffer& buf, float*& xptr);

TBuffer& operator<<(TBuffer& buf, int*& xptr);
TBuffer& operator<<(TBuffer& buf, double*& xptr);
TBuffer& operator<<(TBuffer& buf, float*& xptr);

#ifndef __CINT__

ClassImpT(FairRegistryElementGeneric,T)

template<class T>
FairRegistryElementGeneric<T>::FairRegistryElementGeneric(void) : fData(0)
{
}

template<class T>
FairRegistryElementGeneric<T>::FairRegistryElementGeneric(T* data) : fData(data)
{
}

template<class T>
FairRegistryElementGeneric<T>::~FairRegistryElementGeneric()
{
  if (fData) { delete fData; }
}

template<class T>
FairRegistryElement* FairRegistryElementGeneric<T>::Dup(void) const
{
  return new FairRegistryElementGeneric<T>(new T (*fData));
}
// see FairRegistryElementGeneric.cxx for implementation
template<>
FairRegistryElement* FairRegistryElementGeneric<const char*>::Dup(void) const;


template<class T>
T* FairRegistryElementGeneric<T>::Get(void)
{
  return fData;
}

template<class T>
void FairRegistryElementGeneric<T>::Set(T* data)
{
  if (fData) { delete fData; }
  fData = data;
}



template<>
void FairRegistryElementGeneric<const char*>::Streamer(TBuffer& buf);
template<>
void FairRegistryElementGeneric<char>::Streamer(TBuffer& buf);
template<>
FairRegistryElementGeneric<const char*>::~FairRegistryElementGeneric();

template<> std::ostream& FairRegistryElementGeneric<const char*>::PrintStream(std::ostream& os) const;
template<> std::istream& FairRegistryElementGeneric<const char*>::ReadStream(std::istream& is);
template<> const char* FairRegistryElementGeneric<char>::GetTypeAsString(void) const;
template<> const char* FairRegistryElementGeneric<int>::GetTypeAsString(void) const;
template<> const char* FairRegistryElementGeneric<double>::GetTypeAsString(void) const;
template<> const char* FairRegistryElementGeneric<const char*>::GetTypeAsString(void) const;
template<> const char* FairRegistryElementGeneric<FairRegistry>::GetTypeAsString(void) const;

#if (__GNUC__ == 3 && __GNUC_MINOR__ < 3) || __GNUC__ == 2

#include <FairRegistry.h>

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


template<class T>
void FairRegistryElementGeneric<T>::Streamer(TBuffer& buf)
{
  if (buf.IsReading()) {
    Version_t v = buf.ReadVersion();
    if (v) { }
    FairRegistryElement::Streamer(buf);

    buf >> fData;
  } else {
    buf.WriteVersion(IsA());
    FairRegistryElement::Streamer(buf);
    buf << fData;
  }
}


template<>
std::ostream& FairRegistryElementGeneric<FairRegistry>::PrintStream(std::ostream& os) const;

template<>
std::istream& FairRegistryElementGeneric<FairRegistry>::ReadStream(std::istream& is);

#endif // __CINT__


#endif  // FAIRREGISTRYELEMENTGENERIC_H
