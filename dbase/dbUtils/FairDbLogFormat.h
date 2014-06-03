/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBLOGFORMAT_H
#define FAIRDBLOGFORMAT_H

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "FairDbLogBFormat.h"

using namespace std;

// declare operator function
ostream& operator<<(ostream&, const FairDbLogBFormat&);

class FairDbLogFormat
{
    friend ostream& operator<<(ostream&, const FairDbLogBFormat&);
  public:

#if __GNUC__ == 3 && __GNUC_MINOR__ >= 4
    typedef ios_base::fmtflags fmtflags;
#elif __GNUC__ == 4
    typedef ios_base::fmtflags fmtflags;
#else
#ifdef _CPP_BITS_IOSBASE_H
    typedef ios_base::fmtflags fmtflags;
#else
    typedef int fmtflags;
#endif
#endif

    FairDbLogFormat(int p=6) :
      prc(p), wdt(0), fmt(static_cast<fmtflags>(0)), flc(' ') { }
    FairDbLogFormat(int p, int w) :
      prc(p), wdt(w), fmt(static_cast<fmtflags>(0)), flc(' ') { }
    FairDbLogFormat(const char* f);

    FairDbLogBFormat operator()(double d) const {
      return FairDbLogBFormat(*this,d);
    }

    FairDbLogFormat& fixed()      { fmt=ios::fixed;      return *this;}
    FairDbLogFormat& general()    { fmt=ios::dec;        return *this;}
    FairDbLogFormat& hex()        { fmt=ios::hex;        return *this;}
    FairDbLogFormat& oct()        { fmt=ios::oct;        return *this;}
    FairDbLogFormat& scientific() { fmt=ios::scientific; return *this;}

    FairDbLogFormat& precision(int p) { prc=p; return *this;}
    FairDbLogFormat& width(int w)     { wdt=w; return *this;}

    FairDbLogFormat& set_fill(char c) { flc = c; return *this; }

    FairDbLogFormat& left_justify(int b=1) {
      if (b) { fmt |= ios::left; fmt &= (~ios::right); }
      else { fmt &= ~ios::left; }
      return *this;
    }
    FairDbLogFormat& right_justify(int b=1) {
      if (b) { fmt |= ios::right; fmt &= (~ios::left); }
      else { fmt &= ~ios::right; }
      return *this;
    }
    FairDbLogFormat& show_base(int b=1) {
      if (b) { fmt |= ios::showbase; }
      else { fmt &= ~ios::showbase; }
      return *this;
    }
    FairDbLogFormat& plus(int b=1) {
      if (b) { fmt |= ios::showpos; }
      else { fmt &= ~ios::showpos; }
      return *this;
    }
    FairDbLogFormat& trailing_zeros(int b=1) {
      if (b) { fmt |= ios::showpoint; }
      else { fmt &= ~ios::showpoint; }
      return *this;
    }

  private:
    int      prc;  // Precision
    int      wdt;  // Width
    fmtflags fmt;  // Format
    char     flc;  // Fill character
};

#endif //!FAIRDBLOGFORMAT
