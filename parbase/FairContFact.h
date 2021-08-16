/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRCONTFACT_H
#define FAIRCONTFACT_H

#include <Rtypes.h>    // for Bool_t, ClassDef, etc
#include <TList.h>     // for TList
#include <TNamed.h>    // for TNamed
#include <TString.h>   // for TString

class FairLogger;
class FairParIo;
class FairParSet;

class FairContainer : public TNamed
{
  private:
    FairContainer();
    FairContainer(const FairContainer&);
    FairContainer& operator=(const FairContainer&);

  protected:
    /** available contexts for this parameter container*/
    TList* contexts;
    /** actual context set by the user */
    TString actualContext;
    /** Fair Logger */
    FairLogger* fLogger;   //!

  public:
    FairContainer(const char*, const char*, const char*);
    ~FairContainer();
    void addContext(const char*);
    Bool_t setActualContext(const char* c);
    const char* getDefaultContext();
    const char* getActualContext() { return actualContext.Data(); }
    void print();
    TString getConcatName();
    const char* getContext();
    ClassDefOverride(FairContainer, 0);   // class for list elements in class FairContFact
};

class FairContFact : public TNamed
{
  public:
    FairContFact();
    virtual ~FairContFact();
    Bool_t addContext(const char* name);
    void print();
    FairParSet* getContainer(const char*);
    virtual FairParSet* createContainer(FairContainer*) { return 0; }
    virtual void activateParIo(FairParIo*) {}
    /// @param[in] container Transfers ownership if return value is true
    Bool_t AddContainer(FairContainer*);

  protected:
    TList* containers;   // all parameter containers managed by this factory
    const char* getActualContext(const char* name)
    {
        return (static_cast<FairContainer*>(containers->FindObject(name)))->getActualContext();
    }
    /** Fair Logger */
    FairLogger* fLogger;         //!
    ClassDefOverride(FairContFact, 0);   // base class of all factories for parameter containers

  private:
    FairContFact(const FairContFact&);
    FairContFact& operator=(const FairContFact&);
};

#endif /* !FAIRCONTFACT_H */
