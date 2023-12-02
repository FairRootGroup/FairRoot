/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

//
//  PixelDigiSource.cxx
//  FAIRROOT
//
//  Created by Radoslaw Karabowicz on 19.02.2016.
//
//
#include "PixelDigiSource.h"

#include "FairRootManager.h"
#include "PixelDigi.h"

#include <cstdlib>
#include <cstring>
#include <fairlogger/Logger.h>
#include <string>

PixelDigiSource::PixelDigiSource(TString inputFileName)
    : FairSource()
    , fDigis(PixelDigi::Class(), 10000)
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
    LOG(debug) << "PixelDigiSource created------------";
}

Bool_t PixelDigiSource::Init()
{
    // Get input array
    FairRootManager* ioman = FairRootManager::Instance();

    LOG(info) << "PixelDigiSource::Init";
    if (!ioman)
        LOG(fatal) << "No FairRootManager";

    // Register output array StsDigi
    ioman->Register("PixelDigis", "Pixel", &fDigis, kFALSE);

    fEventHeader.SetName("EventHeader.");
    ioman->Register("EventHeader.", "EvtHeader", &fEventHeader, kFALSE);

    fInputFile.open(fInputFileName.Data(), std::fstream::in);

    if (!fInputFile.is_open()) {
        LOG(fatal) << "PixelDigiSource::Init() fInputFile \"" << fInputFileName.Data() << "\" could not be open!";
        return kFALSE;
    }

    return kTRUE;
}

static int ReadIntFromString(const std::string& wholestr, const std::string& pattern)
{
    std::string tempstr = wholestr;
    tempstr.replace(0, tempstr.find(pattern) + pattern.length(), "");
    tempstr.replace(0, tempstr.find('=') + 1, "");
    return atoi(tempstr.c_str());
}

Int_t PixelDigiSource::ReadEvent(UInt_t i)
{
    fDigis.Delete();
    fNDigis = 0;

    if (i == 0) {
        fInputFile.clear();
        fInputFile.seekg(0, std::ios::beg);
    }

    fCurrentEntryNo = i;

    std::string buffer;
    LOG(debug) << "PixelDigiSource::ReadEvent() Begin of (" << fDigis.GetEntries() << ")";
    do {
        getline(fInputFile, buffer);
        LOG(debug) << "read from file: \"" << buffer << "\"";
        if (buffer.find("EVENT BEGIN") == 0) {
            fRunId = ReadIntFromString(buffer, "RUNID");
            fMCEntryNo = ReadIntFromString(buffer, "MCENTRYNO");
            fPartNo = ReadIntFromString(buffer, "PARTNO");
            fEventHeader.SetRunId(fRunId);
            fEventHeader.SetMCEntryNumber(fMCEntryNo);
            fEventHeader.SetPartNo(fPartNo);

            LOG(debug) << "GOT NEW EVENT " << fMCEntryNo << " (part " << fPartNo << ") with run id = " << fRunId;
        }
        if (buffer.find("EVENT") == 0)
            continue;
        Int_t detId = atoi(buffer.c_str());
        buffer.erase(0, buffer.find(' ') + 1);
        Int_t feId = atoi(buffer.c_str());
        buffer.erase(0, buffer.find(' ') + 1);
        Int_t col = atoi(buffer.c_str());
        buffer.erase(0, buffer.find(' ') + 1);
        Int_t row = atoi(buffer.c_str());
        buffer.erase(0, buffer.find(' ') + 1);
        Double_t charge = atof(buffer.c_str());
        LOG(debug) << "    --/" << fNDigis << "/-->    " << detId << " / " << feId << " / " << col << " / " << row
                   << " / " << charge;
        new (fDigis[fNDigis]) PixelDigi(-1, detId, feId, col, row, charge, 0.);
        fNDigis++;
    } while (fInputFile && (buffer == "EVENT END"));
    LOG(debug) << "PixelDigiSource::ReadEvent() End of";

    if (!fInputFile) {
        return 1;
    }

    return 0;
}

Bool_t PixelDigiSource::ActivateObject(TObject** obj, const char* BrName)
{
    if (strcmp(BrName, "PixelDigis") == 0)
        *obj = &fDigis;
    else if (strcmp(BrName, "EventHeader.") == 0)
        *obj = &fEventHeader;
    else
        return kFALSE;

    return kTRUE;
}

void PixelDigiSource::Reset() {}

Int_t PixelDigiSource::CheckMaxEventNo(Int_t /*EvtEnd*/)
{
    return -1;
}

void PixelDigiSource::FillEventHeader(FairEventHeader* feh)
{
    FairSource::FillEventHeader(feh);
    feh->SetMCEntryNumber(fMCEntryNo);
    static_cast<PixelEventHeader*>(feh)->SetPartNo(fPartNo);
}
