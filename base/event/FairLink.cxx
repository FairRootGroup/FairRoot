/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairLink.cpp
 *
 *  Created on: Dec 23, 2009
 *      Author: stockman
 */

#include "FairLink.h"
#include "FairRootManager.h"

ClassImp(FairLink);


FairLink::FairLink(TString branchName, Int_t index, Float_t weight)
  :fFile(-1),
   fEntry(-1),
   fType(FairRootManager::Instance()->GetBranchId(branchName)),
   fIndex(index),
   fWeight(weight)
{
}


FairLink::FairLink(Int_t file, Int_t entry, TString branchName, Int_t index, Float_t weight)
  :fFile(file),
   fEntry(entry),
   fType(FairRootManager::Instance()->GetBranchId(branchName)),
   fIndex(index),
   fWeight(weight)
{
}

void FairLink::PrintLinkInfo(std::ostream& out) const
{
  out << "(" << GetFile() << "/" << GetEntry() << "/";
  out << GetType() << "/" << GetIndex() << "/" << GetWeight() << ")";
}


