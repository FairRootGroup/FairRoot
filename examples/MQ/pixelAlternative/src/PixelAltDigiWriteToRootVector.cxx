/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelAltDigiWriteToRootVector.h
 *
 *  Created on: 19.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelAltDigiWriteToRootVector.h"

// Includes from base
#include "FairLogger.h"
#include "FairRootManager.h"

// Includes from ROOT
#include "PixelDigi.h"
#include "PixelPayload.h"

#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>

PixelAltDigiWriteToRootVector::PixelAltDigiWriteToRootVector()
    : PixelAltDigiWriteToRootVector("Pixel DigiWriter", 0)
{}

PixelAltDigiWriteToRootVector::PixelAltDigiWriteToRootVector(Int_t iVerbose)
    : PixelAltDigiWriteToRootVector("Pixel DigiWriter", iVerbose)
{}

PixelAltDigiWriteToRootVector::PixelAltDigiWriteToRootVector(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fDigis(nullptr)
    , fOutputRootFile()
    , fOutputRootTree()
    , fPixelEventHeader(0)
    , fPixelDigiVector()
    , fOutputFileName("test.root")
    , fNofOutputFiles(0)
    , fDivideLevel(0)
    , fRunId(0)
    , fMCEntryNo(0)
    , fPartNo(0)
{}

PixelAltDigiWriteToRootVector::~PixelAltDigiWriteToRootVector() = default;

void PixelAltDigiWriteToRootVector::Exec(Option_t* /*opt*/)
{
    Int_t nofDigis = fDigis->GetEntriesFast();

    for (Int_t ifile = 0; ifile < fNofOutputFiles; ifile++) {
        fPixelDigiVector.clear();
        fPixelEventHeader->fRunId = fRunId;
        fPixelEventHeader->fMCEntryNo = fMCEntryNo;
        fPixelEventHeader->fPartNo = ifile;

        //    std::cout << ifile << " > " << std::flush;
        for (Int_t iDigi = 0; iDigi < nofDigis; iDigi++) {
            PixelDigi* currentDigi = static_cast<PixelDigi*>(fDigis->At(iDigi));

            int detId = (int)currentDigi->GetDetectorID();
            Int_t fileToSave = 0;
            if (fDivideLevel == 1) {
                fileToSave = detId / 256 - 1;
            } else if (fDivideLevel == 2) {
                fileToSave = (detId / 256 - 1) * 4 + (detId % 256 - 1);
            }
            //      std::cout << fileToSave << " " << std::flush;
            if (fileToSave != ifile)
                continue;

            int feId = (int)currentDigi->GetFeID();
            int col = (int)currentDigi->GetCol();
            int row = (int)currentDigi->GetRow();
            //      double charge = (double)currentDigi->GetCharge();

            PixelPayload::Digi tempDigi;   // = new PixelPayload::Digi();
            tempDigi.fDetectorID = detId;
            tempDigi.fFeID = feId;
            tempDigi.fCharge = 0.;
            tempDigi.fCol = col;
            tempDigi.fRow = row;
            fPixelDigiVector.push_back(tempDigi);
        }
        fPixelDigiVector.shrink_to_fit();
        //    std::cout << std::endl;
        fOutputRootTree[ifile]->Fill();
    }
    fMCEntryNo++;
}

InitStatus PixelAltDigiWriteToRootVector::Init()
{
    // Get input array
    FairRootManager* ioman = FairRootManager::Instance();

    if (!ioman)
        LOG(fatal) << "No FairRootManager";
    fDigis = static_cast<TClonesArray*>(ioman->GetObject("PixelDigis"));

    if (!fDigis)
        LOG(warn) << "PixelAltDigiWriteToRootVector::Init() No input PixelDigis array!";

    LOG(info) << "-I- " << fName.Data() << "::Init(). Initialization succesfull.";

    fRunId = ioman->GetRunId();

    if (fDivideLevel == 0) {
        fNofOutputFiles = 1;
    } else {
        if (fDivideLevel == 1) {
            fNofOutputFiles = 3;   // 1 file per station (3 stations)
        } else if (fDivideLevel == 2) {
            fNofOutputFiles = 12;   // 1 file per sensor  (3 stations times 4 sensors)
        } else {
            LOG(fatal) << "PixelAltDigiWriteToRootVector::Init(), fDivideLevel = " << fDivideLevel
                       << " unknown, it has to be in the range <0,2>";
            return kFATAL;
        }
    }

    fPixelEventHeader = new PixelPayload::EventHeader();
    for (Int_t ifile = 0; ifile < fNofOutputFiles; ifile++) {
        TString fileName = fOutputFileName;
        TString uniqFile =
            (fDivideLevel == 0 ? "." : (fDivideLevel == 1 ? Form(".s%d.", ifile) : Form(".c%d.", ifile)));
        fileName.Replace(fileName.Last('.'), 1, uniqFile.Data());

        fOutputRootFile[ifile] = new TFile(fileName.Data(), "RECREATE");
        fOutputRootTree[ifile] = new TTree("fairdata", "example MQ 9 Pixel data");
        LOG(debug) << "trying to create branch in file >>" << fOutputRootFile[ifile]->GetName() << "<<";
        fOutputRootTree[ifile]->Branch("EventHeader.", "PixelPayload::EventHeader", &fPixelEventHeader, 0);
        fOutputRootTree[ifile]->Branch("DigiVector.", &fPixelDigiVector, 32000, 0);
        LOG(debug) << "branches created, fPixelDigiVector = >>" << &fPixelDigiVector << "<<";
    }

    return kSUCCESS;
}

InitStatus PixelAltDigiWriteToRootVector::ReInit()
{
    FairRootManager* ioman = FairRootManager::Instance();
    InitStatus Status = kFATAL;
    if (!ioman) {
        LOG(fatal) << "No FairRootManager found.";
    } else {
        fRunId = ioman->GetRunId();
        fMCEntryNo = 0;
        Status = kSUCCESS;
    }
    return Status;
}

void PixelAltDigiWriteToRootVector::Finish()
{
    for (Int_t ifile = 0; ifile < fNofOutputFiles; ifile++) {
        fOutputRootFile[ifile]->Write();
        fOutputRootFile[ifile]->Close();
    }
}
