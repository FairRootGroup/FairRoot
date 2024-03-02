/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

///////////////////////////////////////////////////////////////////////////////
// FairDetParRootFileIo
//
// Interface class to ROOT file for parameter input/output
// Base class for all detectors
//
// This class is derived from the common base class FairDetParIo
// for all inputs/outputs (ROOT file, Oracle, Ascii file).
// It contains all common functionality for all detectors which can be
// implemeted without knowing the exact type of the detector or of the detector
// dependend parameter containers using only the base class types.
///////////////////////////////////////////////////////////////////////////////
#include "FairDetParRootFileIo.h"

#include "FairParRootFileIo.h"   // for FairParRootFile
#include "FairParSet.h"          // for FairParSet
#include "FairRtdbRun.h"         // for FairParVersion, FairRtdbRun
#include "FairRuntimeDb.h"       // for FairRuntimeDb

#include <TDirectory.h>   // for TDirectory, gDirectory
#include <TKey.h>         // for TKey
#include <TROOT.h>        // for TROOT, gROOT
#include <iostream>       // for operator<<, basic_ostream, etc
#include <stdio.h>        // for sprintf

using std::cout;
using std::endl;

FairDetParRootFileIo::FairDetParRootFileIo(FairParRootFile *f)
    : FairDetParIo()
    , pFile(f)
{
    // Constructor takes a pointer to the parameter ROOT file
    //  pFile=f;
}

Bool_t FairDetParRootFileIo::read(FairParSet *pPar)
{
    // generic read function for parameter containers
    auto name = pPar->GetName();
    Int_t version = findInputVersion(name);

    // cout << "-I- FairDetParRootFileIo#  " << name << " : " << version <<  endl;

    if (version <= 0) {
        pPar->setInputVersion(-1, inputNumber);
        return kFALSE;
    }

    if (pPar->getInputVersion(inputNumber) == version && pPar->getInputVersion(inputNumber) != -1) {
        return kTRUE;
    }

    TKey* key = gDirectory->GetKey(name, version);
    if (key) {
        pPar->clear();
        key->Read(pPar);
        pPar->setInputVersion(version, inputNumber);
        pPar->setChanged();
        cout << "Container " << pPar->GetName() << " initialized from ROOT file." << endl;
        return kTRUE;
    }
    pPar->setInputVersion(-1, inputNumber);
    return kFALSE;
}

Int_t FairDetParRootFileIo::write(FairParSet *pPar)
{
    // writes a parameter container to the ROOT file and returns the new version
    // number (returns -1 if the file is not writable)
    if (pFile) {
        pFile->cd();
        if (pFile->IsWritable()) {
            auto name = pPar->GetName();
            pPar->Write(name);
            pPar->setChanged(kFALSE);
            FairRuntimeDb::instance()->setVersionsChanged(kTRUE);
            return getMaxVersion(name);
        } else {
            Error(":write", "Output is not writable");
        }
    }
    Error(":write", "No output open");
    return -1;
}

Int_t FairDetParRootFileIo::getMaxVersion(const char* name)
{
    // returns the maximum version of the container given by name in the ROOT
    // file (return -1 if not found)
    TKey *key = pFile->GetKey(name);
    if (key) {
        return key->GetCycle();
    } else {
        return -1;
    }
}

Int_t FairDetParRootFileIo::findInputVersion(const char* name)
{
    // finds the input version to initialize the container given by name;
    // returns -1 if the version cannot be determined
    FairParVersion *currVers = FairRuntimeDb::instance()->getCurrentRun()->getParVersion(name);
    Int_t v = currVers->getInputVersion(inputNumber);
    if (v > 0) {
        return v;
    }   // predefined
    FairRtdbRun *r = pFile->getRun();
    // cout << "-I- FairDetParRootFileIo::findInputVersion " << r << endl;
    if (!r) {
        return -1;
    }   // run not in ROOT file
    FairParVersion *vers = r->getParVersion(name);
    if (!vers) {
        return -1;
    }   // container not in ROOT file
    return vers->getRootVersion();
}

TObject *FairDetParRootFileIo::findContainer(Text_t *name, Int_t vers)
{
    // finds the parameter container given by its name with a special version in
    // the ROOT file (returns 0 if not successful)
    // This funtion uses internally the ROOT function FindObject(Text_t*), which
    // creates a new object. The calling function must therefore delete the
    // object after usage!
    Text_t cn[80];
    sprintf(cn, "%s;%i", name, vers);
    pFile->cd();
    TObject *p = gROOT->FindObject(cn);
    return p;
}
