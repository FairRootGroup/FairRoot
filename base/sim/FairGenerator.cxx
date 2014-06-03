/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                     FairGenerator source file                 -----
// -------------------------------------------------------------------------


#include "FairGenerator.h"


// -----   Default constructor   -------------------------------------------
FairGenerator::FairGenerator()
  : TNamed() {}
// -------------------------------------------------------------------------



// -----   Constructor with name and title   -------------------------------
FairGenerator::FairGenerator(const char* name, const char* title)
  : TNamed(name, title) {}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairGenerator::~FairGenerator() { }
// -------------------------------------------------------------------------


ClassImp(FairGenerator)
