/*
 * FairMCList.cxx
 *
 *  Created on: Dec 3, 2009
 *      Author: stockman
 */

#include "FairMCList.h"

ClassImp(FairMCList);

FairMCList::FairMCList()
  : TObject(),
    fList(),
    fEntry(-1),
    fType(-1)
{
}

FairMCList::~FairMCList()
{
}
