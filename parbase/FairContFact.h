#ifndef FAIRCONTFACT_H
#define FAIRCONTFACT_H

#include "TList.h"
#include "TNamed.h"

class FairParSet;
class FairParIo;
//class TList;

class FairContainer : public TNamed
{
  private:
    FairContainer();
    FairContainer(const FairContainer& M);
    FairContainer& operator= (const FairContainer&) {return *this;}

  protected:
    TList* contexts;       // available contexts for this parameter container
    TString actualContext; // actual context set by the user
  public:
    FairContainer( const char*, const char*, const char*);
    ~FairContainer();
    void addContext(const char*);
    Bool_t setActualContext(const char* c);
    const char* getDefaultContext();
    const char* getActualContext() { return actualContext.Data(); }
    void print();
    TString getConcatName();
    const char* getContext();
    ClassDef(FairContainer,0) // class for list elements in class FairContFact
};

class FairContFact : public TNamed
{
  public:
    FairContFact();
    virtual ~FairContFact();
    Bool_t addContext(const char* name);
    void print();
    FairParSet* getContainer(const char*);
    virtual FairParSet* createContainer(FairContainer*) {return 0;}
    virtual void activateParIo(FairParIo*) {}
  protected:
    TList* containers;   // all parameter containers managed by this factory
    const char* getActualContext(const char* name) {
      return ((FairContainer*)containers->FindObject(name))->getActualContext();
    }
    ClassDef(FairContFact,0) // base class of all factories for parameter containers
  private:
    FairContFact(const FairContFact& M);
    FairContFact& operator= (const FairContFact&) {return *this;}


};

#endif  /* !FAIRCONTFACT_H */
