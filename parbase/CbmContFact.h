#ifndef CBMCONTFACT_H
#define CBMCONTFACT_H

#include "TList.h"
#include "TNamed.h"

class CbmParSet;
class CbmParIo;
//class TList;

class CbmContainer : public TNamed {
private:
  CbmContainer();
  CbmContainer(const CbmContainer &M);
  CbmContainer& operator= (const CbmContainer&) {return *this;}

protected:
  TList* contexts;       // available contexts for this parameter container
  TString actualContext; // actual context set by the user
public:
  CbmContainer( const char*, const char*, const char*);
  ~CbmContainer();
  void addContext(const char*);
  Bool_t setActualContext(const char* c);
  const char* getDefaultContext();
  const char* getActualContext() { return actualContext.Data(); }
  void print();
  TString getConcatName();
  const char* getContext();
  ClassDef(CbmContainer,0) // class for list elements in class CbmContFact
};

class CbmContFact : public TNamed {
public:
  CbmContFact();
  virtual ~CbmContFact();
  Bool_t addContext(const char* name);
  void print();
  CbmParSet* getContainer(const char*);
  virtual CbmParSet* createContainer(CbmContainer*) {return 0;}
  virtual void activateParIo(CbmParIo*) {}
protected:
  TList* containers;   // all parameter containers managed by this factory
  const char* getActualContext(const char* name) {
     return ((CbmContainer*)containers->FindObject(name))->getActualContext();
  }
  ClassDef(CbmContFact,0) // base class of all factories for parameter containers
private:
  CbmContFact(const CbmContFact &M);
  CbmContFact& operator= (const CbmContFact&) {return *this;}
  
  
};

#endif  /* !CBMCONTFACT_H */
