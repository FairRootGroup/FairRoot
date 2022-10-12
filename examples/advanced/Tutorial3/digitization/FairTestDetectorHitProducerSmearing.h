/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORHITPRODUCERSMEARING_H_
#define FAIRTESTDETECTORHITPRODUCERSMEARING_H_

#include "FairTask.h"   // for InitStatus, FairTask

#include <Rtypes.h>   // for ClassDef

class TClonesArray;

class FairTestDetectorHitProducerSmearing : public FairTask
{
  public:
    /** Default constructor **/
    FairTestDetectorHitProducerSmearing();

    /** Destructor **/
    ~FairTestDetectorHitProducerSmearing() override;

    /** Initiliazation of task at the beginning of a run **/
    InitStatus Init() override;

    /** ReInitiliazation of task when the runID changes **/
    InitStatus ReInit() override;

    /** Executed for each event. **/
    void Exec(Option_t* opt) override;

    /** Load the parameter container from the runtime database **/
    void SetParContainers() override;

    /** Finish task called at the end of the run **/
    void Finish() override;

  private:
    /** Input array from previous already existing data level **/
    TClonesArray* fPointsArray;

    /** Output array to  new data level**/
    TClonesArray* fHitsArray;

    FairTestDetectorHitProducerSmearing(const FairTestDetectorHitProducerSmearing&);
    FairTestDetectorHitProducerSmearing operator=(const FairTestDetectorHitProducerSmearing&);

    ClassDefOverride(FairTestDetectorHitProducerSmearing, 1);
};

#endif /* FAIRTESTDETECTORHITPRODUCERSMEARING_H_ */
