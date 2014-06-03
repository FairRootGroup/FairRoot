/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef VALINTERVAL_H
#define VALINTERVAL_H

#include "TObject.h"                    // for TObject

#include "ValTimeStamp.h"               // for ValTimeStamp

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Bool_t, Option_t, etc
#include "TString.h"                    // for TString

#include <iostream>                     // for ostream

class ValCondition;

class ValInterval : public TObject
{

  public:

    ValInterval();
    ValInterval(const Int_t detMask, const Int_t simMask,
                const ValTimeStamp& tstart, const ValTimeStamp& tend,
                const TString& source);
    virtual ~ValInterval();

    const char* AsString(Option_t* option = "") const;
    Bool_t IsCompatible(const ValCondition& vldc) const;
    Bool_t IsCompatible(const ValCondition* vldc) const;

    Int_t  GetDetectorMask()    const { return fDetectorMask; }
    Int_t  GetSimMask()         const { return fSimMask; }
    ValTimeStamp GetTimeStart() const { return fTimeStart; }
    ValTimeStamp GetTimeEnd()   const { return fTimeEnd; }
    TString GetDataSource()     const { return fDataSource; }
    Int_t  GetDetectorId()    const { return fDetectorMask; }
    Int_t  GetDataId()       const { return fSimMask; }

    void Print(Option_t* option = "") const;

    void TrimTo(const ValInterval& vldr);
    void SetTimeStart(const ValTimeStamp& tstart) { fTimeStart = tstart; }
    void SetTimeEnd(const ValTimeStamp& tend) { fTimeEnd = tend; }

  protected:

    Int_t              fDetectorMask; //  Detector::Detector_t (or compacted)
    Int_t              fSimMask;      // data/mc conditions (or compacted)
    ValTimeStamp       fTimeStart;
    ValTimeStamp       fTimeEnd;
    TString            fDataSource;

  private:

    ClassDef(ValInterval,1)  // IOV Interval of Validity
};

std::ostream& operator<<(std::ostream& os, const ValInterval& vldr);

#endif // VALINTERVAL_H
