/*
 * FairTimebasedMCHitSource.h
 *
 *  Created on: 07.12.2020
 *      Author: tstockmanns
 */

#ifndef EVENTDISPLAY_FAIRTIMEBASEDMCHITSOURCE_H_
#define EVENTDISPLAY_FAIRTIMEBASEDMCHITSOURCE_H_

#include "FairDataSourceI.h"
#include "FairMCPoint.h"
#include "FairTimebasedDataHandlerT.h"

#include <TBranch.h>

class FairTimebasedMCHitSource : public FairDataSourceI
{
  public:
    FairTimebasedMCHitSource();
    FairTimebasedMCHitSource(TString branchName)
        : FairDataSourceI(branchName){};
    virtual ~FairTimebasedMCHitSource();

    virtual InitStatus Init();
    virtual void RetrieveData(double time);
    virtual int GetNData() { return fDataHandler.GetData().size(); };
    virtual TObject* GetData(int index) { return fDataHandler.GetData()[index].first; }
    virtual double GetTime(int index)
    {
        return (fDataHandler.GetData()[index].first->GetTimeStamp() + fDataHandler.GetData()[index].second);
    };
    virtual void Reset() { fDataHandler.Reset(); };

  private:
    TBranch* fBranch = nullptr;                        //!
    std::vector<double> const* fEventTime = nullptr;   //!
    FairTimebasedDataHandlerT<FairHit> fDataHandler;   //!

    ClassDef(FairTimebasedMCHitSource, 1);
};

#endif /* EVENTDISPLAY_FAIRTCASOURCE_H_ */
