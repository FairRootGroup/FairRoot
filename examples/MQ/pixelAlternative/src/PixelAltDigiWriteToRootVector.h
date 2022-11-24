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

#ifndef PIXELALTDIGIWRITETOROOTVECTOR_H
#define PIXELALTDIGIWRITETOROOTVECTOR_H 1

#include "FairTask.h"
#include "PixelPayload.h"

#include <Rtypes.h>
#include <TString.h>
#include <vector>

class TClonesArray;
class TFile;
class TTree;

class PixelAltDigiWriteToRootVector : public FairTask
{
  public:
    /** Default constructor **/
    PixelAltDigiWriteToRootVector();

    /** Standard constructor **/
    PixelAltDigiWriteToRootVector(Int_t iVerbose);

    /** Constructor with name **/
    PixelAltDigiWriteToRootVector(const char* name, Int_t iVerbose);

    /** Destructor **/
    virtual ~PixelAltDigiWriteToRootVector();

    /** Execution **/
    virtual void Exec(Option_t* opt);

    void SetOutputFileName(TString tstr) { fOutputFileName = tstr; };

    void SetDivideLevel(Int_t idiv) { fDivideLevel = idiv; }   // 0 - event, 1 - station, 2 - sensor

  private:
    TClonesArray* fDigis; /** Input array of PixelDigi **/

    TFile* fOutputRootFile[12];
    TTree* fOutputRootTree[12];
    PixelPayload::EventHeader* fPixelEventHeader;
    std::vector<PixelPayload::Digi> fPixelDigiVector;

    TString fOutputFileName;
    Int_t fNofOutputFiles;

    Int_t fDivideLevel;

    Int_t fRunId;
    Int_t fMCEntryNo;
    Int_t fPartNo;

    /** Intialisation **/
    virtual InitStatus Init();

    /** Reinitialisation **/
    virtual InitStatus ReInit();

    /** Reset eventwise counters **/
    void Reset();

    /** Finish at the end of each event **/
    virtual void Finish();

    PixelAltDigiWriteToRootVector(const PixelAltDigiWriteToRootVector&);
    PixelAltDigiWriteToRootVector& operator=(const PixelAltDigiWriteToRootVector&);

    ClassDef(PixelAltDigiWriteToRootVector, 1);
};

#endif
