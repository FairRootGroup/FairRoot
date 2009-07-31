// Class for the GEANE initialization
//
// Author: M. Al-Turany
//
#ifndef FAIRGeaneNEW_H
#define FAIRGeaneNEW_H

#include "TObject.h"
#include "TString.h"


class FairGeaneNew : public TObject
{
 public:

  /** Default constructor **/
  FairGeaneNew();

  FairGeaneNew(const char* name);

  virtual ~FairGeaneNew();

  ClassDef(FairGeaneNew,1)
}; 


#endif
