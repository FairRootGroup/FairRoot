/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#include "FairGenericParTSQLIo.h"


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
  std::cout << "~FairGenericParTSQLIo()\n";
}


bool FairGenericParTSQLIo::read(FairParGenericSet& par)
{
  par.Print();
  std::cout << "FairGenericParTSQLIo::read(FairParGenericSet& par)\n";
  return false;
}

int FairGenericParTSQLIo::write(FairParSet& par)
{
  par.Print();
  std::cout << "FairGenericParTSQLIo::write(FairParSet& par)\n";
  return 1;
}

int FairGenericParTSQLIo::writeSet(FairParGenericSet& par)
{
  par.Print();
  std::cout << "FairGenericParTSQLIo::writeSet(FairParGenericSet& par)\n";
  return 0;
}
