/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 20/10/2004

/////////////////////////////////////////////////////////////
//  FairParIo
//
//  Base class for different parameter input/output sources:
//  Rootfiles, Asciifiles, Oracle
//  It contains a list of detector I/Os.
/////////////////////////////////////////////////////////////

#include "FairParIo.h"

#include "FairDetParIo.h"   // for FairDetParIo

#include <TCollection.h>   // for TIter
#include <TList.h>         // for TList

FairParIo::FairParIo()
    : TObject()
    , detParIoList(new TList())
    , autoWritable(kTRUE)
    , filename("")
{
    // default constructor creates an empty list of detector I/Os
    //  detParIoList=new TList();
    //  autoWritable=kTRUE;
}

FairParIo::~FairParIo()
{
    // default destructor
    if (detParIoList) {
        detParIoList->Delete();
        delete detParIoList;
        detParIoList = 0;
    }
}

void FairParIo::setDetParIo(FairDetParIo* detParIo)
{
    // stores pointer of the input/output class for a detector
    // used for I/O from ROOT file or Ascii file
    const Text_t* detName = detParIo->GetName();
    if (!detParIoList->FindObject(detName)) {
        detParIoList->Add(detParIo);
    }
}

void FairParIo::setInputNumber(Int_t num)
{
    // sets in all detector I/Os the number of the input
    TIter next(detParIoList);
    FairDetParIo* io;
    while ((io = static_cast<FairDetParIo*>(next()))) {
        io->setInputNumber(num);
    }
}

FairDetParIo* FairParIo::getDetParIo(const Text_t* detName)
{
    // returns pointer to input/output class for a detector
    // std::cout << " DetParIO # " << detName << detParIoList->GetEntries()  <<  std::endl;
    return (static_cast<FairDetParIo*>(detParIoList->FindObject(detName)));
}

void FairParIo::removeDetParIo(Text_t* detName)
{
    // removes input/output class for a detector
    TObject* p = detParIoList->FindObject(detName);
    delete p;
    p = 0;
}
