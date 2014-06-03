/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*******************************************
 * Author: M.Babai (M.Babai@rug.nl)        *
 * Modified: D.Bertini (D.Bertini@gsi.de)  *
 * License:                                *
 * Version:                                *
 *******************************************/

#pragma once
#ifndef FAIR_GENERIC_PAR_TSQL_Io_H
#define FAIR_GENERIC_PAR_TSQL_Io_H

#include "FairDetParTSQLIo.h"           // for FairDetParTSQLIo

#include "Rtypes.h"                     // for Bool_t, etc

class FairDbConnectionPool;
class FairParGenericSet;
class FairParSet;
class FairRuntimeDb;

class FairGenericParTSQLIo : public FairDetParTSQLIo
{
  public:
    //! Constructor.
    FairGenericParTSQLIo();

    /**
     *@param cons FairDbConnectionPool which holds a number of
     * initialized db connections.
     *@param dbNum The db which is selected to act as the master for the
     * current operations.
     * Note: A new FairDbConnectionPool object is
     * created (to keep the ownership).
     */
    FairGenericParTSQLIo(FairDbConnectionPool const& cons, int const dbNum = -1);

    //! Destructor.
    virtual ~FairGenericParTSQLIo();

    // Initialize and read.
    Bool_t init(FairParSet* pPar);

    //! Read and write functions.
    Bool_t read(FairParGenericSet* pPar);

    // Fetch the starting of the current run and inser param set into the Database.
    Int_t write(FairParSet* pars);

    // Write parameter set to the Database.
    Int_t writeSet(FairParGenericSet* pars);

    //protected:
  private:
    // To Avoid mistakes.
    FairGenericParTSQLIo(FairGenericParTSQLIo const& ot);
    FairGenericParTSQLIo& operator=(FairGenericParTSQLIo const& ot);

    FairRuntimeDb* fRtdb;


    ClassDef(FairGenericParTSQLIo, 0)
};
#endif//FAIR_GENERIC_PAR_TSQL_Io_H
