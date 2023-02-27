/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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

#include "FairRuntimeDb.h"   // for FairRuntimeDb

#include <TCollection.h>   // for TIter
#include <TObjString.h>
#include <cstring>   // for strlen
#include <fairlogger/Logger.h>
#include <iostream>   // for operator<<, ostream, cout, etc

using std::cout;

FairContainer::FairContainer()
    : TNamed()
    , contexts(nullptr)
    , actualContext("")
{}
// Default constructor

FairContainer::FairContainer(const char* name, const char* title, const char* defContext)
    : TNamed(name, title)
    , contexts(new TList())
    , actualContext("")
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
    auto c = new TObjString(name);
    contexts->Add(c);
}

Bool_t FairContainer::setActualContext(const char* c)
{
    // The function sets the actual context for the container, if it is in the list of
    // accepted contexts. When the actual context was already set before, it prints a warning
    // and ignores the second setting.
    // The function returns kFALSE, when the context is not in the list.
    if (contexts->FindObject(c)) {
        if (actualContext.IsNull()) {
            actualContext = c;
        } else {
            Warning("addContext",
                    "Actual context of parameter container %s already defined as %s",
                    GetName(),
                    actualContext.Data());
        }
        return kTRUE;
    }
    return kFALSE;
}

const char* FairContainer::getDefaultContext()
{
    // Returns the default context
    return (static_cast<TObjString*>(contexts->At(0)))->String().Data();
}

void FairContainer::print()
{
    // prints the name, title of the container together with the actual context set
    // or all possible contexts, when the actual context was not set
    cout << fName << "\t" << fTitle << "\n";
    if (!actualContext.IsNull()) {
        cout << "     actual context:  " << actualContext << "\n";
    } else {
        TIter next(contexts);
        Int_t i = 0;
        TObjString* c;
        cout << "  all contexts:"
             << "\n";
        while ((c = static_cast<TObjString*>(next()))) {
            if (c->String().IsNull()) {
                cout << "     \"\"";
            } else {
                cout << "     " << c->String();
            }
            if (i == 0) {
                cout << "\t default";
            }
            cout << "\n";
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
    TString cn = fName;
    if (!actualContext.IsNull() && actualContext != (static_cast<TObjString*>(contexts->At(0)))->String()) {
        cn += "_";
        cn += actualContext;
    }
    return cn;
}

const char* FairContainer::getContext()
{
    // return the actual context, if set, or the default context
    if (!actualContext.IsNull()) {
        return actualContext.Data();
    } else {
        return getDefaultContext();
    }
}

FairContFact::FairContFact()
    : TNamed()
{}

FairContFact::FairContFact(const char* name, const char* title)
    : TNamed(name, title)
{
    FairRuntimeDb::instance()->addContFactory(this);
}

FairContFact::~FairContFact()
{
    // Destructor deletes the container list and its elements
    FairRuntimeDb::instance()->removeContFactory(this);
    containers->Delete();
    delete containers;
}

Bool_t FairContFact::addContext(const char* name)
{
    // Set the actual context in all containers, which accept this context
    FairContainer* c = nullptr;
    Bool_t found = kFALSE;
    TIter next(containers);
    while ((c = static_cast<FairContainer*>(next()))) {
        if (c->setActualContext(name)) {
            found = kTRUE;
        }
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
    auto c = static_cast<FairContainer*>((containers->FindObject(name)));

    FairParSet* cont = nullptr;
    if (c) {
        TString cn = c->getConcatName();
        FairRuntimeDb* rtdb = FairRuntimeDb::instance();
        if (!(cont = rtdb->findContainer(c->getConcatName().Data()))) {
            if (strlen(c->getActualContext()) == 0) {
                c->setActualContext(c->getDefaultContext());
            }
            cont = createContainer(c);
            if (cont) {
                rtdb->addContainer(cont);
            }
        }
    }
    return cont;
}

void FairContFact::print()
{
    // Loops over all containers in the list and calls their print() function
    cout << "---------------------------------------------------------------------------"
         << "\n";
    cout << GetName() << ":  " << GetTitle() << "\n";
    cout << "---------------------------------------------------------------------------"
         << "\n";
    FairContainer* c;
    TIter next(containers);
    while ((c = static_cast<FairContainer*>(next()))) {
        c->print();
    }
}

Bool_t FairContFact::AddContainer(FairContainer* cont)
{
    // Check if a container already exist in the List of containers
    // If it alread exist print an error message and return kFALSE
    // such that the user can handle the issue
    if (nullptr != containers->FindObject(cont)) {
        LOG(error) << "The container " << cont->GetName() << " already exist in the "
                   << "container factory " << GetName() << ".\n"
                   << "Duplicate container is not added.";
        return kFALSE;
    }

    containers->Add(cont);
    return kTRUE;
}
