// -------------------------------------------------------------------------
// -----                     FairGenerator source file                  -----
// -----                 Created 23/06/04  by  V. Friese               -----
// -------------------------------------------------------------------------


#include "FairGenerator.h"


// -----   Default constructor   -------------------------------------------
FairGenerator::FairGenerator() {}
// -------------------------------------------------------------------------



// -----   Constructor with name and title   -------------------------------
FairGenerator::FairGenerator(const char* name, const char* title)
  : TNamed(name, title) {}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairGenerator::~FairGenerator() { }
// -------------------------------------------------------------------------


ClassImp(FairGenerator)
