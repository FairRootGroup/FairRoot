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

};

class StopTime : public BinaryFunctor
{
  public :
    bool Call(FairTimeStamp* a, double b) {return a->GetTimeStamp() > b;};
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
    FairTSBufferFunctional(TString branchName, TTree* sourceTree);

    virtual ~FairTSBufferFunctional() {};
    TClonesArray* GetData(BinaryFunctor* function, Double_t parameter);
    Bool_t AllDataProcessed();


  private:
    void ReadInNextFilledEntry();
    void ReadInNextEntry();

    TClonesArray* fOutputArray;
    TClonesArray* fBufferArray;
    TClonesArray* fInputArray;

    TBranch* fBranch;
    Int_t fBranchIndex;

    Int_t fVerbose;

    FairTSBufferFunctional(const FairTSBufferFunctional&);
    FairTSBufferFunctional& operator=(const FairTSBufferFunctional&);

    ClassDef(FairTSBufferFunctional,0);

};


#endif
