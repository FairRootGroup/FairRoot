/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 28/01/2009

//_HADES_CLASS_DESCRIPTION
///////////////////////////////////////////////////////////////////////////
//
//  FairParGenericSet
//
//  Base class for all condition-stype parameter containers
//
//  The following functions must be implemented by the derived class:
//
//    void putParams(FairParamList*)    Fills all persistent data members into
//                                   the list for write.
//
//    Bool_t getParams(FairParamList*)  Fills all persistent data members from
//                                   the list after reading. The function
//                                   returns false, when a data member is
//                                   not in the list.
//
///////////////////////////////////////////////////////////////////////////
#include "FairParGenericSet.h"

#include "FairDetParIo.h"    // for FairDetParIo
#include "FairParIo.h"       // for FairParIo
#include "FairParamList.h"   // for FairParamList

#include <TString.h>   // for operator<<, TString
#include <iostream>    // for operator<<, ostream, cout, etc

Bool_t FairParGenericSet::init(FairParIo* inp)
{
    // intitializes the container from an input
    FairDetParIo* input = inp->getDetParIo("FairGenericParIo");
    if (input) {
        return (input->init(this));
    }
    return kFALSE;
}

Int_t FairParGenericSet::write(FairParIo* output)
{
    // writes the container to an output
    FairDetParIo* out = output->getDetParIo("FairGenericParIo");
    if (out) {
        return out->write(this);
    }
    return -1;
}

void FairParGenericSet::printParams()
{
    // prints information about the container
    std::cout << "\n---------------------------------------------\n";
    std::cout << "-----  " << GetName() << "  -----\n";
    if (!paramContext.IsNull()) {
        std::cout << "--  Context/Purpose:  " << paramContext << '\n';
    }
    if (!author.IsNull()) {
        std::cout << "--  Author:           " << author << '\n';
    }
    if (!description.IsNull()) {
        std::cout << "--  Description:      " << description << '\n';
    }
    std::cout << "---------------------------------------------\n";
    FairParamList* condList = new FairParamList;
    putParams(condList);
    condList->print();
    std::cout << "---------------------------------------------\n\n";
    delete condList;
}
