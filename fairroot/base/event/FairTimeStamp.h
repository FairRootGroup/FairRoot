/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTIMESTAMP_H
#define FAIRTIMESTAMP_H

#include "FairMultiLinkedData_Interface.h"   // for FairMultiLinkedData

#include <Rtypes.h>   // for Double_t, etc
#include <iosfwd>     // for ostream
#include <iostream>   // for ostream, cout

/**
 * Base class for Time stamp information
 ** Aug. 2010
 **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairTimeStamp : public FairMultiLinkedData_Interface
{
  public:
    /** Default constructor **/
    FairTimeStamp() = default;

    /** Constructor with time **/
    FairTimeStamp(Double_t time)
        : fTimeStamp(time)
    {}
    /** Constructor with time and time error **/
    FairTimeStamp(Double_t time, Double_t timeerror)
        : fTimeStamp(time)
        , fTimeStampError(timeerror)
    {}

    /** Destructor **/
    ~FairTimeStamp() override = default;
    /** Accessors **/
    Double_t GetTimeStamp() const { return fTimeStamp; }
    Double_t GetTimeStampError() const { return fTimeStampError; }
    /** Modifiers **/
    void SetTimeStamp(Double_t t) { fTimeStamp = t; }
    void SetTimeStampError(Double_t t) { fTimeStampError = t; }
    Int_t Compare(const TObject* obj) const override
    {
        if (this == obj) {
            return 0;
        }
        auto tsobj = static_cast<FairTimeStamp const*>(obj);
        Double_t ts = tsobj->GetTimeStamp();
        Double_t tserror = tsobj->GetTimeStampError();
        if ((fTimeStamp < ts) || (fTimeStamp == ts && fTimeStampError < tserror)) {
            return -1;
        } else if (fTimeStamp == ts && fTimeStampError == tserror) {
            return 0;
        } else {
            return 1;
        }
    }

    virtual std::ostream& PrintTimeInfo(std::ostream& out = std::cout) const;
    Bool_t IsSortable() const override { return kTRUE; };

    virtual bool equal(FairTimeStamp* data)
    {
        return (fTimeStamp == data->GetTimeStamp() && fTimeStampError == data->GetTimeStampError());
    }

    friend std::ostream& operator<<(std::ostream& out, const FairTimeStamp& link)
    {
        link.PrintTimeInfo(out);
        return out;
    }

    bool operator<(const FairTimeStamp& rValue) const { return fTimeStamp < rValue.fTimeStamp; }

  protected:
    Double_t fTimeStamp{-1};        //< Time of digit or Hit  [ns]
    Double_t fTimeStampError{-1};   //< Error on time stamp

    ClassDefOverride(FairTimeStamp, 4);
};

#endif   // FAIRTIMESTAMP_H
