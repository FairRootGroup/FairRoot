#ifndef FAIRPARGENERICSET_H
#define FAIRPARGENERICSET_H

#include "FairParSet.h"

class FairParamList;
class FairDetParIo;
class FairParIo;

class FairParGenericSet : public FairParSet
{
  public:
    FairParGenericSet(const char* name,const char* title,const char* context)
      : FairParSet(name,title,context) {}
    virtual ~FairParGenericSet() {}
    virtual void putParams(FairParamList*)=0;
    virtual Bool_t getParams(FairParamList*)=0;
    virtual void printParams();

    Bool_t init(FairParIo* inp);
    Int_t  write(FairParIo* output);


  protected:
    FairParGenericSet()
      : FairParSet() {}
    ClassDef(FairParGenericSet,1) // Base class for generic-style parameter containers
};

#endif  /* !FAIRPARGENERICSET_H */
