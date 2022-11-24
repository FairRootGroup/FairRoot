/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4MILLEWRITER_H
#define FAIRTUTORIALDET4MILLEWRITER_H

#include "FairTask.h"   // for InitStatus, FairTask

#include <Rtypes.h>   // for Option_t, Bool_t, etc
#include <TString.h>

class Mille;
class TClonesArray;

class FairTutorialDet4MilleWriter : public FairTask
{
  public:
    /** Default constructor **/
    FairTutorialDet4MilleWriter();

    /** Constructor with parameters (Optional) **/
    //  FairTutorialDet4MilleWriter(Int_t verbose);

    /** Destructor **/
    ~FairTutorialDet4MilleWriter();

    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();

    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Finish task called at the end of the run **/
    virtual void Finish();

    void SetWriteAscii(Bool_t val) { fWriteAscii = val; }

    void SetVersion(Int_t val) { fVersion = val; }

    void SetFileName(TString val) { fFileName = val; }

  private:
    void ExecVersion1(Option_t* opt);
    void StraightLineShiftX();
    void StraightLineShiftXY();

    Bool_t IsGoodEvent();

    /** Input array from previous already existing data level **/
    TClonesArray* fTracks;

    /** Input array from previous already existing data level **/
    TClonesArray* fHits;

    Mille* fMille;

    Bool_t fWriteAscii;

    Int_t fVersion;

    TString fFileName;

    /** Output array to  new data level**/
    //  TClonesArray* <OutputDataLevel>;

    FairTutorialDet4MilleWriter(const FairTutorialDet4MilleWriter&);
    FairTutorialDet4MilleWriter operator=(const FairTutorialDet4MilleWriter&);

    ClassDef(FairTutorialDet4MilleWriter, 1);
};

#endif
