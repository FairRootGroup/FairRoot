/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTimeStamp.h"

// -------------------------------------------------------------------------

std::ostream& FairTimeStamp::PrintTimeInfo(std::ostream& out) const
{
  out << "EntryNr of Data: " << fEntryNr << " TimeStamp: " << GetTimeStamp() << " +/- " << GetTimeStampError() << std::endl;
  FairMultiLinkedData_Interface::PrintLinkInfo(out);

  return out;
}
ClassImp(FairTimeStamp)
