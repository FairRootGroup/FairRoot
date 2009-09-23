// Class for the GEANE initialization
//
// Author: M. Al-Turany
//
#ifndef FAIRGeane_H
#define FAIRGeane_H

#include "FairTask.h"
#include "TString.h"

class FairMCApplication;
class FairField;

class FairGeane : public  FairTask
{
 public:

  /** Default constructor **/
  //FairGeane();

  FairGeane(const char* name, TString UserConfig="",    TString UserCuts="");

  FairGeane(TString fUserConfig="",    TString fUserCuts="");

  InitStatus Init();
	
	void SetParTask();	
	
  virtual ~FairGeane();

  void SetField(FairField *field);

  ClassDef(FairGeane,2)

protected:
    FairMCApplication *fApp; //!
	const char* fName; //!
	TString fUserConfig;  //! 
	TString fUserCuts; //!
	

}; 


#endif
