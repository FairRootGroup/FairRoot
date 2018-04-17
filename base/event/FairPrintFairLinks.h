// -------------------------------------------------------------------------
// -----                 FairPrintFairLinks header file             -----
// -----                  Created 20/03/07  by R.Kliemt               -----
// -------------------------------------------------------------------------


/** FairPrintFairLinks.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Prints all FairLinks of a given branch to the screen
 **/


#ifndef FairPrintFairLinks_H
#define FairPrintFairLinks_H


// framework includes
#include "FairTask.h"


#include <vector>
#include <map>

class TClonesArray;

class FairPrintFairLinks : public FairTask
{
 public:

  /** Default constructor **/
	FairPrintFairLinks();

  /** Destructor **/
  virtual ~FairPrintFairLinks();


  /** Virtual method Init **/
  virtual void SetParContainers();

  virtual void AddBranchName(const TString& name){
	  fSelectedBranches->AddLast(new TObjString(name.Data()));
  }

  virtual void PrintBranchNameList(TList* branches);

  virtual InitStatus Init();


  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);

  virtual void Finish();

 protected:
  void InitBranchList(TList* branches);



 private:
  std::map<Int_t, TClonesArray*> fBranches;
  TList* fSelectedBranches;

  void Register();

  void Reset();

  void ProduceHits();


  ClassDef(FairPrintFairLinks,1);

};

#endif
