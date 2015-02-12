/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbParSet.h"

ClassImp(FairDbParSet)

FairDbParSet::FairDbParSet()
  : FairDbObjTableMap("","","",kFALSE)
{
}

FairDbParSet::FairDbParSet(const FairDbParSet& from)
  : FairDbObjTableMap(from)
{
}


FairDbParSet& FairDbParSet::operator=(const FairDbParSet& from)
{
  if (this == &from) { return *this; }

  FairDbObjTableMap::operator=(from);
 
  return *this;
}

FairDbParSet::~FairDbParSet()
{
}

