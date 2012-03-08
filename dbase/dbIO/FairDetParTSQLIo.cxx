/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#include "FairDetParTSQLIo.h"

ClassImp(FairDetParTSQLIo)

/// Constructor
FairDetParTSQLIo::FairDetParTSQLIo()
  : FairDetParIo(),
    fDefaultDb(-1),
    fConnections(new FairDbMultConnector()),
    fcontainerList(0),
    factContVers(0)
{}

/**
 *@param cons FairDbMultConnector which holds a number of
 * initialized db connections.
 *@param dbNum The number of the db which is selected to act as the
 * master for the current operations.
 * Note: A new FairDbMultConnector object is created (to keep the
 * ownership).
 */
FairDetParTSQLIo::FairDetParTSQLIo(FairDbMultConnector const& cons, int const dbNum)
  : FairDetParIo(),
    fDefaultDb(dbNum),
    fConnections(new FairDbMultConnector(cons)),
    fcontainerList(0),
    factContVers(0)
{}

/// Destructor.
FairDetParTSQLIo::~FairDetParTSQLIo()
{
  if( fConnections ) {
    delete fConnections;
  }

  if( factContVers ) {
    delete factContVers;
  }

  if( fcontainerList ) {
    fcontainerList->Delete();
    delete fcontainerList;
  }
}

// commits changes.
void FairDetParTSQLIo::commit()
{
  std::cerr << "<ERROR> Commit() is Not implemented yet. Maybe later"
            << std::endl;
}

// Undo the changes made since last commit.
void FairDetParTSQLIo::rollback()
{
  std::cerr << "<ERROR> Rollback() Not implemented yet. Maybe later\n"
            << "        It remains engine dependent."
            << std::endl;
}

bool FairDetParTSQLIo::read (FairParSet* pars)
{
  pars->Print();
  std::cout << "\n\tFairDetParTSQLIo::read (FairParSet* pars)\n\n";
  return false;
}

int  FairDetParTSQLIo::write(FairParSet* pars)
{
  pars->Print();
  std::cout << "\n\tFairDetParTSQLIo::write(FairParSet* pars)\n\n";
  return 0;
}
