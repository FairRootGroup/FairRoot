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
 ******************************************/
#include "FairParTSQLIo.h"

#include "FairDbLogService.h"

#include "FairDbConnection.h"           // for FairDbConnection
#include "FairDbConnectionPool.h"        // for FairDbConnectionPool, etc
#include "FairDbStatement.h"            // for FairDbStatement
#include "FairDbTableInterfaceStore.h"   // for FairDbTableProxyRegistry
#include "FairDetParIo.h"               // for FairDetParIo
#include "FairGenericParTSQLIo.h"       // for FairGenericParTSQLIo
#include "FairRuntimeDb.h"              // for FairRuntimeDb



#include "Riosfwd.h"                    // for ostream, ifstream
#include "TCollection.h"                // for TIter
#include "TList.h"                      // for TList
#include "TSQLStatement.h"              // for TSQLStatement
#include "TString.h"                    // for TString, operator==, etc

#include <stddef.h>                     // for size_t
#include <stdlib.h>                     // for NULL, exit, getenv
#include <string.h>                     // for strcmp
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <sstream>
#include <memory>                       // for auto_ptr, etc
#include <string>                       // for string, basic_string, etc
#include <vector>                       // for vector, vector<>::iterator
#include <sstream>                      // IWYU pragma: keep
#include <fstream>                      // IWYU pragma: keep
#include <limits.h>

class FairRtdbRun;
class TObject;

using namespace std;


ClassImp(FairParTSQLIo)

FairParTSQLIo::FairParTSQLIo()
  : FairParIo(),
    fCurrentRun(NULL),
    fDefaultDb (-1),
  fConnections(FairDbTableInterfaceStore::Instance().fConnectionPool),
  fGlobalSeqNoIn(MIN_SEQNO),
  fGlobalSeqNoOut(INT_MAX)
{
//  fCurrentRun=NULL;
}


FairParTSQLIo::FairParTSQLIo(FairDbConnectionPool const& cons, int const dbNum)
  : FairParIo(),
    fCurrentRun(NULL),
    fDefaultDb (dbNum),
    fConnections(FairDbTableInterfaceStore::Instance().fConnectionPool),
	fGlobalSeqNoIn(MIN_SEQNO),
    fGlobalSeqNoOut(INT_MAX)
{
//  fCurrentRun=NULL;
}


FairParTSQLIo::~FairParTSQLIo()
{
  disconnect();
}


bool FairParTSQLIo::check()
{
  //FairDbConnectionPool::Status s;
  int stat = -100;
  // Check if at least one DB is connected.
  if(fDefaultDb != -1) { // Has been specified.
    stat = fConnections->GetStatus(fDefaultDb);
    if(stat == FairDbConnectionPool::kFailed ||
        stat == FairDbConnectionPool::kClosed)
      std::cerr << "<Error> The connection to specified default Database"
                << " is not alive.\n";
  } else { // No selection
    for(size_t db = 0; db < fConnections->GetNumDb(); ++db) {
      stat = fConnections->GetStatus(db);
    }
  }
  return kTRUE;
}


void FairParTSQLIo::setDetParIo(Text_t* ioName)
{
  if (fConnections) {
    TObject* io = detParIoList->FindObject(ioName);
    // If does not exist
    if(!io) {
      if (strcmp(ioName, "FairGenericParIo") == 0) {
        io = new FairGenericParTSQLIo();
      }
      if (io) {
        detParIoList->Add(io);
      }
    }
  }
}

void FairParTSQLIo::disconnect()
{
  if(fConnections) {
    Int_t nexceptions = FairDbExceptionLog::GetGELog().Size();
    if (  nexceptions ) {
      DBLOG("FairDb",FairDbLog::kInfo)  << "Database Global Exception Log contains "
                                        << nexceptions << " entries:" << endl;;
      FairDbExceptionLog::GetGELog().Print();
    }

    std::cout << "-I- FairParTSQLIO:: Terminating connection: status = "
              << fConnections->GetStatusAsString(0) << " with n_exceptions# "
              << nexceptions
              <<"\n\n";
    delete fConnections;
    fConnections = 0;
  }
}

bool FairParTSQLIo::activateDetIo()
{
  std::cout << "-I- FairParTSQLIo::activateDetIo()\n";

  if(!fConnections) {
    return false;
  }
  FairDetParIo* io=new FairGenericParTSQLIo();
  detParIoList->Add(io);
  return true;
}

bool FairParTSQLIo::open()
{

  // Connection check ....
  for (Int_t iEntry = 0; iEntry < fConnections->GetNumDb(); ++iEntry) {

    Bool_t fail= kFALSE;

    auto_ptr<FairDbStatement>
    stmtDb(fConnections->CreateStatement(iEntry));
    if ( ! stmtDb.get() ) {
      	DBLOG("FairDb",FairDbLog::kWarning) << "Cannot get a statement for DB entry# " << iEntry
           << "\n  --->  Please check the FAIRDB_TSQL_* environment.  Transaction Failed  ... " << endl;
      return kFALSE;
    }


    // Now prepare Database Infrastructure for each DB entry
	DBLOG("FairDb",FairDbLog::kInfo) << "-I- FairParTSQLIo:.open() checking DB entry# " << iEntry  << endl;

    if (!fConnections->GetConnection(iEntry)->TableExists("FAIRDBGLOBALSEQNO") ) {

     std::vector<std::string> sql_cmds;
     string sql1("CREATE TABLE ");
     sql1 += "FAIRDBLOGENTRYVAL";
     sql1 += "( SEQNO          INT NOT NULL PRIMARY KEY AUTO_INCREMENT,";
     sql1 += "  TIMESTART      DATETIME NOT NULL,";
     sql1 += "  TIMEEND        DATETIME NOT NULL,";
     sql1 += "  DETID          TINYINT,";
     sql1 += "  DATAID         TINYINT,";
     sql1 += "  VERSION        INT,";
     sql1 += "  COMPOSITEID    INT,";
     sql1 += "  TIMEINCR       DATETIME NOT NULL,";
     sql1 += "  TIMETRANS      DATETIME NOT NULL);";

     string sql2("CREATE TABLE ");
     sql2 += "FAIRDBLOGENTRY";
     sql2 += "( SEQNO           INT,";
     sql2 += "  ROW_ID          INT,";
     sql2 += "  TABLENAME       TEXT,";
     sql2 += "  MIN_SEQNO       INT NOT NULL,";
     sql2 += "  MAX_SEQNO       INT NOT NULL,";
     sql2 += "  N_SEQNO         INT NOT NULL,";
     sql2 += "  USERNAME        TEXT,";
     sql2 += "  PROCESS_ID      TEXT,";
     sql2 += "  HOSTNAME        TEXT,";
     sql2 += "  SERVERNAME      TEXT,";
     sql2 += "  LOG_TITLE       TEXT);";
     
     string sql3("CREATE TABLE ");
     sql3 += "FAIRDBGLOBALSEQNO";
     sql3 += "( TABLENAME      CHAR(64) NOT NULL PRIMARY KEY,";
     sql3 += "  LASTUSEDSEQNO  INT );";

     stringstream insert_sql;
     insert_sql << "INSERT INTO FAIRDBGLOBALSEQNO VALUES ('*'," << GetGlobalSeqNoIn() << ");";
  
     sql_cmds.push_back(sql1);
     sql_cmds.push_back(sql2);
     sql_cmds.push_back(sql3);
     sql_cmds.push_back(insert_sql.str());
          

      // Now execute the assemble list of SQL commands.
      auto_ptr<FairDbStatement> stmtDbn(fConnections->CreateStatement(iEntry));

      std::vector<std::string>::iterator itr(sql_cmds.begin()), itrEnd(sql_cmds.end());
      while( itr != itrEnd ) {
        std::string& sql_cmd(*itr++);
		DBLOG("FairDb",FairDbLog::kInfo)  << " Creating Global Meta Data  at DB entry#  " 
										  << iEntry << "  SQL:" << sql_cmd << endl;
	    stmtDbn->ExecuteUpdate(sql_cmd.c_str());
        if ( stmtDbn->PrintExceptions() ) {
          fail = true;
          DBLOG("FairDb",FairDbLog::kFatal) << " ******* Error Creating Meta Data for DB Entry#" 
                                            <<  iEntry << endl;
        }
      }//! (sql_cmds)

      fConnections->SetAuthorisingEntry(iEntry);
      fConnections->GetConnection(iEntry)->SetTableExists();

	  DBLOG("FairDb",FairDbLog::kInfo) << " Meta-structure has been implemented ... continuing " << endl;

    } else {
      // Some Meta-Structure in DB is already existing ... check that !
      TSQLStatement* stmtTSQL = stmtDb->ExecuteQuery("select * from FAIRDBGLOBALSEQNO;");

      if ( stmtTSQL ) {
        while ( stmtTSQL->NextResultRow() ) {
          TString tableName = stmtTSQL->GetString(0);
          int lastUsedSeqNo = stmtTSQL->GetInt(1);
          int abase =  lastUsedSeqNo /  BAS_SEQNO;
          SetGlobalSeqNoIn(abase);
         if ( tableName == "*" && lastUsedSeqNo != GetGlobalSeqNoIn() )  {
              DBLOG("FairDb",FairDbLog::kInfo) << "FAIRDBGLOBALSEQNO table error. Entry * = " <<   lastUsedSeqNo
                 << " but should be: " <<  GetGlobalSeqNoIn() << endl;
            fail = kTRUE;
          } else if  ( tableName != "*" ) {
            string tn3(tableName.Data(),3);
            if ( lastUsedSeqNo < GetGlobalSeqNoIn() || lastUsedSeqNo > GetGlobalSeqNoOut() ) {
                DBLOG("FairDb",FairDbLog::kInfo) << " FAIRDBGLOBALSEQNO table error. Entry " <<  tableName
                   << " but should start with FAIRDB \n"
                   << "     and last used SEQNO: " << lastUsedSeqNo
                   << " should be in range [ " <<  GetGlobalSeqNoIn() << " .. " << GetGlobalSeqNoOut() <<  " ]" << endl;
              fail = kTRUE;
            }
          }
        }
      }

      if ( fail ) {
         DBLOG("FairDb",FairDbLog::kFatal)  
		     << "-I- FairParTSQLIo::open() The FAIRDBGLOBALSEQNO table at DB entry# " << iEntry << " is already\n"
             << " existing but not aligned in sequence nr. range [ " <<  GetGlobalSeqNoIn() << " .. " << GetGlobalSeqNoOut() << " ]"
             << " quit rather than risk damage to this table ... \n" << endl;
        return kFALSE;
      }

       DBLOG("FairDb",FairDbLog::kInfo)  << " Meta-structure for DB entry# " << iEntry 
                                         << " looks OK ... continuing" << endl;
    }

  }//! entries

  // Activate SQL Io
  FairRuntimeDb::instance()->activateParIo(this);
   DBLOG("FairDb",FairDbLog::kInfo) << " connected with DB Entries# " 
                                    << fConnections->GetNumDb() << endl;
  return kTRUE;
}

void FairParTSQLIo::print()
{
  std::cout << "<DEBUG> FairParTSQLIo::print()\n";
  if (fConnections) {
    std::cout << "<INFO> Number of available DBs = " << fConnections->GetNumDb()
              << std::endl;

    TIter next(detParIoList);
    FairDetParIo* io;
    std::cout << " Number of detector I/Os = " << detParIoList->GetSize()
              << "\nDetector IO list:\n";

    while ((io=(FairDetParIo*)next())) {
      std::cout<<" Name = " << io->GetName();
    }//while
    std::cout << std::endl;
  }//if
}//print


void FairParTSQLIo::readVersions(FairRtdbRun* aRun)
{
  // finds the current run containing the parameter container versions
  // in the ROOT file

  fCurrentRun = aRun;

}


void FairParTSQLIo::SetShutdown(Bool_t shutdown)
{
  // Shutdowm setting
  FairDbTableInterfaceStore::Instance().Set("Shutdown = 1");
  FairDbTableInterfaceStore::Instance().Update();

  DBLOG("FairDb",FairDbLog::kInfo) << " Complete Shutdown is set."<< endl;
}

void FairParTSQLIo::SetRollback(TString rollbackdate, TString tablename)
{
  // Rollback settings

  TString rb_cmd = "Rollback:" + tablename + " = '" + rollbackdate + "'";

  FairDbTableInterfaceStore::Instance().Set(rb_cmd.Data());
  FairDbTableInterfaceStore::Instance().Update();

  DBLOG("FairDb",FairDbLog::kInfo) << " Rollback for table: "
                                   << tablename.Data() << " At Date : " << rollbackdate.Data() << " is set "<< endl;
}

void FairParTSQLIo::SetRollbackMode(Int_t mode, TString tablename)
{
  // Rollback Modus settings

  TString modus;

  if ( mode == 0 ) {
    modus="TIMETRANS";
  } else {
    modus="TIMEINCR";
  }

  TString rb_cmd = "RollbackType:" + tablename + " = '" + modus+"'";

  FairDbTableInterfaceStore::Instance().Set(rb_cmd.Data());
  FairDbTableInterfaceStore::Instance().Update();

  DBLOG("FairDb",FairDbLog::kInfo) << " Rollback for table: "
                                   << tablename.Data() << " Using Field: " << modus.Data() << " is set "<< endl;
}


void FairParTSQLIo::SetHoldConnection(Int_t mode)
{

  TString hold_cmd;

  if ( mode == 0 ) { hold_cmd="MakeConnectionsPermanent = 0"; }
  if ( mode == 1 ) { hold_cmd="MakeConnectionsPermanent = 1"; }
  if ( mode == -1 ) { hold_cmd="MakeConnectionsPermanent = -1"; }

  FairDbTableInterfaceStore::Instance().Set(hold_cmd.Data());
  FairDbTableInterfaceStore::Instance().Update();

  DBLOG("FairDb",FairDbLog::kInfo) << " Server Connections set to modus: "  <<  mode << endl;

}


void FairParTSQLIo::SetQueryOrdering()
{
  TString q_order = "OrderContextQuery = 1";
  FairDbTableInterfaceStore::Instance().Set(q_order.Data());
  FairDbTableInterfaceStore::Instance().Update();
  DBLOG("FairDb",FairDbLog::kInfo) << " Set Query Ordering: 1" << endl;
}

void FairParTSQLIo::SetCache(TString cache_file)
{
  TString cache_cmd = "Level2Cache ";
  TString add_on = "'./'";
  TString cache_def;
  if ( cache_file.IsNull() ) { cache_def = cache_cmd + " = " + add_on; }
  else { cache_def = cache_cmd + " = " + "'"+ cache_file + "'"; }

  FairDbTableInterfaceStore::Instance().Set(cache_def.Data());
  FairDbTableInterfaceStore::Instance().Update();

  DBLOG("FairDb",FairDbLog::kInfo) << " Caching is set: "
                                   << cache_def.Data() << endl;

}


void FairParTSQLIo::CombineDataType(TString input_type, TString other_type)
{
  // Data type combination

  TString comb_cmd = "DataTypeUnion:" + input_type + " = '" + other_type+"'";

  FairDbTableInterfaceStore::Instance().Set(comb_cmd.Data());
  FairDbTableInterfaceStore::Instance().Update();

  DBLOG("FairDb",FairDbLog::kInfo) << " Data Type: "
                                   << input_type.Data() << " is combined with DataTypes: " << other_type.Data() << endl;

}


void FairParTSQLIo::SetVerbosity(Int_t level)
{
  FairDbTableInterfaceStore::Instance().SetVerbosity(level);
}


void FairParTSQLIo::SetGlobalSeqNoIn(Int_t seqno){
  // DB check for the SEQNO range calculation
  if ( (seqno <0) || (seqno>9) ) {
	DBLOG("FairDb", FairDbLog::kWarning) << "seqno basis: "<< seqno 
										 << "out of range [0..9], seqno will be reset to 0." << endl;
	seqno=0;
  }
  
  fGlobalSeqNoIn = seqno*BAS_SEQNO;
  fGlobalSeqNoOut = fGlobalSeqNoIn + INC_SEQNO;

  //cout << " SEQNO_IN -------> " << fGlobalSeqNoIn <<  " : " << fGlobalSeqNoOut << endl;
}
