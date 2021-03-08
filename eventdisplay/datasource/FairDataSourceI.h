/**
 * FairDataSourceI.h
 *
 * \brief Abstract interface class to handle different input data for event and timebased data
 *
 *
 * \date 07.12.2020
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
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

    /**
     * Init has to be called in the Init() of a task to activate the read back of a TClonesArray
     */
    virtual InitStatus Init();
    /**
     * Has to be called at the beginning of an Execute to handle the input data.
     * \param time Absolute time in ns which is active at the current event. This data is needed for the timebased input
     * data. For event based data the time is ignored
     */
    virtual void RetrieveData(double time)
    {
        LOG(debug) << "Retrieving Data for " << fBranchName << " for time " << time << " ns - nData = " << GetNData();
    }
    virtual int GetNData() = 0;
    virtual TObject* GetData(int index) = 0;
    virtual double GetTime(int index) { return -1.0; };
    virtual TString GetBranchName() const { return fBranchName; };
    virtual void Reset() = 0;   //< Resets the data containers

  protected:
    TClonesArray* fCArray = nullptr;
    TString fBranchName;

    ClassDef(FairDataSourceI, 1);
};

#endif /* EVENTDISPLAY_FAIRDATASOURCEI_H_ */
