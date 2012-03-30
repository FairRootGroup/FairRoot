/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#pragma once
#ifndef FAIR_PAR_TSQL_IO_h
#define FAIR_PAR_TSQL_IO_h

// C & C++
#include <iostream>

// ROOT
class TList;

// FairRoot
#include "FairParIo.h"

class FairGenericParTSQLIo;
class FairDbMultConnector;

class FairParTSQLIo: public FairParIo
{
  public:
    //_____________ Constructors _______
    /**
     * Default constructor.
     */
    FairParTSQLIo();

    /**
     *@param cons FairDbMultConnector which holds a number of
     * initialized db connections.
     *@param dbNum The db which is selected to act as the master for the
     * current operations.
     * Note: A new FairDbConnection object is
     * created (to keep the ownership).
     */
    FairParTSQLIo(FairDbMultConnector const& cons, int const dbNum = -1);

    /**
     * Destructor
     */
    virtual ~FairParTSQLIo();

    /**
     * Destroy the connection.
     */
    void disconnect();

    /**
     * creates the specified I/O.
     *@param io The name of IO to be created/added in the IO list.
     */
    void setDetParIo(Text_t* io);

    /**
     * Check if at least one connection is alive.
     *@return True if the connection is alive.
     */
    bool check();

    /**
     * If connection exist to at least on of the specified databases,
     * then activate IO and return true.
     *@return True if at least one connection is available.
     */
    bool open();

    /**
     * Print some info. This function maybe removed in future.
     */
    void print();

    /**
     * Set which database connection is going to be the default.
     *@param dbNum The default database identification number.
     */
    inline void SetDefaultDBNum(int const dbNum);

    /**
     *@return The default database identification number.
     */
    inline int  GetDefaultDBNum() const;

    /**
     * Get the connection object.
     *@return The actual FairDBConnection object.
     */
    inline FairDbMultConnector const& GetConnections() const;

  protected:

    bool activateDetIo();

  private:
    // To avoid mistakes.
    FairParTSQLIo(FairParTSQLIo const& ot);
    FairParTSQLIo& operator=(FairParTSQLIo const& ot);

    int fDefaultDb; /**< The default Database connection.*/
    FairDbMultConnector* fConnections;/**< Actual connection set*/

    ClassDef(FairParTSQLIo, 0) // Class for parameter I/O Using TSQL
};
// ______________________ Inline functions ______________

#ifndef __CINT__
inline FairDbMultConnector const& FairParTSQLIo::GetConnections() const
{
  return (*(this->fConnections));
};

inline void FairParTSQLIo::SetDefaultDBNum(int const dbNum)
{
  this->fDefaultDb = dbNum;
};

inline int  FairParTSQLIo::GetDefaultDBNum() const
{
  return this->fDefaultDb;
};
#endif /* __CINT__ */
#endif// END FAIR_PAR_TSQL_h
