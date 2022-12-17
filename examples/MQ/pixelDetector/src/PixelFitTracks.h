/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelFitTracks.h
 *
 *  Created on: 25.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELFITTRACKS_H
#define PIXELFITTRACKS_H 1

#include "FairTask.h"

#include <Rtypes.h>

class TClonesArray;
class PixelDigiPar;
class TList;

class PixelFitTracks : public FairTask
{
  public:
    /** Default constructor **/
    PixelFitTracks();

    /** Standard constructor **/
    PixelFitTracks(Int_t iVerbose);

    /** Constructor with name **/
    PixelFitTracks(const char* name, Int_t iVerbose);

    /** Destructor **/
    ~PixelFitTracks() override;

    /** Execution **/
    void Exec(Option_t* opt) override;

    virtual void GetParList(TList* tempList);
    virtual void InitMQ(TList* tempList);
    virtual void ExecMQ(TList* inputList, TList* outputList);

  private:
    PixelDigiPar* fDigiPar;

    TClonesArray* fHits;      /** Input array of PixelHit **/
    TClonesArray* fTracks;    /** Input array of PixelTrack **/
    TClonesArray* fFitTracks; /** Output array of PixelTrack **/

    Int_t fTNofEvents;

    Int_t fNHits;

    Int_t fNTracks;
    Int_t fTNofTracks;

    Int_t fNFitTracks;
    Int_t fTNofFitTracks;

    Double_t LinearRegression(Int_t nval,
                              Double_t xval[],
                              Double_t yval[],
                              Double_t& valA0,
                              Double_t& errA0,
                              Double_t& valA1,
                              Double_t& errA1);

    /** Get parameter containers **/
    void SetParContainers() override;

    /** Intialisation **/
    InitStatus Init() override;

    /** Reinitialisation **/
    InitStatus ReInit() override;

    /** Reset eventwise counters **/
    void Reset();

    /** Finish at the end of each event **/
    void Finish() override;

    PixelFitTracks(const PixelFitTracks&);
    PixelFitTracks& operator=(const PixelFitTracks&);

    ClassDefOverride(PixelFitTracks, 1);
};

#endif
