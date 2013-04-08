
#include "FairDbTableRow.h"

ClassImp(FairDbTableRow)

FairDbTableRow::FairDbTableRow()
  : TObject(), fOwner(NULL),fVersion(0)
{
}

FairDbTableRow::FairDbTableRow(const FairDbTableRow& from)
  : TObject(from), fOwner(from.fOwner),fVersion(from.fVersion)
{
}

FairDbTableRow::~FairDbTableRow()
{
}

