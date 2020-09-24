/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
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

#include <FairRingSorterTask.h>  // for FairRingSorterTask
#include <Rtypes.h>              // for THashConsistencyHolder, ClassDef
#include <TString.h>             // for TString
#include <RtypesCore.h>          // for Double_t, Int_t

class FairRingSorter;
class FairTimeStamp;
class TBuffer;
class TClass;
class TMemberInspector;

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

    virtual ~FairTestDetectorDigiSorterTask();

    virtual void AddNewDataToTClonesArray(FairTimeStamp* data);
    virtual FairRingSorter* InitSorter(Int_t numberOfCells, Double_t widthOfCells) const;

    ClassDef(FairTestDetectorDigiSorterTask, 1);
};

#endif /* FairTestDetectorDigiSorterTask_H_ */
