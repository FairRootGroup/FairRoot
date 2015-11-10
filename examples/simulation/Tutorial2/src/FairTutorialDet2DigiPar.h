/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairTutorialDetDigiPar header file              -----
// -----                 Created 15/05/08  by F. Uhlig                 -----
// -------------------------------------------------------------------------

#ifndef FAIRTUTORIALDET2DIGIPAR_H
#define FAIRTUTORIALDET2DIGIPAR_H


#include "FairParGenericSet.h"

#include "TObject.h"
#include "TObjArray.h"
#include "TArrayF.h"
#include "TArrayI.h"

class FairParIo;
class FairParamList;


class FairTutorialDet2DigiPar : public FairParGenericSet
{

  public:

    /** Standard constructor **/
    FairTutorialDet2DigiPar(const char* name    = "FairTutorialDet2DigiPar",
                            const char* title   = "Tutorial Det digi parameters",
                            const char* context = "Default");


    /** Destructor **/
    virtual ~FairTutorialDet2DigiPar();


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

  private:

    TArrayF* ftutdetdigipar;  //
    TArrayI ftutdetdigiparsector; //
    Int_t ftutdetdigiparstation; //

    FairTutorialDet2DigiPar(const FairTutorialDet2DigiPar&);
    FairTutorialDet2DigiPar& operator=(const FairTutorialDet2DigiPar&);

    ClassDef(FairTutorialDet2DigiPar,1);


};


#endif





