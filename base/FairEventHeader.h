// -------------------------------------------------------------------------
// -----                       FairEventHeader header file                      -----
// -----          Created 08/09/04                 D.Bertini           -----
// -------------------------------------------------------------------------

#ifndef FAIREVENTHEADER_H
#define FAIREVENTHEADER_H


#include "TNamed.h"

/**
 *  Event Header Class
  **@author D.Bertini <d.bertini@gsi.de>
  **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairEventHeader : public TNamed
{

 public:

  /** Default constructor */
  FairEventHeader();
  /** Set the run ID for this run 
   * @param runid : unique run id 
   */	
  void SetRunId(UInt_t runid){fRunId=runid;}
  /** Get the run ID for this run*/	
  UInt_t GetRunId() {return fRunId;}

  /** 
   * Destructor 
   */
  virtual ~FairEventHeader();



 protected:
   /** Run Id */
   UInt_t fRunId;

  ClassDef(FairEventHeader,1)

};
#endif
