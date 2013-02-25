#ifndef NEWPARAMETERCONTAINER_H
#define NEWPARAMETERCONTAINER_H

#include "FairParGenericSet.h"

class FairParamList;

class NewParameterContainer : public FairParGenericSet
{
  public:

    NewParameterContainer(const char* name="NewParameterContainer",
                          const char* title="NewParameterContainer Parameters",
                          const char* context="TestDefaultContext");
    ~NewParameterContainer(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

  private:
    NewParameterContainer(const NewParameterContainer&);
    NewParameterContainer& operator=(const NewParameterContainer&);

    ClassDef(NewParameterContainer,1)
};

#endif
