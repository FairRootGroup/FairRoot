/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#pragma once
#ifndef FAIRDET_PAR_TSQL_IO_H
#define FAIRDET_PAR_TSQL_IO_H

#include "FairDetParIo.h"               // for FairDetParIo

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for FairDetParTSQLIo::Class, etc

#include <iostream>                     // for operator<<, cout, ostream

class FairDbConnectionPool;
class FairParSet;
class FairRtdbRun;
class TList;

class FairDetParTSQLIo : public FairDetParIo
{
    // ____________ public Members ___________________
  public:
    /// Constructors
    FairDetParTSQLIo();

    /**
     *@param cons FairDbConnectionPool which holds a number of
     * initialized db connections.
     *@param dbNum The db which is selected to act as the master for the
     * current operations.
     * Note: A new FairDbConnectionPool object is
     * created (to keep the ownership).
     */
    FairDetParTSQLIo(FairDbConnectionPool const& cons, int const dbNum = -1);
    virtual ~FairDetParTSQLIo();

    /**
     * Read the parameter set from the DB.
     */
    Bool_t read (FairParSet* pars);

    // Write to database
    Int_t  write(FairParSet* pars);

    // Get start time for the current run
    Int_t getRunStart(FairParSet* pPar = 0);

    //________ DB functions maybe later ____
    // It depends on the used DBMS. We need to see if this is needed.
    // commits changes.
    virtual void commit();

    // Undo the changes made since last commit.
    virtual void rollback();

    inline void print();



  protected:

    int fDefaultDb; /**< The default Database connection.*/
    FairDbConnectionPool* fConnections;//! FairDbConnection
    TList*               fcontainerList;//! List of parameter containers
    FairRtdbRun*         factContVers;  //! The actual list of container versions
    int actRunId; // actual runId (can be -1 if there are no data in Oracle)

    void setChanged(FairParSet* pars);


  private:
    //To avoid mistakes.
    FairDetParTSQLIo(FairDetParTSQLIo const& ot);
    FairDetParTSQLIo& operator=(FairDetParTSQLIo const& ot);

    ClassDef(FairDetParTSQLIo, 0)
};

/// _______________ Inline Implementations ________________
#ifndef __CINT__
inline void FairDetParTSQLIo::print()
{
  std::cout << "FairDetParTSQLIo::print()\n\n";
};
#endif /* __CINT__ */
#endif
