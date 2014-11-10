/* 
 * File:   BaseBaseDigiToHitTask.h
 * Author: winckler
 *
 * Created on December 8, 2014, 2:40 PM
 */

#ifndef BASEDIGITOHIT_H
#define	BASEDIGITOHIT_H

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

// FairRoot - Tutorial3
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorHit.h"
#include "FairTestDetectorPayload.h"


////////////////////////////////////////////////////////////////////////////////////
// below are some struct which checks whether type T derived 
// from tutorial3 or tutorial 7 data class/payload
// Note : better would be to check the API...
template <typename T>
    struct AllowedNonPodType
    {
        template <typename U>
            static constexpr bool testType()
            {
                return 
                        std::is_base_of<MyDigi,U>::value ||
                        std::is_base_of<MyHit,U>::value ||
                        std::is_base_of<FairTestDetectorDigi,U>::value ||
                        std::is_base_of<FairHit,U>::value;
            }
        static constexpr bool value = testType<T>();
    };

template <typename T>
    struct AllowedPodType
    {
        template <typename U>
            static constexpr bool testType()
            {
                return 
                        std::is_base_of<MyPodData::Digi,U>::value ||
                        std::is_base_of<MyPodData::Hit,U>::value ||
                        std::is_base_of<TestDetectorPayload::Digi,U>::value ||
                        std::is_base_of<TestDetectorPayload::Hit,U>::value;
            }
        static constexpr bool value = testType<T>();
    };

    
    
    
// use of the checks struct into std::enable_if, to enable the corresponding implementations
template<typename T>
    using enable_if_AllowedType = typename std::enable_if<AllowedNonPodType<T>::value,int>::type;

template<typename T>
    using enable_if_AllowedPodType = typename std::enable_if<AllowedPodType<T>::value,int>::type;



////////////////////////////////////////////////////////////////////////////////////
// the base class
template <typename DigiType, typename HitType>
class BaseDigiToHitTask
{
  public:
      
   
    BaseDigiToHitTask() : fTaskName(), fDetID(-1), fMCIndex(-1)
    {}
    
    virtual ~BaseDigiToHitTask()
    {}
    
  protected:
      
    std::string fTaskName;
    Int_t fDetID;
    Int_t fMCIndex;
    
    template < typename T=DigiType, enable_if_AllowedType<T> = 0 >
        void ProcessDigi(const DigiType &Digi, TVector3 &pos, TVector3 &dpos, Double_t &t, Double_t &t_err)
        {
            pos.SetXYZ(Digi.GetX() + 0.5, Digi.GetY() + 0.5, Digi.GetZ() + 0.5);
            dpos.SetXYZ(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));
            t=Digi.GetTimeStamp();
            t_err=Digi.GetTimeStampError();
        }
    
    template < typename T=DigiType, enable_if_AllowedPodType<T> = 0  >
        void ProcessDigi(const DigiType &Digi, TVector3 &pos, TVector3 &dpos, Double_t &t, Double_t &t_err)
        {
            pos.SetXYZ(Digi.fX + 0.5, Digi.fY + 0.5, Digi.fZ + 0.5);
            dpos.SetXYZ(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));
            t=Digi.fTimeStamp;
            t_err=Digi.fTimeStampError;
        }
    
    template < typename T=HitType, enable_if_AllowedType<T> = 0 >
        void FillHit(HitType &Hit, const Int_t &detID, const Int_t &MCIndex, const TVector3 &pos, const TVector3 &dpos, const Double_t &t, const Double_t &t_err)
        {
            Hit.SetDetectorID(detID);
            Hit.SetRefIndex(MCIndex);
            Hit.SetPosition(pos);
            Hit.SetPositionError(dpos);
            Hit.SetTimeStamp(t);
            Hit.SetTimeStampError(t_err);
        }
    
    template < typename T=HitType, enable_if_AllowedPodType<T> = 0 >
        void FillHit(HitType &Hit, const Int_t &detID, const Int_t &MCIndex, const TVector3 &pos, const TVector3 &dpos, const Double_t &t, const Double_t &t_err)
        {
            Hit.detID=detID;
            Hit.mcindex=MCIndex;
            
            Hit.fTimeStamp=t;
            Hit.fTimeStampError=t_err;
            
            Hit.posX=pos.X();
            Hit.posY=pos.Y();
            Hit.posZ=pos.Z();
            
            Hit.dposX=dpos.X();
            Hit.dposY=dpos.Y();
            Hit.dposZ=dpos.Z();
        }
    
};




#endif	/* BASEDIGITOHIT_H */

