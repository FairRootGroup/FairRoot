
#include <sstream>

#include "FairDbFieldType.h"
#include "FairDbOutRowStream.h"
#include "FairDbTableMetaData.h"
#include "FairDbString.h"
#include "ValTimeStamp.h"

ClassImp(FairDbOutRowStream)

#define OUT(t,v)                         \
  if ( ! StoreDefaultIfInvalid(t) ) {    \
    ostringstream out;                   \
    out << v;         \
    Store(out.str());                    \
  }                                      \
 
// If writing unsigned dat as signed, convert bit pattern to signed,
// extending sign bit if necessary.
// For BIGINT (size 8) make an exception.  It's used only as
// an alternative to unsigned int so can written without conversion.
#define OUT2(t,v)                         \
  const FairDbFieldType& fType = this->ColFieldType(this->CurColNum());             \
  if ( fType.IsSigned() && fType.GetSize() != 8 ) {                              \
    Int_t v_signed = (Int_t) v;                                                  \
    if ( fType.GetType() == FairDb::kTiny  && v & 0x80   ) v_signed |= 0xffffff00;  \
    if ( fType.GetType() == FairDb::kShort && v & 0x8000 ) v_signed |= 0xffff0000;  \
    OUT(FairDb::kInt,v_signed); }                                                   \
  else {                                                                         \
    OUT(t,v);                                                                    \
  }                                                                              \
 

FairDbOutRowStream::FairDbOutRowStream(const FairDbTableMetaData* metaData) :
  FairDbRowStream(metaData),
  fBadData(kFALSE),
  fCSV()
{


}


//.....................................................................

FairDbOutRowStream::~FairDbOutRowStream()
{

}

//.....................................................................

FairDbOutRowStream& FairDbOutRowStream::operator<<(Bool_t src)
{
  OUT(FairDb::kBool,src);
  return *this;
}

FairDbOutRowStream& FairDbOutRowStream::operator<<(Char_t src)
{
  OUT(FairDb::kChar,src);
  return *this;
}

FairDbOutRowStream& FairDbOutRowStream::operator<<(const Char_t* src)
{
  OUT(FairDb::kString,src);
  return *this;
}

FairDbOutRowStream& FairDbOutRowStream::operator<<(Short_t src)
{
  OUT(FairDb::kShort,src);
  return *this;
}

FairDbOutRowStream& FairDbOutRowStream::operator<<(UShort_t src)
{
  OUT2(FairDb::kUShort,src);
  return *this;
}

FairDbOutRowStream& FairDbOutRowStream::operator<<(Int_t src)
{
  OUT(FairDb::kInt,src);
  return *this;
}

FairDbOutRowStream& FairDbOutRowStream::operator<<(UInt_t src)
{
  OUT2(FairDb::kUInt,src);
  return *this;
}

FairDbOutRowStream& FairDbOutRowStream::operator<<(Float_t src)
{
  OUT(FairDb::kFloat,src);
  return *this;
}

FairDbOutRowStream& FairDbOutRowStream::operator<<(Double_t src)
{
  OUT(FairDb::kDouble,src);
  return *this;
}

FairDbOutRowStream& FairDbOutRowStream::operator<<(const string& src)
{
  OUT(FairDb::kString,src);
  return *this;
}

FairDbOutRowStream& FairDbOutRowStream::operator<<(const ValTimeStamp& src)
{
  if ( ! StoreDefaultIfInvalid(FairDb::kDate) ) {
    Store(FairDb::MakeDateTimeString(src).Data());
  }
  return *this;
}


Bool_t FairDbOutRowStream::StoreDefaultIfInvalid(FairDb::DataTypes type)
{

  FairDbFieldType typeSupplied(type);
  FairDbFieldType typeRequired(CurColFieldType());
  if ( typeSupplied.IsCompatible(typeRequired) ) { return kFALSE; }

  string udef = typeRequired.UndefinedValue();
  cout
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
void FairDbOutRowStream::Store(const string& str)
{

  UInt_t concept = CurColFieldType().GetConcept();
  string delim = "";
  if (    concept == FairDb::kString
          || concept == FairDb::kDate
          || concept == FairDb::kChar ) { delim = "\'"; }

  if ( CurColNum()> 1 ) { fCSV += ','; }
  fCSV += delim;
  if ( concept != FairDb::kString ) { fCSV += str; }
//  When exporting strings, take care of special characters.
  else {
    FairUtilString::MakePrintable(str.c_str(),fCSV);
  }
  fCSV += delim;
  IncrementCurCol();
}

