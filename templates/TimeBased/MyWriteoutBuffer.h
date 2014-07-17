/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* MyWriteoutBuffer.h
 *
 *  Created on: Mar 7, 2012
 *      Author: uhlig
 */

#ifndef MYWRITEOUTBUFFER_H_
#define MYWRITEOUTBUFFER_H_

#include "FairWriteoutBuffer.h"
#include "MyDataClass.h"

class FairTimeStamp;

class MyWriteoutBuffer : public FairWriteoutBuffer
{

  public:
    MyWriteoutBuffer();
    MyWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance);
    void AddNewDataToTClonesArray(FairTimeStamp*);

    virtual ~MyWriteoutBuffer();

    virtual std::vector<std::pair<double, MyDataClass*> > Modify(std::pair<double, MyDataClass*> oldData, std::pair<double, MyDataClass*> newData);

    virtual double FindTimeForData(FairTimeStamp* data) ;
    virtual void FillDataMap(FairTimeStamp* data, double activeTime) ;
    virtual void EraseDataFromDataMap(FairTimeStamp* data);
  protected:

    std::map<MyDataClass, double> fData_map;

    ClassDef(MyWriteoutBuffer, 1);
};

#endif /* MYWRITEOUTBUFFER_H_ */

