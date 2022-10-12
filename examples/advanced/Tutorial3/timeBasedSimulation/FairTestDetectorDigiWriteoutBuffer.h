/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiWriteoutBuffer.h
 *
 *  Created on: May 10, 2011
 *      Author: stockman
 */

#ifndef FairTestDetectorDigiWriteoutBuffer_H_
#define FairTestDetectorDigiWriteoutBuffer_H_

#include "FairTestDetectorDigi.h"   // for FairTestDetectorDigi
#include "FairWriteoutBuffer.h"     // for FairWriteoutBuffer

#include <Rtypes.h>
#include <TString.h>   // for TString
#include <map>         // for map

class FairTimeStamp;

class FairTestDetectorDigiWriteoutBuffer : public FairWriteoutBuffer
{

  public:
    FairTestDetectorDigiWriteoutBuffer();
    FairTestDetectorDigiWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance);

    ~FairTestDetectorDigiWriteoutBuffer() override;

    void AddNewDataToTClonesArray(FairTimeStamp*) override;

    double FindTimeForData(FairTimeStamp* data) override;
    void FillDataMap(FairTimeStamp* data, double activeTime) override;
    void EraseDataFromDataMap(FairTimeStamp* data) override;

  protected:
    std::map<FairTestDetectorDigi, double> fData_map;

    ClassDefOverride(FairTestDetectorDigiWriteoutBuffer, 1);
};

#endif /* FairTestDetectorDigiWriteoutBuffer_H_ */
