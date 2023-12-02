/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//
//  PixelDigiBinSource.h
//
//
//  Created by Radoslaw Karabowicz on 19.02.2016.
//
//

#ifndef PIXELDIGIBINSOURCE_H_
#define PIXELDIGIBINSOURCE_H_

#include "FairSource.h"
#include "PixelEventHeader.h"

#include <Rtypes.h>
#include <TClonesArray.h>
#include <TString.h>
#include <fstream>

class PixelDigiBinSource : public FairSource
{
  public:
    PixelDigiBinSource(TString inputFileName = "test.dat");
    ~PixelDigiBinSource() override = default;

    Bool_t Init() override;

    Int_t ReadEvent(UInt_t i = 0) override;
    void Reset() override;
    Bool_t SpecifyRunId() override
    {
        ReadEvent(0);
        return true;
    };

    Source_Type GetSourceType() override { return kFILE; }

    void SetParUnpackers() override {}

    Bool_t InitUnpackers() override { return kTRUE; }

    Bool_t ReInitUnpackers() override { return kTRUE; }

    /**Check the maximum event number we can run to*/
    Int_t CheckMaxEventNo(Int_t EvtEnd = 0) override;

    void FillEventHeader(FairEventHeader* feh) override;

    void SetInputFileName(const TString& tstr) { fInputFileName = tstr; };

    Bool_t ActivateObject(TObject** obj, const char* BrName) override;

  private:
    PixelEventHeader fEventHeader{};
    TClonesArray fDigis; /** Output array of PixelDigi **/
    Int_t fNDigis;

    Int_t fTNofEvents;
    Int_t fTNofDigis;

    TString fInputFileName;
    std::ifstream fInputFile;

    Int_t fCurrentEntryNo;

    Int_t fRunId;
    Int_t fMCEntryNo;
    Int_t fPartNo;

    PixelDigiBinSource(const PixelDigiBinSource&);
    PixelDigiBinSource& operator=(const PixelDigiBinSource&);

    // Private member functions:
    void Close() override { fInputFile.close(); }

    ClassDefOverride(PixelDigiBinSource, 1);
};

#endif /* defined(PIXELDIGISOURCE_H_) */
