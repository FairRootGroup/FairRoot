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

#include <TCollection.h>         // for TIter
#include <TDatime.h>             // for TDatime
#include <TDirectory.h>          // for TDirectory::TContext
#include <TKey.h>                // for TKey
#include <TList.h>               // for TListIter, TList
#include <TObjString.h>          // for TObjString
#include <TObject.h>             // for TObject
#include <TString.h>             // for TString, Form
#include <fairlogger/Logger.h>   // for LOG
#include <iostream>              // for operator<<, basic_ostream, etc
#include <memory>                // for std::unique_ptr

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

    run = RootFile->Get<FairRtdbRun>(currentRun->GetName());
    if (!run) {
        LOG(warning) << "FairParRootFile::readVersions(" << RootFile->GetName() << "): Reading run "
                     << currentRun->GetName() << " failed";
    }
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

/**
 * \brief Combine a list of parfiles into one, and open it
 * \warning Creation of the allParams file has a race condition.
 *   Create the filename yourself, then use \ref MergeFiles,
 *   and finally \ref open.
 */
Bool_t FairParRootFileIo::open(const TList* fnamelist, Option_t* option, const Text_t* ftitle, Int_t compress)
{
    TDatime currentDate;
    TString newParFileName = "";
    std::unique_ptr<TFile> newParFile;

    TObjString* string;
    TListIter myIter(fnamelist);
    while ((string = static_cast<TObjString*>(myIter.Next()))) {
        std::unique_ptr<TFile> inFile(TFile::Open(string->GetString().Data()));
        if (!inFile) {
            cout << "-W- File \"" << string->GetString().Data() << "\" does not exist" << endl;
            continue;
        }

        newParFileName = string->GetString();
        newParFileName.Remove(newParFileName.Last('/') + 1);
        newParFileName += Form("allParams_%d_%06d.root", currentDate.GetDate(), currentDate.GetTime());
        newParFile.reset(TFile::Open(newParFileName.Data(), "RECREATE"));
        if (newParFile) {
            break;
        }
    }

    if (!newParFile) {
        LOG(error) << "FairParRootFileIo::open: Could not generate merged file";
        return kFALSE;
    }

    MergeFiles(newParFile.get(), fnamelist);

    // Close (and delete object) so that this->open has a clean file
    newParFile.reset();

    std::cout << "**** merged file = \"" << newParFileName.Data() << "\"" << std::endl;

    return this->open(newParFileName, option, ftitle, compress);
}

/**
 * \brief merge many parfiles into one
 * \param newParFile non-owning, already open file to merge content into
 * \param fnamelist  List of filesnames to read data from
 */
void FairParRootFileIo::MergeFiles(TFile* newParFile, const TList* fnamelist)
{
    if (!newParFile) {
        return;
    }
    TDirectory::TContext restorecwd{};
    TObjString* string;
    TListIter myIter(fnamelist);
    while ((string = static_cast<TObjString*>(myIter.Next()))) {
        std::unique_ptr<TFile> inFile(TFile::Open(string->GetString().Data()));
        if (!inFile) {
            cout << "-W- File \"" << string->GetString().Data() << "\" does not exist" << endl;
            continue;
        }

        TList* inputKeys = static_cast<TList*>(inFile->GetListOfKeys());

        TListIter keyIter(inputKeys);
        TKey* inpKey;
        while ((inpKey = static_cast<TKey*>(keyIter.Next()))) {
            TObject* tempObj = inFile->Get(inpKey->GetName());

            newParFile->WriteTObject(tempObj);
        }
    }
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
