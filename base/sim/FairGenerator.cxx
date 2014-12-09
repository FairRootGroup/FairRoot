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


// -----   Copy constructor ------------------------------------------------
FairGenerator::FairGenerator(const FairGenerator& rhs)
  : TNamed(rhs) {}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
FairGenerator::~FairGenerator() { }
// -------------------------------------------------------------------------

// -----   Assignment   ----------------------------------------------------
FairGenerator& FairGenerator::operator= (const FairGenerator& rhs)
{
  // check assignment to self
  if (this == &rhs) return *this;

  // base class assignment
  TNamed::operator=(rhs);

  return *this;
}

// -----   Clone this object   ---------------------------------------------
FairGenerator* FairGenerator::CloneGenerator() const
{
  Fatal("CloneGenerator","Has to be overriden in multi-threading applications.");
  return 0;
}

ClassImp(FairGenerator)
