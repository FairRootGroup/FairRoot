/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#pragma once
#ifndef FAIRDET_PAR_TSQL_IO_H
#define FAIRDET_PAR_TSQL_IO_H

//C && C++
#include <iostream>

// FairRoot
#include "FairDetParIo.h"

class FairRun;
class FairRuntimeDb;
class FairDbMultConnector;
class FairRtdbRun;
class FairParSet;

class FairDetParTSQLIo : public FairDetParIo
{
    // ____________ public Members ___________________
  public:
    /// Constructors
    FairDetParTSQLIo();

    /**
     *@param cons FairDbMultConnector which holds a number of
     * initialized db connections.
     *@param dbNum The db which is selected to act as the master for the
     * current operations.
     * Note: A new FairDbMultConnector object is
     * created (to keep the ownership).
     */
    FairDetParTSQLIo(FairDbMultConnector const& cons, int const dbNum = -1);

    /// Destructor.
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

    ////////////////
    inline void print();
    ///////////////

    // ____________ protected Members ___________________
  protected:

    int fDefaultDb;/**< The default Database connection.*/
    FairDbMultConnector* fConnections;//! FairDbConnection
    TList*               fcontainerList;//! List of parameter containers
    FairRtdbRun*         factContVers;  //! The actual list of container versions
    int actRunId; // actual runId (can be -1 if there are no data in Oracle)

    void setChanged(FairParSet* pars);

    // ____________ private Members ___________________
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
