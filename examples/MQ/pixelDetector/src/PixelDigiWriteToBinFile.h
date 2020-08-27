/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
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

#ifndef PIXELDIGIWRITETOBINFILE_H
#define PIXELDIGIWRITETOBINFILE_H 1

#include "FairTask.h"

#include <Rtypes.h>
#include <TString.h>

class TClonesArray;

#include <fstream>

class PixelDigiWriteToBinFile : public FairTask
{
  public:
    /** Default constructor **/
    PixelDigiWriteToBinFile();

    /** Standard constructor **/
    PixelDigiWriteToBinFile(Int_t iVerbose);

    /** Constructor with name **/
    PixelDigiWriteToBinFile(const char* name, Int_t iVerbose);

    /** Destructor **/
    virtual ~PixelDigiWriteToBinFile();

    /** Execution **/
    virtual void Exec(Option_t* opt);

    void SetOutputFileName(TString tstr) { fOutputFileName = tstr; };

    void SetDivideLevel(Int_t idiv) { fDivideLevel = idiv; }   // 0 - event, 1 - station, 2 - sensor

  private:
    TClonesArray* fDigis; /** Input array of PixelDigi **/

    TString fOutputFileName;
    Int_t fNofOutputFiles;
    std::ofstream fOutputFiles[12];   // no more than 12 output files....

    /** Get parameter containers **/
    virtual void SetParContainers() {}

    Int_t fDivideLevel;

    Int_t fRunId;
    Int_t fMCEntryNo;
    Int_t fPartNo;

    /** Intialisation **/
    virtual InitStatus Init();

    /** Reinitialisation **/
    virtual InitStatus ReInit();

    /** Reset eventwise counters **/
    void Reset() {}

    /** Finish at the end of each event **/
    virtual void Finish();

    PixelDigiWriteToBinFile(const PixelDigiWriteToBinFile&);
    PixelDigiWriteToBinFile& operator=(const PixelDigiWriteToBinFile&);

    ClassDef(PixelDigiWriteToBinFile, 1);
};

#endif
