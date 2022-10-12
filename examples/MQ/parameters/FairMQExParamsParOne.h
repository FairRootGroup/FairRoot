/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXPARAMSPARONE_H_
#define FAIRMQEXPARAMSPARONE_H_

#include <Rtypes.h>             // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>         // for Int_t, Bool_t
#include "FairParGenericSet.h"  // for FairParGenericSet
class FairParamList;  // lines 15-15
class TBuffer;
class TClass;
class TMemberInspector;


class FairMQExParamsParOne : public FairParGenericSet
{
  public:
    /** Standard constructor **/
    FairMQExParamsParOne(const char* name = "FairMQExParamsParOne",
                         const char* title = "FairMQ Example Parameters Parameter One",
                         const char* context = "Default");

    /** Destructor **/
    ~FairMQExParamsParOne() override;

    void print() override;

    /** Reset all parameters **/
    void clear() override;

    void putParams(FairParamList* list) override;
    Bool_t getParams(FairParamList* list) override;

    inline void SetValue(const Int_t& val) { fParameterValue = val; }

  private:
    Int_t fParameterValue;   //

    FairMQExParamsParOne(const FairMQExParamsParOne&);
    FairMQExParamsParOne& operator=(const FairMQExParamsParOne&);

    ClassDefOverride(FairMQExParamsParOne, 1);
};

#endif   // FAIRMQEXPARAMSPARONE_H_
