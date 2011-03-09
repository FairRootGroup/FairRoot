// -------------------------------------------------------------------------
// -----                    FairTrdDigiPar header file                  -----
// -----                 Created 15/05/08  by F. Uhlig                 -----
// -------------------------------------------------------------------------

#ifndef FAIRTUTORIALDETDIGIPAR_H
#define FAIRTUTORIALDETDIGIPAR_H


#include "FairParGenericSet.h"

#include "TObject.h"
#include "TObjArray.h"
#include "TArrayF.h"
#include "TArrayI.h"

class FairParIo;
class FairParamList;


class FairTutorialDetDigiPar : public FairParGenericSet
{

  public:

    /** Standard constructor **/
    FairTutorialDetDigiPar(const char* name    = "FairTutorialDetDigiPar",
                           const char* title   = "Tutorial Det digi parameters",
                           const char* context = "Default");


    /** Destructor **/
    virtual ~FairTutorialDetDigiPar();


    /** Initialisation from input device**/
    //virtual Bool_t init(FairParIo* input);


    /** Output to file **/
    //  virtual Int_t write(FairParIo* output);

    //  virtual void print();
    virtual void printparams();


    /** Reset all parameters **/
    virtual void clear();

    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    // private:

    TArrayF* ftutdetdigipar;  //
    TArrayI ftutdetdigiparsector; //
    Int_t ftutdetdigiparstation; //


    ClassDef(FairTutorialDetDigiPar,1);


};


#endif





