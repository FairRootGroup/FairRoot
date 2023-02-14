/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 FAIRMCMATCHCREATORTASK header file             -----
// -----                  Created 20/03/07  by R.Kliemt               -----
// -------------------------------------------------------------------------

/** FairMCMatchLoaderTask.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Displays all available informations for a given event
 **/

#ifndef FAIRMCMATCHLOADERTASK_H
#define FAIRMCMATCHLOADERTASK_H

#ifndef FAIR_SILENCE_DATAMATCH_DEPRECATION
#warning "FairRoot::DataMatch is deprecated and will be removed in a future major release"
#endif

#include "FairTask.h"   // for FairTask, InitStatus

#include <Rtypes.h>   // for ClassDef

class FairMCMatch;
class TClonesArray;

class FairMCMatchLoaderTask : public FairTask
{
  public:
    /** Default constructor **/
    FairMCMatchLoaderTask();

    /** Destructor **/
    virtual ~FairMCMatchLoaderTask();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    virtual void Finish();

    virtual void InitDataStages() = 0;

  protected:
    FairMCMatch* fMCMatch;

  private:
    TClonesArray* fMCLink;
    int fEventNr;

    void Register();

    void Reset();

    void ProduceHits();

    FairMCMatchLoaderTask(const FairMCMatchLoaderTask&);
    FairMCMatchLoaderTask& operator=(const FairMCMatchLoaderTask&);

    ClassDef(FairMCMatchLoaderTask, 1);
};

#endif
