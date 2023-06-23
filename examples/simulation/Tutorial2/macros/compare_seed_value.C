/********************************************************************************
 *    Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#if !defined(__CLING__) || defined(__ROOTCLING__)
#include "FairBaseParSet.h"

#include <RtypesCore.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <memory>
#endif

int compare_seed_value(TString filename, UInt_t initial_seed)
{

    // Open parameter file and get the stored random seed from the
    // FairBaseParSet parameter container
    // Compare the random seed with the expected one set during the
    // transport run

    std::unique_ptr<TFile> myFile(TFile::Open(filename));
    if (!myFile || myFile->IsZombie()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return 1;
    }

    std::unique_ptr<FairBaseParSet> par(myFile->Get<FairBaseParSet>("FairBaseParSet"));
    if (!par) {
        std::cerr << "Did not find FairBaseParSet in input file" << std::endl;
        return 1;
    }

    UInt_t seed = par->GetRndSeed();

    if (seed == initial_seed) {
        return 0;
    } else {
        std::cout << "Expected seed value  : " << initial_seed << std::endl;
        std::cout << "Seed value from file : " << seed << std::endl;
        return 1;
    }
}
