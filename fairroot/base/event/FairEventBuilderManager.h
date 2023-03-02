/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//* $Id: */

// -------------------------------------------------------------------------
// -----                     FairEventBuilderManager header file              -----
// -----                  Created 20/09/2013 by R. Karabowicz          -----
// -------------------------------------------------------------------------

/** FairEventBuilderManager
 *@author Radoslaw Karabowicz <r.karabowicz@gsi.de>
 *@since 20/09/2013
 *@version 1.0
 **
 ** FairRoot general task for recreating events in Time-Based reconstruction mode.
 ** Various experiments should implement their own version of Event Builder.
 ** The main member of the task is vector of reconstructed events fRecoEvents.
 ** It also contains a vector of implementations of FairEventBuilders, that are
 ** responsible for feeding fRecoEvents vector via FindEvents() function.
 **
 ** The heart of the experiment-specific implemenations is
 ** the AnalyzeAndExtractEvents() function, which should interpret
 ** the experimental data to reconstruct events.
 **/

#ifndef FAIREVENTBUILDERMANAGER_H
#define FAIREVENTBUILDERMANAGER_H 1

#include "FairEventBuilder.h"
#include "FairTask.h"

#include <Rtypes.h>   // ClassDef
#include <vector>

class TClonesArray;

class FairEventBuilderManager : public FairTask
{
  public:
    /** Default constructor **/
    FairEventBuilderManager();

    /** Constructor with task name **/
    FairEventBuilderManager(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    ~FairEventBuilderManager() override;

    /** Execution **/
    void Exec(Option_t* opt) override;

    /** Adding FairEventBuilder **/
    virtual void AddEventBuilder(FairEventBuilder* eventBuilder);

  protected:
    std::vector<FairEventBuilder*> fEventBuilders;
    std::vector<std::vector<std::pair<double, FairRecoEventHeader*>>> fPossibleEvents;

    /** Fill events from various builders **/
    virtual Double_t FillEventVectors();

    /** Analyze and extract events - experiment specific **/
    virtual void AnalyzeAndExtractEvents(Double_t maxEventTimeAllowed) = 0;

    /** Create output tree structure **/
    virtual void CreateAndFillEvent(FairRecoEventHeader* recoEvent);

  private:
    /** Intialisation **/
    InitStatus Init() override;

    /** Reinitialisation **/
    InitStatus ReInit() override;

    /** Finish at the end of each event **/
    void Finish() override;

    ClassDefOverride(FairEventBuilderManager, 1);
};

#endif
