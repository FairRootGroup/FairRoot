/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004
//*-- Modified: 21/06/2005  Denis bertini

//////////////////////////////////////////////////////////////////////////////
// FairParRootFileIo
//
// Interface class for parameter I/O from/to ROOT file
// derived from interface base class FairParIo.
//
// It contains a pointer to the "connection class" of type FairParRootFile
// inherited from TFile.  FairParRootFile contains an object of type FairRtdbRun
// which holds the list of container versions for an event file.
//
// It contains also a list of detector interface classes all having the common
// base type FairDetParRootFileIo. Every detector has its own interface class.
//////////////////////////////////////////////////////////////////////////////
#include "FairParRootFileIo.h"

#include "FairDetParIo.h"    // for FairDetParIo
#include "FairRtdbRun.h"     // for FairRtdbRun
#include "FairRuntimeDb.h"   // for FairRuntimeDb

#include <TCollection.h>   // for TIter
#include <TDatime.h>       // for TDatime
#include <TKey.h>          // for TKey
#include <TList.h>         // for TListIter, TList
#include <TObjString.h>    // for TObjString
#include <TObject.h>       // for TObject
#include <TString.h>       // for TString, Form
#include <iostream>        // for operator<<, basic_ostream, etc

using std::cerr;
using std::cout;
using std::endl;

ClassImp(FairParRootFile);
ClassImp(FairParRootFileIo);

FairParRootFile::FairParRootFile(const Text_t* fname, Option_t* option, const Text_t* ftitle, Int_t compress)
    : TNamed(fname, ftitle)
    , run(nullptr)
    , RootFile(TFile::Open(fname, option, ftitle, compress))
{
    //              : TFile(fname,option,ftitle,compress) {
    // constructor opens a ROOT file
    //  RootFile=TFile::Open(fname,option,ftitle,compress);
    // run=0;
}

FairParRootFile::FairParRootFile(TFile* f)
    : TNamed(f->GetName(), f->GetTitle())
    , run(nullptr)
    , RootFile(f)
{
    //  :TFile(f->GetName(),"UPDATE"){
    // constructor opens a ROOT file
    // RootFile=TFile::Open(f->GetName(),"UPDATE");
    //  RootFile=f;
    //  run=0;
}

FairParRootFile::~FairParRootFile()
{
    // destructor
    delete run;
    run = 0;
    // TODO: What about the file? Should it be closed or not
}

void FairParRootFile::readVersions(FairRtdbRun* currentRun)
{
    // finds the current run containing the parameter container versions
    // in the ROOT file
    delete run;

    run = static_cast<FairRtdbRun*>(RootFile->Get((const_cast<char*>(currentRun->GetName()))));
    // cout << "-I- FairParRootFile :: readversions " << currentRun->GetName() << " : " << run << endl;
}

FairParRootFileIo::FairParRootFileIo()
    : FairParIo()
    , file(nullptr)
    , fMerging(kFALSE)
{
    // constructor
    //  file=0;
    //  fMerging=kFALSE;
}

FairParRootFileIo::FairParRootFileIo(Bool_t merged)
    : FairParIo()
    , file(nullptr)
    , fMerging(merged)
{
    // constructor
    //  file=0;
    //  fMerging=merged;
}

FairParRootFileIo::~FairParRootFileIo()
{
    // destructor closes an open file
    close();
}

Bool_t FairParRootFileIo::open(const Text_t* fname, Option_t* option, const Text_t* ftitle, Int_t compress)
{
    // It opens a ROOT file (default option "READ"). An open file will be closed.
    // The detector I/Os for all detectors defined in the setup are activated.

    // DB, lock file for NFS in case of mulitple access
    // gDirectory->ReadKeys();
    close();
    if (fMerging) {
        // used test merging
        std::fstream* f = new std::fstream(fname);
        if (f->good()) {
            // check if file already exists
            option = "UPDATE";
        } else {
            // if file doesn't exist recreate option is used
            option = "RECREATE";
        }
        f->close();
        delete f;
    }

    file = new FairParRootFile(fname, option, ftitle, compress);

    if (file && file->IsOpen()) {
        filename = fname;
        FairRuntimeDb::instance()->activateParIo(this);
        return kTRUE;
    }
    cerr << "-E- Could not open input file " << fname << endl;
    Fatal("open", "Could not open input file");
    return kFALSE;
}

Bool_t FairParRootFileIo::open(const TList* fnamelist, Option_t* option, const Text_t* ftitle, Int_t compress)
{
    TDatime currentDate;
    TString newParFileName = "";
    TFile* newParFile = 0;

    TObjString* string;
    TListIter myIter(fnamelist);

    TKey* inpKey;

    TFile* inFile;

    Int_t nofFiles = 0;
    while ((string = static_cast<TObjString*>(myIter.Next()))) {
        inFile = TFile::Open(string->GetString().Data());
        if (!inFile) {
            cout << "-W- File \"" << string->GetString().Data() << "\" does not exist" << endl;
            continue;
        }

        if (nofFiles == 0) {
            newParFileName = string->GetString();
            newParFileName.Replace(newParFileName.Last('/') + 1, newParFileName.Length(), "");
            newParFileName =
                Form("%sallParams_%d_%06d.root", newParFileName.Data(), currentDate.GetDate(), currentDate.GetTime());
            newParFile = TFile::Open(newParFileName.Data(), "RECREATE");
        }

        TList* inputKeys = static_cast<TList*>(inFile->GetListOfKeys());

        TListIter keyIter(inputKeys);
        while ((inpKey = static_cast<TKey*>(keyIter.Next()))) {
            TObject* tempObj = inFile->Get(inpKey->GetName());

            newParFile->cd();
            tempObj->Write();
        }
        inFile->Close();

        nofFiles++;
    }
    if (newParFile != 0) {
        newParFile->Close();
    } else {
        std::cout << "****NO file to close file = \"" << std::endl;
    }
    std::cout << "**** merged file = \"" << newParFileName.Data() << "\"" << std::endl;

    return this->open(newParFileName, option, ftitle, compress);
}

Bool_t FairParRootFileIo::open(TFile* f)
{
    // It opens a ROOT file (default option "READ"). An open file will be closed.
    // The detector I/Os for all detectors defined in the setup are activated.
    // close();
    file = new FairParRootFile(f);
    if (file && file->IsOpen()) {
        filename = file->GetName();
        FairRuntimeDb::instance()->activateParIo(this);
        return kTRUE;
    }
    return kFALSE;
}

void FairParRootFileIo::close()
{
    // closes an open ROOT file and deletes the detector I/Os
    if (file) {
        file->Close();
        delete file;
        file = 0;
    }
    if (detParIoList) {
        detParIoList->Delete();
    }
}

void FairParRootFileIo::print()
{
    // prints the content of a open ROOT file and the list of detector I/Os
    if (file) {
        file->ls();
        TIter next(detParIoList);
        FairDetParIo* io;
        cout << "Root file I/O " << file->GetName() << " is open\n";
        cout << "detector I/Os: ";
        while ((io = static_cast<FairDetParIo*>(next()))) {
            cout << " " << io->GetName();
        }
        cout << '\n';
    } else {
        cout << "No ROOT file open\n";
    }
}

FairParRootFile* FairParRootFileIo::getParRootFile()
{
    // returns a pointer to the current ROOT file
    return file;
}

void FairParRootFileIo::readVersions(FairRtdbRun* currentRun)
{
    // reads the parameter container versions for the current run from
    // the ROOT file
    if (file) {
        file->readVersions(currentRun);
    }
}

TList* FairParRootFileIo::getKeys()
{
    // returns the list of keys found in the ROOT file
    if (file) {
        return file->GetListOfKeys();
    }
    return 0;
}
