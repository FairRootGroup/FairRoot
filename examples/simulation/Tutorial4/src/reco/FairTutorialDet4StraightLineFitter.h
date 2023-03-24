/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4STRAIGHTLINEFITTER_H
#define FAIRTUTORIALDET4STRAIGHTLINEFITTER_H

#include "FairTask.h"   // for InitStatus, FairTask

#include <Rtypes.h>   // for ClassDef
#include <TClonesArray.h>

class FairTutorialDet4StraightLineFitter : public FairTask
{
  public:
    /** Default constructor **/
    FairTutorialDet4StraightLineFitter();

    /** Constructor with parameters (Optional) **/
    //  FairTutorialDet4StraightLineFitter(Int_t verbose);

    /** Destructor **/
    ~FairTutorialDet4StraightLineFitter() override = default;

    /** Initiliazation of task at the beginning of a run **/
    InitStatus Init() override;

    /** Executed for each event. **/
    void Exec(Option_t* opt) override;

    void SetVersion(Int_t val) { fVersion = val; }

  private:
    /** Input array from previous already existing data level **/
    TClonesArray const* fHits{nullptr};

    /** Output array to  new data level**/
    TClonesArray fTracks;

    Int_t fVersion;

    Bool_t IsGoodEvent();

    FairTutorialDet4StraightLineFitter(const FairTutorialDet4StraightLineFitter&);
    FairTutorialDet4StraightLineFitter operator=(const FairTutorialDet4StraightLineFitter&);

    ClassDefOverride(FairTutorialDet4StraightLineFitter, 1);
};

#endif
