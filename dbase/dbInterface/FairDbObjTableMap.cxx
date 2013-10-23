#include "FairDbObjTableMap.h"

ClassImp(FairDbObjTableMap)

FairDbObjTableMap::FairDbObjTableMap()
  : TObject(),
    fVersion(0),
    fDbEntry(0),
    fLogTitle(""),
    fCombo(-2),
    fTimeStart(),
    fTimeEnd(),
    fDetType(),
    fSimType(),
    fOwner(NULL)
{
}

FairDbObjTableMap::FairDbObjTableMap(const FairDbObjTableMap& from)
  : TObject(from),
    fVersion(from.fVersion),
    fDbEntry(from.fDbEntry),
    fLogTitle(from.fLogTitle),
    fCombo(from.fCombo),
    fTimeStart(from.fTimeStart),
    fTimeEnd(from.fTimeEnd),
    fDetType(from.fDetType),
    fSimType(from.fSimType),
    fOwner(from.fOwner)
{
}

FairDbObjTableMap& FairDbObjTableMap::operator=(const FairDbObjTableMap& from)
{
  if (this == &from) { return *this; }

  TObject::operator=(from);
  fVersion=from.fVersion;
  fDbEntry=from.fDbEntry;
  fLogTitle=from.fLogTitle;
  fCombo=from.fCombo;
  fTimeStart=from.fTimeStart;
  fTimeEnd=from.fTimeEnd;
  fDetType=from.fDetType;
  fSimType=from.fSimType;
  fOwner=from.fOwner;

  return *this;
}

FairDbObjTableMap::~FairDbObjTableMap()
{
}

