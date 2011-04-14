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

class BinaryFunctor : public std::binary_function<double,double,bool>
{
  public :
    virtual bool operator() (double a, double b) = 0;
    virtual bool Call(double a, double b) = 0;
};

class StopTime : public BinaryFunctor
{
  public :
    bool operator() (double a, double b) {Call(a, b);};
    bool Call(double a, double b) {return a > b;};
};

class TimeGap : public BinaryFunctor
{
  public:
    TimeGap():fOldTime(-1.) {};
    bool operator()(double a, double b) {
      return Call(a, b);
    }

    bool Call(double a, double b) {
      if (fOldTime < 0) {
        fOldTime = a;
        return false;
      }
      if (a - fOldTime > b) {
        fOldTime = a;
        return true;
      } else {
        fOldTime = a;
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

    ClassDef(FairTSBufferFunctional,0);

};


#endif
