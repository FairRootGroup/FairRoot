/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairDbOutTableBuffer.h"
#include "FairDbLogService.h"
#include "FairDbFieldType.h"            // for FairDbFieldType, string
#include "FairDbString.h"               // for MakePrintable
#include "ValTimeStamp.h"               // for ValTimeStamp
#include "FairDbStreamer.h"

#include "Riosfwd.h"                    // for ostream
#include "TString.h"                    // for TString

#include <iostream>                     // for ostringstream, etc

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;

ClassImp(FairDbOutTableBuffer)

#define OUTSTREAMER(t,v)                         \
  if ( ! StoreDefaultIfInvalid(t) ) {    \
    ostringstream out;                   \
    out << v;         \
    Store(out.str());                    \
  }                                      \
 

#define OUTSTREAMER2(t,v)                         \
  const FairDbFieldType& fType = this->ColFieldType(this->CurColNum());             \
  if ( fType.IsSigned() && fType.GetSize() != 8 ) {                              \
    Int_t v_signed = (Int_t) v;                                                  \
    if ( fType.GetType() == FairDb::kTiny  && v & 0x80   ) v_signed |= 0xffffff00;  \
    if ( fType.GetType() == FairDb::kShort && v & 0x8000 ) v_signed |= 0xffff0000;  \
    OUTSTREAMER(FairDb::kInt,v_signed); }                                                   \
  else {                                                                         \
    OUTSTREAMER(t,v);                                                                    \
  }                                                                              \
 

FairDbOutTableBuffer::FairDbOutTableBuffer(const FairDbTableMetaData* metaData) :
  FairDbTableBuffer(metaData),
  fBadData(kFALSE),
  fCSV()
{
}

FairDbOutTableBuffer::~FairDbOutTableBuffer()
{
}


FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(Bool_t src)
{
  OUTSTREAMER(FairDb::kBool,src);
  return *this;
}

FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(Char_t src)
{
  OUTSTREAMER(FairDb::kChar,src);
  return *this;
}

FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(const Char_t* src)
{
  OUTSTREAMER(FairDb::kString,src);
  return *this;
}

FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(Short_t src)
{
  OUTSTREAMER(FairDb::kShort,src);
  return *this;
}

FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(UShort_t src)
{
  OUTSTREAMER2(FairDb::kUShort,src);
  return *this;
}

FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(Int_t src)
{
  OUTSTREAMER(FairDb::kInt,src);
  return *this;
}

FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(UInt_t src)
{
  OUTSTREAMER2(FairDb::kUInt,src);
  return *this;
}

FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(Float_t src)
{
  OUTSTREAMER(FairDb::kFloat,src);
  return *this;
}

FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(Double_t src)
{
  OUTSTREAMER(FairDb::kDouble,src);
  return *this;
}

FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(const string& src)
{
  OUTSTREAMER(FairDb::kString,src);
  return *this;
}

FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(const ValTimeStamp& src)
{
  if ( ! StoreDefaultIfInvalid(FairDb::kDate) ) {
    Store(FairDb::MakeDateTimeString(src).Data());
  }
  return *this;
}


FairDbOutTableBuffer& FairDbOutTableBuffer::operator<<(const FairDbStreamer& src)
{
  OUTSTREAMER(FairDb::kString,src.AsString());
  return *this;
}


Bool_t FairDbOutTableBuffer::StoreDefaultIfInvalid(FairDb::DataTypes type)
{
  FairDbFieldType typeSupplied(type);
  FairDbFieldType typeRequired(CurColFieldType());

  if ( typeSupplied.IsCompatible(typeRequired) ) {
    return kFALSE;
  }

  string udef = typeRequired.UndefinedValue();
  MAXDBLOG("FairDb",FairDbLog::kError,20)
      << "In table " << TableNameTc()
      << " column "<< CurColNum()
      << " (" << CurColName() << ")"
      << " of type " << typeRequired.AsString()
      << " is incompatible with user type " << typeSupplied.AsString()
      << ", value \"" << udef
      << "\" will be substituted." <<  endl;
  Store(udef.c_str());
  fBadData = kTRUE;
  return kTRUE;
}

void FairDbOutTableBuffer::Store(const string& str)
{

  UInt_t concept = CurColFieldType().GetConcept();
  string delim = "";
  string snull = "NULL";

  if (    concept == FairDb::kString
          || concept == FairDb::kDate
          || concept == FairDb::kChar ) { delim = "\'"; }


  if ( CurColNum()> 1 ) { fCSV += ','; }
  fCSV += delim ;
  if ( concept != FairDb::kString ) { fCSV += str; }
  else {
    FairUtilString::MakePrintable(str.c_str(),fCSV);
  }
  fCSV += delim;
  //cout << " FairDbOutTableBuffer  IO :: FCSV   ----> " << fCSV << endl;
  IncrementCurCol();
}

