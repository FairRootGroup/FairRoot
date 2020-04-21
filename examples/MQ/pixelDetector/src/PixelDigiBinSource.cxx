/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

//
//  PixelDigiBinSource.cxx
//  FAIRROOT
//
//  Created by Radoslaw Karabowicz on 19.02.2016.
//
//
#include "PixelDigiBinSource.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "PixelDigi.h"
#include "PixelEventHeader.h"

#include <TClonesArray.h>
#include <TObject.h>
#include <TString.h>
#include <cstring>
#include <string>

PixelDigiBinSource::PixelDigiBinSource(TString inputFileName)
    : FairSource()
    , fEventHeader(nullptr)
    , fDigis(nullptr)
    , fNDigis(0)
    , fTNofEvents(0)
    , fTNofDigis(0)
    , fInputFileName(inputFileName)
    , fInputFile()
    , fCurrentEntryNo(0)
    , fRunId(0)
    , fMCEntryNo(0)
    , fPartNo(0)
{
    LOG(debug) << "PixelDigiBinSource created------------";
}

PixelDigiBinSource::~PixelDigiBinSource() {}

Bool_t PixelDigiBinSource::Init()
{
    // Get input array
    FairRootManager* ioman = FairRootManager::Instance();

    LOG(info) << "PixelDigiBinSource::Init";
    if (!ioman)
        LOG(fatal) << "No FairRootManager";

    // Register output array StsDigi
    fDigis = new TClonesArray("PixelDigi", 10000);
    ioman->Register("PixelDigis", "Pixel", fDigis, kFALSE);

    fEventHeader = new PixelEventHeader();
    fEventHeader->SetName("EventHeader.");
    ioman->Register("EventHeader.", "EvtHeader", fEventHeader, kFALSE);

    fInputFile.open(fInputFileName.Data(), std::fstream::in | std::fstream::binary);

    if (!fInputFile.is_open()) {
        LOG(fatal) << "PixelDigiBinSource::Init() fInputFile \"" << fInputFileName.Data() << "\" could not be open!";
        return kFALSE;
    }

    return kTRUE;
}

Int_t PixelDigiBinSource::ReadEvent(UInt_t i)
{
    fDigis->Clear();
    fNDigis = 0;

    if (!fInputFile) {
        return 1;
    }

    if (i == 0) {
        fInputFile.clear();
        fInputFile.seekg(0, std::ios::beg);
    }

    fCurrentEntryNo = i;

    std::string buffer;
    LOG(debug) << "PixelDigiBinSource::ReadEvent() Begin of (" << fDigis->GetEntries() << ")";

    Int_t head[4];   // runId, MCEntryNo, PartNo, NofDigis
    fInputFile.read((char*)head, sizeof(head));

    if (fInputFile.eof()) {
        LOG(info) << "End of file reached!";
        return 1;
    }

    Int_t dataSize = 4;   // detId, feId, col, row

    const Int_t constNofData = head[3] * dataSize;
    short int dataCont[constNofData];
    fInputFile.read((char*)dataCont, sizeof(dataCont));

    fRunId = head[0];
    fMCEntryNo = head[1];
    fPartNo = head[2];
    fEventHeader->SetRunId(fRunId);
    fEventHeader->SetMCEntryNumber(fMCEntryNo);
    fEventHeader->SetPartNo(fPartNo);

    for (Int_t idata = 0; idata < head[3]; idata++) {
        LOG(debug) << "    --/" << idata << "/-->    " << dataCont[idata * dataSize + 0] << " / "
                   << dataCont[idata * dataSize + 1] << " / " << dataCont[idata * dataSize + 2] << " / "
                   << dataCont[idata * dataSize + 3] << " / "
                   << " 0.";
        new ((*fDigis)[fNDigis]) PixelDigi(-1,
                                           (Int_t)dataCont[idata * dataSize + 0],
                                           (Int_t)dataCont[idata * dataSize + 1],
                                           (Int_t)dataCont[idata * dataSize + 2],
                                           (Int_t)dataCont[idata * dataSize + 3],
                                           0.,
                                           0.);
        fNDigis++;
    }
    LOG(debug) << "PixelDigiBinSource::ReadEvent() End of";

    if (!fInputFile) {
        return 1;
    }

    return 0;
}

Bool_t PixelDigiBinSource::ActivateObject(TObject** obj, const char* BrName)
{
    if (strcmp(BrName, "PixelDigis") == 0)
        *obj = (TObject*)fDigis;
    else if (strcmp(BrName, "EventHeader.") == 0)
        *obj = (TObject*)fEventHeader;
    else
        return kFALSE;

    return kTRUE;
}

void PixelDigiBinSource::Close() { fInputFile.close(); }

void PixelDigiBinSource::Reset() {}

Int_t PixelDigiBinSource::CheckMaxEventNo(Int_t /*EvtEnd*/) { return -1; }

void PixelDigiBinSource::FillEventHeader(FairEventHeader* feh)
{
    ((PixelEventHeader*)feh)->SetRunId(fRunId);
    ((PixelEventHeader*)feh)->SetMCEntryNumber(fMCEntryNo);
    ((PixelEventHeader*)feh)->SetPartNo(fPartNo);
}

ClassImp(PixelDigiBinSource);
