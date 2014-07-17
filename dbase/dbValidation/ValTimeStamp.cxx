/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "ValTimeStamp.h"

#include "RConfig.h"                    // for R__MACOSX
#include "TString.h"

#include <climits>
#include <math.h> // IWYU pragma: keep 
// IWYU pragma: no_include <architecture/i386/math.h>
#include <stdio.h>                      // for printf, sprintf
#include <string.h>                     // for strrchr
#include <time.h>                       // for tm, localtime, gmtime, time, etc
#include <sys/time.h>                   // for gettimeofday 
// IWYU pragma: no_include <sys/_structs.h>

using std::cout;
using std::endl;

// <DB> This could be a work arround to use the 32/64
// implementation dependancy ...

/*
typedef int32_t my_time32;
typedef int64_t my_time64;
my_time32 get_mytime32()
{
  if (sizeof(time_t) == sizeof(my_time32)) {
    return time(NULL);
  } else {
    return (my_time32)(time(NULL));
  }
}


my_time64 get_mytime64()
{
  if (sizeof(time_t) == sizeof(my_time64)) {
    return time(NULL);
  } else {
    return (my_time64)(time(NULL));
  }
}
*/


ClassImp(ValTimeStamp)


const Int_t kNsPerSec = 1000000000;


std::ostream& operator<<(std::ostream& os, const ValTimeStamp& ts)
{
  if (os.good()) {
    if (os.tie()) { os.tie()->flush(); }
    os << ts.AsString("c");
  }

  if (os.flags() & std::ios::unitbuf) { os.flush(); }
  return os;
}

ValTimeStamp ValTimeStamp::GetBOT()
{
  return ValTimeStamp((time_t)0,0);
}

ValTimeStamp ValTimeStamp::GetEOT()
{
  // Unix End of Time
  return ValTimeStamp((time_t)INT_MAX,0);
}

ValTimeStamp ValTimeStamp::GetNBOT()
{
  // Unix Begin of Time
  return ValTimeStamp((time_t)INT_MIN,0);
}


ValTimeStamp::ValTimeStamp() : fSec(0), fNanoSec(0) { Set(); }
ValTimeStamp::~ValTimeStamp() { ; }

ValTimeStamp::ValTimeStamp(UInt_t year, UInt_t month,
                           UInt_t day,  UInt_t hour,
                           UInt_t min,  UInt_t sec,
                           UInt_t nsec,
                           Bool_t isUTC, Int_t secOffset)
  : fSec(0), fNanoSec(0)
{
  Set(year, month, day, hour, min, sec, nsec, isUTC, secOffset);
}

ValTimeStamp::ValTimeStamp(UInt_t date, UInt_t time, UInt_t nsec,
                           Bool_t isUTC, Int_t secOffset)
  : fSec(0), fNanoSec(0)
{
  Set(date, time, nsec, isUTC, secOffset);
}

const char* ValTimeStamp::Format(Option_t* option) const
{
  const int nbuffers = 8;
  static char formatted[nbuffers][64];
  static char formatted2[nbuffers][64];
  static int ibuffer = nbuffers;
  ibuffer = (ibuffer+1)%nbuffers;

  TString opt = option;
  opt.ToLower();

  if (opt.Contains("sec")) {
    sprintf(formatted[ibuffer], "{%d,%d}", fSec, fNanoSec);
    return formatted[ibuffer];
  }

#ifdef linux
  const char* RFC822   = "%a, %d %b %Y %H:%M:%S %z (%Z) +#9ld nsec";
  const char* ISO8601  = "%Y-%m-%d %H:%M:%S.#9.9ld%z";
  const char* ISO8601Z = "%Y-%m-%d %H:%M:%S.#9.9ldZ";
#else
  const char* RFC822   = "%a, %d %b %Y %H:%M:%S %Z +#9ld nsec";
  const char* ISO8601  = "%Y-%m-%d %H:%M:%S.#9.9ld%Z";
  const char* ISO8601Z = "%Y-%m-%d %H:%M:%S.#9.9ldZ";
#endif
  const char* SQL = "%Y-%m-%d %H:%M:%S";

  Bool_t asLocal = opt.Contains("l");
  Bool_t asSQL   = opt.Contains("z");
  if (asSQL) { asLocal = kFALSE; }

  const char* format = RFC822;
  if (opt.Contains("iso")) {
    format = ISO8601;
    if (!asLocal) { format = ISO8601Z; }
  }
  if (asSQL) { format = SQL; }

  struct tm* ptm;
  time_t seconds = (time_t) fSec;
  ptm = (asLocal) ? localtime(&seconds) : gmtime(&seconds);

  strftime(formatted[ibuffer], sizeof(formatted[ibuffer]), format, ptm);

  if (asSQL) { return formatted[ibuffer]; }

  char* ptr = strrchr(formatted[ibuffer], '#');
  if (ptr) { *ptr = '%'; }    // substitute % for #
  sprintf(formatted2[ibuffer], formatted[ibuffer], fNanoSec);

  return formatted2[ibuffer];
}


const char* ValTimeStamp::AsString(Option_t* option) const
{
  const int nbuffers = 8;
  static char formatted[nbuffers][64];
  static char formatted2[nbuffers][64];
  static int ibuffer = nbuffers;
  ibuffer = (ibuffer+1)%nbuffers;

  TString opt = option;
  opt.ToLower();

  if (opt.Contains("2")) {
    sprintf(formatted[ibuffer], "{%d,%d}", fSec, fNanoSec);
    return formatted[ibuffer];
  }

#ifdef linux
  const char* RFC822   = "%a, %d %b %Y %H:%M:%S %z (%Z) +#9ld nsec";
  const char* ISO8601  = "%Y-%m-%d %H:%M:%S.#9.9ld%z";
  const char* ISO8601Z = "%Y-%m-%d %H:%M:%S.#9.9ldZ";
#else
  const char* RFC822   = "%a, %d %b %Y %H:%M:%S %Z +#9ld nsec";
  const char* ISO8601  = "%Y-%m-%d %H:%M:%S.#9.9ld%Z";
  const char* ISO8601Z = "%Y-%m-%d %H:%M:%S.#9.9ldZ";
#endif
  const char* SQL = "%Y-%m-%d %H:%M:%S";

  Bool_t asLocal = opt.Contains("l");
  Bool_t asSQL   = opt.Contains("s");
  if (asSQL) { asLocal = kFALSE; }

  const char* format = RFC822;
  if (opt.Contains("c")) {
    format = ISO8601;
    if (!asLocal) { format = ISO8601Z; }
  }
  if (asSQL) { format = SQL; }

  struct tm* ptm;
  time_t seconds = (time_t) fSec;
  ptm = (asLocal) ? localtime(&seconds) : gmtime(&seconds);

  strftime(formatted[ibuffer], sizeof(formatted[ibuffer]), format, ptm);

  if (asSQL) { return formatted[ibuffer]; }

  char* ptr = strrchr(formatted[ibuffer], '#');
  if (ptr) { *ptr = '%'; }    // substitute % for #
  sprintf(formatted2[ibuffer], formatted[ibuffer], fNanoSec);

  return formatted2[ibuffer];
}


void ValTimeStamp::Copy(ValTimeStamp& ts) const
{
  ts.fSec     = fSec;
  ts.fNanoSec = fNanoSec;
}


Int_t ValTimeStamp::GetDate(Bool_t inUTC, Int_t secOffset,
                            UInt_t* year, UInt_t* month, UInt_t* day) const
{

  time_t atime = fSec + secOffset;
  struct tm* ptm = (inUTC) ? gmtime(&atime) : localtime(&atime);

  if (year) { *year  = ptm->tm_year + 1900; }
  if (month) { *month = ptm->tm_mon + 1; }
  if (day) { *day   = ptm->tm_mday; }

  return (1900+ptm->tm_year)*10000 + (1+ptm->tm_mon)*100 + ptm->tm_mday;

}
Int_t ValTimeStamp::GetTime(Bool_t inUTC, Int_t secOffset,
                            UInt_t* hour, UInt_t* min, UInt_t* sec) const
{
  time_t atime = fSec + secOffset;
  struct tm* ptm = (inUTC) ? gmtime(&atime) : localtime(&atime);

  if (hour) { *hour = ptm->tm_hour; }
  if (min) { *min  = ptm->tm_min; }
  if (sec) { *sec  = ptm->tm_sec; }

  return ptm->tm_hour*10000 + ptm->tm_min*100 + ptm->tm_sec;

}

Int_t ValTimeStamp::GetZoneOffset()
{
#ifndef R__WIN32
  tzset();
#if !defined(R__MACOSX) && !defined(R__FBSD)
  return  timezone;   /* unix specs long int */
#else
  time_t* tp = 0;
  time(tp);
  return localtime(tp)->tm_gmtoff;
#endif
#else
  _tzset();
  return _timezone;   /* Win32 specs */
#endif
}

void ValTimeStamp::Add(const ValTimeStamp& offset)
{
  fSec     += offset.fSec;
  fNanoSec += offset.fNanoSec;
  NormalizeNanoSec();
}

void ValTimeStamp::Add(Double_t seconds)
{
  fSec += (Int_t) seconds;
  fNanoSec += (Int_t) (fmod(seconds,1.0) * 1e9);
  NormalizeNanoSec();
  if(seconds > 1e6)
    cout <<"-I- ValTimeStamp::Add(): "
         << " ValTimeStamp moved by offset "
         << seconds <<" which is too large to achieve ns accuracy."
         << endl;
}

void ValTimeStamp::Print(Option_t* option) const
{
  // Print date and time.

  printf("Date/Time = %s\n", AsString(option));

}

void ValTimeStamp::Set()
{

#ifdef R__WIN32
  ULARGE_INTEGER time;
  GetSystemTimeAsFileTime((FILETIME*)&time);
  fNanoSec = Int_t((time.QuadPart * (unsigned __int64) 100) %
                   (unsigned __int64) 1000000000);
  time.QuadPart -=
    (unsigned __int64) (1000*1000*10)       // seconds
    * (unsigned __int64) (60 * 60 * 24)       // days
    * (unsigned __int64) (134774);            // # of days

  fSec     = Int_t(time.QuadPart/(unsigned __int64) (1000*1000*10));
#else
  struct timeval now;
  if (!gettimeofday(&now,0)) {
    fSec     = now.tv_sec;
    fNanoSec = now.tv_usec * 1000;
  } else {
    time_t nowtime;
    time(&nowtime);
    fSec     = nowtime;
    fNanoSec = 0;
  }
#endif
  static Int_t sec = 0, nsec = 0, fake_ns = 0;

  if (fSec == sec && fNanoSec == nsec) {
    fNanoSec += ++fake_ns;
  } else {
    fake_ns = 0;
    sec     = fSec;
    nsec    = fNanoSec;
  }

}


void ValTimeStamp::Set(Int_t year, Int_t month, Int_t day,
                       Int_t hour, Int_t min, Int_t sec,
                       Int_t nsec, Bool_t isUTC, Int_t secOffset)
{
  if (year <= 37) { year += 2000; }
  if (year >= 70 && year <= 137) { year += 1900; }
  if (year >= 1900) { year -= 1900; }

  struct tm tmstruct;
  tmstruct.tm_year  = year;
  tmstruct.tm_mon   = month-1;
  tmstruct.tm_mday  = day;
  tmstruct.tm_hour  = hour;
  tmstruct.tm_min   = min;
  tmstruct.tm_sec   = sec + secOffset;
  tmstruct.tm_isdst = -1;

  const time_t bad_time_t = (time_t) -1;
  time_t utc_sec = (isUTC) ? MktimeFromUTC(&tmstruct) : mktime(&tmstruct);

  if (utc_sec == bad_time_t) {
    cout << "-I- ValTimeStamp::Set time returned -1" << endl;
  }

  fSec  = utc_sec;
  fNanoSec = nsec;

  NormalizeNanoSec();
}


void ValTimeStamp::Set(Int_t date, Int_t time, Int_t nsec,
                       Bool_t isUTC, Int_t secOffset)
{
  Int_t year  = date/10000;
  Int_t month = (date-year*10000)/100;
  Int_t day   = date%100;


  const Int_t oneday = 240000;
  while (time < 0) {
    time += oneday;
    day  -= 1;
  }
  while (time > oneday) {
    time -= oneday;
    day  += 1;
  }
  Int_t hour  = time/10000;
  Int_t min   = (time-hour*10000)/100;
  Int_t sec   = time%100;

  Set(year, month, day, hour, min, sec, nsec, isUTC, secOffset);

}


void ValTimeStamp::NormalizeNanoSec()
{

  while (fNanoSec < 0) {
    fNanoSec += kNsPerSec;
    fSec -= 1;
  }

  while (fNanoSec >= kNsPerSec) {
    fNanoSec -= kNsPerSec;
    fSec += 1;
  }
}

time_t ValTimeStamp::MktimeFromUTC(tm_t* tmstruct)
{
  const Int_t days[]     = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  const Int_t daysLeap[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  Int_t year = tmstruct->tm_year + 1900;
  Bool_t isleap = ValTimeStamp::IsLeapYear(year);

  const Int_t* daysInMonth = days;
  if (isleap) { daysInMonth = daysLeap; }


  int& ref_tm_mon = tmstruct->tm_mon;
  int& ref_tm_mday = tmstruct->tm_mday;
  // count days in months past
  tmstruct->tm_yday = 0;
  for (Int_t imonth = 0; imonth < ref_tm_mon; imonth++) {
    tmstruct->tm_yday += daysInMonth[imonth];
  }
  tmstruct->tm_yday += ref_tm_mday - 1;


  while (ref_tm_mday > daysInMonth[ref_tm_mon]) {
    ref_tm_mday -= daysInMonth[ref_tm_mon];
    ref_tm_mon++;
  }


  tmstruct->tm_isdst = 0;


  Int_t utc_sec = tmstruct->tm_sec +
                  tmstruct->tm_min*60 +
                  tmstruct->tm_hour*3600 +
                  tmstruct->tm_yday*86400 +
                  (tmstruct->tm_year-70)*31536000 +
                  ((tmstruct->tm_year-69)/4)*86400;

  return utc_sec;
}


Bool_t ValTimeStamp::IsLeapYear(Int_t year)
{

  if (year%4 != 0) {
    return false;
  } else {
    if (year%400 == 0) {
      return true;
    } else {
      if (year%100 == 0) {
        return false;
      } else {
        return true;
      }
    }
  }

}


void ValTimeStamp::DumpTMStruct(const tm_t& tmstruct)
{

  printf(" tm { year %4d, mon   %2d, day   %2d,\n",
         tmstruct.tm_year,
         tmstruct.tm_mon,
         tmstruct.tm_mday);
  printf("      hour   %2d, min   %2d, sec   %2d,\n",
         tmstruct.tm_hour,
         tmstruct.tm_min,
         tmstruct.tm_sec);
  printf("      wday   %2d, yday %3d, isdst %2d",
         tmstruct.tm_wday,
         tmstruct.tm_yday,
         tmstruct.tm_isdst);
#ifdef linux
//#ifdef __GNUC__
// special GCC extras
  printf(",\n      tm_gmtoff %7ld,  tm_zone \"%s\"",
#ifdef __USE_BSD
         tmstruct.tm_gmtoff,tmstruct.tm_zone);
#else
         tmstruct.__tm_gmtoff,tmstruct.__tm_zone);
#endif
#endif
  printf("}\n");
}

