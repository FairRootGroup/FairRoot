/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#pragma once
#ifndef FAIRDET_PAR_TSQL_IO_H
#define FAIRDET_PAR_TSQL_IO_H

#include "FairDetParIo.h"
#include "FairDbMultConnector.h"
#include "FairRtdbRun.h"
#include "FairParSet.h"

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

    virtual bool read (FairParSet* pars);
    virtual int  write(FairParSet* pars);

    ////////////////
    inline void print();
    ///////////////
    //________ DB functions maybe later ____
    // commits changes.
    virtual void commit();

    // Undo the changes made since last commit.
    virtual void rollback();

    // ____________ protected Members ___________________
  protected:

    int fDefaultDb;/**< The default Database connection.*/
    FairDbMultConnector* fConnections;//! FairDbConnection
    TList*               fcontainerList;//! List of parameter containers
    FairRtdbRun*         factContVers;  //! The actual list of container versions

    void setChanged(FairParSet*);

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
