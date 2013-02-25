#include <memory>
#include <cassert>

#include "TCollection.h"
#include "TList.h"
#include "TSQLColumnInfo.h"
#include "TSQLStatement.h"
#include "TSQLServer.h"
#include "TSQLTableInfo.h"
#include "TString.h"

#include "Detector.h"
#include "SimFlag.h"
#include "FairDbProxy.h"
#include "FairDbMultConnector.h"
#include "FairDbFieldType.h"
#include "FairDbResult.h"
#include "FairDbServices.h"
#include "FairDbString.h"
#include "FairDbStatement.h"
#include "FairDbTableMetaData.h"
#include "FairDbTimerManager.h"
#include "ValContext.h"
#include "FairDbString.h"

ClassImp(FairDbProxy)


FairDbProxy::FairDbProxy(FairDbMultConnector& cascader,
                         const string& tableName,
                         const FairDbTableMetaData* metaData,
                         const FairDbTableMetaData* metaValid,
                         const FairDbTableProxy* tableProxy) :
  fMultConnector(cascader),
  fMetaData(metaData),
  fMetaValid(metaValid),
  fSqlCondition(),
  fTableName(tableName),
  fTableNameUc(FairUtilString::ToUpper(tableName)),
  fTableProxy(tableProxy),
  fValSuffix("VAL")
{
  if ( fTableName != fTableNameUc ) { fValSuffix = "Validity"; }

}

FairDbProxy::~FairDbProxy()
{

}

void FairDbProxy::FindTimeBoundaries(const ValContext& vc,
                                     const FairDb::Task& task,
                                     UInt_t dbNo,
                                     ValTimeStamp earliestCreate,
                                     ValTimeStamp& start,
                                     ValTimeStamp& end) const
{
  cout << "FindTimeBoundaries for table " <<  fTableName
       << " context " << vc
       << " task " << task
       << " Earliest creation date " <<  earliestCreate
       << " database " << dbNo << endl;

//  Set the limits wide open
  start = ValTimeStamp(0,0);
  end   = ValTimeStamp(0x7FFFFFFF,0);

//  Construct a Time Gate on the current date.

  const ValTimeStamp curVTS = vc.GetTimeStamp();
  Int_t timeGate = FairDb::GetTimeGate(this->GetTableName());
  time_t vcSec = curVTS.GetSec() - timeGate;
  ValTimeStamp startGate(vcSec,0);
  vcSec += 2*timeGate;
  ValTimeStamp endGate(vcSec,0);
  string earliestCreateString(FairDb::MakeDateTimeString(earliestCreate));
  string startGateString(FairDb::MakeDateTimeString(startGate));
  string endGateString(FairDb::MakeDateTimeString(endGate));

// Extract information for ValContext.

  Detector::Detector_t    detType(vc.GetDetector());
  SimFlag::SimFlag_t       simFlg(vc.GetSimFlag());

// Use an auto_ptr to manage ownership of FairDbStatement and TSQLStatement
  auto_ptr<FairDbStatement> stmtDb(fMultConnector.CreateStatement(dbNo));

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
    sql << " and DetectorMask & " << static_cast<unsigned int>(detType)
        << " and SimMask & " << static_cast<unsigned int>(simFlg)
        << " and CREATIONDATE >= '" << earliestCreateString << "'"
        << " and  Task = " << task;
    cout << "  FindTimeBoundaries query no. " << i_limit
         << " SQL:" <<sql.c_str() << endl;

    auto_ptr<TSQLStatement> stmt(stmtDb->ExecuteQuery(sql.c_str()));
    stmtDb->PrintExceptions(0);

//  If the query returns data, convert to a time stamp and trim the limits
    TString date;
    if ( ! stmt.get() || ! stmt->NextResultRow() || stmt->IsNull(0) ) { continue; }
    date = stmt->GetString(0);
    if ( date.IsNull() ) { continue; }
    ValTimeStamp ts(FairDb::MakeTimeStamp(date.Data()));
    cout << "  FindTimeBoundaries query result: " << ts << endl;
    if ( i_limit <= 2 && ts < end   ) { end   = ts; }
    if ( i_limit >= 3 && ts > start ) { start = ts; }

  }

  cout << "FindTimeBoundaries for table " <<  fTableName
       << " found " << start << " .. " << end << endl;

}

UInt_t FairDbProxy::GetNumDb() const
{
  return fMultConnector.GetNumDb();
}

FairDbResultSet*  FairDbProxy::QueryAllValidities (UInt_t dbNo,UInt_t seqNo) const
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

  cout << "Database: " << dbNo
       << " query: " << sql.GetString() << endl;

//  Apply query and return result..
  FairDbStatement* stmtDb = fMultConnector.CreateStatement(dbNo);
  return new FairDbResultSet(stmtDb,sql,fMetaValid,fTableProxy,dbNo);

}



FairDbResultSet*  FairDbProxy::QuerySeqNo(UInt_t seqNo, UInt_t dbNo) const
{

  FairDbTimerManager::gTimerManager.RecMainQuery();
  FairDbString sql;
  sql << "select * from " << fTableName << " where "
      << "    SEQNO= " << seqNo;

  if ( FairDbServices::OrderContextQuery() && fMetaData->HasRowCounter() ) {
    sql << " order by ROW_COUNTER";
  }

  cout  << "Database: " << dbNo
        << " SeqNo query: " << sql.c_str() << endl;

//  Apply query and return result..
  FairDbStatement* stmtDb = fMultConnector.CreateStatement(dbNo);
  return new FairDbResultSet(stmtDb,sql,fMetaData,fTableProxy,dbNo);

}
FairDbResultSet*  FairDbProxy::QuerySeqNos(SeqList_t& seqNos,
    UInt_t dbNo,
    const string& sqlData,
    const string& fillOpts) const
{
  if ( seqNos.size() == 0 ) { return 0; }

  FairDbTimerManager::gTimerManager.RecMainQuery();
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

  if ( FairDbServices::OrderContextQuery() && fMetaData->HasRowCounter() ) {
    sql << ",ROW_COUNTER";
  }

  cout << "Database: " << dbNo
       << " SeqNos query: " << sql.c_str() << endl;

//  Apply query and return result..
  FairDbStatement* stmtDb = fMultConnector.CreateStatement(dbNo);
  return new FairDbResultSet(stmtDb,sql,fMetaData,fTableProxy,dbNo,fillOpts);

}
FairDbResultSet*  FairDbProxy::QueryValidity (const ValContext& vc,
    const FairDb::Task& task,
    UInt_t dbNo) const
{

  const ValTimeStamp curVTS = vc.GetTimeStamp();
  Int_t timeGate = FairDb::GetTimeGate(this->GetTableName());
  time_t vcSec = curVTS.GetSec() - timeGate;
  ValTimeStamp startGate(vcSec,0);
  vcSec += 2*timeGate;
  ValTimeStamp endGate(vcSec,0);

// Extract information for ValContext.

  string startGateString(FairDb::MakeDateTimeString(startGate));
  string endGateString(FairDb::MakeDateTimeString(endGate));
  Detector::Detector_t    detType(vc.GetDetector());
  SimFlag::SimFlag_t       simFlg(vc.GetSimFlag());

// Generate SQL for context.

  FairDbString context;
  context << "    TimeStart <= '" << endGateString << "' "
          << "and TimeEnd    > '" << startGateString << "' "
          << "and DetectorMask & " << static_cast<unsigned int>(detType)
          << " and SimMask & " << static_cast<unsigned int>(simFlg);

//  Apply query and return result..

  return this->QueryValidity(context.GetString(),task,dbNo);

}

FairDbResultSet*  FairDbProxy::QueryValidity (const string& context,
    const FairDb::Task& task,
    UInt_t dbNo) const
{

// Generate SQL for validity table.

  FairDbString sql;

// Queries are normally ordered by creation date (the later the better)
// but make an exception for DBUSUBRUNSUMMARY which has open-ended
// end date and an unreliable creation date so the latest start date is
// best.
// Same for DBURUNSUMMARY.  Bogus entries with wrong validity are stomping
// real values for the same reason.  These should be cleaned +up in the DB
// but TIMESTART should be always more valid than CREATIONDATE for such info
  string orderByName("CREATIONDATE");
  if ((fTableName == "DBUSUBRUNSUMMARY") || (fTableName == "DBURUNSUMMARY")) {
    orderByName = "TIMESTART";
  }
  sql << "select * from " << fTableName << fValSuffix
      << " where " ;
  if ( fSqlCondition != ""
     ) { sql << fSqlCondition << " and "; }
  sql << context;
  if ( task != FairDb::kAnyTask
     ) sql << " and  Task = " << task
             << " order by " << orderByName << " desc;" << '\0';

  cout << "Database: " << dbNo
       << " query: " << sql.c_str() << endl;

//  Apply query and return result..

  FairDbStatement* stmtDb = fMultConnector.CreateStatement(dbNo);
  return new FairDbResultSet(stmtDb,sql,fMetaValid,fTableProxy,dbNo);

}
//.....................................................................

FairDbResultSet*  FairDbProxy::QueryValidity (UInt_t seqNo,
    UInt_t dbNo) const
{
// Generate SQL for validity table.

  FairDbString sql;
  sql << "select * from " << fTableName << fValSuffix << " where ";
  if ( fSqlCondition != "" ) { sql << fSqlCondition << " and "; }
  sql << "SEQNO = " << seqNo << ";";

  cout << "Database: " << dbNo
       << " SEQNO query: " << sql.c_str() << endl;

//  Apply query and return result..

  FairDbStatement* stmtDb = fMultConnector.CreateStatement(dbNo);
  return new FairDbResultSet(stmtDb,sql,fMetaValid,fTableProxy,dbNo);

}

Bool_t FairDbProxy::RemoveSeqNo(UInt_t seqNo,
                                UInt_t dbNo) const
{
// Generate SQL to remove SeqNo in main table.
  FairDbString sql;
  sql  << "delete from  " << fTableName
       << " where SEQNO = " << seqNo << ";"
       << '\0';

  cout << "Database: " << dbNo
       << " RemoveSeqNo SQL: " << sql.c_str() << endl;

//  Apply query.
  auto_ptr<FairDbStatement> stmtDb(fMultConnector.CreateStatement(dbNo));
  if ( ! stmtDb.get() ) { return false; }
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    cout << "SQL: " << sql.c_str()
         << " Failed. " << endl;
    return false;
  }

// Generate SQL to remove SeqNo in validity table.
  sql.GetString().erase();
  sql << "delete from  " << fTableName << fValSuffix
      << " where SEQNO = " << seqNo << ";"
      << '\0';

  cout << "Database: " << dbNo
       << " RemoveSeqNo SQL: " << sql.c_str() << endl;

//  Apply query.
  if (  ! stmtDb->ExecuteUpdate(sql.c_str()) ||  stmtDb->PrintExceptions() ) {
    cout << "SQL: " << sql.c_str()
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
      << " set INSERTDATE = \'" << ts.AsString("s")
      << "\' where SEQNO = " << SeqNo << ";"
      << '\0';

  cout << "Database: " << dbNo
       << " ReplaceInsertDate SQL: "
       << sql.c_str() << endl;

//  Apply query.
  auto_ptr<FairDbStatement> stmtDb(fMultConnector.CreateStatement(dbNo));
  if ( ! stmtDb.get() ) { return false; }
  if (! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    cout << "SQL: " << sql.c_str()
         << " Failed. " << endl;
    return false;
  }

  return true;

}
//.....................................................................

Bool_t FairDbProxy::ReplaceSeqNo(UInt_t oldSeqNo,
                                 UInt_t newSeqNo,
                                 UInt_t dbNo) const
{

  if ( ! fMultConnector.GetConnection(dbNo) ) {
    cout
        << "Cannot renumber " << oldSeqNo
        << " no connection to cascade entry " << dbNo << endl;
    return false;
  }
// Deal with Oracle separately - it's best.
  if ( fMultConnector.GetConnection(dbNo)->GetDbType () == FairDb::kOracle ) {
    return this->ReplaceSeqNoOracle(oldSeqNo,newSeqNo,dbNo);
  }

// Generate SQL to replace SeqNo in validity table.
  FairDbString sql;
  sql << "update  " << fTableName << fValSuffix
      << " set SEQNO = " << newSeqNo
      << " where SEQNO = " << oldSeqNo << ";"
      << '\0';

  cout << "Database: " << dbNo
       << " ReplaceSeqNo SQL: " << sql.c_str() << endl;

//  Apply query.
  auto_ptr<FairDbStatement> stmtDb(fMultConnector.CreateStatement(dbNo));
  if ( ! stmtDb.get() ) { return false; }
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    cout << "SQL: " << sql.c_str()
         << " Failed. " << endl;
    return false;
  }

// Generate SQL to replace SeqNo in main table.
  sql.GetString().erase();
  sql  << "update  " << fTableName
       << " set SEQNO = " << newSeqNo
       << " where SEQNO = " << oldSeqNo << ";"
       << '\0';

  cout << "Database: " << dbNo
       << " ReplaceSeqNo SQL: " << sql.c_str() << endl;

//  Apply query.
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    cout << "SQL: " << sql.c_str()
         << " Failed. " << endl;
    return false;
  }

  return true;

}

Bool_t FairDbProxy::ReplaceSeqNoOracle(UInt_t oldSeqNo,
                                       UInt_t newSeqNo,
                                       UInt_t dbNo) const
{

  FairDbResultSet* rsOld = QueryValidity(oldSeqNo,dbNo);
  if ( rsOld && rsOld->IsBeforeFirst() ) { rsOld->FetchRow(); }
  if ( ! rsOld || rsOld->IsExhausted() ) {
    cout << "Cannot renumber " << oldSeqNo
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
  cout << "Database: " << dbNo
       << " ReplaceSeqNo SQL (insert new VAL): " << sql.c_str() << endl;
  delete rsOld;

//  Apply query.
  auto_ptr<FairDbStatement> stmtDb(fMultConnector.CreateStatement(dbNo));
  if ( ! stmtDb.get() ) { return false; }
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    cout << "SQL: " << sql.c_str()
         << " Failed. " << endl;
    return false;
  }

// Generate SQL to replace SeqNo in main table.
  sql.GetString().erase();
  sql  << "update  " << fTableName
       << " set SEQNO = " << newSeqNo
       << " where SEQNO = " << oldSeqNo << ";";

  cout << "Database: " << dbNo
       << " ReplaceSeqNo SQL (rename main entry): " << sql.c_str() << endl;

//  Apply query.
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    cout << "SQL: " << sql.c_str()
         << " Failed. " << endl;
    return false;
  }

// Generate SQL to remove old SeqNo in validity table.
  sql.GetString().erase();
  sql  << "delete from  " << fTableName << fValSuffix
       << " where SEQNO = " << oldSeqNo << ";";

  cout << "Database: " << dbNo
       << " ReplaceSeqNo SQL (delete old VAL): " << sql.c_str() << endl;

//  Apply query.
  if ( ! stmtDb->ExecuteUpdate(sql.c_str()) || stmtDb->PrintExceptions() ) {
    cout << "SQL: " << sql.c_str()
         << " Failed. " << endl;
    return false;
  }

  return true;

}

void  FairDbProxy::StoreMetaData(FairDbTableMetaData& metaData) const
{


  const char* tableName = metaData.TableName().c_str();
  cout << "Get meta-data for table: " << tableName << endl;

//  Check each Db in turn until table found and store table meta data.

  for ( UInt_t dbNo = 0; dbNo < fMultConnector.GetNumDb(); dbNo++ ) {
    FairDbConnection* connection = fMultConnector.GetConnection(dbNo);
    TSQLServer* server = connection->GetServer();
    if ( ! server ) { continue; }
    connection->Connect();
    TSQLTableInfo* meta = server->GetTableInfo(tableName);
    if ( ! meta ) {
      connection->DisConnect();
      continue;
    }
    cout << "Meta-data query succeeded on cascade entry " << dbNo << endl;

    // Clear out any existing data, although there should not be any.
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

      // For now continue to check for unsigned (even though not supported)
      if ( !colInfo->IsSigned() ) { fldType.SetUnsigned(); }
      metaData.SetColFieldType(fldType,col);

      metaData.SetColIsNullable(col,colInfo->IsNullable());


      cout     << "Column "         << col << " " << name
               << " SQL type "      << colInfo->GetSQLType()
               << " SQL type name " << colInfo->GetTypeName()
               << " DBI type "      << fldType.AsString()
               << " data size: "    << fldType.GetSize()
               << " col size: "     << colInfo->GetLength() << endl;

    }
    delete meta;
    connection->DisConnect();
    return;
  }
}


Bool_t FairDbProxy::TableExists(Int_t selectDbNo) const
{

  return fMultConnector.TableExists(fTableName,selectDbNo);

}

