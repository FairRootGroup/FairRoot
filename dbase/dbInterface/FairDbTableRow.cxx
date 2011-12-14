
#include "FairDbTableRow.h"

ClassImp(FairDbTableRow)

FairDbTableRow::FairDbTableRow():
  fOwner(0)
{
}
//.....................................................................

FairDbTableRow::FairDbTableRow(const FairDbTableRow& from) : TObject(from)
{

}


FairDbTableRow::~FairDbTableRow()
{

}

