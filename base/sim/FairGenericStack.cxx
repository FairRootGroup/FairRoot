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
FairGenericStack::FairGenericStack(Int_t size)
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
// -----   Virtual method PushTrack   --------------------------------------
void FairGenericStack::PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
                                 Double_t px, Double_t py, Double_t pz,
                                 Double_t e, Double_t vx, Double_t vy, Double_t vz,
                                 Double_t time, Double_t polx, Double_t poly,
                                 Double_t polz, TMCProcess proc, Int_t& ntr,
                                 Double_t weight, Int_t is)
{

}

void FairGenericStack::PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
                                 Double_t px, Double_t py, Double_t pz,
                                 Double_t e, Double_t vx, Double_t vy, Double_t vz,
                                 Double_t time, Double_t polx, Double_t poly,
                                 Double_t polz, TMCProcess proc, Int_t& ntr,
                                 Double_t weight, Int_t is, Int_t secondMotherID)
{

}
// -----   Virtual method PopNextTrack   -----------------------------------
TParticle* FairGenericStack::PopNextTrack(Int_t& iTrack)
{
  return 0;
}
// -------------------------------------------------------------------------
// -----   Virtual method PopPrimaryForTracking   --------------------------
TParticle* FairGenericStack::PopPrimaryForTracking(Int_t iPrim)
{
  return 0;
}
// -------------------------------------------------------------------------
// -----   Public method AddParticle   -------------------------------------
void FairGenericStack::AddParticle(TParticle* oldPart)
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
void FairGenericStack::UpdateTrackIndex(TRefArray* detList)
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
void FairGenericStack::Print(Option_t* option) const
{
}
// -------------------------------------------------------------------------
// -----   Virtual method SetCurrentTrack   --------------------------------
void FairGenericStack::SetCurrentTrack(Int_t iTrack)
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
ClassImp(FairGenericStack)
