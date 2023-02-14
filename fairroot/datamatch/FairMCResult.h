/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCResult.h
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#ifndef FAIRMCRESULT_H_
#define FAIRMCRESULT_H_

#ifndef FAIR_SILENCE_DATAMATCH_DEPRECATION
#warning "FairRoot::DataMatch is deprecated and will be removed in a future major release"
#endif

#include "FairMCEntry.h"    // for FairMCEntry
#include "FairMCObject.h"   // for FairMCObject

#include <Rtypes.h>   // for Int_t, FairMCResult::Class, etc
#include <iostream>   // for operator<<, ostream, etc

class FairMCResult : public FairMCObject
{
  public:
    FairMCResult();
    FairMCResult(Int_t start, Int_t stop);

    FairMCResult(const FairMCResult& result)
        : FairMCObject(result.GetStartType(), result.GetEntryVector())
        , fStartType(result.GetStartType())
        , fStopType(result.GetStopType())
    {}

    FairMCResult& operator=(const FairMCResult& result)
    {

        if (this == &result) {
            return *this;
        }

        FairMCObject::operator=(result);
        fStartType = result.fStartType;
        fStopType = result.fStopType;

        return *this;
    }

    virtual ~FairMCResult();

    void SetStartType(Int_t start) { fStartType = start; }
    void SetStopType(Int_t stop) { fStopType = stop; }

    Int_t GetStartType(void) const { return fStartType; }
    Int_t GetStopType(void) const { return fStopType; }

    virtual void PrintInfo(std::ostream& out = std::cout) { out << *this; }

    friend std::ostream& operator<<(std::ostream& out, const FairMCResult& result)
    {
        out << "MC Link from: " << result.GetStartType() << " to " << result.GetStopType() << ":" << std::endl;
        (static_cast<FairMCObject>(result)).PrintInfo(out);
        return out;
    }

  private:
    Int_t fStartType;
    Int_t fStopType;

    ClassDef(FairMCResult, 2);
};

#endif /* FairMCResult_H_ */
