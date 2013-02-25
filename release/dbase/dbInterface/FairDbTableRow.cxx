
#include "FairDbTableRow.h"

ClassImp(FairDbTableRow)

FairDbTableRow::FairDbTableRow()
  : TObject(), fOwner(NULL)
{
}
//.....................................................................

FairDbTableRow::FairDbTableRow(const FairDbTableRow& from)
  : TObject(from), fOwner(from.fOwner)
{

}

FairDbTableRow::~FairDbTableRow()
{

}

