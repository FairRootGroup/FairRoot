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

#include "FairTask.h"

#include <TClonesArray.h>
#include <TObjString.h>
#include <map>

class FairPrintFairLinks : public FairTask
{
  public:
    /** Default constructor **/
    FairPrintFairLinks();

    /** Destructor **/
    ~FairPrintFairLinks() override;

    virtual void AddBranchName(const TString& name) { fSelectedBranches->AddLast(new TObjString(name.Data())); }

    virtual void PrintBranchNameList(TList* branches);

    InitStatus Init() override;

    /** Virtual method Exec **/
    void Exec(Option_t* opt) override;

    void Finish() override;

  protected:
    void InitBranchList(TList* branches);

  private:
    std::map<Int_t, TClonesArray*> fBranches;
    TList* fSelectedBranches;

    void Register();
    void Reset();
    void ProduceHits();

    ClassDefOverride(FairPrintFairLinks, 1);
};

#endif
