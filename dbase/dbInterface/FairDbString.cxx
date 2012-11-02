#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

#include "FairDbString.h"

ClassImp(FairDbString)

FairDbString::FairDbString()
  : fString()
{

}
FairDbString::FairDbString(const Char_t* str) :
  fString(str)
{

}

FairDbString::FairDbString(const std::string& str) :
  fString(str)
{
}
FairDbString::~FairDbString()
{
}

#define OUT(t,v)               \
    ostringstream out;         \
    out << v;                  \
    fString.append(out.str()); \
    return *this;


FairDbString& FairDbString::operator<<(Int_t data)   { OUT(Int_t,data) }
FairDbString& FairDbString::operator<<(UInt_t data)  { OUT(UInt_t,data) }
FairDbString& FairDbString::operator<<(Float_t data) { OUT(Float_t,data) }
FairDbString& FairDbString::operator<<(Char_t data)
{
  fString.append(1,data);
  return *this;
}
FairDbString& FairDbString::operator<<(const Char_t* data)
{
  fString.append(data);
  return *this;
}
FairDbString& FairDbString::operator<<(const std::string& data)
{
  fString.append(data);
  return *this;
}


// namespace String Utility

void FairUtilString::MakePrintable(const Char_t* in,
                                   std::string& out)
{

  Bool_t hasSpecial = false;
  Int_t index       = 0;
  while ( UChar_t c = in[index++]  ) {
    if (     c == '\\'   || c == '\n'    || c == '\t'     || c == '\'' || c == '\"'
             ||  c <= '\x08' || (c >= '\x0b' && c <= '\x1f' ) || c >= '\x7f' ) {
      hasSpecial = true;
      break;
    }
  }
  if ( ! hasSpecial ) {
    out += in;
    return;
  }
  index = 0;
  while ( UChar_t c = in[index++] ) {
    // Skip really unprInt_table ones.
    if ( c <= '\x08' || (c >= '\x0b' && c <= '\x1f' ) || c >= '\x7f' ) { continue; }
    if  ( c == '\\' || c == '\n' || c == '\t' || c == '\'' || c == '\"') {
      switch ( c ) {
      case '\\':
        out += "\\\\";
        break;
      case '\n':
        out += "\\n";
        break;
      case '\t':
        out += "\\t";
        break;
      case '\'':
        out += "\\\'";
        break;
      case '\"':
        out += "\\\"";
        break;
      }
    } else { out += c; }
  }
}

void FairUtilString::StringTok(std::vector<std::string>& ls,
                               const std::string& str,
                               const std::string& tok)
{
  const string::size_type S     = str.size();
  const string::size_type toksz = tok.size();
  string::size_type  i = 0;

  while (i < S) {
    // eat leading whitespace
    while ( (i<S) && (tok.find(str[i])<=toksz) ) {
      ++i;
    }
    if (i == S) { return; } // nothing left but WS

    // find end of word
    string::size_type  j = i+1;
    while ( (j<S) && !(tok.find(str[j])<=toksz) ) {
      ++j;
    }

    // add word
    ls.push_back(str.substr(i,j-i));

    // set up for next loop
    i = j+1;
  }
}
Bool_t FairUtilString::IsInt(const Char_t* s)
{
  Char_t* endptr;
  Double_t d = strtod(s, &endptr);
  if (endptr==s && d==0.0) { return false; } // Conversion to Double_t failed...

  // Check if this number is Int_t or Float_t
  if (strchr(s,'.')) { return false; }
  if (strchr(s,'E')) { return false; }
  if (strchr(s,'e')) { return false; }

  // All checks for "Int_tness" passed
  return true;
}
Bool_t FairUtilString::IsFloat(const Char_t* s)
{
  Char_t* endptr;
  Double_t d = strtod(s, &endptr);
  if (endptr==s && d==0.0) { return false; }

  // All checks for "Float_tness" passed
  return true;
}
Bool_t FairUtilString::IsBool(const Char_t* s)
{
  Bool_t isvalid;
  atob(s,isvalid);
  return isvalid;
}
Bool_t FairUtilString::atob(const Char_t* s)
{
  Bool_t isvalid;
  Bool_t value = atob(s,isvalid);
  if (isvalid) { return value; }

  // Oops, what have we here?
  cout << "-I- FairUtilString Attempt to convert string "
       << value << " to Bool_t. Result is false \n";
  return false;

}

Bool_t FairUtilString::atob(const Char_t* s, Bool_t& isvalid)
{
  isvalid = true;

  std::string v(s);
  if (v == "true") { return true; } // C++ style
  if (v == "false") { return false; }
  if (v == "kTRUE") { return true; } // ROOT style
  if (v == "kFALSE") { return false; }
  if (v == "TRUE") { return true; } // Some other reasonable variations...
  if (v == "FALSE") { return false; }
  if (v == "True") { return true; }
  if (v == "False") { return false; }
  if (v == "on") { return true; }
  if (v == "off") { return false; }
  if (v == "On") { return true; }
  if (v == "Off") { return false; }
  if (v == "ON") { return true; }
  if (v == "OFF") { return false; }

  isvalid = false;
  return false;  // by default invalid strings are false
}


Int_t FairUtilString::cmp_nocase(const std::string& s1, const std::string& s2)
{
  std::string::const_iterator p1=s1.begin();
  std::string::const_iterator p2=s2.begin();
  while (p1!=s1.end() && p2!=s2.end()) {
    if (toupper(*p1) != toupper(*p2)) {
      return (toupper(*p1)<toupper(*p2)) ? -1 : 1;
    }
    ++p1;
    ++p2;
  }
  return (s2.size()==s1.size()) ? 0 : (s1.size()<s2.size()) ? -1:1;
}

Int_t FairUtilString::cmp_wildcard(const std::string& s, const std::string& w)
{
  std::string::size_type locStar = w.find('*');
  if ( locStar == std::string::npos ) { return s.compare(w); }
  return strncmp(s.c_str(),w.c_str(),locStar);
}


std::string FairUtilString::ToUpper(const std::string& str)
{
  std::string out(str);
  unsigned loc = str.size();
  while ( loc ) {
    --loc;
    out[loc] = toupper(out[loc]);
  }
  return out;
}

std::string FairUtilString::ToLower(const std::string& str)
{
  std::string out(str);
  unsigned loc = str.size();
  while ( loc ) {
    --loc;
    out[loc] = tolower(out[loc]);
  }
  return out;
}

