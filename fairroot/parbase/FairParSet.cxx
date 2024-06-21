/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 20/10/2004

/////////////////////////////////////////////////////////////
//  FairParSet
//
//  Base class for all parameter containers
/////////////////////////////////////////////////////////////
#include "FairParSet.h"

#include "FairRuntimeDb.h"   // for FairRuntimeDb

#include <fairlogger/Logger.h>
#include <iostream>   // for operator<<, ostream, etc

using std::cout;

FairParSet::FairParSet(const char* name, const char* title, const char* context, Bool_t owner)
    : TObject()
    , fName(name)
    , fTitle(title)
    , detName("")
    , versions()
    , status(kFALSE)
    , changed(kFALSE)
    , owned(owner)
    , paramContext(context)
    , author("")
    , description("")
{
    for (int i = 0; i < 3; i++) {
        versions[i] = -1;
    }
}

bool FairParSet::CallInitIO(FairParIo* io, const char* context)
{
    if (!io) {
        return false;
    }
    bool retval = init(io);
    if (!retval) {
        LOGP(warn, "{}({})::init(io) failed for {}", ClassName(), GetName(), context);
    }
    return retval;
}

Bool_t FairParSet::init()
{
    // intitializes the container from an input in run time
    // database. If this is not successful it is initialized from
    // the second input. If this failes too, it returns an error.
    // (calls internally the init function in the derived class)
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    if (!rtdb) {
        LOG(error) << "FairParSet::init()/" << GetName() << ": No RTDB";
        return false;
    }

    bool allFound = CallInitIO(rtdb->getFirstInput(), "first input");
    if (allFound) {
        setInputVersion(-1, 2);
        return allFound;
    }

    allFound = CallInitIO(rtdb->getSecondInput(), "second input");

    return allFound;
}

Int_t FairParSet::write()
{
    // writes the container to the output defined in the runtime database
    // returns the output version in the ROOT file
    // returns -1 if error occured
    // (calls internally the init function in the derived class)
    FairParIo* output = FairRuntimeDb::instance()->getOutput();
    if (output) {
        return write(output);
    }
    LOG(error) << "write() " << GetName() << " could not be written to output";
    return -1;
}

void FairParSet::print()
{
    // prints information about container (versions,status,hasChanged...)
    LOG(info) << "-----  " << GetName() << "  -----";
    if (!paramContext.IsNull()) {
        LOG(info) << "Context/Purpose:       " << paramContext;
    }
    if (!author.IsNull()) {
        LOG(info) << "Author:                " << author;
    }
    if (!description.IsNull()) {
        LOG(info) << "Description:           " << description;
    }
    LOG(info) << "first input version:   " << versions[1];
    LOG(info) << "second input version:  " << versions[2];
    LOG(info) << "has" << (changed ? "" : " not") << " changed";
    LOG(info) << "is" << (status ? "" : " not") << " static";
}

void FairParSet::clear()
{
    status = false;
    resetInputVersions();
}

void FairParSet::resetInputVersions()
{
    // resets the input versions if the container is not static
    if (!status) {
        for (int i = 0; i < 3; i++) {
            versions[i] = -1;
        }
        changed = false;
    }
}

FairParSet::FairParSet(const FairParSet& from)
    : TObject(from)
    , fName(from.fName)
    , fTitle(from.fTitle)
    , detName(from.detName)
    , versions()
    , status(from.status)
    , changed(from.changed)
    , owned(from.owned)
    , paramContext(from.paramContext)
    , author(from.author)
    , description(from.description)
{
    /*
 fName    = from.fName;
 fTitle   = from.fTitle;
 detName  = from.detName;
*/
    for (int i = 0; i < 3; i++)
        versions[i] = from.versions[i];
    /*
 status   = from.status;
 changed  = from.changed;
 owned    = from.owned;
 paramContext = from.paramContext;
 author       = from.author;
 description  = from.description;
*/
}

FairParSet& FairParSet::operator=(const FairParSet& from)
{
    if (this == &from) {
        return *this;
    }

    TObject::operator=(from);
    fName = from.fName;
    fTitle = from.fTitle;
    detName = from.detName;
    for (Int_t i = 0; i < 3; i++)
        versions[i] = from.versions[i];
    status = from.status;
    changed = from.changed;
    owned = from.owned;
    paramContext = from.paramContext;
    author = from.author;
    description = from.description;

    return *this;
}
