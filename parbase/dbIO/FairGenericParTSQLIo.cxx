/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#include "FairGenericParTSQLIo.h"

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "FairParSet.h"                 // for FairParSet
#include "FairRtdbRun.h"                // for FairRtdbRun
#include "FairRuntimeDb.h"              // for FairRuntimeDb

#include "Riosfwd.h"                    // for ostream
#include "TString.h"                    // for TString

#include <iostream>                     // for operator<<, basic_ostream, etc

class FairDbConnectionPool;

ClassImp(FairGenericParTSQLIo)

//! Constructor
FairGenericParTSQLIo::FairGenericParTSQLIo()
  : FairDetParTSQLIo(),
    fRtdb(FairRuntimeDb::instance())
{
  fName = "FairGenericParIo";
//  fRtdb = FairRuntimeDb::instance();
}

/**
 *@param cons FairDbConnectionPool which holds a number of
 * initialized db connections.
 *@param dbNum The db which is selected to act as the master for the
 * current operations.
 * Note: A new FairDbConnectionPool object is
 * created (to keep the ownership).
 */
FairGenericParTSQLIo::FairGenericParTSQLIo(FairDbConnectionPool const& cons,
    int const dbNum)
  : FairDetParTSQLIo(cons, dbNum),
    fRtdb(FairRuntimeDb::instance())
{
  fName = "FairGenericParIo";
//  fRtdb = FairRuntimeDb::instance();
}

//! Destructor
FairGenericParTSQLIo::~FairGenericParTSQLIo()
{
  std::cout << "\n\n\t<DEBUG>~FairGenericParTSQLIo() Destroy\n\n";
}

Bool_t FairGenericParTSQLIo::read(FairParGenericSet* par)
{
  UInt_t rid = fRtdb->getCurrentRun()->getRunId();
  par->fill(rid);

  std::cout << "-I- FairGenericParTSQLIo::read(FairParGenericSet* par) done for runId#  " <<  rid << std::endl;

  return kTRUE;
}

Bool_t FairGenericParTSQLIo::init(FairParSet* pPar)
{

  std::cout << "-I- FairGenericParTSQLIo::init(FairParSet* par) called  " << std::endl;
  if (pPar->InheritsFrom("FairParGenericSet")) {
    return read((FairParGenericSet*)pPar);
  }

  Error("FairGenericParTSQLIo::init(FairParSet*, Int_t*)",
        "%s does not inherit from FairParGenericSet", pPar->GetName());

  return false;
}

Int_t FairGenericParTSQLIo::write(FairParSet* par)
{
  if (par->InheritsFrom("FairParGenericSet")) {
    return writeSet((FairParGenericSet*)par);
  }
  Error("FairGenericParOraIo::write(FairParSet*)",
        "%s does not inherit from FairParGenericSet",par->GetName());
  return -1;
}

Int_t FairGenericParTSQLIo::writeSet(FairParGenericSet* par)
{
  if(!par) {
    std::cerr << "-E FairGenericParTSQLIo::writeSet() : no Parameter container#\n" << std::endl;;
    return -1;
  }

  std::cout << "-I- FairGenericParTSQLIo::writeSet(FairParGenericSet* par)\n"
            << " Name is " << par->GetName()
            << " Context = " << par->getParamContext()
            <<"\n---------------  Storage of "<< par->GetName()<<"  ---------------\n"
            << "Class name = " << par->ClassName() << std::endl;

  UInt_t rid = fRtdb->getCurrentRun()->getRunId();
  par->store(rid);

  std::cout << "-I- FairGenericParTSQLIo::WriteSet() done  for runID# " <<  rid << std::endl;
  return 1;
}
