/**
 * FairTCASource.h
 *
 * \brief Handles a TClonesArray as input object. No timebased operations are done and the TClonesArray is handled as it
 * 		  is received by the FairRootManager
 *
 * \date 07.12.2020
 * \author Tobias Stockmanns <t.stockmanns@fz-juelich.de>
 */

#ifndef EVENTDISPLAY_FAIRTCASOURCE_H_
#define EVENTDISPLAY_FAIRTCASOURCE_H_

#include "FairDataSourceI.h"
#include "FairMCPoint.h"
#include "FairTimeStamp.h"
#include "TClonesArray.h"

class FairTCASource : public FairDataSourceI
{
  public:
    FairTCASource();
    FairTCASource(TString branchName)
        : FairDataSourceI(branchName){};
    virtual ~FairTCASource();

    virtual int GetNData() { return fCArray->GetEntries(); };
    virtual TObject* GetData(int index) { return fCArray->At(index); }
    virtual double GetTime(int index)
    {
        TObject* dataObj = fCArray->At(index);
        double time = -1.0;
        if (dataObj->InheritsFrom("FairTimeStamp")) {
            time = static_cast<FairTimeStamp*>(dataObj)->GetTimeStamp();
        } else if (dataObj->InheritsFrom("FairMCPoint")) {
            time = static_cast<FairMCPoint*>(dataObj)->GetTime();
        }
        return time;
    };
    virtual void Reset(){};

  private:
    ClassDef(FairTCASource, 1);
};

#endif /* EVENTDISPLAY_FAIRTCASOURCE_H_ */
