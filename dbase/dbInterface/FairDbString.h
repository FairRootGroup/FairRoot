/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBSTRING
#define FAIRDBSTRING



#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                     // for Char_t, Bool_t, Int_t, etc
#endif
#endif

#ifndef VECTOR
#include <vector>                       // for vector
#define VECTOR
#endif
#ifndef STRING
#include <string>                       // for string
#define STRING
#endif
#include <sstream>                      // for ostringstream, dec, etc


namespace FairUtilString
{
Bool_t atob(const Char_t* s);
Bool_t atob(const Char_t* s, Bool_t& isvalid);
Int_t  cmp_nocase(const std::string& s1, const std::string& s2);
Int_t  cmp_wildcard(const std::string& s, const std::string& w);
void MakePrintable(const Char_t* in,
                   std::string& out);
void StringTok(std::vector<std::string>& ls,
               const std::string& str,
               const std::string& tok);
Bool_t IsBool(const Char_t* s);
Bool_t IsInt(const Char_t* s);
Bool_t IsFloat(const Char_t* s);

std::string ToLower(const std::string& str);
std::string ToUpper(const std::string& str);

template <class T>
std::string ToString(const T& t, std::ios_base & (*f)(std::ios_base&) = std::dec)
{
  std::ostringstream oss;
  oss << f << t;
  return oss.str();
}
}


class FairDbString
{

  public:
    FairDbString();
    FairDbString(const Char_t* str);
    FairDbString(const std::string& str);
    virtual ~FairDbString();

// State testing member functions
    const Char_t* c_str() const { return fString.c_str(); }
    const std::string& GetString() const { return fString; }

// State changing member functions
    FairDbString& operator<<(Int_t data);
    FairDbString& operator<<(UInt_t data);
    FairDbString& operator<<(Float_t data);
    FairDbString& operator<<(Char_t data);
    FairDbString& operator<<(const Char_t* data);
    FairDbString& operator<<(const std::string& data);
    void Clear() { fString.clear(); }
    std::string& GetString() { return fString; }

  private:
    std::string fString;
    ClassDef(FairDbString,0)     // output stringstream

};

#endif // FairDbString

