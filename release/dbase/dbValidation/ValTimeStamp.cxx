
#include "ValTimeStamp.h"
#include <climits>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#include "TString.h"

ClassImp(ValTimeStamp)

const Int_t kNsPerSec = 1000000000;

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const ValTimeStamp& ts)
{
  if (os.good()) {
    if (os.tie()) { os.tie()->flush(); } // instead of opfx
    os << ts.AsString("c");
  }
  // instead of os.osfx()
  if (os.flags() & std::ios::unitbuf) { os.flush(); }
  return os;
}

ValTimeStamp ValTimeStamp::GetBOT()
{
  return ValTimeStamp((time_t)0,0);
}

ValTimeStamp ValTimeStamp::GetEOT()
{
  return ValTimeStamp((time_t)INT_MAX,0);
}

ValTimeStamp ValTimeStamp::GetNBOT()
{
  return ValTimeStamp((time_t)INT_MIN,0);
}


//_____________________________________________________________________________
// don't put these in the header or using the include file w/ CINT
// become problematic

// default ctor sets it value to current time (as best possible)
ValTimeStamp::ValTimeStamp() : fSec(0), fNanoSec(0) { Set(); }
ValTimeStamp::~ValTimeStamp() { ; }

//_____________________________________________________________________________
ValTimeStamp::ValTimeStamp(UInt_t year, UInt_t month,
                           UInt_t day,  UInt_t hour,
                           UInt_t min,  UInt_t sec,
                           UInt_t nsec,
                           Bool_t isUTC, Int_t secOffset)
  : fSec(0), fNanoSec(0)
{
  // Create a ValTimeStamp and set it to the specified year, month,
  // day, time, hour, minute, second and nanosec.
  // If !isUTC then it is assumed to be the standard local time zone.
  //
  // If local time is PST then one can use
  //    ValTimeStamp(year,month,day,hour,min,sec,nsec,kFALSE,0);
  // or
  //    Int_t secOffset = 8*60*60;
  //    ValTimeStamp(year,month,day,hour,min,sec,nsec,kTRUE,8*60*60);

  Set(year, month, day, hour, min, sec, nsec, isUTC, secOffset);
}

//_____________________________________________________________________________
ValTimeStamp::ValTimeStamp(UInt_t date, UInt_t time, UInt_t nsec,
                           Bool_t isUTC, Int_t secOffset)
  : fSec(0), fNanoSec(0)
{
  // Create a ValTimeStamp and set it to the specified date, time, nanosec.
  // If !isUTC then it is assumed to be the standard local time zone.

  Set(date, time, nsec, isUTC, secOffset);
}

//_____________________________________________________________________________
const char* ValTimeStamp::AsString(Option_t* option) const
{
  // Return the date & time as a string.
  //
  // Result is pointer to a statically allocated string.
  // User should copy this into their own buffer before calling
  // this method again.  This is somewhat mitigated
  // by use of a circular buffer of strings.
  //
  // Option "l" returns it in local zone format
  // (can be applied to default or compact format).
  //
  // Default format is RFC822 compliant:
  //   "Mon, 02 Jan 2001 18:11:12 +0000 (GMT) +999999999 nsec"
  //   "Mon, 02 Jan 2001 10:11:12 -0800 (PST) +999999999 nsec"
  //
  // Option "c" compact is (almost) ISO 8601 compliant:
  //   "2001-01-02 18:11:12.9999999999Z"
  //   "2001-01-02 10:11:12.9999999999-0800"  if PST
  //      * uses "-" as date separator as specified in ISO 8601
  //      * uses "." rather than preferred "," for decimal separator
  //      * -HHMM is the difference between local and UTC (if behind, + if ahead).
  //   The "-HHMM" is replaced with "Z" if given as UTC.
  //   To be strictly conforming it should use "T" instead of the
  //   blank separating the date and time.
  //
  // Option "2" returns as {sec,nsec} integers.
  //
  // Option "s" returns "2001-01-02 18:11:12" with an implied UTC,
  // overrides "l" option.

  // Internally uses a circular list of buffers to avoid problems
  // using AsString multiple times in a single statement.

  const int nbuffers = 8;     // # of buffers

  static char formatted[nbuffers][64];  // strftime fields substituted
  static char formatted2[nbuffers][64]; // nanosec field substituted
  static int ibuffer = nbuffers;
  ibuffer = (ibuffer+1)%nbuffers; // each call moves to next buffer

  TString opt = option;
  opt.ToLower();

  if (opt.Contains("2")) {
    // return string formatted as integer {sec,nsec}
    sprintf(formatted[ibuffer], "{%d,%d}", fSec, fNanoSec);
    return formatted[ibuffer];
  }

#ifdef linux
  // under linux %z is the hour offset and %Z is the timezone name
  const char* RFC822   = "%a, %d %b %Y %H:%M:%S %z (%Z) +#9ld nsec";
  const char* ISO8601  = "%Y-%m-%d %H:%M:%S.#9.9ld%z";
  const char* ISO8601Z = "%Y-%m-%d %H:%M:%S.#9.9ldZ";
#else
  // otherwise only %Z is guarenteed to be defind
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
  time_t seconds = (time_t) fSec;   // deal with possible mismatch of types
  // of fSec and the time_t required
  // by functions

  // get the components into a tm struct
  ptm = (asLocal) ? localtime(&seconds) : gmtime(&seconds);

  // format all but the nsec field
  // size_t length =
  strftime(formatted[ibuffer], sizeof(formatted[ibuffer]), format, ptm);

  if (asSQL) { return formatted[ibuffer]; }

  // hack in the nsec part
  char* ptr = strrchr(formatted[ibuffer], '#');
  if (ptr) { *ptr = '%'; }    // substitute % for #
  sprintf(formatted2[ibuffer], formatted[ibuffer], fNanoSec);

  return formatted2[ibuffer];
}

//_____________________________________________________________________________
void ValTimeStamp::Copy(ValTimeStamp& ts) const
{
  // Copy this to ts.

  ts.fSec     = fSec;
  ts.fNanoSec = fNanoSec;

}

//_____________________________________________________________________________
Int_t ValTimeStamp::GetDate(Bool_t inUTC, Int_t secOffset,
                            UInt_t* year, UInt_t* month, UInt_t* day) const
{
  // Return date in form of 19971224 (i.e. 24/12/1997),
  // if non-zero pointers supplied for year, month, day fill those as well

  time_t atime = fSec + secOffset;
  struct tm* ptm = (inUTC) ? gmtime(&atime) : localtime(&atime);

  if (year) { *year  = ptm->tm_year + 1900; }
  if (month) { *month = ptm->tm_mon + 1; }
  if (day) { *day   = ptm->tm_mday; }

  return (1900+ptm->tm_year)*10000 + (1+ptm->tm_mon)*100 + ptm->tm_mday;

}

//_____________________________________________________________________________
Int_t ValTimeStamp::GetTime(Bool_t inUTC, Int_t secOffset,
                            UInt_t* hour, UInt_t* min, UInt_t* sec) const
{
  // Return time in form of 123623 (i.e. 12:36:23),
  // if non-zero pointers supplied for hour, min, sec fill those as well

  time_t atime = fSec + secOffset;
  struct tm* ptm = (inUTC) ? gmtime(&atime) : localtime(&atime);

  if (hour) { *hour = ptm->tm_hour; }
  if (min) { *min  = ptm->tm_min; }
  if (sec) { *sec  = ptm->tm_sec; }

  return ptm->tm_hour*10000 + ptm->tm_min*100 + ptm->tm_sec;

}

//_____________________________________________________________________________
Int_t ValTimeStamp::GetZoneOffset()
{
  // Static method returning local (current) time zone offset from UTC.
  // This is the difference in seconds between UTC and local standard time.

  // ?? should tzset (_tzset) be called?
#ifndef R__WIN32
  tzset();
#if !defined(R__MACOSX) && !defined(R__FBSD)
  return  timezone;   /* unix has extern long int */
#else
  time_t* tp = 0;
  time(tp);
  return localtime(tp)->tm_gmtoff;
#endif
#else
  _tzset();
  return _timezone;   /* Win32 prepends "_" */
#endif
}

//_____________________________________________________________________________
void ValTimeStamp::Add(const ValTimeStamp& offset)
{
  // Add "offset" as a delta time.

  fSec     += offset.fSec;
  fNanoSec += offset.fNanoSec;
  NormalizeNanoSec();

}

void ValTimeStamp::Add(Double_t seconds)
{
  // Add 'seconds' as a delta time

  fSec += (Int_t) seconds;
  fNanoSec += (Int_t) (fmod(seconds,1.0) * 1e9);
  NormalizeNanoSec();
  if(seconds > 1e6)
    cout <<"-I- ValTimeStamp::Add(): "
         << " ValTimeStamp moved by offset "
         << seconds <<" which is too large to maintain ns accuracy."
         << endl;
}

//_____________________________________________________________________________
void ValTimeStamp::Print(Option_t* option) const
{
  // Print date and time.

  printf("Date/Time = %s\n", AsString(option));

}

//_____________________________________________________________________________
void ValTimeStamp::Set()
{
  // Set Date/Time to current time as reported by the system.
  // no accounting for nanoseconds with std ANSI functions,
  // ns part faked so that subsequent calls simply add 1 to it
  // this ensures that calls within the same second come back
  // distinct (and sortable).

#ifdef R__WIN32
  ULARGE_INTEGER time;
  GetSystemTimeAsFileTime((FILETIME*)&time);
  // NT keeps time in FILETIME format which is 100ns ticks since
  // Jan 1, 1601. TTimeStamps use time in 100ns ticks since Jan 1, 1970.
  // The difference is 134774 days.
  fNanoSec = Int_t((time.QuadPart * (unsigned __int64) 100) %
                   (unsigned __int64) 1000000000);
  time.QuadPart -=
    (unsigned __int64) (1000*1000*10)       // seconds
    * (unsigned __int64) (60 * 60 * 24)       // days
    * (unsigned __int64) (134774);            // # of days

  fSec     = Int_t(time.QuadPart/(unsigned __int64) (1000*1000*10));
#else
  // this should work on UNIX to get microsec precision
  // we'll stick to a ns hack to make calls unique
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

//_____________________________________________________________________________
void ValTimeStamp::Set(Int_t year, Int_t month, Int_t day,
                       Int_t hour, Int_t min, Int_t sec,
                       Int_t nsec, Bool_t isUTC, Int_t secOffset)
{
  // Set Date/Time from components.
  //
  // month & day both use normal 1..12 and 1..31 counting
  // hours, min, sec run from 0 to 23, 59, 59 respectively;
  // secOffset provides method for adjusting for alternative timezones
  //
  // "year"  |    0    1 ... 37 | 38...69   |   70 .. 100  101 ..  137
  // true    | 2000 2001   2037 | undefined | 1970   2000 2001 .. 2037
  //
  // "year"  | 138...1969 | 1970 .. 2037 | ...
  // true    | undefined  | 1970 .. 2037 | undefined
  //


  // deal with special formats of year
  if (year <= 37) { year += 2000; }
  if (year >= 70 && year <= 137) { year += 1900; }
  // tm.tm_year is years since 1900
  if (year >= 1900) { year -= 1900; }

  struct tm tmstruct;
  tmstruct.tm_year  = year;    // years since 1900
  tmstruct.tm_mon   = month-1; // months since Jan [0,11]
  tmstruct.tm_mday  = day;     // day of the month [1,31]
  tmstruct.tm_hour  = hour;    // hours since midnight [0,23]
  tmstruct.tm_min   = min;     // minutes after the hour [0,59]
  tmstruct.tm_sec   = sec + secOffset;  // seconds after the minute [0,59]
  tmstruct.tm_isdst = -1;     // let "mktime" determine DST setting

  const time_t bad_time_t = (time_t) -1;
  // convert tm struct to time_t, if values are given in UTC then
  // no standard routine exists and we'll have to use our homegrown routine,
  // if values are given in local time then use "mktime"
  // which also normalizes the tm struct as a byproduct
  time_t utc_sec = (isUTC) ? MktimeFromUTC(&tmstruct) : mktime(&tmstruct);

  //   ValTimeStamp::Dump_tm_struct(tmstruct);

  if (utc_sec == bad_time_t)

  {
    cout << "-I- ValTimeStamp::Set mktime returned -1" << endl;
  }

  fSec  = utc_sec;
  fNanoSec = nsec;

  NormalizeNanoSec();
}

//_____________________________________________________________________________
void ValTimeStamp::Set(Int_t date, Int_t time, Int_t nsec,
                       Bool_t isUTC, Int_t secOffset)
{
  // Set date/time from integers of the form [yy]YYMMDD and HHMMSS,
  // assume UTC (UTC) components:
  //
  //  MM: 01=January .. 12=December
  //  DD: 01 .. 31
  //
  //  HH: 00=midnight .. 23
  //  MM: 00 .. 59
  //  SS: 00 .. 69
  //
  // Date must be in format 980418 or 19980418
  //                       1001127 or 20001127  (i.e. year 100 = 2000).
  // Time must be in format 224512 (second precision).
  // Date must be >= 700101.

  Int_t year  = date/10000;
  Int_t month = (date-year*10000)/100;
  Int_t day   = date%100;

  // protect against odd attempts at time offsets
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

//_____________________________________________________________________________
void ValTimeStamp::NormalizeNanoSec()
{
  // Ensure that the fNanoSec field is in range [0,99999999].

  // deal with negative values
  while (fNanoSec < 0) {
    fNanoSec += kNsPerSec;
    fSec -= 1;
  }
  // deal with values inf fNanoSec greater than one sec
  while (fNanoSec >= kNsPerSec) {
    fNanoSec -= kNsPerSec;
    fSec += 1;
  }
}
//_____________________________________________________________________________
time_t ValTimeStamp::MktimeFromUTC(tm_t* tmstruct)
{
  // Equivalent of standard routine "mktime" but
  // using the assumption that tm struct is filled with UTC, not local, time.

  // This version *ISN'T* configured to handle every possible
  // weirdness of out-of-range values in the case of normalizing
  // the tm struct.

  // This version *DOESN'T* correctly handle values that can't be
  // fit into a time_t (i.e. beyond year 2038-01-18 19:14:07, or
  // before the start of Epoch).

  const Int_t days[]     = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  const Int_t daysLeap[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  Int_t year = tmstruct->tm_year + 1900;
  Bool_t isleap = ValTimeStamp::IsLeapYear(year);

  const Int_t* daysInMonth = days;
  if (isleap) { daysInMonth = daysLeap; }

  // fill in tmstruct->tm_yday

  int& ref_tm_mon = tmstruct->tm_mon;
  int& ref_tm_mday = tmstruct->tm_mday;
  // count days in months past
  tmstruct->tm_yday = 0;
  for (Int_t imonth = 0; imonth < ref_tm_mon; imonth++) {
    tmstruct->tm_yday += daysInMonth[imonth];
  }
  tmstruct->tm_yday += ref_tm_mday - 1;  // day [1-31] but yday [0-365]

  // adjust if day in this month is more than the month has
  while (ref_tm_mday > daysInMonth[ref_tm_mon]) {
    ref_tm_mday -= daysInMonth[ref_tm_mon];
    ref_tm_mon++;
  }

  // *should* calculate tm_wday (0-6) here ...

  // UTC is never DST
  tmstruct->tm_isdst = 0;

  // Calculate seconds since the Epoch based on formula in
  // POSIX  IEEEE Std 1003.1b-1993 pg 22

  Int_t utc_sec = tmstruct->tm_sec +
                  tmstruct->tm_min*60 +
                  tmstruct->tm_hour*3600 +
                  tmstruct->tm_yday*86400 +
                  (tmstruct->tm_year-70)*31536000 +
                  ((tmstruct->tm_year-69)/4)*86400;

  return utc_sec;
}

//_____________________________________________________________________________
Bool_t ValTimeStamp::IsLeapYear(Int_t year)
{
  // Is the given year a leap year.


  // The calendar year is 365 days long, unless the year is exactly divisible
  // by 4, in which case an extra day is added to February to make the year
  // 366 days long. If the year is the last year of a century, eg. 1700, 1800,
  // 1900, 2000, then it is only a leap year if it is exactly divisible by
  // 400. Therefore, 1900 wasn't a leap year but 2000 was. The reason for
  // these rules is to bring the average length of the calendar year into
  // line with the length of the Earth's orbit around the Sun, so that the
  // seasons always occur during the same months each year.

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

//_____________________________________________________________________________
void ValTimeStamp::DumpTMStruct(const tm_t& tmstruct)
{
  // Print out the "tm" structure:
  // tmstruct.tm_year = year;    // years since 1900
  // tmstruct.tm_mon  = month-1; // months since Jan [0,11]
  // tmstruct.tm_mday = day;     // day of the month [1,31]
  // tmstruct.tm_hour = hour;    // hours since midnight [0,23]
  // tmstruct.tm_min  = min;     // minutes after the hour [0,59]
  // tmstruct.tm_sec  = sec;     // seconds after the minute [0,59]
  // tmstruct.tm_wday            // day of week [0,6]
  // tmstruct.tm_yday            // days in year [0,365]
  // tmstruct.tm_isdst           // DST [-1/0/1]  (unknown,false,true)

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
//_____________________________________________________________________________
