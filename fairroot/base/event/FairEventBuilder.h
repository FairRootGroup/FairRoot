/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//* $Id: */

// -------------------------------------------------------------------------
// -----                     FairEventBuilder header file                -----
// -----                  Created 23/09/2013 by R. Karabowicz          -----
// -------------------------------------------------------------------------

/** FairEventBuilder
 *@author Radoslaw Karabowicz <r.karabowicz@gsi.de>
 *@since 23/09/2013
 *@version 1.0
 **
 ** FairRoot base task for the event buffers.
 ** The tasks may:
 ** 1. analyze data to reconstruct event times or other characteristics
 **    in the function TClonesArray* FindEvents(), that returns
 **    TClonesArray of FairRecoEvents
 ** 2. identify the data that could belong to event in the
 **    function and insert this identified data to the output TClonesArrays
 **    in the function StoreEventData(event)
 ** The implementations may be using any or both of the above functions.
 **/

#ifndef FAIREVENTBUILDER_H
#define FAIREVENTBUILDER_H 1

#include "FairRecoEventHeader.h"
#include "FairWriteoutBuffer.h"

#include <Rtypes.h>
#include <TStopwatch.h>
#include <TString.h>
#include <utility>   // pair
#include <vector>

class TClonesArray;
// class FairRecoEventHeader;

class FairEventBuilder : public FairWriteoutBuffer
{
  public:
    /** Default constructor **/
    FairEventBuilder();

    /** Constructor with task name **/
    FairEventBuilder(TString branchName, TString className, TString folderName, Bool_t persistance);

    /** Destructor **/
    ~FairEventBuilder() override;

    virtual void WriteOutAllDeadTimeData();

    virtual std::vector<std::pair<double, FairRecoEventHeader*>> FindEvents() = 0;
    virtual void StoreEventData(FairRecoEventHeader* /*recoEvent*/) = 0;

    void SetIdentifier(Int_t ident) { fIdentifier = ident; }
    Int_t GetIdentifier() { return fIdentifier; }

    virtual Bool_t Init() = 0;

    void Print(Option_t* option = "") const override = 0;

    /** Finish at the end of each event **/
    virtual void Finish();

    Double_t AllowedTime() { return fMaxAllowedEventCreationTime; };
    void SetMaxAllowedTime(Double_t td) { fMaxAllowedEventCreationTime = td; };

    void SetBuilderName(const char* name) { fBuilderName = name; }
    TString GetBuilderName() { return fBuilderName; }

  private:
    TString fBuilderName;

    TStopwatch fTimer;
    Double_t fExecTime;

    Int_t fIdentifier;
    Double_t fMaxAllowedEventCreationTime;

    ClassDefOverride(FairEventBuilder, 1);
};

#endif
