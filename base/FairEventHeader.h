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

  /** Default constructor **/
  FairEventHeader();
  void SetRunId(UInt_t runid){fRunId=runid;}
  UInt_t GetRunId() {return fRunId;}


  /** Destructor **/
  virtual ~FairEventHeader();




 protected:
   UInt_t fRunId;

  ClassDef(FairEventHeader,1)

};
#endif
