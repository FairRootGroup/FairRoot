/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----             FairEvtGenGenerator source file                      -----
// -----          Created 09/10/06  by S. Spataro                      -----
// -------------------------------------------------------------------------
#include "FairEvtGenGenerator.h"

#include "FairPrimaryGenerator.h"   // for FairPrimaryGenerator

#include <TF1.h>       // for TF1
#include <TRandom.h>   // for TRandom, gRandom
#include <algorithm>   // max
#include <fairlogger/Logger.h>

FairEvtGenGenerator::FairEvtGenGenerator()
    : FairGenerator()
    , fFileName("")
    , fInputFile(nullptr)
    , fGasmode(0)
    , fRsigma(0.)
    , fDensityFunction(nullptr)
{}

FairEvtGenGenerator::FairEvtGenGenerator(const char* fileName)
    : FairGenerator("EvtGen", fileName)
    , fFileName(fileName)
    , fInputFile(nullptr)
    , fGasmode(0)
    , fRsigma(0.)
    , fDensityFunction(0)
{
    LOG(info) << "FairEvtGenGenerator: Opening input file " << fileName;
    fInputFile = fopen(fFileName, "r");
    if (!fInputFile)
    //  fInputFile = new ifstream(fFileName);
    //  if ( ! fInputFile->is_open() )
    {
        Fatal("FairEvtGenGenerator", "Cannot open input file.");
    }

    // fPDG=TDatabasePDG::Instance();
}

FairEvtGenGenerator::FairEvtGenGenerator(const char* fileName, Double_t Rsigma, TF1* DensityFunction)
    : FairGenerator("EvtGen", fileName)
    , fFileName(fileName)
    , fInputFile(nullptr)
    , fGasmode(1)
    , fRsigma(Rsigma)
    , fDensityFunction(DensityFunction)
{
    LOG(info) << "FairEvtGenGenerator: Opening input file " << fileName;
    fInputFile = fopen(fFileName, "r");
    if (!fInputFile) {
        LOG(fatal) << "Cannot open input file.";
    }
}

FairEvtGenGenerator::~FairEvtGenGenerator()
{
    delete fDensityFunction;
    if (fInputFile) {
        fclose(fInputFile);
    }
}

Bool_t FairEvtGenGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{
    // Check for input file
    if (!fInputFile) {
        // if ( ! fInputFile->is_open() ) {
        LOG(info) << "FairEvtGenGenerator: Input file not open!";
        return kFALSE;
    }

    // Define event variable to be read from file
    Int_t ntracks = 0, eventID = 0, ncols = 0;

    // Define track variables to be read from file
    Int_t nLine = 0, pdgID = 0, nDecay = 0, nM1 = -1, nM2 = -1, nDF = -1, nDL = -1;
    Float_t fPx = 0., fPy = 0., fPz = 0., fE = 0.;
    Float_t fVx = 0., fVy = 0., fVz = 0., fT = 0.;

    // Read event header line from input file

    Int_t max_nr = 0;

    Text_t buffer[200];
    ncols = fscanf(fInputFile, "%d\t%d", &eventID, &ntracks);

    if (ncols && ntracks > 0) {

        // LOG(info) << "Event number: " << eventID << "\tNtracks: " << ntracks;
        // std::stringstream ss;
        for (Int_t ii = 0; ii < 15; ii++) {
            ncols += fscanf(fInputFile, "%s", buffer);
            //   ss << buffer << "\t" ;
        }
        // LOG(info) << ss.str();

        for (Int_t ll = 0; ll < ntracks; ll++) {
            ncols += fscanf(fInputFile,
                            "%d %d %d %d %d %d %d %g %f %f %f %f %f %f %f",
                            &nLine,
                            &pdgID,
                            &nDecay,
                            &nM1,
                            &nM2,
                            &nDF,
                            &nDL,
                            &fPx,
                            &fPy,
                            &fPz,
                            &fE,
                            &fT,
                            &fVx,
                            &fVy,
                            &fVz);
            //  LOG(info) << nLine << "\t" << pdgID << "\t" << nDecay << "\t" << nM1 << "\t" << nM2 << "\t" << nDF <<
            //  "\t" << nDL <<
            //  "\t" << fPx << "\t" << fPy << "\t" << fPz << "\t" << fE << "\t" << fT << "\t" << fVx << "\t" << fVy <<
            //  "\t" << fVz;
            max_nr = std::max(max_nr, nDF);
            max_nr = std::max(max_nr, nDL);
            if ((nDF == -1) && (nDL == -1)) {

                /* Check if fGasmode is set */
                if (fGasmode == 1) {

                    // Random 2D point in a circle of radius r (simple beamprofile)
                    Double_t fX, fY, fZ, radius;
                    radius = gRandom->Gaus(0, fRsigma);
                    gRandom->Circle(fX, fY, radius);
                    fVx = fVx + fX;
                    fVy = fVy + fY;

                    // calculate fZ according to some (probability) density function of the
                    // gas
                    fZ = fDensityFunction->GetRandom();
                    fVz = fVz + fZ;
                }
                //    printf("Insert coordinates: %f, %f, %f ...\n", fVx, fVy, fVz);
                primGen->AddTrack(pdgID, fPx, fPy, fPz, fVx, fVy, fVz);
            }
        }
    } else {
        LOG(info) << "FairEvtGenGenerator: End of input file reached ";
        CloseInput();
        return kFALSE;
    }

    // If end of input file is reached : close it and abort run
    if (feof(fInputFile)) {
        LOG(info) << "FairEvtGenGenerator: End of input file reached ";
        CloseInput();
        return kFALSE;
    }

    /*
    LOG(info) << "FairEvtGenGenerator: Event " << eventID << ",  vertex = ("
    << vx << "," << vy << "," << vz << ") cm,  multiplicity "
    << ntracks;
  */

    return kTRUE;
}

void FairEvtGenGenerator::CloseInput()
{
    if (fInputFile) {
        // if ( fInputFile->is_open() ) {
        {
            LOG(info) << "FairEvtGenGenerator: Closing input file " << fFileName;
            //  fInputFile->close();

            fclose(fInputFile);
        }
        // delete fInputFile;
        fInputFile = nullptr;
    }
}
