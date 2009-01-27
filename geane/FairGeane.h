// Class for the GEANE initialization
//
// Author: M. Al-Turany
//
#ifndef CBMGeane_H
#define CBMGeane_H

#include "TObject.h"
#include "TString.h"

class FairMCApplication;
class FairField;

class FairGeane : public TObject
{
 public:

  /** Default constructor **/
  FairGeane();

  FairGeane(const char* name, TString fUserConfig="",    TString fUserCuts="");

  virtual ~FairGeane();

  void SetField(FairField *field);

  ClassDef(FairGeane,1)
protected:
  
  FairMCApplication *fApp;

}; 


#endif
