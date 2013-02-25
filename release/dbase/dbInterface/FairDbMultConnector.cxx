#include <cstdlib>
#include <memory>
using std::auto_ptr;
#include <sstream>

#include "TList.h"
#include "TROOT.h"
#include "TSQLStatement.h"
#include "TSystem.h"

#include "FairDbMultConnector.h"
#include "FairDb.h"
#include "FairDbString.h"

ClassImp(FairDbMultConnector)

FairDbMultConnector::FairDbMultConnector():
  fGlobalSeqNoDbNo(-1),
  fConnections(),
  fTemporaryTables()
{
//  Current cascader configuration comes from 3 environmental
//  variables:-
//
//    ENV_DB_URL             a semi-colon separated list of URLs
//    ENV_DB_USER            user name (one or a semi-colon separated list)
//    ENV_DB_PSWD            password (one or a semi-colon separated list)
//
//    or the _UPDATE alternatives e.g. ENV_DB_UPDATE_USER
//
// The _UPDATE versions take priority.


// Extract args from  ENV_DB environmental variables
  const char*      strUser = gSystem->Getenv("ENV_TSQL_UPDATE_USER");
  if ( ! strUser ) { strUser = gSystem->Getenv("ENV_TSQL_USER"); }
  const char*      strPswd = gSystem->Getenv("ENV_TSQL_UPDATE_PSWD");
  if ( ! strPswd ) { strPswd = gSystem->Getenv("ENV_TSQL_PSWD"); }
  const char*       strUrl = gSystem->Getenv("ENV_TSQL_UPDATE_URL");
  if ( !strUrl ) { strUrl = gSystem->Getenv("ENV_TSQL_URL"); }
  string userList     = ( strUser ) ? strUser : "";
  string pswdList     = ( strPswd ) ? strPswd : "";
  string urlList      = ( strUrl  ) ? strUrl  : "";

  if ( urlList == "" || userList == "" || pswdList == "" ) {
    cout << "-E- FairDbMultConnector() "
         << "Cannnot open a Database cascade;\n"
         << "   the environmental variables ENV_DB_*:-" << endl
         << "USER: \"" << userList << "\" PSWD:\"" << pswdList
         << "\" URL:\"" << urlList << endl
         << " are either not defined or empty.\n"
         << "   Please check your settings of ENV_DB_USER,"
         << " ENV_DB_PSWD and ENV_DB_URL\n"
         << "Aborting due to above errors " << endl;
    exit(1);
  }

  std::vector<std::string> users, pswds, urls;
  FairUtilString::StringTok(users, userList, ";");
  FairUtilString::StringTok(pswds, pswdList, ";");
  FairUtilString::StringTok(urls,  urlList,  ";");

  bool fail = false;

  for (unsigned entry = 0; entry < urls.size(); ++entry ) {
    string url  = urls[entry];
    string user = ( entry >= users.size() ) ? users[0] : users[entry];
    string pswd = ( entry >= pswds.size() ) ? pswds[0] : pswds[entry];

    // Handle empty password designated as '\0'
    // (an empty null terminated character string)
    if ( pswd == "\\0" ) { pswd = ""; }

    FairDbConnection* con = new FairDbConnection(url,user,pswd);
    fConnections.push_back(con);
    if ( ! con->Open() ) {
      fail = true;
      continue;
    }

//  Attempt to locate first GlobalSeqNo/GLOBALSEQNO table.
    if ( fGlobalSeqNoDbNo != -1 ) { continue; }
    auto_ptr<FairDbStatement>  stmtDb(new FairDbStatement(*con));
    if ( ! stmtDb.get() ) { continue; }
    TSQLStatement* stmt = stmtDb->ExecuteQuery("Select * from GLOBALSEQNO where 1=0");
    if ( stmt ) {
      fGlobalSeqNoDbNo = fConnections.size()-1;
      delete stmt;
      stmt = 0;
    }

//  Check for presence of a DB_STATE_FLAG table
    if ( this->GetTableDbNo("DBI_STATE_FLAGS",entry) != -1 ) {
      cout << " -E- FairDbMultConnector  POSSIBLE VERSION SHEAR DETECTED !!!\n"
           << "    The DB_STATE_FLAGS table is present on cascade entry " << entry << ".  This table will\n"
           << "    only be introduced to manage backward incompatible changes that could lead\n"
           << "    to version shear between the code and the database.  This version of the\n"
           << "    code does not support the change the presence of that table indicates\n"
           << "    so has to shut down. \n";
      fail = true;
    }
  }

  cout << *this;

//  Abort, if there have been any failures.
  if ( fail ) {

    cout << " -E- FairDbMultConnector() Aborting due to above errors" << endl;
    exit(1);
  }

}


FairDbMultConnector::FairDbMultConnector(const FairDbMultConnector& conn)
  :   fGlobalSeqNoDbNo(conn.fGlobalSeqNoDbNo),
      fConnections(conn.fConnections),
      fTemporaryTables(conn.fTemporaryTables)
{
  /*
  fGlobalSeqNoDbNo=conn.fGlobalSeqNoDbNo;
  fConnections=conn.fConnections;
  fTemporaryTables=conn.fTemporaryTables;
  */
}
//.....................................................................

FairDbMultConnector::~FairDbMultConnector()
{

  cout << "-I- FairDbMultConnector : Destroying FairDbMultConnector"
       << endl;
  for (Int_t dbNo = this->GetNumDb()-1; dbNo >= 0; --dbNo) {
    delete fConnections[dbNo];
  }

}

//.....................................................................

ostream& operator<<(ostream& os, const FairDbMultConnector& cascader)
{

  os << "-I- FairDbMultConnector() Status:- " << endl
     << "Status   URL" << endl << endl;

  int maxDb = cascader.GetNumDb();
  for (Int_t dbNo = 0; dbNo < maxDb; ++dbNo)
    os << cascader.GetStatusAsString(dbNo) << " "
       << ( ( dbNo == cascader.fGlobalSeqNoDbNo ) ? "(auth)  " : "        ")
       << cascader.GetURL(dbNo) << endl;
  os << endl;
  return os;

}

//.....................................................................

Int_t FairDbMultConnector::AllocateSeqNo(const string& tableName,
    Int_t requireGlobal, /* =0 */
    Int_t dbNo  /* = 0 */) const
{
  bool isTemporary = IsTemporaryTable(tableName,dbNo);

  //  Deal with global requests.

  if (     requireGlobal > 0
           || ( requireGlobal == 0 && dbNo == fGlobalSeqNoDbNo && ! isTemporary ) ) {
    if ( fGlobalSeqNoDbNo < 0 ) {
      cout << " -I- FairDbMultConnector: Unable to issue global SEQNO - no authorising DB in cascade\n"
           << "  will issue local one instead" << endl;
    } else if ( isTemporary ) {
      cout << " -I- FairDbMultConnector: Unable to issue global SEQNO - " << tableName << " is temporary\n"
           << "  will issue local one instead" << endl;
    } else { return this->ReserveNextSeqNo(tableName,true,fGlobalSeqNoDbNo); }
  }

  // Deal with local requests
  return this->ReserveNextSeqNo(tableName,false,dbNo);

}

//.....................................................................

FairDbStatement* FairDbMultConnector::CreateStatement(UInt_t dbNo) const
{
//  <NB>
//  As the caller is responsible for destroying the statement after use
//  consider:-
//
//  #include <memory>
//  using std::auto_ptr;
//
//  ...
//
//  auto_ptr<FairDbStatement> stmt(cascader.CreateStatement(dbNo));


  if ( this->GetStatus(dbNo) == kFailed ) { return 0; }
  FairDbConnection& conDb = *fConnections[dbNo];
  FairDbStatement* stmtDb = new FairDbStatement(conDb);
  stmtDb->PrintExceptions();
  return stmtDb;

}
//.....................................................................

Int_t FairDbMultConnector::CreateTemporaryTable(const string& tableNameMc,
    const string& tableDescr)
{

  string tableName = FairUtilString::ToUpper(tableNameMc);
  if (    tableName == ""
          || tableDescr[0] != '('
          || tableDescr[tableDescr.size()-1] != ')' ) {
    cout << "-I- FairDbMultConnector:: Illegal input args:-" << endl
         << "     Table Name: " << tableName
         << "  Table Description: " << tableDescr
         <<endl;
    return -1;
  }

// Find a DB that will accept the command.
  string sqlMakeTable;

  Int_t dbNoAcc       = -1;
  auto_ptr<FairDbStatement> stmtDb;
  for (UInt_t dbNoTry = 0; dbNoTry < fConnections.size(); ++dbNoTry ) {
    stmtDb.reset(this->CreateStatement(dbNoTry));
    if ( stmtDb.get() ) {
      sqlMakeTable = " create temporary table ";
      sqlMakeTable += tableName;
      sqlMakeTable += " ";
      sqlMakeTable += tableDescr;
      sqlMakeTable += ";";
      stmtDb->ExecuteUpdate(sqlMakeTable.c_str());
      if ( stmtDb->GetExceptionLog().IsEmpty() ) {
        dbNoAcc = dbNoTry;
        this->GetConnection(dbNoAcc)->SetTableExists(tableName);
        break;
      }
      // print exceptions

    }
  }

  if ( dbNoAcc < 0 ) {
    if ( stmtDb.get()) { stmtDb->PrintExceptions(); }
    return -1;
  }

// Make connection permanent if not already.
  FairDbConnection& conDb = *fConnections[dbNoAcc];
  if ( conDb.IsTemporary() ) {
    conDb.SetPermanent();
    cout << "-I- FairDbMultConnector:  Making connection: " << conDb.GetUrl()
         << " permanent to preserve temporary tables." << endl;
  }

// Create SQL to create auxillary validity table and write to same Db.
  sqlMakeTable = FairDb::GetValDescr(tableName.c_str(),true);

  cout << "-I- FairDbMultConnector:  Validity Table creation: "
       << " Database: " << dbNoAcc << " "
       << sqlMakeTable << endl;
  stmtDb->ExecuteUpdate(sqlMakeTable.c_str());
  if ( stmtDb->PrintExceptions() ) { return -1; }
  this->GetConnection(dbNoAcc)->SetTableExists(tableName+"VAL");
  fTemporaryTables[tableName] = dbNoAcc;
  return dbNoAcc;

}


const FairDbConnection* FairDbMultConnector::GetConnection(UInt_t dbNo) const
{

  if ( this->GetStatus(dbNo) == kFailed ) { return 0; }
  return fConnections[dbNo];

}
//.....................................................................

FairDbConnection* FairDbMultConnector::GetConnection(UInt_t dbNo)
{

  if ( this->GetStatus(dbNo) == kFailed ) { return 0; }
  return fConnections[dbNo];

}

string FairDbMultConnector::GetDbName(UInt_t dbNo) const
{

  string dbName;

  if ( dbNo < this->GetNumDb() ) { dbName = fConnections[dbNo]->GetDbName(); }
  else { cout << "-I- FairDbMultConnector: Database does not contain entry " << dbNo << endl; }
  return dbName;

}


Int_t FairDbMultConnector::GetDbNo(const string& dbName) const
{
  for ( unsigned dbNo = 0; dbNo < this->GetNumDb(); ++dbNo) {
    if ( dbName == fConnections[dbNo]->GetDbName() ) { return dbNo; }
  }

  cout << "-I- FairDbMultConnector:Database does not contain entry " << dbName << endl;
  return -1;

}


string FairDbMultConnector::GetStatusAsString(UInt_t dbNo) const
{

  Int_t status = GetStatus(dbNo);

  switch ( status ) {
  case kClosed:
    return "Closed";
  case kOpen:
    return "Open  ";
  default:
    return "Failed";
  }

}
Int_t FairDbMultConnector::GetTableDbNo(const string& tableName,
                                        Int_t selectDbNo /* -1 */) const
{
  string::const_iterator itr    = tableName.begin();
  string::const_iterator itrEnd = tableName.end();
  while ( itr != itrEnd ) if ( islower(*itr++) ) { return -1; }

// Loop over cascade looking for table.
  for (UInt_t dbNoTry = 0; dbNoTry < fConnections.size(); ++dbNoTry ) {
    if ( selectDbNo >= 0 && (UInt_t) selectDbNo != dbNoTry ) { continue; }
    const FairDbConnection* con =  this->GetConnection(dbNoTry);
    if ( con && con->TableExists(tableName) ) { return dbNoTry; }
  }

  return -1;

}
//.....................................................................

void FairDbMultConnector::HoldConnections()
{

  for (UInt_t dbNo = 0; dbNo < fConnections.size(); ++dbNo ) {
    fConnections[dbNo]->ConnectStatement();
  }
}

Bool_t FairDbMultConnector::IsTemporaryTable(const string& tableName,
    Int_t dbNo) const
{

  map<string,Int_t>::const_iterator itr
  = fTemporaryTables.find(tableName);
  return (     itr != fTemporaryTables.end()
               &&  (*itr).second == dbNo );

}



FairDbMultConnector::BLock::BLock(FairDbStatement* stmtDB, const string& seqnoTable, const string& dataTable) :
  fStmt(stmtDB),
  fSeqnoTableName(seqnoTable),
  fDataTableName(dataTable),
  fLocked(kFALSE)
{
  if ( ! fStmt ) {
    cout << "-E FairDbMultConnector::Block  Cannot obtain statment to set lock" << endl;
    return;
  }

  this->SetBLock(kTRUE);

}

FairDbMultConnector::BLock::~BLock()
{

  this->SetBLock(kFALSE);
  delete fStmt;
  fStmt = 0;

}

void FairDbMultConnector::BLock::SetBLock(Bool_t setting)
{
  if ( setting == fLocked || ! fStmt ) { return; }

  if ( fStmt->GetDBType() != FairDb::kMySQL ) {
    fLocked = setting;
    return;
  }

  string sql;

  if ( setting ) {
    sql = "LOCK TABLES ";
    sql += fSeqnoTableName + " WRITE";
    if ( fDataTableName != "" ) { sql += ", " + fDataTableName  + "VAL WRITE"; }
  } else {
    sql = "UNLOCK TABLES;";
  }
  cout << "Lock requested: " << setting
       << " issuing lock command: " << sql << endl;
  fStmt->ExecuteUpdate(sql.c_str());
  if ( fStmt->GetExceptionLog().IsEmpty() ) { fLocked = setting; }
  fStmt->PrintExceptions();

}

void FairDbMultConnector::ReleaseConnections()
{

  for (UInt_t dbNo = 0; dbNo < fConnections.size(); ++dbNo ) {
    fConnections[dbNo]->DisConnectStatement();
  }
}

Int_t FairDbMultConnector::ReserveNextSeqNo(const string& tableName,
    Bool_t isGlobal,
    UInt_t dbNo) const
{

  FairDbString sql;

  string seqnoTableName = isGlobal ? "GLOBALSEQNO" : "LOCALSEQNO";
  bool seqnoTableNameExists = this->TableExists(seqnoTableName,dbNo);
  bool tableNameExists      = this->TableExists(tableName,dbNo);

  auto_ptr<FairDbStatement> stmtDb(this->CreateStatement(dbNo) );
  if ( ! stmtDb.get() ) { return 0; }

  // Check that required SEQNO table exists.

  if ( isGlobal ) {
    if ( ! seqnoTableNameExists ) {
      cout<< "-I- FairDbMultConnector: Unable to issue global SEQNO - " << dbNo
          << " is not an authorising DB" << endl;
      return 0;
    }
  } else {
    if ( ! seqnoTableNameExists ) {
      sql.Clear();
      sql << "CREATE TABLE " << seqnoTableName
          << "(TABLENAME      CHAR(64) NOT NULL PRIMARY KEY,\n"
          << " LASTUSEDSEQNO  INT )";

      cout<< "-I- FairDbMultConnector: Database: " << dbNo
          << " create local SEQNO table query: " << sql.c_str() << endl;
      stmtDb->ExecuteUpdate(sql.c_str());
      if ( stmtDb->PrintExceptions() ) { return 0; }
      sql.Clear();
      sql << "INSERT INTO " <<  seqnoTableName << " VALUES ('*',0)";
      cout<< "-I- FairDbMultConnector: Database: " << dbNo
          << " prime local SEQNO table query: " << sql.c_str() << endl;
      stmtDb->ExecuteUpdate(sql.c_str());
      if ( stmtDb->PrintExceptions() ) { return 0; }
    }
  }

// Lock seqno table by creating a lock object on the stack.
// Table will be unlocked when lock object destroyed.

  string dataTable;
// Only pass in table name if it's not temporary and exists in
// the selected DB otherwise Lock will try to lock a non-existent table.
  if (  ! this->IsTemporaryTable(tableName,dbNo)
        && tableNameExists ) { dataTable = tableName; }
  BLock Block(this->CreateStatement(dbNo),seqnoTableName,dataTable);
  if ( ! Block.IsBLocked() ) {
    cout<< "-I- FairDbMultConnector: Unable to lock " << seqnoTableName << endl;
    return 0;
  }

// Find row containing last used SeqNo for this table.
// Not that comparison is case insensitive.
  sql.Clear();
  sql << "select * from " << seqnoTableName << " where TABLENAME = '*' or TABLENAME = '";
  sql << tableName + "' order by TABLENAME";
  cout<< "-I- FairDbMultConnector: "<< seqnoTableName << " query: " << sql.c_str() << endl;
  TSQLStatement* stmt = stmtDb->ExecuteQuery(sql.c_str());
  stmtDb->PrintExceptions(0);
  Int_t seqNoDefault = 0;
  if ( stmt && stmt->NextResultRow() ) {
    seqNoDefault = stmt->GetInt(1);
  } else {
    cout<< "-I- FairDbMultConnector: Unable to find default SeqNo"
        << " due to above error" << endl;
    delete stmt;
    stmt = 0;
    return 0;
  }
  Int_t seqNoTable = seqNoDefault;
  if ( stmt->NextResultRow() ) {
    seqNoTable = stmt->GetInt(1);
  }
  delete stmt;
  stmt = 0;
  cout<< "-I- FairDbMultConnector: query returned last used seqno: " << seqNoTable << endl;

//  If the table exists, make sure that the seqNo hasn't already been used.
//  This is paranoia code and expensive, so only do the check once for
//  each tableName/isGlobal/dbNo combination.

  static std::string checkedCombinations;
  ostringstream combination;
  combination << ":" << tableName << isGlobal << dbNo << ":";
  bool notChecked = checkedCombinations.find(combination.str()) == std::string::npos;
  if ( notChecked ) { checkedCombinations += combination.str(); }
  if ( tableNameExists && notChecked ) {
    Int_t seqNoMin = seqNoDefault;
    Int_t seqNoMax = seqNoDefault + FairDb::kMAXLOCALSEQNO;
    sql.Clear();
    sql << "select max(SEQNO) from " << tableName << "VAL"
        << " where SEQNO between " << seqNoMin << " and " << seqNoMax;
    cout<< "-I- FairDbMultConnector: Database: " << dbNo
        << " max  SEQNO query: " << sql.c_str() << endl;
    stmt  =  stmtDb->ExecuteQuery(sql.c_str());
    if ( stmtDb->PrintExceptions() ) { return 0; }
    Int_t  minValue = 0;
    // Queries returning group function results can be null.
    if (  stmt && stmt->NextResultRow() && ! stmt->IsNull(0) ) {
      minValue = stmt->GetInt(0);
      if ( minValue <= 0 ) { minValue = 0; }  // Should never happen.
    }
    delete stmt;
    stmt = 0;

    if ( minValue > seqNoTable ) {
      cout<< "-I- FairDbMultConnector: "
          << "Database: " << dbNo << " "
          << seqnoTableName << " has last used SEQNO of "
          << seqNoTable << " for table " << tableName
          << ",\n    but the highest SEQNO in the band " << seqNoMin << " to " << seqNoMax
          << " is " <<  minValue << " for that table\n    "
          << seqnoTableName << " is out of date! It will be updated for " << tableName << endl;
      seqNoTable = minValue;
    }
  }


//  Update last used SeqNo and record in table.
  sql.Clear();
  sql << "delete from " << seqnoTableName << " where TABLENAME='";
  sql << tableName + "'";
  cout<< "-I- FairDbMultConnector: SEQNO entry removal: "
      << sql.c_str() << endl;
  stmtDb->ExecuteUpdate(sql.c_str());
  if ( stmtDb->PrintExceptions() ) { return 0; }

  seqNoTable++;

  sql.Clear();
  sql << "insert into  " << seqnoTableName << " values('";
  sql << tableName + "'," << seqNoTable << ")";
  cout<< "-I- FairDbMultConnector: SEQNO entry add: "
      << sql.c_str() << endl;
  stmtDb->ExecuteUpdate(sql.c_str());
  if ( stmtDb->PrintExceptions() ) { return 0; }

  return seqNoTable;

}

void FairDbMultConnector::SetPermanent(UInt_t dbNo,
                                       Bool_t permanent  )
{

  if ( dbNo < fConnections.size() ) {
    fConnections[dbNo]->SetPermanent(permanent);
  }

}
