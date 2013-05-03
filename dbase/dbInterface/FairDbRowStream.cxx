#include "FairDbRowStream.h"

#include "FairDbString.h"               // for ToUpper
#include "FairDbTableMetaData.h"        // for FairDbTableMetaData, string

class FairDbFieldType;

using std::string;

ClassImp(FairDbRowStream)


FairDbRowStream::FairDbRowStream(const FairDbTableMetaData* metaData) :
  fCurCol(1),
  fHasRowCounter(kFALSE),
  fMetaData(metaData)
{
  fHasRowCounter = fMetaData->HasRowCounter();

}



FairDbRowStream::~FairDbRowStream()
{

}


const FairDbFieldType& FairDbRowStream::ColFieldType(UInt_t col) const
{

  return fMetaData->ColFieldType(col);
}

string FairDbRowStream::ColName(UInt_t col) const
{
  return fMetaData->ColName(col);
}

const FairDbFieldType& FairDbRowStream::CurColFieldType() const
{

  return fMetaData->ColFieldType(fCurCol);
}


string FairDbRowStream::CurColName() const
{

  return fMetaData->ColName(fCurCol);
}


UInt_t FairDbRowStream::NumCols() const
{

  return fMetaData->NumCols();

}


string FairDbRowStream::TableName() const
{

  return FairUtilString::ToUpper(fMetaData->TableName());
}

string FairDbRowStream::TableNameTc() const
{

  return fMetaData->TableName();
}
