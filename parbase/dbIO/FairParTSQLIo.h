/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * Modified by: D.Bertini@gsi.de       *
 * License:                            *
 * Version:                            *
 ***************************************/
#pragma once
#ifndef FAIR_PAR_TSQL_IO_h
#define FAIR_PAR_TSQL_IO_h

#include "FairParIo.h"                  // for FairParIo
#include "Rtypes.h"                     // for FairParTSQLIo::Class, etc


#define MIN_SEQNO 0
#define MAX_SEQNO 999999999
#define BAS_SEQNO 100000000
#define INC_SEQNO  99999999


class FairDbConnectionPool;
class FairRtdbRun;

class FairParTSQLIo: public FairParIo
{
  public:
    //_____________ Constructors _______
    /**
     * Default constructor.
     */
    FairParTSQLIo();

    /**
     *@param cons FairDbConnectionPool which holds a number of
     * initialized db connections.
     *@param dbNum The db which is selected to act as the master for the
     * current operations.
     * Note: A new FairDbConnection object is
     * created (to keep the ownership).
     */
    FairParTSQLIo(FairDbConnectionPool const& cons, int const dbNum = -1);

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

    void close() {disconnect();}

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
    inline FairDbConnectionPool const& GetConnections() const;

    void readVersions(FairRtdbRun* aRun);
    FairRtdbRun* getCurrentRun() {return fCurrentRun;}


    /**
     * SQL IO Configuration functions
       *
     **/


    void SetShutdown(Bool_t shutdown=kFALSE);
    void SetRollback(TString rollbackdate, TString tablename="*");
    void SetRollbackMode(Int_t mode=0, TString tablename="*");
    void SetHoldConnection(Int_t mode=1);
    void SetQueryOrdering();
    void SetCache(TString cache_file="");
    void CombineDataType(TString input_type, TString other_type);

	/** 
      Define the SeqNo boundaries
	*/ 

    void  SetGlobalSeqNoIn(Int_t seqno);
    Int_t GetGlobalSeqNoIn()  {return  fGlobalSeqNoIn;}
    Int_t GetGlobalSeqNoOut() {return  fGlobalSeqNoOut;}

    /**
     *  Verbosity Control
     **/

    void SetVerbosity(Int_t level=1);

  protected:

    bool activateDetIo();

  private:
    // To avoid mistakes.
    FairParTSQLIo(FairParTSQLIo const& ot);
    FairParTSQLIo& operator=(FairParTSQLIo const& ot);

    FairRtdbRun* fCurrentRun;
    int fDefaultDb;
    FairDbConnectionPool* fConnections;
    Int_t fGlobalSeqNoIn;
    Int_t fGlobalSeqNoOut;    

    ClassDef(FairParTSQLIo, 0) // Class for parameter I/O Using TSQL
};
// ______________________ Inline functions ______________

#ifndef __CINT__
inline FairDbConnectionPool const& FairParTSQLIo::GetConnections() const
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
