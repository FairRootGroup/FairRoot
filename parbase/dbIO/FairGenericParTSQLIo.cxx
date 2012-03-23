/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#include "FairGenericParTSQLIo.h"

#include "FairParSet.h"
#include "FairParGenericSet.h"

ClassImp(FairGenericParTSQLIo)

//! Constructor
FairGenericParTSQLIo::FairGenericParTSQLIo()
  : FairDetParTSQLIo()
{
  fName = "FairGenericParIo";
}

/**
 *@param cons FairDbMultConnector which holds a number of
 * initialized db connections.
 *@param dbNum The db which is selected to act as the master for the
 * current operations.
 * Note: A new FairDbMultConnector object is
 * created (to keep the ownership).
 */
FairGenericParTSQLIo::FairGenericParTSQLIo(FairDbMultConnector const& cons,
    int const dbNum)
  : FairDetParTSQLIo(cons, dbNum)
{
  fName = "FairGenericParIo";
}

//! Destructor
FairGenericParTSQLIo::~FairGenericParTSQLIo()
{
  std::cout << "\n\n\t<DEBUG>~FairGenericParTSQLIo() Destroy\n\n";
}

//bool FairGenericParTSQLIo::read(FairParGenericSet& par)
Bool_t FairGenericParTSQLIo::read(FairParGenericSet& par)
{
  std::cout << "\n\n\t<DEBUG>FairGenericParTSQLIo::read(FairParGenericSet& par)\n\n";
  par.Print();
  return false;
}

//bool FairGenericParTSQLIo::init(FairParSet* pPar, int* n)
Bool_t FairGenericParTSQLIo::init(FairParSet* pPar, Int_t* n)
{
  std::cout << "\n\n\t<DEBUG>FairGenericParTSQLIo::init(FairParSet* pars, int* n)\n\n";

  // calls read(FairParGenericSet*,Int_t*)
  if (pPar->InheritsFrom("FairParGenericSet")) {
    std::cout << "@@@@@@<Init From db>@@@@@@@\n\n";
    return read((FairParGenericSet*)pPar);
  }
  Error("FairGenericParTSQLIo::init(FairParSet*, Int_t*)",
        "%s does not inherit from FairParGenericSet", pPar->GetName());
  return false;
}

int FairGenericParTSQLIo::write(FairParSet& par)
{
  std::cout << "\n\n\t<DEBUG>FairGenericParTSQLIo::write(FairParSet& par)\n\n";
  par.Print();
  return -1;
}

int FairGenericParTSQLIo::writeSet(FairParGenericSet& par)
{
  std::cout << "\n\n\t<DEBUG>FairGenericParTSQLIo::writeSet(FairParGenericSet& par)\n\n";
  par.Print();
  return -1;
}
