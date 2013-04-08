/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#include "FairGenericParTSQLIo.h"

#include "FairParSet.h"
#include "FairParGenericSet.h"
#include "FairParamList.h"
#include "FairRuntimeDb.h"
#include "FairRtdbRun.h"

#include "TList.h"


ClassImp(FairGenericParTSQLIo)

//! Constructor
FairGenericParTSQLIo::FairGenericParTSQLIo()
  : FairDetParTSQLIo()
{
  fName = "FairGenericParIo";
  fRtdb = FairRuntimeDb::instance();
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
  fRtdb = FairRuntimeDb::instance();
}

//! Destructor
FairGenericParTSQLIo::~FairGenericParTSQLIo()
{
  std::cout << "\n\n\t<DEBUG>~FairGenericParTSQLIo() Destroy\n\n";
}

Bool_t FairGenericParTSQLIo::read(FairParGenericSet* par)
{
  UInt_t rid = fRtdb->getCurrentRun()->getRunId();
  par->Fill(rid);

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
  par->Store(rid);

  std::cout << "-I- FairGenericParTSQLIo::WriteSet() done  for runID# " <<  rid << std::endl;
  return 1;
}
