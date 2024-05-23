/********************************************************************************
 * Copyright (C) 2018-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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
    ~FairPrintFairLinks() override = default;

    virtual void AddBranchName(const TString& name) { fSelectedBranches.AddLast(new TObjString(name.Data())); }

    virtual void PrintBranchNameList(TList* branches);

    InitStatus Init() override;

    /** Virtual method Exec **/
    void Exec(Option_t* opt) override;

  protected:
    void InitBranchList(TList* branches);

  private:
    std::map<Int_t, TClonesArray*> fBranches;
    TList fSelectedBranches;

    void Register();
    void Reset();
    void ProduceHits();

    ClassDefOverride(FairPrintFairLinks, 1);
};

#endif
