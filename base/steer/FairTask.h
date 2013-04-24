// -------------------------------------------------------------------------
// -----                      FairTask header file                      -----
// -----          Created 12/01/04  by M. Al-Turany / D. Bertini       -----
// -------------------------------------------------------------------------


/** FairTask
 * @author M. Al-Turany, Denis Bertini
 * @since 12.01.04
 **
 ** Base class for tasks in the cbmroot framework.
 ** Derived classes should implement the Exec method.
 **/

#ifndef FAIRTASK_H
#define FAIRTASK_H

#include "FairLogger.h"
#include "FairRootManager.h"

#include "TTask.h"

enum InitStatus {kSUCCESS, kERROR, kFATAL};

class FairTask : public TTask
{

  public:

    /** Default constructor **/
    FairTask();


    /** Standard constructor
    *@param name        Name of task
    *@param iVerbose    Verbosity level
    **/
    FairTask(const char* name, Int_t iVerbose = 1);


    /** Destructor **/
    virtual ~FairTask();


    /** Initialisation at begin of run. For this task and all of the
        subtasks. **/
    void InitTask();


    /** Reinitialisation. For this task and all of the subtasks. **/
    void ReInitTask();


    /** Set parameters. For this task and all of the subtasks. **/
    void SetParTask();


    /** Action at end of run. For this task and all of the subtasks. **/
    virtual void FinishTask();

    /** Action at end of event. For this task and all of the subtasks. **/
    virtual void FinishEvent();

    /** Set verbosity level. For this task and all of the subtasks. **/
    void SetVerbose(Int_t iVerbose);

    void SetInputPersistance(Bool_t val) {fInputPersistance = val;}

    void CheckInputPersistance(TString branchName) {
      FairRootManager* ioman = FairRootManager::Instance();
      fInputPersistance = ioman->CheckBranch(branchName);
    }


  protected:

    Int_t        fVerbose;  //  Verbosity level
    Int_t        fInputPersistance; ///< Indicates if input branch is persistant
    FairLogger*  fLogger; //!

    /** Intialisation at begin of run. To be implemented in the derived class.
    *@value  Success   If not kSUCCESS, task will be set inactive.
    **/
    virtual InitStatus Init() { return kSUCCESS; };


    /** Reinitialisation. To be implemented in the derived class.
    *@value  Success   If not kSUCCESS, task will be set inactive.
    **/
    virtual InitStatus ReInit() { return kSUCCESS; };


    /** Intialise parameter containers.
        To be implemented in the derived class.
    **/
    virtual void SetParContainers() { };


    /** Action after each event. To be implemented in the derived class **/
    virtual void Finish() { };

    //  /** Action after each event. To be implemented in the derived class **/
    //  virtual void FinishTask() { };


    /** Recursive intialisation of subtasks at begin of run **/
    void InitTasks();


    /** Recursive reinitialisation of subtasks **/
    void ReInitTasks();


    /** Recursive parameter initialisation for subtasks **/
    void SetParTasks();

    /** Recursive finish of subtasks **/
    void FinishTasks();

    /** Recursive FinishEvent of subtasks **/
    void FinishEvents();

  private:
    FairTask(const FairTask&);
    FairTask& operator=(const FairTask&);

    ClassDef(FairTask,2);

};


#endif
