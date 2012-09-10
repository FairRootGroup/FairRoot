/*
 * FairMCResult.h
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#ifndef FAIRMCRESULT_H_
#define FAIRMCRESULT_H_

#include "FairMCObject.h"

//#include <TObject.h>
//#include <vector>
//#include <string>

#include<iostream>

class FairMCResult: public FairMCObject {
 public:
  FairMCResult();
  FairMCResult(Int_t start, Int_t stop);
  FairMCResult(const FairMCResult& result)
    : FairMCObject(result.GetStartType(), result.GetEntryVector()),
      fStartType(result.GetStartType()),
      fStopType(result.GetStopType())
    {
    }

  virtual ~FairMCResult();

  void SetStartType(Int_t start){fStartType = start;}
  void SetStopType(Int_t stop){fStopType = stop;}
  
  Int_t GetStartType(void) const {return fStartType;}
  Int_t GetStopType(void) const {return fStopType;}
  
  void operator=(const FairMCResult& result){
    fStartType = result.GetStartType();
    fStopType = result.GetStopType();
    SetStage(result.GetEntryVector());
  }
  
  virtual void Print(std::ostream& out = std::cout){ out << *this;}
  
  friend std::ostream& operator<< (std::ostream& out, const FairMCResult& result){
    out << "MC Link from: " << result.GetStartType() << " to "  << result.GetStopType() << ":" << std::endl;
    ((FairMCObject)result).Print(out);
    return out;
  }


private:
  Int_t fStartType;
  Int_t fStopType;
  
  ClassDef(FairMCResult, 2);
};

#endif /* FairMCResult_H_ */
