/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#pragma once
#ifndef FAIR_GENERIC_PAR_TSQL_Io_H
#define FAIR_GENERIC_PAR_TSQL_Io_H

// C & C++
#include <iostream>

// FairRoot
#include "FairParSet.h"
#include "FairParGenericSet.h"
#include "FairDetParTSQLIo.h"

// ROOT

class FairGenericParTSQLIo : public FairDetParTSQLIo
{
  public:
    //! Constructor.
    FairGenericParTSQLIo();

    /**
     *@param cons FairDbMultConnector which holds a number of
     * initialized db connections.
     *@param dbNum The db which is selected to act as the master for the
     * current operations.
     * Note: A new FairDbMultConnector object is
     * created (to keep the ownership).
     */
    FairGenericParTSQLIo(FairDbMultConnector const& cons, int const dbNum = -1);

    //! Destructor.
    virtual ~FairGenericParTSQLIo();

    bool read(FairParGenericSet& pset);
    virtual int write(FairParSet& pars);
    virtual int writeSet(FairParGenericSet& pars);

    //protected:
  private:
    // To Avoid mistakes.
    FairGenericParTSQLIo(FairGenericParTSQLIo const& ot);
    FairGenericParTSQLIo& operator=(FairGenericParTSQLIo const& ot);

    ClassDef(FairGenericParTSQLIo, 0)
};
#endif//FAIR_GENERIC_PAR_TSQL_Io_H
