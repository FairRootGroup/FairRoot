
#ifndef FAIRREGISTRYITEMXXX_H
#define FAIRREGISTRYITEMXXX_H

#include <TBuffer.h>
#include <TObject.h>

#include <FairRegistryItem.h>

#include <typeinfo>
#include <iostream>

template<class T> class FairRegistryItemXxx : public FairRegistryItem
{
  public:
    // Only Want FairRegistry to call Get/Set/etc methods
    friend class FairRegistry;

    FairRegistryItemXxx();
    ~FairRegistryItemXxx();

    void Dump() const { std::cerr << *fData; }
    void Print(Option_t* /* option */ ="") const { std::cout << *fData; }

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

    FairRegistryItemXxx(T* data);
    T* Get(void);               // Only let FairRegistry call
    void Set(T* data);          // these methods.
    FairRegistryItem* Dup(void) const;

    T* fData;

    ClassDefT(FairRegistryItemXxx<T>,1)
};
ClassDefT2(FairRegistryItemXxx,T)


// Provide these so C++ base types act like ROOT types inside
// a ROOT Streamer function.  This lets the same template to be used.
TBuffer& operator>>(TBuffer& buf, int*& xptr);
TBuffer& operator>>(TBuffer& buf, double*& xptr);
TBuffer& operator>>(TBuffer& buf, float*& xptr);

TBuffer& operator<<(TBuffer& buf, int*& xptr);
TBuffer& operator<<(TBuffer& buf, double*& xptr);
TBuffer& operator<<(TBuffer& buf, float*& xptr);

#ifndef __CINT__
#include <iostream>

ClassImpT(FairRegistryItemXxx,T)

template<class T>
FairRegistryItemXxx<T>::FairRegistryItemXxx(void) : fData(0)
{
}

template<class T>
FairRegistryItemXxx<T>::FairRegistryItemXxx(T* data) : fData(data)
{
}

template<class T>
FairRegistryItemXxx<T>::~FairRegistryItemXxx()
{
  if (fData) { delete fData; }
}

template<class T>
FairRegistryItem* FairRegistryItemXxx<T>::Dup(void) const
{
  return new FairRegistryItemXxx<T>(new T (*fData));
}
// see FairRegistryItemXxx.cxx for implementation
template<>
FairRegistryItem* FairRegistryItemXxx<const char*>::Dup(void) const;


template<class T>
T* FairRegistryItemXxx<T>::Get(void)
{
  return fData;
}

template<class T>
void FairRegistryItemXxx<T>::Set(T* data)
{
  if (fData) { delete fData; }
  fData = data;
}


// These specialized templates are in FairRegistryItemXxx.cxx
//
template<>
void FairRegistryItemXxx<const char*>::Streamer(TBuffer& buf);
template<>
void FairRegistryItemXxx<char>::Streamer(TBuffer& buf);
template<>
FairRegistryItemXxx<const char*>::~FairRegistryItemXxx();

template<> std::ostream& FairRegistryItemXxx<const char*>::PrintStream(std::ostream& os) const;
template<> std::istream& FairRegistryItemXxx<const char*>::ReadStream(std::istream& is);
template<> const char* FairRegistryItemXxx<char>::GetTypeAsString(void) const;
template<> const char* FairRegistryItemXxx<int>::GetTypeAsString(void) const;
template<> const char* FairRegistryItemXxx<double>::GetTypeAsString(void) const;
template<> const char* FairRegistryItemXxx<const char*>::GetTypeAsString(void) const;
template<> const char* FairRegistryItemXxx<FairRegistry>::GetTypeAsString(void) const;

#if (__GNUC__ == 3 && __GNUC_MINOR__ < 3) || __GNUC__ == 2

#include <FairRegistry.h>

template<> const char* FairRegistryItemXxx<char>::GetTypeAsString(void) const
{ return "char"; }

template<> const char* FairRegistryItemXxx<int>::GetTypeAsString(void) const
{ return "int"; }

template<> const char* FairRegistryItemXxx<double>::GetTypeAsString(void) const
{ return "double"; }

template<> const char* FairRegistryItemXxx<const char*>::GetTypeAsString(void) const
{ return "string"; }

template<> const char* FairRegistryItemXxx<FairRegistry>::GetTypeAsString(void) const
{ return "FairRegistry"; }

template<> std::ostream& FairRegistryItemXxx<FairRegistry>::PrintStream(std::ostream& os) const
{ return fData->PrintStream(os); }

template<> std::istream& FairRegistryItemXxx<FairRegistry>::ReadStream(std::istream& is)
{ if (!fData) { fData = new FairRegistry(); } return fData->ReadStream(is); }
#endif

// This assumes that objects spring forth (like ROOT objects)
template<class T>
void FairRegistryItemXxx<T>::Streamer(TBuffer& buf)
{
  if (buf.IsReading()) {
    Version_t v = buf.ReadVersion();
    if (v) { }
    FairRegistryItem::Streamer(buf);

    buf >> fData;
  } else {
    buf.WriteVersion(IsA());
    FairRegistryItem::Streamer(buf);
    buf << fData;
  }
}


#include <FairRegistry.h>

template<>
std::ostream& FairRegistryItemXxx<FairRegistry>::PrintStream(std::ostream& os) const;

template<>
std::istream& FairRegistryItemXxx<FairRegistry>::ReadStream(std::istream& is);

#endif // __CINT__


#endif  // REGISTRYITEMXXX_H
