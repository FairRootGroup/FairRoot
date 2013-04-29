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
