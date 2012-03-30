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
  /*
   * Initialize paramter from the data base.
   */
  std::cout << "\t<DEBUG>FairGenericParTSQLIo::read(FairParGenericSet* par)"
            << "\n Reading parameters form the database.\n";
  par->Print();
  std::cout << "============= End of reading params ==========\n";
  return kTRUE;
}

Bool_t FairGenericParTSQLIo::init(FairParSet* pPar)
{
  std::cout << "\n\n\t<DEBUG>FairGenericParTSQLIo::init(FairParSet* pars, int* n)\n\n";

  if (pPar->InheritsFrom("FairParGenericSet")) {
    std::cout << "@@@@@@ <Init From db> @@@@@@@\n\n";
    return read((FairParGenericSet*)pPar);
  }
  Error("FairGenericParTSQLIo::init(FairParSet*, Int_t*)",
        "%s does not inherit from FairParGenericSet", pPar->GetName());
  return false;
}

Int_t FairGenericParTSQLIo::write(FairParSet* par)
{
  std::cout << "\n===================================================\n"
            << "\t<DEBUG>FairGenericParTSQLIo::Write(FairParSet* par)\n";
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
    std::cerr << "No par not initialized\n";
    return -1;
  }

  std::cout << "\t<DEBUG>FairGenericParTSQLIo::writeSet(FairParGenericSet* par)\n"
            << " Name is " << par->GetName()
            << " Context = " << par->getParamContext()
            <<"\n---------------  Storage of "<< par->GetName()<<"  ---------------\n"
            << "Class name = " << par->ClassName() << std::endl;

  // Initialize the par list object
  FairParamList* paramList = new FairParamList();
  par->putParams(paramList);

  // Get the list to insert.
  TList* pList = paramList->getList();
  TIter next(pList);
  FairParamObj* po;

  /*
   * Build a list of Insert queries and sumbit all in one go. Or build
   * a query per paramobject and insert directly.
   */
  while ((po=(FairParamObj*)next())) {
    std::cout << " po.Name = " << po->GetName()      << '\n'
              << " po.val = "  << po->getParamValue()<< '\n'
              << " po.Type = " << po->getParamType() << '\n'
              << " po.Basic = " << po->isBasicType()  << '\n'
              << " po.Bytes = " << po->getBytesPerValue()<< '\n'
              << " po.getClassVersion = " << po->getClassVersion() << '\n'
              << " po.getLength = " << po->getLength() << '\n'
              << " po.getNumParams = " << po->getNumParams()<<'\n'
              << "____________________________\n";
    po->print();
    std::cout << "\n++++++++++++++++++++++++\n";
  }
  std::cout << "\n========== END OF STORAGE ========================\n";
  return 1;
}
