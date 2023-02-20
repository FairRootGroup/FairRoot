/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 20/10/2004

///////////////////////////////////////////////////////////////////
//  FairRun
//
//  class for the parameter versions of an event file
//
//  The name of each run is the run id converted to a string.
//  The run id number identifies the event file.
//  In the parameter ROOT file the valid parameter versions are
//  accessible via the name.
//  Associated with the run is a list of container
//  names with the versions of the containers in the two
//  possible inputs and the output (class FairParVersions).
//  The input versions are used during the initialisation
//  used during the initialisation of the containers.
///////////////////////////////////////////////////////////////////
#include "FairRtdbRun.h"

#include <TCollection.h>   // for TIter
#include <TList.h>         // for TList
#include <fstream>         // for fstream
#include <iomanip>         // for setw, operator<<
#include <iostream>        // for cout

using std::cout;
using std::ios;
using std::setw;

ClassImp(FairParVersion);
ClassImp(FairRtdbRun);

FairParVersion::FairParVersion(const char* name)
    : TNamed(name, "version info")
    , rootVersion(0)
{
    // constructor with the name of the container
    //  rootVersion=0;
    for (Int_t i = 0; i < 3; i++) {
        inputVersions[i] = -1;
    }
}

FairRtdbRun::FairRtdbRun(const Text_t* name, const Text_t* refName)
    : TNamed(name, "run parameters")
    , parVersions(new TList())
    , refRun(refName)
{
    // constructor with the run id and reference run as strings
    //  parVersions=new TList();
    //  refRun=refName;
}

FairRtdbRun::FairRtdbRun(Int_t r, Int_t rr)
    //  :TNamed(r,""),
    : TNamed()
    , parVersions(new TList())
    , refRun("")
{
    char name[255];
    sprintf(name, "%i", r);
    SetName(name);
    setRefRun(rr);
}

FairRtdbRun::FairRtdbRun(FairRtdbRun& run)
    : TNamed(run)
    , parVersions(new TList())
    , refRun(run.refRun)
{
    // copy constructor
    TList* lv = run.getParVersions();
    TIter next(lv);
    FairParVersion* pv;
    while ((pv = static_cast<FairParVersion*>(next()))) {
        parVersions->Add(pv);
    }
}

FairRtdbRun::FairRtdbRun()
    : TNamed()
    , parVersions(NULL)
    , refRun("")
{
    // default Constructor
    // parVersions has to be set to zero otherwise the
    // root file is not browsable
}

FairRtdbRun::~FairRtdbRun()
{
    // destructor
    if (parVersions) {
        parVersions->Delete();
        delete parVersions;
        parVersions = 0;
    }
}

void FairRtdbRun::addParVersion(FairParVersion* pv)
{
    // adds a container version object to the list
    parVersions->Add(pv);
}

FairParVersion* FairRtdbRun::getParVersion(const Text_t* name)
{
    // return a container version object called by the name of
    // the container
    return static_cast<FairParVersion*>(parVersions->FindObject(name));
}

void FairRtdbRun::resetInputVersions()
{
    TIter next(parVersions);
    FairParVersion* v;
    while ((v = static_cast<FairParVersion*>(next()))) {
        v->resetInputVersions();
    }
}

void FairRtdbRun::resetOutputVersions()
{
    TIter next(parVersions);
    FairParVersion* v;
    while ((v = static_cast<FairParVersion*>(next()))) {
        v->setRootVersion(0);
    }
}

void FairRtdbRun::print()
{
    // prints the list of container versions for this run
    cout << "run: " << GetName() << '\n';
    FairParVersion* v;
    TIter next(parVersions);
    while ((v = static_cast<FairParVersion*>(next()))) {
        cout.setf(ios::left, ios::adjustfield);
        cout << "  " << setw(45) << v->GetName();
        cout.setf(ios::right, ios::adjustfield);
        cout << setw(11) << v->getInputVersion(1) << setw(11) << v->getInputVersion(2) << setw(11)
             << v->getRootVersion() << '\n';
    }
}

void FairRtdbRun::write(std::fstream& fout)
{
    // writes the list of container versions for this run to fstream
    fout << "run: " << GetName() << '\n';
    FairParVersion* v;
    TIter next(parVersions);
    while ((v = static_cast<FairParVersion*>(next()))) {
        fout.setf(ios::left, ios::adjustfield);
        fout << "  " << setw(45) << v->GetName();
        fout.setf(ios::right, ios::adjustfield);
        fout << setw(11) << v->getInputVersion(1) << setw(11) << v->getInputVersion(2) << setw(11)
             << v->getRootVersion() << '\n';
    }
}
