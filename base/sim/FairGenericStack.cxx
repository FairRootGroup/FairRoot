/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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
}
// -------------------------------------------------------------------------
// -----   Copy constructor   ----------------------------------------------
FairGenericStack::FairGenericStack(const FairGenericStack& rhs)
  : TVirtualMCStack(rhs),
    fLogger(0),
    fDetList(0),
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

// -------------------------------------------------------------------------
// -----   Virtual method PushTrack   --------------------------------------
void FairGenericStack::PushTrack(Int_t, Int_t, Int_t,
                                 Double_t, Double_t, Double_t,
                                 Double_t, Double_t, Double_t, Double_t,
                                 Double_t, Double_t, Double_t,
                                 Double_t, TMCProcess, Int_t&,
                                 Double_t, Int_t)
{

}

void FairGenericStack::PushTrack(Int_t, Int_t, Int_t,
                                 Double_t, Double_t, Double_t,
                                 Double_t, Double_t, Double_t, Double_t,
                                 Double_t, Double_t, Double_t,
                                 Double_t, TMCProcess, Int_t&,
                                 Double_t, Int_t, Int_t)
{

}
// -----   Virtual method PopNextTrack   -----------------------------------
TParticle* FairGenericStack::PopNextTrack(Int_t&)
{
  return 0;
}
// -------------------------------------------------------------------------
// -----   Virtual method PopPrimaryForTracking   --------------------------
TParticle* FairGenericStack::PopPrimaryForTracking(Int_t)
{
  return 0;
}
// -------------------------------------------------------------------------
// -----   Public method AddParticle   -------------------------------------
void FairGenericStack::AddParticle(TParticle*)
{
}
// -----   Public method SetDetArrayList  ----------------------------------
void FairGenericStack::SetDetArrayList(TRefArray* detArray)
{
  fDetList=detArray;
  if(fDetList!=0) { fDetIter=fDetList->MakeIterator(); }
}
// -------------------------------------------------------------------------
// -----   Public method FillTrackArray   ----------------------------------
void FairGenericStack::FillTrackArray()
{
}
// -------------------------------------------------------------------------
// -----   Public method UpdateTrackIndex   --------------------------------
void FairGenericStack::UpdateTrackIndex(TRefArray*)
{

}
// -------------------------------------------------------------------------
// -----   Public method Reset   -------------------------------------------
void FairGenericStack::Reset()
{
}
// -------------------------------------------------------------------------
// -----   Public method Register   ----------------------------------------
void FairGenericStack::Register()
{
}
// -------------------------------------------------------------------------
// -----   Public method Print  --------------------------------------------
void FairGenericStack::Print(Option_t*) const
{
}
// -------------------------------------------------------------------------
// -----   Virtual method SetCurrentTrack   --------------------------------
void FairGenericStack::SetCurrentTrack(Int_t)
{
}
// -------------------------------------------------------------------------
// -----   Virtual method GetNtrack   --------------------------------------
Int_t FairGenericStack::GetNtrack() const
{
  return 0;
}
// -------------------------------------------------------------------------
// -----   Virtual method GetNprimary   ------------------------------------
Int_t FairGenericStack::GetNprimary() const
{
  return 0;
}
// -------------------------------------------------------------------------
// -----   Virtual method GetCurrentTrack   --------------------------------
TParticle* FairGenericStack::GetCurrentTrack() const
{
  return NULL;
}
// -------------------------------------------------------------------------
// -----   Virtual method GetCurrentTrackNumber   --------------------------
Int_t FairGenericStack::GetCurrentTrackNumber() const
{
  return 0;
}
// -------------------------------------------------------------------------
// -----   Virtual method GetCurrentParentTrackNumber   --------------------
Int_t FairGenericStack::GetCurrentParentTrackNumber() const
{
  return 0;
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
