/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                       FairGenericStack source file                    -----
// -----             Created 10/08/04  by D. Bertini                   -----
// -------------------------------------------------------------------------
#include "FairGenericStack.h"
#include "FairLogger.h"                 // for FairLogger
#include "TRefArray.h"

// -----   Default constructor   -------------------------------------------
FairGenericStack::FairGenericStack()
  : TVirtualMCStack(),
    fLogger(FairLogger::GetLogger()),
    fDetList(0),
    fDetIter(0),
    fVerbose(1)
{
}
// -------------------------------------------------------------------------
// -----   Constructor with estimated array dimension   --------------------
FairGenericStack::FairGenericStack(Int_t)
  : TVirtualMCStack(),
    fLogger(FairLogger::GetLogger()),
    fDetList(0),
    fDetIter(0),
    fVerbose(1)
{
}
// -------------------------------------------------------------------------
// -----   Destructor   ----------------------------------------------------
FairGenericStack::~FairGenericStack()
{
  delete fDetIter;
}
// -------------------------------------------------------------------------
// -----   Copy constructor   ----------------------------------------------
FairGenericStack::FairGenericStack(const FairGenericStack& rhs)
  : TVirtualMCStack(rhs),
    fLogger(FairLogger::GetLogger()),
    fDetList(rhs.fDetList),
    fDetIter(0),
    fVerbose(rhs.fVerbose)
{
}

// -------------------------------------------------------------------------
// -----   Assignment operator   -------------------------------------------
FairGenericStack& FairGenericStack::operator=(const FairGenericStack& rhs)
{
  // check assignment to self
  if (this == &rhs) return *this;

  // base class assignment
  TVirtualMCStack::operator=(rhs);

  // assignment oiperator
  fLogger = 0;
  fDetList = 0;
  fDetIter = 0;
  fVerbose = rhs.fVerbose;

  return *this;
}

// -----   Public method SetDetArrayList  ----------------------------------
void FairGenericStack::SetDetArrayList(TRefArray* detArray)
{
  fDetList=detArray;
  if(fDetList!=0) { fDetIter=fDetList->MakeIterator(); }
}

// -------------------------------------------------------------------------
// -----   Virtual method  CloneStack  -------------------------------------
FairGenericStack* FairGenericStack::CloneStack() const
{
  Fatal("CloneStack","Has to be overriden in multi-threading applications.");
  return 0;
}

// -------------------------------------------------------------------------
ClassImp(FairGenericStack)
