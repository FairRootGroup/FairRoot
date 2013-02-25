// -------------------------------------------------------------------------
// -----                 FAIRMCMATCHCREATORTASK header file             -----
// -----                  Created 20/03/07  by R.Kliemt               -----
// -------------------------------------------------------------------------


/** FAIRMCMATCHCREATORTASK.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Displays all available informations for a given event
 **/


#ifndef FAIRMCMATCHCREATORTASK_H
#define FAIRMCMATCHCREATORTASK_H


// framework includes
#include "FairTask.h"
#include "FairMCMatch.h"


#include <vector>
#include <map>

class TClonesArray;

class FairMCMatchCreatorTask : public FairTask
{
  public:

    /** Default constructor **/
    FairMCMatchCreatorTask();

    /** Destructor **/
    virtual ~FairMCMatchCreatorTask();


    /** Virtual method Init **/
    virtual void SetParContainers();
    void SetPersistance(Bool_t pers) {fPersistance = pers;}
    Bool_t GetPersistance() {return fPersistance;}

    virtual InitStatus Init();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    virtual void Finish();

    virtual void InitDataStages() = 0;

  protected:
    FairMCMatch* fMCMatch;

  private:

    std::map<std::string, TClonesArray*> fBranches;
    Bool_t fPersistance;
    TClonesArray* fMCLink;//->
    Int_t fEventNr;

    InitStatus InitBranches();

    void Register();

    void Reset();

    void ProduceHits();


    ClassDef(FairMCMatchCreatorTask,1);

};

#endif
