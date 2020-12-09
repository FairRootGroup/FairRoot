/*
 * FairDataSourceI.h
 *
 *  Created on: 07.12.2020
 *      Author: tstockmanns
 */

#ifndef EVENTDISPLAY_FAIRDATASOURCEI_H_
#define EVENTDISPLAY_FAIRDATASOURCEI_H_

#include "FairTask.h"

#include <TClonesArray.h>
#include <TObject.h>
#include <TString.h>
#include <fairlogger/Logger.h>

class FairDataSourceI : public TObject
{
  public:
    FairDataSourceI();
    FairDataSourceI(TString branchName)
        : fBranchName(branchName){};
    virtual ~FairDataSourceI();

    virtual InitStatus Init();
    virtual void RetrieveData(double time)
    {
        LOG(debug) << "Retrieving Data for " << fBranchName << " for time " << time << " ns - nData = " << GetNData();
    }
    virtual int GetNData() = 0;
    virtual TObject* GetData(int index) = 0;
    virtual double GetTime(int index) { return -1.0; };
    virtual TString GetBranchName() const { return fBranchName; };
    virtual void Reset() = 0;

  protected:
    TClonesArray* fCArray = nullptr;
    TString fBranchName;

    ClassDef(FairDataSourceI, 1);
};

#endif /* EVENTDISPLAY_FAIRDATASOURCEI_H_ */
