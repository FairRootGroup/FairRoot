/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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

#include "PixelDigiPar.h"

#include "FairParamList.h"   // for FairParamList

#include <iostream>

PixelDigiPar::PixelDigiPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fFeCols(0)
    , fFeRows(0)
    , fMaxFEperCol(0)
    , fDimX(0.)
    , fDimY(0.)
    , fRadius(0.)
    , fThreshold(0.)
    , fNoise(0.)
    , fCSigma(0.)
    , fFeBusClock(0.)
    , fChargeConvMethod(0)
    , fPixelSorterCellWidth(0.)
    , fPixelSorterNumberOfCells(0)
{
    clear();
}

// -----   Destructor   ----------------------------------------------------
PixelDigiPar::~PixelDigiPar(void) {}

void PixelDigiPar::putParams(FairParamList* list)
{
    if (!list)
        return;
    list->add("dimX", fDimX);
    list->add("dimY", fDimY);

    list->add("threshold", fThreshold);
    list->add("noise", fNoise);
    list->add("FECols", fFeCols);
    list->add("FERows", fFeRows);
    list->add("MaxFEperCol", fMaxFEperCol);
    list->add("ClustRad", fRadius);
    list->add("QCloudSigma", fCSigma);
    list->add("fe_BusClock", fFeBusClock);

    list->add("chargeconv_method", fChargeConvMethod);

    list->add("PixelSorterCellWidth", fPixelSorterCellWidth);
    list->add("PixelSorterNumberOfCells", fPixelSorterNumberOfCells);
}

Bool_t PixelDigiPar::getParams(FairParamList* list)
{
    if (!list)
        return kFALSE;
    if (!list->fill("dimX", &fDimX))
        return kFALSE;
    if (!list->fill("dimY", &fDimY))
        return kFALSE;
    if (!list->fill("threshold", &fThreshold))
        return kFALSE;
    if (!list->fill("noise", &fNoise))
        return kFALSE;
    if (!list->fill("FECols", &fFeCols))
        return kFALSE;
    if (!list->fill("FERows", &fFeRows))
        return kFALSE;
    if (!list->fill("MaxFEperCol", &fMaxFEperCol))
        return kFALSE;
    if (!list->fill("ClustRad", &fRadius))
        return kFALSE;
    if (!list->fill("QCloudSigma", &fCSigma))
        return kFALSE;
    if (!list->fill("fe_BusClock", &fFeBusClock))
        return kFALSE;
    if (!list->fill("chargeconv_method", &fChargeConvMethod))
        return kFALSE;
    if (!list->fill("PixelSorterCellWidth", &fPixelSorterCellWidth))
        return kFALSE;
    if (!list->fill("PixelSorterNumberOfCells", &fPixelSorterNumberOfCells))
        return kFALSE;
    return kTRUE;
}

void PixelDigiPar::Print(Option_t*) const
{
    std::cout << "SDS Pixel Digitization Parameters:" << std::endl;
    std::cout << "   fDimX (cm)   = " << fDimX << std::endl;
    std::cout << "   fDimY (cm)   = " << fDimY << std::endl;
    std::cout << "   Charge Threshold (e-)        = " << fThreshold << std::endl;
    std::cout << "   Noise (ENC+Dispersion) (e-)  = " << fNoise << std::endl;
    std::cout << "   Columns on FE                = " << fFeCols << std::endl;
    std::cout << "   Rows on FE                   = " << fFeRows << std::endl;
    std::cout << "   Maximum number of FE per column = " << fMaxFEperCol << std::endl;
    std::cout << "   Cluster search radius (channels) = " << fRadius << std::endl;
    std::cout << "   Charge cloud sigma (cm) = " << fCSigma << std::endl;
    std::cout << "   charge conv. (0:ideal, 1:TOT)    = " << fChargeConvMethod << std::endl;
}
