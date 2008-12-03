// Class for the GEANE initialization
//
// Author: M. Al-Turany
//
#ifndef CBMGeane_H
#define CBMGeane_H

#include "TObject.h"
#include "TString.h"

class CbmMCApplication;
class CbmField;

class CbmGeane : public TObject
{
 public:

  /** Default constructor **/
  CbmGeane();

  CbmGeane(const char* name, TString fUserConfig="",    TString fUserCuts="");

  virtual ~CbmGeane();

  void SetField(CbmField *field);

  ClassDef(CbmGeane,1)
protected:
  
  CbmMCApplication *fApp;

}; 


#endif
