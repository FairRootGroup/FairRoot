/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairTutPropTr.h
 *
 * @since 2019-09-10
 * @author R. Karabowicz
 */

#ifndef FAIRTUTGEANETR_H
#define FAIRTUTGEANETR_H 1

#include "FairPropagator.h"
#include "FairTask.h"

class TClonesArray;
class FairTutPropPoint;

class FairTutPropTr : public FairTask
{
  public:
    /** Default constructor **/
    FairTutPropTr();

    /** Destructor **/
    ~FairTutPropTr();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    void SetPropagator(FairPropagator* prop) { fPro = prop; }

  private:
    void Reset();

    /** Finish at the end of run **/
    virtual void Finish();

    void InitPropagator();
    bool fPropagatorSet;

    /** Input array of Points **/
    TClonesArray* fPointArray;

    /** Output array of Hits **/
    TClonesArray* fTrackParIni;     // initial MC track parameters
    TClonesArray* fTrackParFinal;   // final MC track parameters
    TClonesArray* fTrackParProp;    // calculated track parameters
    TClonesArray* fTrackParWrong;   // demonstrate effect of wrong charge

    FairPropagator* fPro;

    ClassDef(FairTutPropTr, 1);
};

#endif   // FAIRTUTGEANETR_H
