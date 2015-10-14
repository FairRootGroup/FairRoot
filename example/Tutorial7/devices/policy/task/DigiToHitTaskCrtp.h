/* 
 * File:   DigiToHitTask.h
 * Author: winckler
 *
 * Created on December 2, 2014, 10:44 AM
 */

#ifndef DIGITOHITTASK_H
#define	DIGITOHITTASK_H

// std
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

// root
#include "Rtypes.h"
#include "TMath.h"

// FairRoot
#include "TVector3.h"

// FairRoot - Tutorial7
#include "BaseProcessorTaskPolicy.h"
#include "FairHit.h"
#include "MyDigi.h"
#include "MyHit.h"


//////////////// TClonesArray container version

class DigiToHitTaskCrtp : public BaseProcessorTaskPolicy< DigiToHitTaskCrtp >
{

  public:
    DigiToHitTaskCrtp() : BaseProcessorTaskPolicy< DigiToHitTaskCrtp >(),
        fOutputContainer(nullptr), 
        fTaskName(), 
        fDetID(-1), 
        fMCIndex(-1)
    {}

    virtual ~DigiToHitTaskCrtp()
    {}

    void InitTask(const std::string &ClassName)
    {
        InitContainer(ClassName.c_str());
    }

    void InitContainer(const char* ClassName)
    {
        fOutputContainer = new TClonesArray(ClassName);
    }

    void InitContainer(TClonesArray* array)
    {
        fOutputContainer = array;
    }

    void ExecuteTask(TClonesArray* inputdata)
    {
        fOutputContainer->Delete();
        for(unsigned int idigi(0);idigi<inputdata->GetEntriesFast();idigi++)
        {
            TVector3 pos;
            TVector3 dpos;
            Double_t timestamp=0;
            Double_t timestampErr=0;

            MyDigi* digi = (MyDigi*)inputdata->At(idigi);
            ProcessDigi(*digi, pos, dpos, timestamp, timestampErr);

            MyHit* hit = new ((*fOutputContainer)[idigi]) MyHit(fDetID, fMCIndex, pos, dpos);
            hit->SetTimeStamp(digi->GetTimeStamp());
            hit->SetTimeStampError(digi->GetTimeStampError());
        }
    }

    TClonesArray* GetOutputData()
    {
        return fOutputContainer;
    }

  protected:


    inline void ProcessDigi(const MyDigi &Digi, TVector3 &pos, TVector3 &dpos, Double_t &t, Double_t &t_err)
    {
        pos.SetXYZ(Digi.GetX() + 0.5, Digi.GetY() + 0.5, Digi.GetZ() + 0.5);
        dpos.SetXYZ(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));
        t = Digi.GetTimeStamp();
        t_err = Digi.GetTimeStampError();
    }

    TClonesArray* fOutputContainer;
    std::string fTaskName;
    Int_t fDetID;
    Int_t fMCIndex;
};

#endif /* DIGITOHITTASK_H */
