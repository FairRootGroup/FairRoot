/*
 * FairTSBufferFunctionalFunctional.h
 *
 *  Created on: Feb 18, 201
 *      Author: stockman
 */

#ifndef FairTSBufferFunctionalFunctional_H_
#define FairTSBufferFunctionalFunctional_H_

#include "FairTimeStamp.h"

#include "TObject.h"
#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"

#include <functional>

class BinaryFunctor : public std::binary_function<FairTimeStamp* ,double, bool>
{
  public :
    virtual bool operator() (FairTimeStamp* a, double b) {return Call(a,b);};
    virtual bool Call(FairTimeStamp* a, double b) = 0;
    virtual bool TimeOut() {return false;}

};

class StopTime : public BinaryFunctor
{
  public :
    StopTime():fRequestTime(-1), fOldTime(-1), fSameTimeRequestCounter(0) {};
    bool Call(FairTimeStamp* a, double b) {fRequestTime = b; return a->GetTimeStamp() > b;};
    bool TimeOut() {
      if (fRequestTime > fOldTime) {
        fOldTime = fRequestTime;
        fSameTimeRequestCounter = 0;
        std::cout << "RequestedTime: " << fRequestTime << std::endl;
        return false;
      } else if (fRequestTime == fOldTime) {
        std::cout << "-I- FairTSBufferFunctional StopTime has requested the same data as before: " << fRequestTime << std::endl;
        fSameTimeRequestCounter++;
      } else {
        std::cout << "-E- FairTSBufferFunctional StopTime Functor has requested time " << fRequestTime << " smaller than old time " << fOldTime << std::endl;
        return true;
      }
      if (fSameTimeRequestCounter > 9) {
        return true;
      } else { return false; }
    }

  private :
    double fRequestTime;
    double fOldTime;
    int fSameTimeRequestCounter;
};

class TimeGap : public BinaryFunctor
{
  public:
    TimeGap():fOldTime(-1.) {};



    bool Call(FairTimeStamp* a, double b) {
      double aTime = a->GetTimeStamp();

      if (fOldTime < 0) {
        fOldTime = aTime;
        return false;
      }
      if (aTime - fOldTime > b) {
        fOldTime = aTime;
        return true;
      } else {
        fOldTime = aTime;
        return false;
      }
    };


  private:
    double fOldTime;
};


class FairTSBufferFunctional : public TObject
{

  public:
    FairTSBufferFunctional(TString branchName, TTree* sourceTree, BinaryFunctor* function);

    virtual ~FairTSBufferFunctional() {};
    TClonesArray* GetData(Double_t parameter);
    void SetFunction(BinaryFunctor* function) {fFunction=function;}
    Bool_t AllDataProcessed();
    Bool_t TimeOut() {return fFunction->TimeOut();}


  private:
    void ReadInNextFilledEntry();
    void ReadInNextEntry();

    TClonesArray* fOutputArray;
    TClonesArray* fBufferArray;
    TClonesArray* fInputArray;

    BinaryFunctor* fFunction;

    TBranch* fBranch;
    Int_t fBranchIndex;

    Int_t fVerbose;

    FairTSBufferFunctional(const FairTSBufferFunctional&);
    FairTSBufferFunctional& operator=(const FairTSBufferFunctional&);

    ClassDef(FairTSBufferFunctional,0);

};


#endif
