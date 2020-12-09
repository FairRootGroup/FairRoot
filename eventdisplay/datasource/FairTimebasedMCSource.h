/*
 * FairTimebasedMCSource.h
 *
 *  Created on: 07.12.2020
 *      Author: tstockmanns
 */

#ifndef EVENTDISPLAY_FAIRTIMEBASEDMCSOURCE_H_
#define EVENTDISPLAY_FAIRTIMEBASEDMCSOURCE_H_

#include "FairDataSourceI.h"
#include "FairMCPoint.h"
#include "FairTimebasedDataHandlerT.h"

#include <TBranch.h>

class FairTimebasedMCSource : public FairDataSourceI
{
  public:
    FairTimebasedMCSource();
    FairTimebasedMCSource(TString branchName)
        : FairDataSourceI(branchName){};
    virtual ~FairTimebasedMCSource();

    virtual InitStatus Init();
    virtual void RetrieveData(double time);
    virtual int GetNData() { return fDataHandler.GetData().size(); };
    virtual TObject* GetData(int index) { return fDataHandler.GetData()[index].first; }
    virtual double GetTime(int index)
    {
        return (fDataHandler.GetData()[index].first->GetTime() + fDataHandler.GetData()[index].second);
    };
    virtual void Reset() { fDataHandler.Reset(); };

  private:
    TBranch* fBranch = nullptr;                            //!
    std::vector<double> const* fEventTime = nullptr;       //!
    FairTimebasedDataHandlerT<FairMCPoint> fDataHandler;   //!

    ClassDef(FairTimebasedMCSource, 1);
};

#endif /* EVENTDISPLAY_FAIRTCASOURCE_H_ */
