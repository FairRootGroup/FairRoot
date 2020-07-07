/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTTUTPROPTRACKFINDER_H_
#define FAIRTTUTPROPTRACKFINDER_H_

#include "FairTask.h"   // for InitStatus, FairTask

#include <Rtypes.h>   // for ClassDef

class TClonesArray;

class FairTutPropTrackFinder : public FairTask
{
  public:
    /** Default constructor **/
    FairTutPropTrackFinder();

    /** Destructor **/
    ~FairTutPropTrackFinder();

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

  private:
    std::string fHitsArray1Name;
    std::string fHitsArray2Name;

    /** Input array of hits1 **/
    TClonesArray* fHitsArray1;
    /** Input array of hits2 **/
    TClonesArray* fHitsArray2;

    /** Output array to  new data level**/
    TClonesArray* fTracksArray;

    bool FindCircPar(double* p1, double* p2, double* p3, double* cl);

    FairTutPropTrackFinder(const FairTutPropTrackFinder&);
    FairTutPropTrackFinder operator=(const FairTutPropTrackFinder&);

    ClassDef(FairTutPropTrackFinder, 1);
};

#endif /* FAIRTTUTPROPTRACKFINDER_H_ */
