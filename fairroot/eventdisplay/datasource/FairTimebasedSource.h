/**
 * FairTimebasedSource.h
 *
 * \brief Handles timebased data via the GetData method. A time window has to be given in which the data is received.
 *
 * \date 07.12.2020
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 */

#ifndef EVENTDISPLAY_FAIRTIMEBASEDSOURCE_H_
#define EVENTDISPLAY_FAIRTIMEBASEDSOURCE_H_

#include "FairDataSourceI.h"
#include "FairTSBufferFunctional.h"   // IWYU pragma: keep needed for cint
#include "FairTimeStamp.h"

class FairTimebasedSource : public FairDataSourceI
{
  public:
    FairTimebasedSource();
    FairTimebasedSource(TString branchName, Double_t windowMinus, Double_t windowPlus)
        : FairDataSourceI(branchName)
        , fTimeWindowPlus(windowMinus)
        , fTimeWindowMinus(windowPlus){};
    virtual ~FairTimebasedSource();

    virtual void RetrieveData(double time);
    virtual int GetNData() { return fCArray->GetEntries(); };
    virtual TObject* GetData(int index) { return fCArray->At(index); }
    virtual double GetTime(int index) { return static_cast<FairTimeStamp*>(fCArray->At(index))->GetTimeStamp(); }
    virtual void Reset(){};

  private:
    BinaryFunctor* fStartFunctor{new StopTime()};   //!
    BinaryFunctor* fStopFunctor{new StopTime()};    //!
    Double_t fTimeWindowPlus{-1.0};                 //!< time window in ns data is taken before the event time
    Double_t fTimeWindowMinus{-1.0};                //!< time window in ns data is taken after the event time

    ClassDef(FairTimebasedSource, 1);
};

#endif /* EVENTDISPLAY_FAIRTCASOURCE_H_ */
