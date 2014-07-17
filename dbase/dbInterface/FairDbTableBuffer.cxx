/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbTableBuffer.h"

#include "FairDbString.h"               // for ToUpper
#include "FairDbTableMetaData.h"        // for FairDbTableMetaData, string

class FairDbFieldType;

using std::string;

ClassImp(FairDbTableBuffer)


FairDbTableBuffer::FairDbTableBuffer(const FairDbTableMetaData* metaData) :
  fCurCol(1),
  fHasRowCounter(kFALSE),
  fMetaData(metaData)
{
  fHasRowCounter = fMetaData->HasRowCounter();
}

FairDbTableBuffer::~FairDbTableBuffer()
{

}

const FairDbFieldType& FairDbTableBuffer::ColFieldType(UInt_t col) const
{
  return fMetaData->ColFieldType(col);
}

string FairDbTableBuffer::ColName(UInt_t col) const
{
  return fMetaData->ColName(col);
}

const FairDbFieldType& FairDbTableBuffer::CurColFieldType() const
{
  return fMetaData->ColFieldType(fCurCol);
}


string FairDbTableBuffer::CurColName() const
{
  return fMetaData->ColName(fCurCol);
}


UInt_t FairDbTableBuffer::NumCols() const
{
  return fMetaData->NumCols();
}


string FairDbTableBuffer::TableName() const
{
  return FairUtilString::ToUpper(fMetaData->TableName());
}

string FairDbTableBuffer::TableNameTc() const
{
  return fMetaData->TableName();
}
