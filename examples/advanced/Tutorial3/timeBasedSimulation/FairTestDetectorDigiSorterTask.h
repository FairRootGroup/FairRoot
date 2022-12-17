/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiSorterTask.h
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#ifndef FairTestDetectorDigiSorterTask_H_
#define FairTestDetectorDigiSorterTask_H_

#include <FairRingSorterTask.h>   // for FairRingSorterTask
#include <Rtypes.h>               // for Double_t, etc
#include <TString.h>              // for TString

class FairRingSorter;
class FairTimeStamp;

class FairTestDetectorDigiSorterTask : public FairRingSorterTask
{
  public:
    FairTestDetectorDigiSorterTask();
    FairTestDetectorDigiSorterTask(const char* name)
        : FairRingSorterTask(name){};
    FairTestDetectorDigiSorterTask(Int_t numberOfCells,
                                   Double_t widthOfCells,
                                   TString inputBranch,
                                   TString outputBranch,
                                   TString folderName)
        : FairRingSorterTask(numberOfCells, widthOfCells, inputBranch, outputBranch, folderName){};

    ~FairTestDetectorDigiSorterTask() override;

    void AddNewDataToTClonesArray(FairTimeStamp* data) override;
    FairRingSorter* InitSorter(Int_t numberOfCells, Double_t widthOfCells) const override;

    ClassDefOverride(FairTestDetectorDigiSorterTask, 1);
};

#endif /* FairTestDetectorDigiSorterTask_H_ */
