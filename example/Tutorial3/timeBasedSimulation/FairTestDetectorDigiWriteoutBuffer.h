/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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

#include "FairWriteoutBuffer.h" // for FairWriteoutBuffer

#include "FairTestDetectorDigi.h" // for FairTestDetectorDigi

#include "Rtypes.h"
#include "TString.h" // for TString

#include <map> // for map

class FairTimeStamp;

class FairTestDetectorDigiWriteoutBuffer : public FairWriteoutBuffer
{

  public:
    FairTestDetectorDigiWriteoutBuffer();
    FairTestDetectorDigiWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance);

    virtual ~FairTestDetectorDigiWriteoutBuffer();

    void AddNewDataToTClonesArray(FairTimeStamp*);

    virtual double FindTimeForData(FairTimeStamp* data);
    virtual void FillDataMap(FairTimeStamp* data, double activeTime);
    virtual void EraseDataFromDataMap(FairTimeStamp* data);

  protected:
    std::map<FairTestDetectorDigi, double> fData_map;

    ClassDef(FairTestDetectorDigiWriteoutBuffer, 1);
};

#endif /* FairTestDetectorDigiWriteoutBuffer_H_ */
