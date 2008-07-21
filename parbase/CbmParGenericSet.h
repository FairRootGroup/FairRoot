#ifndef CBMPARGENERICSET_H
#define CBMPARGENERICSET_H

#include "CbmParSet.h"

class CbmParamList;

class CbmParGenericSet : public CbmParSet {
public:
  CbmParGenericSet(const char* name,const char* title,const char* context)
         : CbmParSet(name,title,context) {}
  virtual ~CbmParGenericSet() {}
  virtual Bool_t init(CbmParIo*);
  virtual Int_t write(CbmParIo*);
  virtual void putParams(CbmParamList*)=0;
  virtual Bool_t getParams(CbmParamList*)=0;
  virtual void printParams();
protected:
  CbmParGenericSet() {}
  ClassDef(CbmParGenericSet,1) // Base class for generic-style parameter containers
};

#endif  /* !CBMPARGENERICSET_H */
