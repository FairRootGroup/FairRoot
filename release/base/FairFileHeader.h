// -------------------------------------------------------------------------
// -----                         FairFileHeader source file           -----
// -----            Created 20/04/11                 M.Al-Turany        -----
// -------------------------------------------------------------------------

#ifndef FAIRFILEHEADER_H
#define FAIRFILEHEADER_H


#include "TNamed.h"
#include "TList.h"
#include "TObjString.h"
#include "TFile.h"


class FairFileInfo;

/**
 *  File Header Class
   **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairFileHeader : public TNamed
{

  public:

    /** Default constructor */
    FairFileHeader();

    /**Add a class name of a task*/
    void AddTaskClassName(TString taskname);

    /** Set the run ID for this run
       * @param runid : unique run id
       */
    void SetRunId(UInt_t runid) {fRunId=runid;}

    /** Get the run ID for this run*/
    UInt_t GetRunId() {return fRunId;}

    /** Return the list of tasks class names */
    TList* GetListOfTasks() {return fTaskList;}

    void AddInputFile(TFile* f, UInt_t id, UInt_t ChId);

    /**
     * Destructor
     */
    virtual ~FairFileHeader();


    FairFileInfo* GetFileInfo(UInt_t id, UInt_t ChId);




  protected:
    /** Run Id */
    UInt_t fRunId;

    /**list of TObjStrings presenting the class names of tasks used to produce this file */
    TList* fTaskList;

    /**list of TObjStrings presenting the input files used to produce this file*/
    TList* fFileList;

  private:
    FairFileHeader(const FairFileHeader&);
    FairFileHeader& operator=(const FairFileHeader&);


    ClassDef(FairFileHeader,2)

};
#endif
