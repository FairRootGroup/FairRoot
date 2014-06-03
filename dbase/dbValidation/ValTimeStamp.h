/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef VALTIMESTAMP_H
#define VALTIMESTAMP_H

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Bool_t, UInt_t, etc
#include "TTimeStamp.h"                 // for timespec_t, tm_t

#include <iostream>                     // IWYU pragma: keep
// IWYU pragma: no_include <sys/select.h>
class ValTimeStamp
{

    friend Bool_t operator==(const ValTimeStamp& lhs, const ValTimeStamp& rhs);
    friend Bool_t operator!=(const ValTimeStamp& lhs, const ValTimeStamp& rhs);
    friend Bool_t operator< (const ValTimeStamp& lhs, const ValTimeStamp& rhs);
    friend Bool_t operator<=(const ValTimeStamp& lhs, const ValTimeStamp& rhs);
    friend Bool_t operator> (const ValTimeStamp& lhs, const ValTimeStamp& rhs);
    friend Bool_t operator>=(const ValTimeStamp& lhs, const ValTimeStamp& rhs);

    friend ValTimeStamp operator- (const ValTimeStamp& lhs, const ValTimeStamp& rhs);

  public:


    static ValTimeStamp GetBOT();
    static ValTimeStamp GetEOT();
    static ValTimeStamp GetNBOT();
    ValTimeStamp();

    ValTimeStamp(const ValTimeStamp& source)
      : fSec(source.fSec), fNanoSec(source.fNanoSec) { }


    ValTimeStamp& operator=(const ValTimeStamp& source) {
      if (this != &source) {fSec = source.fSec; fNanoSec = source.fNanoSec;}
      return *this;
    }


    ValTimeStamp(const timespec_t& ts)
      : fSec(ts.tv_sec), fNanoSec(ts.tv_nsec)
    { NormalizeNanoSec(); }

    ValTimeStamp(const time_t& t, const Int_t nsec)
      : fSec(t), fNanoSec(nsec)
    { NormalizeNanoSec(); }

    ValTimeStamp(UInt_t year, UInt_t month,
                 UInt_t day,  UInt_t hour,
                 UInt_t min,  UInt_t sec,
                 UInt_t nsec=0,
                 Bool_t isUTC=kTRUE, Int_t secOffset=0);


    ValTimeStamp(UInt_t date, UInt_t time, UInt_t nsec,
                 Bool_t isUTC=kTRUE, Int_t secOffset=0);

    ValTimeStamp(Double_t seconds)
      : fSec((Int_t)seconds), fNanoSec((Int_t)((seconds-fSec)*1.0e9))
    { NormalizeNanoSec(); }

    virtual ~ValTimeStamp();

    operator double() const { return fSec + 1.0e-9 * fNanoSec; }


    timespec_t     GetTimeSpec() const
    { timespec_t value = {fSec,fNanoSec}; return value; }

    time_t         GetSec(void) const { return fSec;}
    Int_t          GetNanoSec(void) const { return fNanoSec; }
    Double_t GetSeconds(void) const { return fSec+(fNanoSec/1.0e9); }
    const char*    AsString(Option_t* option="") const;
    const char*    Format(Option_t* option="") const;
    void           Copy(ValTimeStamp& vldts) const;
    Int_t          GetDate(Bool_t inUTC=kTRUE, Int_t secOffset=0,
                           UInt_t* year=0, UInt_t* month=0,
                           UInt_t* day=0) const;
    Int_t          GetTime(Bool_t inUTC=kTRUE, Int_t secOffset=0,
                           UInt_t* hour=0, UInt_t* min=0,
                           UInt_t* sec=0) const;

    void           Add(const ValTimeStamp& offset);
    void           Add(Double_t seconds);

    void           Print(Option_t* option="") const;

    static Int_t   GetZoneOffset();
    static time_t  MktimeFromUTC(tm_t* tmstruct);
    static Bool_t  IsLeapYear(Int_t year);
    static void    DumpTMStruct(const tm_t& tmstruct);

  private:

    void           Set();
    void           Set(Int_t year, Int_t month, Int_t day,
                       Int_t hour, Int_t min, Int_t sec,
                       Int_t nsec, Bool_t isUTC, Int_t secOffset);
    void           Set(Int_t date, Int_t time, Int_t nsec,
                       Bool_t isUTC, Int_t secOffset);
    void           NormalizeNanoSec();

    Int_t  fSec;
    Int_t  fNanoSec;

    ClassDef(ValTimeStamp,2)
};

std::ostream& operator<<(std::ostream& os, const ValTimeStamp& vldts);

#ifndef __CINT__

inline Bool_t operator==(const ValTimeStamp& lhs, const ValTimeStamp& rhs)
{
  return lhs.fSec  == rhs.fSec &&
         lhs.fNanoSec == rhs.fNanoSec;
}

inline Bool_t operator!=(const ValTimeStamp& lhs, const ValTimeStamp& rhs)
{
  return lhs.fSec  != rhs.fSec ||
         lhs.fNanoSec != rhs.fNanoSec;
}

inline Bool_t operator<(const ValTimeStamp& lhs, const ValTimeStamp& rhs)
{
  return lhs.fSec  < rhs.fSec ||
         ( lhs.fSec  == rhs.fSec &&
           lhs.fNanoSec <  rhs.fNanoSec   );
}

inline Bool_t operator<=(const ValTimeStamp& lhs, const ValTimeStamp& rhs)
{
  return lhs.fSec  < rhs.fSec ||
         ( lhs.fSec  == rhs.fSec &&
           lhs.fNanoSec <= rhs.fNanoSec   );
}

inline Bool_t operator>(const ValTimeStamp& lhs, const ValTimeStamp& rhs)
{
  return lhs.fSec  > rhs.fSec ||
         ( lhs.fSec  == rhs.fSec &&
           lhs.fNanoSec >  rhs.fNanoSec   );
}

inline Bool_t operator>=(const ValTimeStamp& lhs, const ValTimeStamp& rhs)
{
  return lhs.fSec  > rhs.fSec ||
         ( lhs.fSec  == rhs.fSec &&
           lhs.fNanoSec >= rhs.fNanoSec   );
}

inline ValTimeStamp operator-(const ValTimeStamp& lhs, const ValTimeStamp& rhs)
{
  return ValTimeStamp(lhs.GetSec()     - rhs.GetSec(),
                      lhs.GetNanoSec() - rhs.GetNanoSec());
}

#endif /* __CINT__ */
#endif // VADTIMESTAMP_H
