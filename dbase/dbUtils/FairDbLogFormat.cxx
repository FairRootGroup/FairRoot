/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbLogFormat.h"
#include "FairDbLogBFormat.h"


ostream& operator<<(ostream& os, const FairDbLogBFormat& bf)
{
  int p = os.precision();
  FairDbLogFormat::fmtflags f =
    os.setf(bf.f.fmt,static_cast<FairDbLogFormat::fmtflags>(0xFFFF));
  char c = os.fill();

  if (bf.f.flc != c) { os.fill(bf.f.flc); }

  if ((bf.f.fmt&ios::hex) || (bf.f.fmt&ios::oct)) {
    os.setf(bf.f.fmt, ios::basefield);
    os << setprecision(bf.f.prc) << setw(bf.f.wdt) << (int)bf.val;
  } else {
    os << setprecision(bf.f.prc) << setw(bf.f.wdt) << bf.val;
  }

  // Reset stream
  if (c != os.fill()) { os.fill(c); }
  os.precision(p);
  os.flags(f);
  return os;
}

FairDbLogFormat::FairDbLogFormat(const char* f)
{
  int i, j=0, k=0;
  char c, n[2][16];
  prc = 6;
  wdt = 0;
  fmt = static_cast<fmtflags>(0);
  flc = ' ';
  for (i=0; f[i] != '\0'; ++i) {
    switch(c = f[i]) {
    case '-':
      fmt |= ios::left;
      break;
    case '+':
      fmt |= ios::showpos;
      break;
    case ' ':
      break;
    case 'O':
      flc = '0';
      fmt |= ios::left;
      break;
    case 'd':
      break;
    case 'u':
      break;
    case 'i':
      break;
    case 'o':
      fmt |= ios::oct;
      fmt |= ios::showbase;
      break;
    case 'x':
      fmt |= ios::hex;
      fmt |= ios::showbase;
      break;
    case 'X':
      fmt |= ios::hex;
      fmt |= ios::showbase;
      break;
    case 'f':
      fmt |= ios::fixed;
      break;
    case 'e':
      fmt |= ios::scientific;
      break;
    case 'E':
      fmt |= ios::scientific;
      break;
    case 'g':
      break;
    case 'G':
      break;
    default:
      if (c == '.') {
        n[j][k] = '\0';
        ++j;
        k = 0;
      } else {
        if (c >= '0' && c <= '9') { n[j][k++] = c; }
      }
      break;
    }
  }
  if (k!=0 || j!=0) {
    if (j==0) { n[0][k] = '\0'; }
    wdt = atoi(n[0]);
  }
  if (j>0) {
    n[1][k] = '\0';
    prc = atoi(n[1]);
  }
}
