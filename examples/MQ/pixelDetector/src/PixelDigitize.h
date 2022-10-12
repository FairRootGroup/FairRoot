/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelHit.h
 *
 *  Created on: 16.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELDIGITIZE_H
#define PIXELDIGITIZE_H 1

#include "FairTask.h"

class TClonesArray;
class PixelDigiPar;

class PixelDigitize : public FairTask
{
  public:
    /** Default constructor **/
    PixelDigitize();

    /** Standard constructor **/
    PixelDigitize(Int_t iVerbose);

    /** Constructor with name **/
    PixelDigitize(const char* name, Int_t iVerbose);

    /** Destructor **/
    ~PixelDigitize() override;

    /** Execution **/
    void Exec(Option_t* opt) override;

    virtual void GetParList(TList* tempList);
    virtual void InitMQ(TList* tempList);
    virtual void ExecMQ(TList* inputList, TList* outputList);

  private:
    PixelDigiPar* fDigiPar;

    TClonesArray* fPoints; /** Input array of PixelPoint **/
    TClonesArray* fDigis;  /** Output array of PixelDigi **/

    Int_t fNPoints;
    Int_t fNDigis;

    Int_t fTNofEvents;
    Int_t fTNofPoints;
    Int_t fTNofDigis;

    Int_t fFeCols;        // Colums read per Frontend
    Int_t fFeRows;        // Rows read per Frontend
    Int_t fMaxFEperCol;   // max number of Frontend elemens per column
    Double_t fPitchX;     // Pixel cell size X
    Double_t fPitchY;     // Pixel cell size Y

    /** Activate pixel **/
    void ActivatePixel(Int_t index, Int_t detId, Int_t feId, Int_t col, Int_t row, Double_t charge, Double_t timestamp);

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

    PixelDigitize(const PixelDigitize&);
    PixelDigitize& operator=(const PixelDigitize&);

    ClassDefOverride(PixelDigitize, 1);
};

#endif
