/********************************************************************************
 * Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   RooDataGenerator.h
 * Author: winckler
 *
 * Created on December 11, 2014, 1:16 PM
 */

#ifndef ROODATAGENERATOR_H
#define ROODATAGENERATOR_H

// root
#include <TDatime.h>

// roofit
#include "RooArgSet.h"
#include "RooConstVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooGlobalFunc.h"
#include "RooProdPdf.h"
#include "RooRandom.h"
#include "RooRealVar.h"

struct RdmVarParameters
{
    RdmVarParameters(double min, double max, double mean, double sigma)
        : fMin(min)
        , fMax(max)
        , fMean(mean)
        , fSigma(sigma)
    {}

    RdmVarParameters(double mean, double sigma)
        : fMin(mean - 6 * sigma)
        , fMax(mean + 6 * sigma)
        , fMean(mean)
        , fSigma(sigma)
    {}

    double fMin;
    double fMax;
    double fMean;
    double fSigma;
};

struct PDFConfig
{
    PDFConfig()
        : fX(-10, 3)
        , fY(10, 2)
        , fZ(0, 0.5)
        , fTErr(0.005, 0.001)
    {}

    void Set(const RdmVarParameters& x,
             const RdmVarParameters& y,
             const RdmVarParameters& z,
             const RdmVarParameters& terr)
    {
        fX = x;
        fY = y;
        fZ = z;
        fTErr = terr;
    }

    RdmVarParameters fX;
    RdmVarParameters fY;
    RdmVarParameters fZ;
    RdmVarParameters fTErr;
};

class MultiVariatePDF
{
  public:
    MultiVariatePDF(unsigned int tStart = 0)
        : MultiVariatePDF(PDFConfig(), tStart)
    {}

    MultiVariatePDF(const PDFConfig& opt, unsigned int tStart = 0)
        : fOpt(opt)
        , fX("x", "x", fOpt.fX.fMin, fOpt.fX.fMax)
        , fY("y", "y", fOpt.fY.fMin, fOpt.fY.fMax)
        , fZ("z", "z", fOpt.fZ.fMin, fOpt.fZ.fMax)
        , fT("t", "t", static_cast<double>(tStart), static_cast<double>(tStart + 1))
        , fTErr("tErr", "tErr", fOpt.fTErr.fMin, fOpt.fTErr.fMax)
        , fMeanT("mu_t", "mean of t-distribution", (static_cast<double>(tStart) + static_cast<double>(tStart + 1)) / 2)
        , fSigmaT("fSigmaT", "width of t-distribution", 0.1)
        , fGaussX("fGaussX", "gaussian PDF", fX, RooFit::RooConst(fOpt.fX.fMean), RooFit::RooConst(fOpt.fX.fSigma))
        , fGaussY("fGaussY", "gaussian PDF", fY, RooFit::RooConst(fOpt.fY.fMean), RooFit::RooConst(fOpt.fY.fSigma))
        , fGaussZ("fGaussZ", "gaussian PDF", fZ, RooFit::RooConst(fOpt.fZ.fMean), RooFit::RooConst(fOpt.fZ.fSigma))
        , fGaussT("fGaussT", "gaussian PDF", fT, fMeanT, fSigmaT)
        , fGaussTErr("fGaussTErr",
                     "gaussian PDF",
                     fTErr,
                     RooFit::RooConst((fTErr.getMin() + fTErr.getMax()) / 2),
                     RooFit::RooConst(fOpt.fTErr.fSigma))
        , fModel("fGaussXyzt_ter",
                 "fGaussX*fGaussY*fGaussZ*fGaussT*fGaussTErr",
                 RooArgList(fGaussX, fGaussY, fGaussZ, fGaussT, fGaussTErr))
    {
        RooMsgService::instance().setGlobalKillBelow(RooFit::MsgLevel::ERROR);
        RooRandom::randomGenerator()->SetSeed(TDatime().GetTime());
    }

    MultiVariatePDF(const MultiVariatePDF&) = delete;
    MultiVariatePDF operator=(const MultiVariatePDF&) = delete;

    ~MultiVariatePDF() {}

    RooDataSet* GetGeneratedData(unsigned int n, unsigned int ti)
    {
        fT.setRange(static_cast<double>(ti), static_cast<double>(ti + 1));
        fMeanT.setVal(static_cast<double>(ti + 0.5));
        return fModel.generate(RooArgSet(fX, fY, fZ, fT, fTErr), n);
    }

  private:
    PDFConfig fOpt;

    RooRealVar fX;
    RooRealVar fY;
    RooRealVar fZ;
    RooRealVar fT;
    RooRealVar fTErr;

    RooRealVar fMeanT;
    RooRealVar fSigmaT;

    RooGaussian fGaussX;
    RooGaussian fGaussY;
    RooGaussian fGaussZ;
    RooGaussian fGaussT;
    RooGaussian fGaussTErr;

    RooProdPdf fModel;
};

#endif /* ROODATAGENERATOR_H */
