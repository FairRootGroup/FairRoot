/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelWriteToFile.h
 *
 *  Created on: 19.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELDIGIWRITETOFILE_H
#define PIXELDIGIWRITETOFILE_H 1

#include "FairTask.h"

#include <Rtypes.h>
#include <TString.h>
#include <fstream>

class TClonesArray;

class PixelDigiWriteToFile : public FairTask
{
  public:
    /** Default constructor **/
    PixelDigiWriteToFile();

    /** Standard constructor **/
    PixelDigiWriteToFile(Int_t iVerbose);

    /** Constructor with name **/
    PixelDigiWriteToFile(const char* name, Int_t iVerbose);

    /** Destructor **/
    ~PixelDigiWriteToFile() override;

    /** Execution **/
    void Exec(Option_t* opt) override;

    void SetOutputFileName(const TString& tstr) { fOutputFileName = tstr; }

    void SetDivideLevel(Int_t idiv) { fDivideLevel = idiv; }   // 0 - event, 1 - station, 2 - sensor

  private:
    TClonesArray* fDigis; /** Input array of PixelDigi **/

    TString fOutputFileName;
    Int_t fNofOutputFiles;
    std::ofstream fOutputFiles[12];   // no more than 12 output files....

    Int_t fDivideLevel;

    Int_t fRunId;
    Int_t fMCEntryNo;
    Int_t fPartNo;

    /** Intialisation **/
    InitStatus Init() override;

    /** Reinitialisation **/
    InitStatus ReInit() override;

    /** Reset eventwise counters **/
    void Reset() {}

    /** Finish at the end of each event **/
    void Finish() override;

    PixelDigiWriteToFile(const PixelDigiWriteToFile&);
    PixelDigiWriteToFile& operator=(const PixelDigiWriteToFile&);

    ClassDefOverride(PixelDigiWriteToFile, 1);
};

#endif
