// -------------------------------------------------------------------------
// -----                    CbmTrdDigiPar header file                  -----
// -----                 Created 15/05/08  by F. Uhlig                 -----
// -------------------------------------------------------------------------

#ifndef CBMTUTORIALDETDIGIPAR_H
#define CBMTUTORIALDETDIGIPAR_H


#include "CbmParGenericSet.h"

#include "TObject.h"
#include "TObjArray.h"
#include "TArrayF.h"
#include "TArrayI.h"

class CbmParIo;
class CbmParamList;


class CbmTutorialDetDigiPar : public CbmParGenericSet 
{

 public:

  /** Standard constructor **/
  CbmTutorialDetDigiPar(const char* name    = "CbmTutorialDetDigiPar",
			const char* title   = "Tutorial Det digi parameters",
			const char* context = "Default");


  /** Destructor **/
  virtual ~CbmTutorialDetDigiPar();


  /** Initialisation from input device**/
  //virtual Bool_t init(CbmParIo* input);


  /** Output to file **/
  //  virtual Int_t write(CbmParIo* output);

  //  virtual void print(); 
  virtual void printparams();

  
  /** Reset all parameters **/
  virtual void clear();

  void putParams(CbmParamList*);
  Bool_t getParams(CbmParamList*);

  // private:

  TArrayF ftutdetdigipar;  //
  TArrayI ftutdetdigiparsector; //
  Int_t ftutdetdigiparstation; //


  ClassDef(CbmTutorialDetDigiPar,1);


};


#endif





