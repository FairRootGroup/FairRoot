
#include "FairDbTableRow.h"

ClassImp(FairDbTableRow)

FairDbTableRow::FairDbTableRow()
  : TObject(),
    fVersion(0),
    fTimeStart(),
    fTimeEnd(),
    fDetType(),
    fSimType(),
    fOwner(NULL)
{
}

FairDbTableRow::FairDbTableRow(const FairDbTableRow& from)
  : TObject(from),
    fVersion(from.fVersion),
    fTimeStart(from.fTimeStart),
    fTimeEnd(from.fTimeEnd),
    fDetType(from.fDetType),
    fSimType(from.fSimType),
    fOwner(from.fOwner)
{
}

FairDbTableRow& FairDbTableRow::operator=(const FairDbTableRow& from)
{
  if (this == &from) { return *this; }

  TObject::operator=(from);
  fVersion=from.fVersion;
  fTimeStart=from.fTimeStart;
  fTimeEnd=from.fTimeEnd;
  fDetType=from.fDetType;
  fSimType=from.fSimType;
  fOwner=from.fOwner;

  return *this;
}

FairDbTableRow::~FairDbTableRow()
{
}

