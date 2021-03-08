/*
 * FairTimebasedMCHitSource.h
 *
 * \brief Combines event based FairHits (with relative times) with absolute event times.
 *
 * \date 07.12.2020
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
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
    FairTimebasedMCHitSource(TString branchName, double holdTime = 10.0)
        : FairDataSourceI(branchName)
        , fDataHandler(holdTime){};
    virtual ~FairTimebasedMCHitSource();

    virtual InitStatus Init();
    /**
     * Deletes data which is older than time + holdTime and adds new data from input TClonesArray
     * \param time Absolute time in ns which determines which data is deleted and which new event is read in
     */
    virtual void RetrieveData(double time);
    virtual int GetNData() { return fDataHandler.GetData().size(); };
    virtual TObject* GetData(int index) { return fDataHandler.GetData()[index].first; }
    virtual double GetTime(int index)
    {
        return (fDataHandler.GetData()[index].first->GetTimeStamp() + fDataHandler.GetData()[index].second);
    };
    virtual void Reset() { fDataHandler.Reset(); };
    void SetHoldTime(double time) { fDataHandler.SetHoldTime(time); }

  private:
    TBranch* fBranch = nullptr;                        //!
    std::vector<double> const* fEventTime = nullptr;   //!
    FairTimebasedDataHandlerT<FairHit> fDataHandler;   //!

    ClassDef(FairTimebasedMCHitSource, 1);
};

#endif /* EVENTDISPLAY_FAIRTCASOURCE_H_ */
