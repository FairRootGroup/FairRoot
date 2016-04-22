/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTimeStamp.h"

// -----   Default constructor   -------------------------------------------
FairTimeStamp::FairTimeStamp()
  : FairMultiLinkedData_Interface(),
    fTimeStamp(-1),
    fTimeStampError(-1),
    fEntryNr()
{
}
// -----   Standard constructor   ------------------------------------------
FairTimeStamp::FairTimeStamp(Double_t time)
  : FairMultiLinkedData_Interface(),
    fTimeStamp(time),
    fTimeStampError(-1),
    fEntryNr()
{
}

FairTimeStamp::FairTimeStamp(Double_t time, Double_t timeerror)
  : FairMultiLinkedData_Interface(),
    fTimeStamp(time),
    fTimeStampError(timeerror),
    fEntryNr()
{
}

// -----   Destructor   ----------------------------------------------------
FairTimeStamp::~FairTimeStamp()
{
}

// -------------------------------------------------------------------------

std::ostream& FairTimeStamp::PrintTimeInfo(std::ostream& out) const
{
  out << "EntryNr of Data: " << fEntryNr << " TimeStamp: " << GetTimeStamp() << " +/- " << GetTimeStampError() << std::endl;
  FairMultiLinkedData_Interface::PrintLinkInfo(out);

  return out;
}
ClassImp(FairTimeStamp)
