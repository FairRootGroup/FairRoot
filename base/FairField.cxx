// -------------------------------------------------------------------------
// -----                       FairField source file                    -----
// -----                Created 06/01/04  by M. Al/Turany              -----
// -----                Redesign 13/02/06  by V. Friese                -----
// -------------------------------------------------------------------------

#include"FairField.h"



// -----   Default constructor   -------------------------------------------
FairField::FairField()
  : TVirtualMagField("FAIR Magnetic Field"), fType(0), fLogger(FairLogger::GetLogger())
{
}
// -------------------------------------------------------------------------



// -----   Constructor with name and title   -------------------------------
FairField::FairField(const char* name, const char* title)
  :TVirtualMagField(name), fType(0) , fLogger(FairLogger::GetLogger())
{

}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairField::~FairField() { }
// -------------------------------------------------------------------------



// -----   Test field type Constant   --------------------------------------
Bool_t FairField::IsConst()
{
  if ( fType == 1 ) { return kTRUE; }
  return kFALSE;
}
// -------------------------------------------------------------------------



// -----   Test field type Map   -------------------------------------------
Bool_t FairField::IsMap()
{
  if ( fType == 2 ) { return kTRUE; }
  return kFALSE;
}
// -------------------------------------------------------------------------
void FairField::GetFieldValue(const Double_t point[3], Double_t* bField)
{
  bField[0] = GetBx(point[0], point[1], point[2]);
  bField[1] = GetBy(point[0], point[1], point[2]);
  bField[2] = GetBz(point[0], point[1], point[2]);
}


ClassImp(FairField)
