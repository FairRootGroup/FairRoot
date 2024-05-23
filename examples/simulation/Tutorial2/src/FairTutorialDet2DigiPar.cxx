/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairTutorialDet2DigiPar source file              -----
// -----                  Created 05/06/08  by F. Uhlig                -----
// -------------------------------------------------------------------------

#include "FairTutorialDet2DigiPar.h"

#include "FairParamList.h"

#include <TString.h>
#include <fairlogger/Logger.h>

FairTutorialDet2DigiPar::FairTutorialDet2DigiPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , ftutdetdigiparsector()
    , ftutdetdigiparstation(-1)
{
    detName = "TutorialDet";
}

void FairTutorialDet2DigiPar::printparams()
{
    LOG(info) << "Print";
    LOG(info) << "ftutdetdigiparstation: " << ftutdetdigiparstation;
    Int_t size = ftutdetdigiparsector.GetSize();
    LOG(info) << "size: " << size;
    for (Int_t i = 0; i < size; i++) {
        LOG(info) << i << " :" << ftutdetdigiparsector.GetAt(i);
    }
    size = ftutdetdigipar.GetSize();
    LOG(info) << "size: " << size;
    for (Int_t i = 0; i < size; i++) {
        LOG(info) << i << " :" << ftutdetdigipar.GetAt(i);
    }
}

void FairTutorialDet2DigiPar::putParams(FairParamList* l)
{
    // print();
    LOG(info) << "I am in FairTutorialDet2DigiPar::putParams ";
    if (!l) {
        return;
    }
    l->add("FairTutorialDet2DigiStations", ftutdetdigiparstation);
    l->add("FairTutorialDet2DigiSectorsPerStation", ftutdetdigiparsector);
    Int_t count_sectors = 0;
    for (Int_t i = 0; i < ftutdetdigiparstation; i++) {
        count_sectors += ftutdetdigiparsector[i];
    }
    Int_t array_size = (count_sectors * 10 + ftutdetdigiparstation * 3);
    LOG(info) << "Array Size: " << array_size;
    /*   Float_t zwischen[array_size];
     for (Int_t i=0; i< array_size; i++) {
       zwischen[i] = ftutdetdigipar.GetAt(i);
     }
   */
    ftutdetdigipar.Set(array_size);
    l->add("FairTutorialDet2DigiPar", ftutdetdigipar);
}

Bool_t FairTutorialDet2DigiPar::getParams(FairParamList* l)
{
    // print();

    LOG(info) << "I am in FairTutorialDet2DigiPar::getParams ";

    if (!l) {
        return kFALSE;
    }
    if (!l->fill("FairTutorialDet2DigiStations", &ftutdetdigiparstation)) {
        return kFALSE;
    }
    ftutdetdigiparsector.Set(ftutdetdigiparstation);

    if (!l->fill("FairTutorialDet2DigiSectorsPerStation", &ftutdetdigiparsector)) {
        return kFALSE;
    }

    Int_t count_sectors = 0;
    for (Int_t i = 0; i < ftutdetdigiparstation; i++) {
        count_sectors += ftutdetdigiparsector[i];
    }
    LOG(info) << "Total number of sectors: " << count_sectors;

    Int_t array_size = (count_sectors * 10 + ftutdetdigiparstation * 3);
    LOG(info) << "Array Size: " << array_size;
    ftutdetdigipar.Set(array_size);
    // Float_t zwischen[array_size];
    if (!(l->fill("FairTutorialDet2DigiPar", &ftutdetdigipar))) {
        LOG(warn) << "Could not initialize FairTutorialDet2DigiPar";
        return kFALSE;
    }
    // ftutdetdigipar.Set(array_size, zwischen);
    return kTRUE;
}
