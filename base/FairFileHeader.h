// -------------------------------------------------------------------------
// -----                         FairFileHeader source file           -----
// -----            Created 20/04/11                 M.Al-Turany        -----
// -------------------------------------------------------------------------

#ifndef FAIRFILEHEADER_H
#define FAIRFILEHEADER_H


#include "TNamed.h"

/**
 *  File Header Class
   **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairFileHeader : public TNamed
{

  public:

    /** Default constructor */
    FairFileHeader();
    /** Set the run ID for this run
     * @param runid : unique run id
     */
    void SetRunId(UInt_t runid) {fRunId=runid;}
    /** Get the run ID for this run*/
    UInt_t GetRunId() {return fRunId;}

    /**
     * Destructor
     */
    virtual ~FairFileHeader();

  protected:
    /** Run Id */
    UInt_t fRunId;

    ClassDef(FairFileHeader,1)

};
#endif
