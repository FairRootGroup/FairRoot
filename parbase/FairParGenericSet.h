#ifndef CBMPARGENERICSET_H
#define CBMPARGENERICSET_H

#include "FairParSet.h"

class FairParamList;

class FairParGenericSet : public FairParSet {
public:
  FairParGenericSet(const char* name,const char* title,const char* context)
         : FairParSet(name,title,context) {}
  virtual ~FairParGenericSet() {}
  virtual Bool_t init(FairParIo*);
  virtual Int_t write(FairParIo*);
  virtual void putParams(FairParamList*)=0;
  virtual Bool_t getParams(FairParamList*)=0;
  virtual void printParams();
protected:
  FairParGenericSet() {}
  ClassDef(FairParGenericSet,1) // Base class for generic-style parameter containers
};

#endif  /* !CBMPARGENERICSET_H */
