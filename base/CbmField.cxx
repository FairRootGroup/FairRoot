// -------------------------------------------------------------------------
// -----                       CbmField source file                    -----
// -----                Created 06/01/04  by M. Al/Turany              -----
// -----                Redesign 13/02/06  by V. Friese                -----
// -------------------------------------------------------------------------


#include "CbmField.h"



// -----   Default constructor   -------------------------------------------
CbmField::CbmField() 
 : TNamed("", "CBM Magnetic Field"), fType(0)
{ 
}
// -------------------------------------------------------------------------



// -----   Constructor with name and title   -------------------------------
CbmField::CbmField(const char* name, const char* title) 
  : TNamed(name, title), fType(0) 
{
  
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
CbmField::~CbmField() { }
// -------------------------------------------------------------------------



// -----   Test field type Constant   --------------------------------------
Bool_t CbmField::IsConst() {
  if ( fType == 1 ) return kTRUE;
  return kFALSE;
}
// -------------------------------------------------------------------------



// -----   Test field type Map   -------------------------------------------
Bool_t CbmField::IsMap() {
  if ( fType == 2 ) return kTRUE;
  return kFALSE;
}
// -------------------------------------------------------------------------
void CbmField::GetFieldValue(const Double_t point[3], Double_t* bField) 
{
  bField[0] = GetBx(point[0], point[1], point[2]);
  bField[1] = GetBy(point[0], point[1], point[2]);
  bField[2] = GetBz(point[0], point[1], point[2]);
}


ClassImp(CbmField)
