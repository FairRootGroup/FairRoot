/*
 * MySorterTask.h
 *
 *  Created on: Mar 7, 2012
 *      Author: uhlig
 */

#ifndef MYSORTERTASK_H_
#define MYSORTERTASK_H_

#include <FairRingSorterTask.h>
#include <FairRingSorter.h>

class MySorterTask: public FairRingSorterTask
{
  public:
    MySorterTask();

    MySorterTask(const char* name)
      : FairRingSorterTask(name) {};

    MySorterTask(Int_t numberOfCells, Double_t widthOfCells,
                 TString inputBranch, TString outputBranch,
                 TString folderName)
      : FairRingSorterTask(numberOfCells, widthOfCells, inputBranch,
                           outputBranch, folderName) { };

    virtual ~MySorterTask();

    virtual void AddNewDataToTClonesArray(FairTimeStamp* data);
    virtual FairRingSorter* InitSorter(Int_t numberOfCells, Double_t widthOfCells) const;

    ClassDef(MySorterTask, 1);
};

#endif /* MYSORTERTASK_H_ */
