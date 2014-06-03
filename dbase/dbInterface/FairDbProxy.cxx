/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbProxy.h"
#include "FairDbLogService.h"
#include "FairDbConnection.h"           // for FairDbConnection
#include "FairDbFieldType.h"            // for FairDbFieldType
#include "FairDbConnectionPool.h"        // for FairDbConnectionPool
#include "FairDbResult.h"               // for cout, FairDbResultPool, endl
#include "FairDbUtils.h"             // for FairDbUtils
#include "FairDbStatement.h"            // for FairDbStatement
#include "FairDbString.h"               // for FairDbString, ToUpper
#include "FairDbTableMetaData.h"        // for FairDbTableMetaData
#include "FairDbStopWatchManager.h"         // for FairDbStopWatchManager, etc
#include "DataType.h"                    // for DataType_t
#include "ValCondition.h"                 // for ValCondition, operator<<
#include "ValTimeStamp.h"               // for ValTimeStamp, operator<<, etc
#include "db_detector_def.h"            // for Detector, etc

#include "Riosfwd.h"                    // for ostream
#include "TCollection.h"                // for TIter
#include "TList.h"                      // for TList
#include "TObject.h"                    // for TObject
#include "TSQLColumnInfo.h"             // for TSQLColumnInfo
#include "TSQLServer.h"                 // for TSQLServer
#include "TSQLStatement.h"              // for TSQLStatement
#include "TSQLTableInfo.h"              // for TSQLTableInfo
#include "TString.h"                    // for TString

#include <sys/select.h>                 // for time_t
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <memory>                       // for auto_ptr, etc

using std::cout;
using std::endl;
using std::auto_ptr;
using std::string;

ClassImp(FairDbProxy)


FairDbProxy::FairDbProxy(FairDbConnectionPool& cascader,
                         const string& tableName,
                         const FairDbTableMetaData* metaData,
                         const FairDbTableMetaData* metaValid,
                         const FairDbTableInterface* tableProxy) :
  fConnectionPool(cascader),
  fMetaData(metaData),
  fMetaValid(metaValid),
  fSqlCondition(),
  fTableName(tableName),
  fTableNameUc(FairUtilString::ToUpper(tableName)),
  fTableInterface(tableProxy),
  fValSuffix("VAL")
{
  if ( fTableName != fTableNameUc ) { fValSuffix = "Validity"; }

}

FairDbProxy::~FairDbProxy()
{

}

void FairDbProxy::FindTimeLimits(const ValCondition& vc,
                                 const FairDb::Version& task,
                                 UInt_t dbNo,
                                 ValTimeStamp earliestCreate,
                                 ValTimeStamp& start,
                                 ValTimeStamp& end) const
{
  DBLOG("FairDb",FairDbLog::kInfo) << "FindTimeLimits for table: " <<  fTableName
                                   << " context: " << vc
                                   << " version: " << task
                                   << " Earliest transaction date: " <<  earliestCreate
                                   << " database: " << dbNo << endl;

//  Set the limits wide open
  start = ValTimeStamp(0,0);
  end   = ValTimeStamp(0x7FFFFFFF,0);

//  Construct a Time Gate on the current date.

  const ValTimeStamp curVTS = vc.GetTimeStamp();
  Int_t timeGate = FairDb::GetTimeWindow(this->GetTableName());
  time_t vcSec = curVTS.GetSec() - timeGate;
  ValTimeStamp startGate(vcSec,0);
  vcSec += 2*timeGate;
  ValTimeStamp endGate(vcSec,0);
  string earliestCreateString(FairDb::MakeDateTimeString(earliestCreate));
  string startGateString(FairDb::MakeDateTimeString(startGate));
  string endGateString(FairDb::MakeDateTimeString(endGate));

// Extract information for ValCondition.

  Detector::Detector_t    detType(vc.GetDetector());
  DataType::DataType_t       simFlg(vc.GetDataType());

// Use an auto_ptr to manage ownership of FairDbStatement and TSQLStatement
  auto_ptr<FairDbStatement> stmtDb(fConnectionPool.CreateStatement(dbNo));

  for (int i_limit =1; i_limit <= 4; ++i_limit ) {
    FairDbString sql("select ");
    if ( i_limit == 1 ) sql  << "min(TIMESTART) from " << fTableName
                               << "VAL where TIMESTART > '" << endGateString << "' ";
    if ( i_limit == 2 ) sql  << "min(TIMEEND) from " << fTableName
                               << "VAL where TIMEEND > '" << endGateString  << "' ";
    if ( i_limit == 3 ) sql  << "max(TIMESTART) from " << fTableName
                               << "VAL where TIMESTART < '" << startGateString << "' ";
    if ( i_limit == 4 ) sql  << "max(TIMEEND) from " << fTableName
                               << "VAL where TIMEEND < '" << startGateString  << "' ";
    sql << " and DETID & " << static_cast<unsigned int>(detType)
        << " and DATAID & " << static_cast<unsigned int>(simFlg)
        << " and TIMEINCR >= '" << earliestCreateString << "'"
        << " and  VERSION = " << task;
    DBLOG("FairDb",FairDbLog::kInfo) << "  FindTimeLimits query id: " << i_limit
                                     << " SQL:" <<sql.c_str() << endl;

    auto_ptr<TSQLStatement> stmt(stmtDb->ExecuteQuery(sql.c_str()));
    stmtDb->PrintExceptions(0);

//  If the query returns data, convert to a time stamp and trim the limits
    TString date;
    if ( ! stmt.get() || ! stmt->NextResultRow() || stmt->IsNull(0) ) { continue; }
    date = stmt->GetString(0);
    if ( date.IsNull() ) { continue; }
    ValTimeStamp ts(FairDb::MakeTimeStamp(date.Data()));
    DBLOG("FairDb",FairDbLog::kInfo) << "  FindTimeLimits query result: " << ts << endl;
    if ( i_limit <= 2 && ts < end   ) { end   = ts; }
    if ( i_limit >= 3 && ts > start ) { start = ts; }

  }

  DBLOG("FairDb",FairDbLog::kInfo)<< "FindTimeLimits for table: " <<  fTableName
                                  << " found: " << start << " .. " << end << endl;

}

UInt_t FairDbProxy::GetNumDb() const
{
  return fConnectionPool.GetNumDb();
}

FairDbResultPool*  FairDbProxy::QueryAllValidities (UInt_t dbNo,UInt_t seqNo) const
{

  FairDbString sql;

  sql << "select * from " << fTableName << fValSuffix;
  if ( fSqlCondition != "" ) { sql << " where " << fSqlCondition; }
  if ( seqNo > 0 ) {
    if ( fSqlCondition == "" ) { sql << " where "; }
    else { sql << " and "; }
    sql << "seqno = " << seqNo;
  }
  sql  << ";" << '\0';

  DBLOG("FairDb",FairDbLog::kInfo) << "Database: " << dbNo
                                   << " query: " << sql.GetString() << endl;

  FairDbStatement* stmtDb = fConnectionPool.CreateStatement(dbNo);
  return new FairDbResultPool(stmtDb,sql,fMetaValid,fTableInterface,dbNo);

}



FairDbResultPool*  FairDbProxy::QuerySeqNo(UInt_t seqNo, UInt_t dbNo) const
{

  FairDbStopWatchManager::gStopWatchManager.RecMainQuery();
  FairDbString sql;
  sql << "select * from " << fTableName << " where "
      << "    SEQNO= " << seqNo;

  if ( FairDbUtils::OrderContextQuery() && fMetaData->HasRowCounter() ) {
    sql << " order by ROW_ID";
  }

  DBLOG("FairDb",FairDbLog::kInfo)   << "Database: " << dbNo
                                     << " SeqNo query: " << sql.c_str() << endl;

//  Apply query and return result..
  FairDbStatement* stmtDb = fConnectionPool.CreateStatement(dbNo);
  return new FairDbResultPool(stmtDb,sql,fMetaData,fTableInterface,dbNo);

}

FairDbResultPool*  FairDbProxy::QuerySeqNos(SeqList_t& seqNos,
    UInt_t dbNo,
    const string& sqlData,
    const string& fillOpts) const
{
  if ( seqNos.size() == 0 ) { return 0; }

  FairDbStopWatchManager::gStopWatchManager.RecMainQuery();
  FairDbString sql;
  sql << "select * from " << fTableName << " where ";

  if ( sqlData != "" ) { sql << "( "; }
  Bool_t first = kTRUE;
  SeqList_t::const_iterator itr1 = seqNos.begin();

  while ( itr1 != seqNos.end() ) {
    UInt_t seq1 = *itr1;
    UInt_t seq2 = seq1;
    SeqList_t::const_iterator itr2 = itr1;
    while ( itr2 != seqNos.end() && seq2 == *itr2 ) {
      ++itr2;
      ++seq2;
    }
    if ( first ) {
      first = kFALSE;
    } else {
      sql << "or ";
    }
    if ( seq2 > seq1 + 1) {
      sql << "SEQNO between " << seq1 << " and " << seq2-1 << ' ';
      itr1 = itr2;
    } else {
      sql << "SEQNO = " << seq1 << ' ';
      ++itr1;
    }
  }

  if ( sqlData != "" ) { sql << ")  and " << "(" << sqlData << ")" << " "; }

  sql << "order by SEQNO";

  if ( FairDbUtils::OrderContextQuery() && fMetaData->HasRowCounter() ) {
    sql << ",ROW_ID";
  }

  DBLOG("FairDb",FairDbLog::kInfo)  << "Database: " << dbNo
                                    << " SeqIds query: " << sql.c_str() << endl;

//  Apply query and return result..
  FairDbStatement* stmtDb = fConnectionPool.CreateStatement(dbNo);
  return new FairDbResultPool(stmtDb,sql,fMetaData,fTableInterface,dbNo,fillOpts);

}
FairDbResultPool*  FairDbProxy::QueryValidity (const ValCondition& vc,
    const FairDb::Version& task,
    UInt_t dbNo) const
{

  const ValTimeStamp curVTS = vc.GetTimeStamp();
  Int_t timeGate = FairDb::GetTimeWindow(this->GetTableName());
  time_t vcSec = curVTS.GetSec() - timeGate;
  ValTimeStamp startGate(vcSec,0);
  vcSec += 2*timeGate;
  ValTimeStamp endGate(vcSec,0);

// Get info  for ValCondition.

  string startGateString(FairDb::MakeDateTimeString(startGate));
  string endGateString(FairDb::MakeDateTimeString(endGate));
  Detector::Detector_t    detType(vc.GetDetector());
  DataType::DataType_t       simFlg(vc.GetDataType());

// Generate SQL for context.

  FairDbString context;
  context << "    TimeStart <= '" << endGateString << "' "
          << "and TimeEnd    > '" << startGateString << "' "
          << "and DETID & " << static_cast<unsigned int>(detType)
          << " and DATAID & " << static_cast<unsigned int>(simFlg);


  return this->QueryValidity(context.GetString(),task,dbNo);

}

FairDbResultPool*  FairDbProxy::QueryValidity (const string& context,
    const FairDb::Version& task,
    UInt_t dbNo) const
{

// Create SQL statement for the validation table.

  FairDbString sql;

  string orderByName("TIMEINCR");
  if ((fTableName == "FAIRDRUNSUMMARY") ) {
    orderByName = "TIMESTART";
  }
  sql << "select * from " << fTableName << fValSuffix
      << " where " ;
  if ( fSqlCondition != ""
     ) { sql << fSqlCondition << " and "; }
  sql << context;
  if ( task != FairDb::kAnyVersion
     ) sql << " and  Version = " << task
             << " order by " << orderByName << " desc;" << '\0';

  DBLOG("FairDb",FairDbLog::kInfo) << "db_id: " << dbNo
                                   << " SQL query: " << sql.c_str() << endl;


  FairDbStatement* stmtDb = fConnectionPool.CreateStatement(dbNo);
  return new FairDbResultPool(stmtDb,sql,fMetaValid,fTableInterface,dbNo);
}


FairDbResultPool*  FairDbProxy::QueryValidity (UInt_t seqNo,
    UInt_t dbNo) const
{
// Generate SQL for validity table.

  FairDbString sql;
  sql << "select * from " << fTableName << fValSuffix << " where ";
  if ( fSqlCondition != "" ) { sql << fSqlCondition << " and "; }
  sql << "SEQNO = " << seqNo << ";";

  DBLOG("FairDb",FairDbLog::kInfo)  << "db_id: " << dbNo
                                    << " SEQNO query: " << sql.c_str() << endl;

  FairDbStatement* stmtDb = fConnectionPool.CreateStatement(dbNo);
  return new FairDbResultPool(stmtDb,sql,fMetaValid,fTableInterface,dbNo);

}

Bool_t FairDbProxy::RemoveSeqNo(UInt_t seqNo,
                                UInt_t dbNo) const
{
// Generate SQL to remove SeqNo in main table.
  FairDbString sql;
  sql  << "delete from  " << fTableName
       << " where SEQNO = " << seqNo << ";"
       << '\0';

  DBLOG("FairDb",FairDbLog::kInfo)<< "Database: " << dbNo
                                  << " RemoveSeqNo SQL: " << sql.c_str() << endl;

//  Apply query.
  auto_ptr<FairDbStatement> stmtDb(fConnectionPool.CreateStatement(dbNo));
  if ( ! stmtDb.get() ) { return false; }
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "SQL: " << sql.c_str()
                                            << " Failed. " << endl;
    return false;
  }

// Generate SQL to remove SeqNo in validity table.
  sql.GetString().erase();
  sql << "delete from  " << fTableName << fValSuffix
      << " where SEQNO = " << seqNo << ";"
      << '\0';

  DBLOG("FairDb",FairDbLog::kInfo) << "Database: " << dbNo
                                   << " RemoveSeqNo SQL: " << sql.c_str() << endl;

//  Apply query.
  if (  ! stmtDb->ExecuteUpdate(sql.c_str()) ||  stmtDb->PrintExceptions() ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "SQL: " << sql.c_str()
                                            << " Failed. " << endl;
    return false;
  }

  return true;

}

Bool_t FairDbProxy::ReplaceInsertDate(const ValTimeStamp& ts,
                                      UInt_t SeqNo,
                                      UInt_t dbNo) const
{

// Generate SQL.
  FairDbString sql;
  sql << "update  " << fTableName << fValSuffix
      << " set TIMETRANS = \'" << ts.AsString("s")
      << "\' where SEQNO = " << SeqNo << ";"
      << '\0';

  DBLOG("FairDb",FairDbLog::kInfo) << "Database: " << dbNo
                                   << " ReplaceInsertDate SQL: "
                                   << sql.c_str() << endl;

//  Apply query.
  auto_ptr<FairDbStatement> stmtDb(fConnectionPool.CreateStatement(dbNo));
  if ( ! stmtDb.get() ) { return false; }
  if (! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "SQL: " << sql.c_str()
                                            << " Failed. " << endl;
    return false;
  }

  return true;

}


Bool_t FairDbProxy::ReplaceSeqNo(UInt_t oldSeqNo,
                                 UInt_t newSeqNo,
                                 UInt_t dbNo) const
{

  if ( ! fConnectionPool.GetConnection(dbNo) ) {
    DBLOG("FairDb",FairDbLog::kWarning)
        << "Cannot renumber " << oldSeqNo
        << " no connection to DB entry# " << dbNo << endl;
    return false;
  }
  // Specs for Oracle
  if ( fConnectionPool.GetConnection(dbNo)->GetDbType () == FairDb::kOracle ) {
    return this->ReplaceSeqNoOracle(oldSeqNo,newSeqNo,dbNo);
  }

  // Generate SQL to replace SeqNo in validity table.
  FairDbString sql;
  sql << "update  " << fTableName << fValSuffix
      << " set SEQNO = " << newSeqNo
      << " where SEQNO = " << oldSeqNo << ";"
      << '\0';

  DBLOG("FairDb",FairDbLog::kInfo) << "Database: " << dbNo
                                   << " ReplaceSeqNo SQL: " << sql.c_str() << endl;

//  Apply query.
  auto_ptr<FairDbStatement> stmtDb(fConnectionPool.CreateStatement(dbNo));
  if ( ! stmtDb.get() ) { return false; }
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "SQL: " << sql.c_str()
                                            << " Failed. " << endl;
    return false;
  }

// Generate SQL to replace SeqNo in main table.
  sql.GetString().erase();
  sql  << "update  " << fTableName
       << " set SEQNO = " << newSeqNo
       << " where SEQNO = " << oldSeqNo << ";"
       << '\0';

  DBLOG("FairDb",FairDbLog::kInfo) << "Database: " << dbNo
                                   << " ReplaceSeqNo SQL: " << sql.c_str() << endl;

//  Apply query.
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "SQL: " << sql.c_str()
                                            << " Failed. " << endl;
    return false;
  }

  return true;

}

Bool_t FairDbProxy::ReplaceSeqNoOracle(UInt_t oldSeqNo,
                                       UInt_t newSeqNo,
                                       UInt_t dbNo) const
{

  FairDbResultPool* rsOld = QueryValidity(oldSeqNo,dbNo);
  if ( rsOld && rsOld->IsBeforeFirst() ) { rsOld->FetchRow(); }
  if ( ! rsOld || rsOld->IsExhausted() ) {
    DBLOG("FairDb",FairDbLog::kWarning) << "Cannot renumber " << oldSeqNo
                                        << " it does not exist" << endl;
    delete rsOld;
    return false;
  }

// Generate SQL to add new SeqNo in validity vable.

  FairDbString sql;
  sql << "insert into " << fTableName << fValSuffix
      << " values (" << newSeqNo;

  rsOld->IncrementCurCol();
  UInt_t numCols =rsOld->NumCols();
  for (UInt_t iCol = 2; iCol <= numCols; ++iCol) {
    UInt_t concept = rsOld->CurColFieldType().GetConcept();
    string delim = "";
    if (    concept == FairDb::kString
            || concept == FairDb::kDate
            || concept == FairDb::kChar ) { delim = "\'"; }
    sql << "," << delim << rsOld->CurColValue() << delim ;
    rsOld->IncrementCurCol();
  }
  sql << ")";
  DBLOG("FairDb",FairDbLog::kInfo) << "Database: " << dbNo
                                   << " ReplaceSeqNo SQL (insert new VAL): " << sql.c_str() << endl;
  delete rsOld;

//  Apply query.
  auto_ptr<FairDbStatement> stmtDb(fConnectionPool.CreateStatement(dbNo));
  if ( ! stmtDb.get() ) { return false; }
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20)<< "SQL: " << sql.c_str()
                                           << " Failed. " << endl;
    return false;
  }

// Generate SQL to replace SeqNo in main table.
  sql.GetString().erase();
  sql  << "update  " << fTableName
       << " set SEQNO = " << newSeqNo
       << " where SEQNO = " << oldSeqNo << ";";

  DBLOG("FairDb",FairDbLog::kInfo) << "Database: " << dbNo
                                   << " ReplaceSeqNo SQL (rename main entry): " << sql.c_str() << endl;

//  Apply query.
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "SQL: " << sql.c_str()
                                            << " Failed. " << endl;
    return false;
  }

// Generate SQL to remove old SeqNo in validity table.
  sql.GetString().erase();
  sql  << "delete from  " << fTableName << fValSuffix
       << " where SEQNO = " << oldSeqNo << ";";

  DBLOG("FairDb",FairDbLog::kInfo) << "Database: " << dbNo
                                   << " ReplaceSeqNo SQL (delete old VAL): " << sql.c_str() << endl;

//  Apply query.
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "SQL: " << sql.c_str()
                                            << " Failed. " << endl;
    return false;
  }

  return true;

}

void  FairDbProxy::CreateMetaData(FairDbTableMetaData& metaData) const
{

  const char* tableName = metaData.TableName().c_str();
  DBLOG("FairDb",FairDbLog::kInfo) << "Create meta-data for table: " << tableName << endl;

  // Checking meta-data
  for ( UInt_t dbNo = 0; dbNo < fConnectionPool.GetNumDb(); dbNo++ ) {
    FairDbConnection* connection = fConnectionPool.GetConnection(dbNo);
    TSQLServer* server = connection->GetServer();
    if ( ! server ) { continue; }
    connection->Connect();
    TSQLTableInfo* meta = server->GetTableInfo(tableName);
    if ( ! meta ) {
      connection->DisConnect();
      continue;
    }
    DBLOG("FairDb",FairDbLog::kInfo) << "Meta-data query succeeded on db_id: " << dbNo << endl;

    // Clear out possible existing data
    metaData.Clear();

    const TList* cols =  meta->GetColumns();
    TIter colItr(cols);
    int col = 0;
    while ( TSQLColumnInfo* colInfo = dynamic_cast<TSQLColumnInfo*>(colItr.Next()) ) {

      ++col;
      string name(colInfo->GetName());
      name = FairUtilString::ToUpper(name);
      metaData.SetColName(name,col);

      FairDbFieldType fldType(colInfo->GetSQLType(),
                              colInfo->GetLength(),
                              colInfo->GetTypeName());

      // For now continue to check for unsigned
      if ( !colInfo->IsSigned() ) { fldType.SetUnsigned(); }
      metaData.SetColFieldType(fldType,col);

      metaData.SetColIsNullable(col,colInfo->IsNullable());


      DBLOG("FairDb",FairDbLog::kInfo) << "Column: "         << col << " | " <<  name  << " | "
                                       << " SQL_type: "      << colInfo->GetSQLType()  << " | "
                                       << " SQL_type_def: " << colInfo->GetTypeName()  << " | "
                                       << " DB_data_type: "      << fldType.AsString()  << " | "
                                       << " data_size: "    << fldType.GetSize() << " | "
                                       << " col_length: "     << colInfo->GetLength() << endl;
    }

    delete meta;
    connection->DisConnect();
    return;
  }
}


Bool_t FairDbProxy::TableExists(Int_t selectDbNo) const
{
  return fConnectionPool.TableExists(fTableName,selectDbNo);
}

