/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#include "FairGenericParTSQLIo.h"

#include "FairParSet.h"
#include "FairParGenericSet.h"
#include "FairParamList.h"

#include "TList.h"


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

Bool_t FairGenericParTSQLIo::read(FairParGenericSet* par)
{
  std::cout << "\n\n\t<DEBUG>FairGenericParTSQLIo::read(FairParGenericSet* par)\n\n";
  par->Print();
  return false;
}

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

Int_t FairGenericParTSQLIo::write(FairParSet* par)
{
  std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
            << "\t<DEBUG>FairGenericParTSQLIo::Write(FairParSet* par)\n";
  if (par->InheritsFrom("FairParGenericSet")) {
    return writeSet((FairParGenericSet*)par);
  }
  std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
  Error("FairGenericParOraIo::write(FairParSet*)",
        "%s does not inherit from FairParGenericSet",par->GetName());
  return -1;
}

Int_t FairGenericParTSQLIo::writeSet(FairParGenericSet* par)
{
  if(!par) {
    std::cout << "No par not initialized\n";
    return -1;
  }
  std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
            << "\t<DEBUG>FairGenericParTSQLIo::writeSet(FairParGenericSet* par)\n";
  std::cout << "Name is " << par->GetName()
            << " Context = " << par->getParamContext();
  std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";

  std::cout <<"---------------  Storage of "<< par->GetName()<<"  ---------------\n";
  std::cout << "Class name = " << par->ClassName() << std::endl;

  FairParamList* paramList = new FairParamList();
  par->putParams(paramList);

  TList* pList=paramList->getList();
  TIter next(pList);
  FairParamObj* po;

  while ((po=(FairParamObj*)next())) {
    std::cout << " po.Name =" << po->GetName() << '\n'
              << " po.val = " << po->getParamValue()<< '\n'
              << " po.Type =" << po->getParamType()
              << "\n+++++\n";
  }
  return -1;
}
