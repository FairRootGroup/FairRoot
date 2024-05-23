/*
 * FairTimebasedMCSource.h
 *
 * \brief Combines event based FairMCPoints with absolute event times.
 *
 * \date 07.12.2020
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
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
    FairTimebasedMCSource(TString branchName, double holdTime = 10.0)
        : FairDataSourceI(branchName)
        , fDataHandler(holdTime){};
    virtual ~FairTimebasedMCSource();

    virtual InitStatus Init();
    /**
     * Deletes data which is older than time + holdTime and adds new data from input TClonesArray
     * \param simTime Absolute time in ns which determines which data is deleted and which new event is read in
     */
    virtual void RetrieveData(double simTime);
    virtual int GetNData() { return fDataHandler.GetData().size(); };
    virtual TObject* GetData(int index) { return fDataHandler.GetData()[index].first; }
    virtual double GetTime(int index)
    {
        return (fDataHandler.GetData()[index].first->GetTime() + fDataHandler.GetData()[index].second);
    };
    virtual void Reset() { fDataHandler.Reset(); };
    void SetHoldTime(double time) { fDataHandler.SetHoldTime(time); }

  private:
    TBranch* fBranch = nullptr;                            //!
    std::vector<double> const* fEventTime = nullptr;       //!
    FairTimebasedDataHandlerT<FairMCPoint> fDataHandler;   //!

    ClassDef(FairTimebasedMCSource, 1);
};

#endif /* EVENTDISPLAY_FAIRTCASOURCE_H_ */
