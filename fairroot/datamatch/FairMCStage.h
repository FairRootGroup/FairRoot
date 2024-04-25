/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCStage.h
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#ifndef FAIRMCSTAGE_H_
#define FAIRMCSTAGE_H_

#ifndef FAIR_SILENCE_DATAMATCH_DEPRECATION
#warning "FairRoot::DataMatch is deprecated and will be removed in a future major release"
#endif

#include "FairMCObject.h"   // for FairMCObject

#include <Rtypes.h>   // for Bool_t, Double_t, etc
#include <iostream>   // for ostream, basic_ostream, etc
#include <string>     // for string, operator<<, etc

class FairMCStage : public FairMCObject
{
  public:
    FairMCStage();
    FairMCStage(Int_t id, const std::string& fileName, const std::string& branchName, Double_t weight = 1.0);

    FairMCStage(const FairMCStage& mcStage)
        : FairMCObject(mcStage)
        , fBranchName(mcStage.fBranchName)
        , fFileName(mcStage.fFileName)
        , fWeight(mcStage.fWeight)
        , fLoaded(mcStage.fLoaded)
        , fFill(mcStage.fFill)
    {}

    FairMCStage& operator=(const FairMCStage& result)
    {

        if (this == &result) {
            return *this;
        }

        FairMCObject::operator=(result);
        fBranchName = result.fBranchName;
        fFileName = result.fFileName;
        fWeight = result.fWeight;
        fLoaded = result.fLoaded;
        fFill = result.fFill;

        return *this;
    }

    virtual ~FairMCStage();

    void SetBranchName(const std::string& branchName) { fBranchName = branchName; }
    void SetFileName(const std::string& fileName) { fFileName = fileName; }
    void SetWeight(Double_t weight) { fWeight = weight; }
    void SetLoaded(Bool_t loaded) { fLoaded = loaded; }
    void SetFill(Bool_t fill) { fFill = fill; }

    std::string GetBranchName() const { return fBranchName; }
    std::string GetFileName() const { return fFileName; }
    Double_t GetWeight() const { return fWeight; }
    Bool_t GetLoaded() const { return fLoaded; }
    Bool_t GetFill() const { return fFill; }

    virtual void ClearEntries()
    {
        FairMCObject::ClearEntries();
        fLoaded = kFALSE;
    }

    virtual void PrintInfo(std::ostream& out) { out << *this; }

    friend std::ostream& operator<<(std::ostream& out, const FairMCStage& stage)
    {
        out << stage.GetStageId() << ": " << stage.GetBranchName() << " // " << stage.GetFileName()
            << std::endl;   //" with weight: " << stage.GetWeight() << std::endl;
        (static_cast<FairMCObject>(stage)).PrintInfo(out);
        return out;
    }

  private:
    std::string fBranchName;
    std::string fFileName;
    Double_t fWeight;
    Bool_t fLoaded;   ///< indicates if this stage was loaded already from a Link file
    Bool_t fFill;     ///< indicates if a corresponding DataFile with FairLinks exists to fill this stage

    ClassDef(FairMCStage, 1);
};

#endif /* FAIRMCSTAGE_H_ */
