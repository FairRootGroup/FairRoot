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


#include "TTask.h"
//#include "TObject.h"


enum InitStatus {kSUCCESS, kERROR, kFATAL};



class FairTask : public TTask {

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
  

protected:

  Int_t   fVerbose;       //  Verbosity level


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

  ClassDef(FairTask,1);
    
};


#endif
