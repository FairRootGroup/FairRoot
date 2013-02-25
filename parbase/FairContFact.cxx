#//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

/////////////////////////////////////////////////////////////
//
//  FairContFact
//
//  Base class of all factories for the parameter containers
//
/////////////////////////////////////////////////////////////

#include "FairContFact.h"
#include "FairRuntimeDb.h"

#include "TObjString.h"


#include <iostream>

using std::cout;

ClassImp(FairContainer)
ClassImp(FairContFact)

FairContainer::FairContainer()
  :TNamed(),
   contexts(NULL),
   actualContext(""),
   fLogger(FairLogger::GetLogger())
{
}
// Default constructor

FairContainer::FairContainer(const char* name, const char* title,
                             const char* defContext)
  : TNamed(name, title),
    contexts(new TList()),
    actualContext(""),
    fLogger(FairLogger::GetLogger())
{
  // Constructor
  // Arguments:  name       = name of the corresponding parameter container
  //             title      = title of this parameter container
  //             defContext = default context of this parameter container
  addContext(defContext);
}

FairContainer::~FairContainer()
{
  // Destructor deletes the list of accepted contexts
  if (contexts) {
    contexts->Delete();
    delete contexts;
  }
}

void FairContainer::addContext(const char* name)
{
  // Adds a context to the list of accepted contexts
  TObjString* c=new TObjString(name);
  contexts->Add(c);
}

Bool_t FairContainer::setActualContext(const char* c)
{
  // The function sets the actual context for the container, if it is in the list of
  // accepted contexts. When the actual context was already set before, it prints a warning
  // and ignores the second setting.
  // The function returns kFALSE, when the context is not in the list.
  if (contexts->FindObject(c)) {
    if (actualContext.IsNull()) { actualContext=c; }
    else Warning("addContext",
                   "Actual context of parameter container %s already defined as %s",
                   GetName(),actualContext.Data());
    return kTRUE;
  }
  return kFALSE;
}

const char* FairContainer::getDefaultContext()
{
  // Returns the default context
  return ((TObjString*)contexts->At(0))->String().Data();
}

void FairContainer::print()
{
  // prints the name, title of the container together with the actual context set
  // or all possible contexts, when the actual context was not set
  cout<<fName<<"\t"<<fTitle<<"\n";
  if (!actualContext.IsNull()) { cout<<"     actual context:  "<<actualContext<<"\n"; }
  else {
    TIter next(contexts);
    Int_t i=0;
    TObjString* c;
    cout<<"  all contexts:"<<"\n";
    while ((c=(TObjString*)next())) {
      if (c->String().IsNull()) { cout<<"     \"\""; }
      else { cout<<"     "<<c->String(); }
      if (i==0) { cout<<"\t default"; }
      cout<<"\n";
      i++;
    }
  }
}

TString FairContainer::getConcatName()
{
  // Returns the name of the parameter container used in the constructor and the
  // runtime database.
  // When the parameter container supportes different contexts (not only an empty string)
  // and the actual context set is not the default context, the new name of the parameter
  // container is concatinated as
  //      original container name  +  _  +  actualcontext
  TString cn=fName;
  if (!actualContext.IsNull() && actualContext!=((TObjString*)contexts->At(0))->String()) {
    cn+="_";
    cn+=actualContext;
  }
  return cn;
}

const char* FairContainer::getContext()
{
  // return the actual context, if set, or the default context
  if (!actualContext.IsNull()) { return actualContext.Data(); }
  else { return getDefaultContext(); }
}

//------------------------------------------------------------------

FairContFact::FairContFact()
  : TNamed(),
    containers(new TList),
    fLogger(FairLogger::GetLogger())
{
  // Constructor creates a list to store objects of type FairContainer
  //  containers=new TList;
}

FairContFact::~FairContFact()
{
  // Destructor deletes the container list and its elements
  containers->Delete();
  delete containers;
}

Bool_t FairContFact::addContext(const char* name)
{
  // Set the actual context in all containers, which accept this context
  FairContainer* c=0;
  Bool_t found=kFALSE;
  TIter next(containers);
  while ((c=(FairContainer*)next())) {
    if (c->setActualContext(name)) { found=kTRUE; }
  }
  return found;
}

FairParSet* FairContFact::getContainer(const char* name)
{
  // Returns the pointer to the parameter container in the runtime database
  // If this parameter container does not yet exit, it calls the function
  // createContainer(FairContainer*), which is implemented in the derived classes
  // and calls the corresponding constructor. Then the pointer it added in the
  // runtime database.
  FairContainer* c=(FairContainer*)(containers->FindObject(name));

  FairParSet* cont=0;
  if (c) {
    TString cn=c->getConcatName();
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!(cont=rtdb->findContainer(c->getConcatName().Data()))) {
      if (strlen(c->getActualContext())==0) { c->setActualContext(c->getDefaultContext()); }
      cont=createContainer(c);
      if (cont) { rtdb->addContainer(cont); }
    }
  }
  return cont;
}

void FairContFact::print()
{
  // Loops over all containers in the list and calls their print() function
  cout<<"---------------------------------------------------------------------------"<<"\n";
  cout<<GetName()<<":  "<<GetTitle()<<"\n";
  cout<<"---------------------------------------------------------------------------"<<"\n";
  FairContainer* c;
  TIter next(containers);
  while ((c=(FairContainer*)next())) { c->print(); }
}
