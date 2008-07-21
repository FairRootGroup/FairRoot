// -------------------------------------------------------------------------
// -----                       CbmEventHeader header file                      -----
// -----          Created 08/09/04                 D.Bertini           -----
// -------------------------------------------------------------------------

#ifndef CBMEVENTHEADER_H
#define CBMEVENTHEADER_H


#include "TNamed.h"

/**
 *  Event Header Class
  **@author D.Bertini <d.bertini@gsi.de>
  **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class CbmEventHeader : public TNamed
{

 public:

  /** Default constructor **/
  CbmEventHeader();
  void SetRunId(UInt_t runid){fRunId=runid;}
  UInt_t GetRunId() {return fRunId;}


  /** Destructor **/
  virtual ~CbmEventHeader();




 protected:
   UInt_t fRunId;

  ClassDef(CbmEventHeader,1)

};
#endif
