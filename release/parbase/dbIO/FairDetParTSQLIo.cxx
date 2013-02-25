/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#include "FairDetParTSQLIo.h"

#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairDbMultConnector.h"
#include "FairRtdbRun.h"
#include "FairParSet.h"

ClassImp(FairDetParTSQLIo)

/// Constructor
FairDetParTSQLIo::FairDetParTSQLIo()
  : FairDetParIo(),
    fDefaultDb(-1),
    fConnections(new FairDbMultConnector()),
    fcontainerList(0),
    factContVers(0),
    actRunId(-1)
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
    factContVers(0),
    actRunId(-1)
{}

/// Destructor.
FairDetParTSQLIo::~FairDetParTSQLIo()
{
  std::cout << "\n\t<DEBUG> FairDetParTSQLIo::~FairDetParTSQLIo()\n\n";
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

int FairDetParTSQLIo::getRunStart(FairParSet* pPar)
{
  std::cout << "\n\n\n\n\t<DEBUG> FairDetParTSQLIo::getRunStart(FairParSet* pPar)\n\n\n\n";
  actRunId=-1;
  int runStart=-1;
  factContVers=FairRuntimeDb::instance()->getCurrentRun();

  if (!factContVers) {
    Error("getRunStart()","current run not set in runtime database");
    return -1;
  }

  const Text_t* refRun=factContVers->getRefRun();

  if (strlen(refRun) > 0) {
    sscanf(refRun,"%i",&actRunId);
  } else {
    actRunId=factContVers->getRunId();
  }

  if(pPar) {
    Int_t contVers = 10;//getPredefVersion(pPar);
    if (contVers>=0) {
      actRunId = contVers;
    }
  }
  //runStart=pConn->getRunStart(actRunId);
  return runStart;
}

void FairDetParTSQLIo::setChanged(FairParSet* pPar)
{
  // sets the changed flag, the version (id of actual run) and the comment
  pPar->setChanged();
  //pPar->setInputVersion(getActRunId(), inputNumber);
  TString s="Read from TSQL\n             Valid for Run Id ";
  //s.Append(Form("%d",getActRunId()));
  s.Append("\n             Status at ");
  //s.Append(pConn->getHistoryDate());
  pPar->setDescription(s.Data());
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


Bool_t FairDetParTSQLIo::read (FairParSet* pars)
{
  std::cout << "========================================================\n";
  pars->Print();
  std::cout << "\n\t<DEBUG>FairDetParTSQLIo::READ(FairParSet* pars)\n"
            << "========================================================\n";
  return false;
}

Int_t  FairDetParTSQLIo::write(FairParSet* pars)
{
  std::cout << "========================================================\n"
            <<"\t<DEBUG> FairDetParTSQLIo::WRITE(FairParSet* pars)\n"
            << "Name is = " << pars->GetName() << " "
            << " Desc = " << pars->getDescription() << " "
            << " Autho = " << pars->getAuthor() << " "
            << " Context = " << pars->getParamContext() << " "
            << " DetNAme = " << pars->getDetectorName()
            << "\n========================================================\n";
  return 0;
}
