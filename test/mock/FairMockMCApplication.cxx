/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
# include "FairMockMCApplication.h"

FairMockMCApplication::FairMockMCApplication(const char* name, const char* title)
  :TVirtualMCApplication(name,title)
{
}

FairMockMCApplication::FairMockMCApplication()
  :TVirtualMCApplication()
{
}

FairMockMCApplication::~FairMockMCApplication()
{
  delete gMC;
  gMC=0;
}


ClassImp(FairMockMCApplication)
