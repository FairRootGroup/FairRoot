/*
 * FairTestDetectorDigiWriteoutBuffer.h
 *
 *  Created on: May 10, 2011
 *      Author: stockman
 */

#ifndef FairTestDetectorDigiWriteoutBufferR_H_
#define FairTestDetectorDigiWriteoutBuffer_H_

#include "FairWriteoutBuffer.h"
#include "FairTestDetectorDigi.h"

class FairTimeStamp;

class FairTestDetectorDigiWriteoutBuffer : public FairWriteoutBuffer
{

  public:
    FairTestDetectorDigiWriteoutBuffer();
    FairTestDetectorDigiWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance);

    virtual ~FairTestDetectorDigiWriteoutBuffer();

    void AddNewDataToTClonesArray(FairTimeStamp*);

    virtual double FindTimeForData(FairTimeStamp* data) ;
    virtual void FillDataMap(FairTimeStamp* data, double activeTime) ;
    virtual void EraseDataFromDataMap(FairTimeStamp* data);
  protected:

    std::map<FairTestDetectorDigi, double> fData_map;

    ClassDef(FairTestDetectorDigiWriteoutBuffer, 1);
};

#endif /* FairTestDetectorDigiWriteoutBuffer_H_ */
