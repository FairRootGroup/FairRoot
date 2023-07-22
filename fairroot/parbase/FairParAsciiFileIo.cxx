/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

///////////////////////////////////////////////////////////////////////////////
// FairParAsciiFileIo
//
// Interface class for parameter I/O from ASCII file
// derived from the interface base class FairParIo
//
// It contains pointers to the ascii file and to the interface classes for all
// detectors defined in the actual setup.
///////////////////////////////////////////////////////////////////////////////
#include "FairParAsciiFileIo.h"

#include "FairGenericParAsciiFileIo.h"
#include "FairRuntimeDb.h"   // for FairRuntimeDb

#include <TCollection.h>   // for TIter
#include <TList.h>         // for TList, TListIter
#include <TObjString.h>    // for TObjString
#include <TString.h>       // for TString, operator<<
#include <TSystem.h>       // for TSystem, gSystem
#include <cstring>         // for strcmp
#include <fairlogger/Logger.h>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

void FairParAsciiFileIo::ActivateSelf()
{
    if (getDetParIo("FairGenericParIo")) {
        return;
    }
    auto pn = new FairGenericParAsciiFileIo(getFile());
    setDetParIo(pn);
}

Bool_t FairParAsciiFileIo::open(const Text_t* fname, const Text_t* status)
{
    // opens file
    // if a file is already open, this file will be closed
    // activates detector I/Os
    close();
    if ((strcmp(status, "in") != 0) && (strcmp(status, "out") != 0)) {
        cout << "Put the right stream option for file " << fname
             << "\n  writing state : out\n   reading state : in  \nopen  aborted \n";
        return kFALSE;
    }
    if (strcmp(status, "in") == 0) {
        file.open(fname, std::ios::in);
    };
    if (strcmp(status, "out") == 0) {
        file.open(fname, std::ios::out);
    };
    if (file.is_open()) {
        filename = fname;
        ActivateSelf();
        FairRuntimeDb::instance()->activateParIo(this);
        return kTRUE;
    }
    cerr << "-E- Could not open input file " << fname << endl;
    Fatal("open", "Could not open input file");
    return kFALSE;
}

Bool_t FairParAsciiFileIo::open(const TList* fnamelist, const Text_t* status)
{
    if (0 == fnamelist->GetEntries()) {
        LOG(error) << "The defined list of parameter files is empty. There are no parameters initialized from the "
                      "ASCII files.";
        return kFALSE;
    }
    TString outFileName = gSystem->WorkingDirectory();

    outFileName += "/all_";
    Int_t pid = gSystem->GetPid();
    outFileName += pid;
    outFileName += ".par";

    MergeFiles(outFileName, fnamelist);

    return open(outFileName, status);
}

void FairParAsciiFileIo::MergeFiles(const char* fname, const TList* fnamelist)
{
    TString catCommand = "cat ";
    TObjString* string;
    TListIter myIter(fnamelist);
    while ((string = static_cast<TObjString*>(myIter.Next()))) {
        // check if the file exist
        // if file exist return value is false
        TString strParPath = string->GetString();
        gSystem->ExpandPathName(strParPath);
        if (gSystem->AccessPathName(strParPath))
            LOG(fatal) << "Parameter file " << strParPath << " does not exist.";
        catCommand += string->GetString();
        catCommand += " ";
    }
    catCommand += "> ";
    catCommand += fname;

    gSystem->Exec(catCommand);
}

void FairParAsciiFileIo::close()
{
    file.close();
    FairParIo::close();
}

void FairParAsciiFileIo::print()
{
    // prints information about the file and the detector I/Os
    if (check()) {
        cout << "Ascii I/O " << filename << " is open\n";
        FairParIo::print();
    } else {
        cout << "No file open\n";
    }
}
