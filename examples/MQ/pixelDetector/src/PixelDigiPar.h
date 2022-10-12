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
 *  Created on: 17.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELDIGIPAR_H
#define PIXELDIGIPAR_H

#include "FairParGenericSet.h"   // for FairParGenericSet

#include <Rtypes.h>   // for PixelDigiPar::Class, ClassDef, PixelD...
class FairParamList;

//! Digitization Parameter Class for Pixel detector
class PixelDigiPar : public FairParGenericSet
{
  public:
    PixelDigiPar(const char* name = "PixelDigiParameters",
                 const char* title = "Pixel digi parameters",
                 const char* context = "TestDefaultContext");
    ~PixelDigiPar() override;
    void clear() override {}
    void putParams(FairParamList* list) override;
    Bool_t getParams(FairParamList* list) override;

    void Print(Option_t*) const override;

    Double_t GetXPitch() const { return fDimX; }
    Double_t GetYPitch() const { return fDimY; }
    Double_t GetThreshold() const { return fThreshold; }
    Double_t GetNoise() const { return fNoise; }
    Double_t GetQCloudSigma() const { return fCSigma; }
    Int_t GetFECols() const { return fFeCols; }
    Int_t GetFERows() const { return fFeRows; }
    Int_t GetMaxFEperCol() const { return fMaxFEperCol; }
    Double_t GetClustRadius() const { return fRadius; }
    Double_t GetFeBusClock() const { return fFeBusClock; }
    Double_t GetTimeStep() const { return (1. / fFeBusClock * 1000.); }   ///< Time step of one clock cycle in ns
    Int_t GetChargeConvMethod() const { return fChargeConvMethod; }
    Double_t GetPixelSorterCellWidth() const { return fPixelSorterCellWidth; }
    Int_t GetPixelSorterNumberOfCells() const { return fPixelSorterNumberOfCells; }

    void SetXPitch(Double_t x) { fDimX = x; }
    void SetYPitch(Double_t x) { fDimY = x; }
    void SetThreshold(Double_t x) { fThreshold = x; }
    void SetNoise(Double_t x) { fNoise = x; }
    void SetQCloudSigma(Double_t x) { fCSigma = x; }
    void SetFECols(Int_t x) { fFeCols = x; }
    void SetFERows(Int_t x) { fFeRows = x; }
    void SetMaxFEperCol(Int_t x) { fMaxFEperCol = x; }
    void SetClustRadius(Double_t x) { fRadius = x; }
    void SetFeBusClock(Double_t x) { fFeBusClock = x; }
    void SetChargeConvMethod(Int_t x) { fChargeConvMethod = x; }
    void SetPixelSorterCellWidth(Double_t x) { fPixelSorterCellWidth = x; }
    void SetPixelSorterNumberOfCells(Int_t x) { fPixelSorterNumberOfCells = x; }

  private:
    // Pixel Parameters
    Int_t fFeCols;                     // Colums read per Frontend
    Int_t fFeRows;                     // Rows read per Frontend
    Int_t fMaxFEperCol;                // max number of Frontend elemens per column
    Double_t fDimX;                    // Pixel cell size X
    Double_t fDimY;                    // Pixel cell size Y
    Double_t fRadius;                  // Clusterfinder search radius (channel numbers)
    Double_t fThreshold;               // Discriminator Threshold (electrons)
    Double_t fNoise;                   // Gaussian electronics noise including threshold dispersion (electrons)
    Double_t fCSigma;                  // Gaussian charge cloud smearing
    Double_t fFeBusClock;              // Frontend bus clock to determin noise rate
    Int_t fChargeConvMethod;           // 0: ideal conversion; 1: TOT calculation
    Double_t fPixelSorterCellWidth;    // Parameter for TimeStamp Sorter
    Int_t fPixelSorterNumberOfCells;   // Parameter for TimeStamp Sorter

    ClassDefOverride(PixelDigiPar, 1);
};

#endif /*!PIXELDIGIPAR_H*/
