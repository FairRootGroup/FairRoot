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
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorHit.h"

//////////////// TClonesArray container version
template<typename T, typename U>
class DigiToHitTask_base : public BaseProcessorTaskPolicy< DigiToHitTask_base<T,U> >
{
    typedef T Digi_type;
    typedef U Hit_type;

  public:
    DigiToHitTask_base() : BaseProcessorTaskPolicy< DigiToHitTask_base<T,U> >(),
        fOutputContainer(nullptr),
        fTaskName(),
        fDetID(-1),
        fMCIndex(-1)
    {}

    DigiToHitTask_base(const DigiToHitTask_base&) = delete;
    DigiToHitTask_base operator=(const DigiToHitTask_base&) = delete;

    virtual ~DigiToHitTask_base()
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
        for(int idigi(0);idigi<inputdata->GetEntriesFast();idigi++)
        {
            TVector3 pos;
            TVector3 dpos;
            Double_t timestamp=0;
            Double_t timestampErr=0;

            Digi_type* digi = static_cast<Digi_type*>(inputdata->At(idigi));
            ProcessDigi(*digi, pos, dpos, timestamp, timestampErr);

            Hit_type* hit = new ((*fOutputContainer)[idigi]) Hit_type(fDetID, fMCIndex, pos, dpos);
            hit->SetTimeStamp(digi->GetTimeStamp());
            hit->SetTimeStampError(digi->GetTimeStampError());
        }
    }

    TClonesArray* GetOutputData()
    {
        return fOutputContainer;
    }

  protected:


    void ProcessDigi(const Digi_type &Digi, TVector3 &pos, TVector3 &dpos, Double_t &t, Double_t &t_err)
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

typedef DigiToHitTask_base<MyDigi,MyHit> DigiToHitTask;
typedef DigiToHitTask_base<FairTestDetectorDigi,FairTestDetectorHit> DigiToHitTaskTuto3_t;

#endif /* DIGITOHITTASK_H */
