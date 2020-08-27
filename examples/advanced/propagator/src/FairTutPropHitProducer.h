/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTTUTPROPHITPRODUCER_H_
#define FAIRTTUTPROPHITPRODUCER_H_

#include "FairTask.h"   // for InitStatus, FairTask

#include <Rtypes.h>   // for ClassDef

class TClonesArray;

class FairTutPropHitProducer : public FairTask
{
  public:
    /** Default constructor **/
    FairTutPropHitProducer();

    /** Destructor **/
    ~FairTutPropHitProducer();

    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();

    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

    void SetPointsArrayName(const std::string& tempName) { fPointsArrayName = tempName; };
    void SetHitsArrayName(const std::string& tempName) { fHitsArrayName = tempName; };

  private:
    std::string fPointsArrayName;
    std::string fHitsArrayName;

    /** Input array from previous already existing data level **/
    TClonesArray* fPointsArray;
    TClonesArray* fTracksArray;

    /** Output array to  new data level**/
    TClonesArray* fHitsArray;

    FairTutPropHitProducer(const FairTutPropHitProducer&);
    FairTutPropHitProducer operator=(const FairTutPropHitProducer&);

    ClassDef(FairTutPropHitProducer, 1);
};

#endif /* FAIRTTUTPROPHITPRODUCER_H_ */
