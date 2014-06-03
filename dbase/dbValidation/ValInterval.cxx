/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "ValInterval.h"

#include "DataType.h"                   // for EDataType::kUnknown, etc
#include "ValCondition.h"                 // for ValCondition
#include "db_detector_def.h"            // for Detector, etc

#include <stdio.h>                      // for sprintf, printf

ClassImp(ValInterval)


std::ostream& operator<<(std::ostream& os, const ValInterval& vldr)
{
  return os << vldr.AsString();
}


ValInterval::ValInterval()
  : fDetectorMask(0), fSimMask(0),
    fTimeStart(), fTimeEnd(), fDataSource("unknown")
{

}

ValInterval::ValInterval(const Int_t detMask, const Int_t simMask,
                         const ValTimeStamp& tstart,
                         const ValTimeStamp& tend,
                         const TString& source)
  : fDetectorMask(detMask), fSimMask(simMask),
    fTimeStart(tstart), fTimeEnd(tend), fDataSource(source)
{

}

ValInterval::~ValInterval()
{

}


const char* ValInterval::AsString(Option_t* option) const
{

  static char newstring[255] = " ";

  TString opt = option;
  opt.ToLower();

  Bool_t opt_a = opt.Contains("a");
  Bool_t opt_c = opt.Contains("c");

  TString detbits;
  if (opt_a) {
    detbits = Detector::MaskToString(fDetectorMask);
  } else {
    sprintf(newstring,"det_id %#4.4x",fDetectorMask);
    detbits = newstring;
  }

  TString simbits;
  if (opt_a) {
    simbits = DataType::MaskToString(fSimMask);
  } else {
    sprintf(newstring,"data_id %#4.4x",fSimMask);
    simbits = newstring;
  }


  static char timeopt[4] = "c  ";
  timeopt[0] = (opt.Contains("s")?'s':'c');
  TString start_str = fTimeStart.AsString(timeopt);
  TString end_str;
  if ( ! opt.Contains("1")) {
    end_str = fTimeEnd.AsString(timeopt);
    if ( !opt_c ) { end_str.Prepend("\n\t "); }
    else { end_str.Prepend(" "); }
  }
  if ( ! opt_c ) { start_str.Prepend("\n\t "); }

  TString source;
  if ( ! opt.Contains("-")) {
    source +=  (opt_c) ? " '" : "\n\t origin: ";
    source += fDataSource;
    source +=  (opt_c) ? "'" : "";
  }

  sprintf(newstring,
          "|%s|%s|%s%s%s",
          (const char*)detbits,
          (const char*)simbits,
          (const char*)start_str,
          (const char*)end_str,
          (const char*)source);

  return newstring;
}


Bool_t ValInterval::IsCompatible(const ValCondition& vldc) const
{

  Int_t detector = (Int_t)vldc.GetDetector();
  Int_t datatype  = (Int_t)vldc.GetDataType();


  if ( ! (detector & fDetectorMask) &&
       (detector      != Detector::kUnknown ||
        fDetectorMask != Detector::kUnknown    ) ) { return kFALSE; }
  if ( ! (datatype  & fSimMask) &&
       (datatype  != DataType::kUnknown ||
        fSimMask != DataType::kUnknown   ) ) { return kFALSE; }

  if ( vldc.GetTimeStamp() <  fTimeStart ) { return kFALSE; }
  if ( vldc.GetTimeStamp() >= fTimeEnd   ) { return kFALSE; }

  return kTRUE;
}

Bool_t ValInterval::IsCompatible(const ValCondition* vldc) const
{
  return IsCompatible(*vldc);
}


void ValInterval::Print(Option_t* option) const
{
  printf("%s\n",AsString(option));
}


void ValInterval::TrimTo(const ValInterval& vldr)
{

  fDetectorMask &= vldr.fDetectorMask;
  fSimMask      &= vldr.fSimMask;
  if (fTimeStart < vldr.fTimeStart) { fTimeStart = vldr.fTimeStart; }
  if (fTimeEnd   > vldr.fTimeEnd  ) { fTimeEnd   = vldr.fTimeEnd; }
  if (!fDataSource.Contains(vldr.fDataSource)) {
    fDataSource   += ", ";
    fDataSource   += vldr.fDataSource;
  }
}


