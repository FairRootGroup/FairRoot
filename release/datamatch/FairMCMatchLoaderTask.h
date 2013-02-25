// -------------------------------------------------------------------------
// -----                 FAIRMCMATCHCREATORTASK header file             -----
// -----                  Created 20/03/07  by R.Kliemt               -----
// -------------------------------------------------------------------------


/** PNDMCMATCHCREATORTASK.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Displays all available informations for a given event
 **/


#ifndef FAIRMCMATCHLOADERTASK_H
#define FAIRMCMATCHLOADERTASK_H


// framework includes
#include "FairTask.h"
#include "FairMCMatch.h"


#include <vector>
#include <map>

class TClonesArray;

class FairMCMatchLoaderTask : public FairTask
{
  public:

    /** Default constructor **/
    FairMCMatchLoaderTask();

    /** Destructor **/
    virtual ~FairMCMatchLoaderTask();


    /** Virtual method Init **/
    virtual void SetParContainers();
    virtual InitStatus Init();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    virtual void Finish();

    virtual void InitDataStages() = 0;

  private:

    TClonesArray* fMCLink;
    int fEventNr;
    FairMCMatch* fMCMatch;

    void Register();

    void Reset();

    void ProduceHits();

    ClassDef(FairMCMatchLoaderTask,1);
};

#endif
