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
#include "BaseDigiToHitTask.h"
#include "FairHit.h"
#include "MyPodData.h"
#include "MyDigi.h"
#include "MyHit.h"


template <typename DigiType, typename HitType>
class DigiToHitTask : public BaseDigiToHitTask<DigiType,HitType>
{
  public:
      
    DigiToHitTask() : BaseDigiToHitTask<DigiType,HitType>()
    {}
    
    virtual ~DigiToHitTask()
    {
    }
    
    using BaseDigiToHitTask<DigiType,HitType>::fDetID;
    using BaseDigiToHitTask<DigiType,HitType>::fMCIndex;
    using BaseDigiToHitTask<DigiType,HitType>::fTaskName;
    using BaseDigiToHitTask<DigiType,HitType>::ProcessDigi;
    using BaseDigiToHitTask<DigiType,HitType>::FillHit;
    
    void ExecuteTask(std::vector<DigiType>& inputdata)
    {
        if(fOutputContainer.size()>0)
            fOutputContainer.clear();
        
        HitType Hit;
        for(unsigned int digi(0);digi<inputdata.size();digi++)
        {
            TVector3 pos;
            TVector3 dpos;
            Double_t timestamp=0;
            Double_t timestampErr=0;
            ProcessDigi(inputdata[digi], pos, dpos, timestamp, timestampErr);
            FillHit(Hit,fDetID,fMCIndex, pos, dpos, timestamp, timestampErr);
            fOutputContainer.push_back(Hit);
        }
    }
    
    std::vector<HitType>& GetOutputData()
    {
        return fOutputContainer;
    }
    
  protected:
      
    std::vector<HitType> fOutputContainer;
};



//////////////// TClonesArray container version

template <typename DigiType, typename HitType>
class DigiToHitTask_TCA : public BaseDigiToHitTask<DigiType,HitType>
{
    
    using BaseDigiToHitTask<DigiType,HitType>::fDetID;
    using BaseDigiToHitTask<DigiType,HitType>::fMCIndex;
    using BaseDigiToHitTask<DigiType,HitType>::fTaskName;
    using BaseDigiToHitTask<DigiType,HitType>::ProcessDigi;
    using BaseDigiToHitTask<DigiType,HitType>::FillHit;
    
  public:
      
    DigiToHitTask_TCA() : 
        BaseDigiToHitTask<DigiType,HitType>(), 
        fOutputContainer(nullptr)
    {}
    
    virtual ~DigiToHitTask_TCA()
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
        //HitType Hit;
        fOutputContainer->Delete();
        for(unsigned int idigi(0);idigi<inputdata->GetEntriesFast();idigi++)
        {
            TVector3 pos;
            TVector3 dpos;
            Double_t timestamp=0;
            Double_t timestampErr=0;
            
            DigiType* digi = (DigiType*)inputdata->At(idigi);
            ProcessDigi(*digi, pos, dpos, timestamp, timestampErr);
            //FillHit(Hit,fDetID,fMCIndex, pos, dpos, timestamp, timestampErr);
            
            HitType* hit = new ((*fOutputContainer)[idigi]) HitType(fDetID, fMCIndex, pos, dpos);
            hit->SetTimeStamp(digi->GetTimeStamp());
            hit->SetTimeStampError(digi->GetTimeStampError());
            //fOutputContainer.push_back(Hit);
        }
    }
    
    TClonesArray* GetOutputData()
    {
        return fOutputContainer;
    }
    
  protected:
      
    TClonesArray* fOutputContainer;
};




#endif	/* DIGITOHITTASK_H */

