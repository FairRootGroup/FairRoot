/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/********************************************
 * Author:     M.Babai (M.Babai@rug.nl)     *
 * Modified:   D.Bertini (D.Bertini@gsi.de) *
 * License:                                 *
 * Version:                                 *
 *******************************************/
#include "FairDetParTSQLIo.h"

#include "FairDbConnectionPool.h"        // for FairDbConnectionPool
#include "FairDbTableInterfaceStore.h"   // for FairDbTableInterfaceStore
#include "FairParSet.h"                 // for FairParSet
#include "FairRtdbRun.h"                // for FairRtdbRun
#include "FairRuntimeDb.h"              // for FairRuntimeDb

#include "TList.h"                      // for TList
#include "TString.h"                    // for TString

#include <stdio.h>                      // for sscanf
#include <string.h>                     // for strlen

ClassImp(FairDetParTSQLIo)

/// Constructor
FairDetParTSQLIo::FairDetParTSQLIo()
  : FairDetParIo(),
    fDefaultDb(-1),
    fConnections(FairDbTableInterfaceStore::Instance().fConnectionPool),
    fcontainerList(0),
    factContVers(0),
    actRunId(-1)
{}

/**
 *@param cons FairDbConnectionPool which holds a number of
 * initialized db connections.
 *@param dbNum The number of the db which is selected to act as the
 * master for the current operations.
 * Note: A new FairDbConnectionPool object is created (to keep the
 * ownership).
 */

FairDetParTSQLIo::FairDetParTSQLIo(FairDbConnectionPool const& cons, int const dbNum)
  : FairDetParIo(),
    fDefaultDb(dbNum),
    fConnections(new FairDbConnectionPool(cons)),
    fcontainerList(0),
    factContVers(0),
    actRunId(-1)
{}


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
