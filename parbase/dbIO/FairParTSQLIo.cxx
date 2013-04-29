/*******************************************
 * Author: M.Babai (M.Babai@rug.nl)        *
 * Modified: D.Bertini (D.Bertini@gsi.de)  *
 * License:                                *
 * Version:                                *
 ******************************************/

#include "FairParTSQLIo.h"
#include "FairGenericParTSQLIo.h"
#include "FairDbMultConnector.h"
#include "FairDbStatement.h"
#include "FairDbTableProxyRegistry.h"
#include "FairRuntimeDb.h"

#include <iostream>
#include <sstream>
#include <memory>
using namespace std;

ClassImp(FairParTSQLIo)

FairParTSQLIo::FairParTSQLIo()
  : FairParIo(),
    fCurrentRun(NULL),
    fDefaultDb (-1),
    fConnections(FairDbTableProxyRegistry::Instance().fMultConnector)
{
//  fCurrentRun=NULL;
}


FairParTSQLIo::FairParTSQLIo(FairDbMultConnector const& cons, int const dbNum)
  : FairParIo(),
    fCurrentRun(NULL),
    fDefaultDb (dbNum),
    fConnections(FairDbTableProxyRegistry::Instance().fMultConnector)
{
//  fCurrentRun=NULL;
}


FairParTSQLIo::~FairParTSQLIo()
{
  disconnect();
}


bool FairParTSQLIo::check()
{
  //FairDbMultConnector::Status s;
  int stat = -100;
  // Check if at least one DB is connected.
  if(fDefaultDb != -1) { // Has been specified.
    stat = fConnections->GetStatus(fDefaultDb);
    if(stat == FairDbMultConnector::kFailed ||
        stat == FairDbMultConnector::kClosed)
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
    std::cout << "\n\t<DEBUG> Terminating connection and status = "
              << fConnections->GetStatusAsString(0)
              <<"\n\n";
    delete fConnections;
    fConnections = 0;
  }
}

bool FairParTSQLIo::activateDetIo()
{
  std::cout << "<DEBUG> FairParTSQLIo::activateDetIo()\n";
  // FIXME FIXME Maybe better to call check first
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
      cout << "-E- FairParTSQLIo::open() Cannot get a statement for DB entry# " << iEntry
           << "\n  --->  Please check the ENV_TSQL_* environment.  Transaction Failed  ... " << endl;
      return kFALSE;
    }

    // Now prepare Database for each DB entry
    cout << "-I- FairParTSQLIo:.open() checking DB entry# " << iEntry  << endl;

    if (!fConnections->GetConnection(iEntry)->TableExists("GLOBALSEQNO") ) {
      TString work = getenv("VMCWORKDIR");
      work = work + "/dbase/dbInput/prepare_db.sql";
      ostringstream os;
      os << work.Data();
      string fileName = os.str();
      ifstream inp(fileName.c_str());
      if ( ! inp.is_open() ) {
        cout << "-E-  FairParTSQLIo cannot read prepared sql commands in  input file#  " << fileName << endl;
        exit(1);
      }

      // Add sql for prepare
      std::vector<std::string> sql_cmds;
      string sql;
      while ( ! inp.eof() ) {
        string line;
        getline(inp,line);
        // Remove trailing spaces.
        while ( line.size() > 0 && *(line.rbegin()) == ' ' ) { line.erase(line.size()-1); }
        // Ignore empty lines and comments
        if ( line.size() == 0 || line[0] == '#' ) { continue; }
        sql += line;
        // If terminating semicolon found execute command.
        if ( *(line.rbegin()) == ';' ) {
          sql_cmds.push_back(sql);
          sql = "";
        }
      }

      // Now execute the assemble list of SQL commands.
      auto_ptr<FairDbStatement> stmtDbn(fConnections->CreateStatement(iEntry));

      std::vector<std::string>::iterator itr(sql_cmds.begin()), itrEnd(sql_cmds.end());
      while( itr != itrEnd ) {
        std::string& sql_cmd(*itr++);
        cout <<"-I- FairParTSQLIo executing at DB entry#  " << iEntry << "  SQL:" << sql_cmd << endl;
        stmtDbn->ExecuteUpdate(sql_cmd.c_str());
        if ( stmtDbn->PrintExceptions() ) {
          fail = true;
          cout << "-E- FairParTSQLIo ******* Error Executing SQL commands ***********  " << endl;
        }
      }

      fConnections->SetAuthorisingEntry(iEntry);
      fConnections->GetConnection(iEntry)->SetTableExists();

      cout << "-I- FairParTSQLIo:.open() Meta-structure has been implemented ... continuing " << endl;

    } else {
      // Some Meta-Structure in DB is already existing ... check that !
      TSQLStatement* stmtTSQL = stmtDb->ExecuteQuery("select * from GLOBALSEQNO;");

      if ( stmtTSQL ) {
        while ( stmtTSQL->NextResultRow() ) {
          TString tableName = stmtTSQL->GetString(0);
          int lastUsedSeqNo = stmtTSQL->GetInt(1);
          if ( tableName == "*" && lastUsedSeqNo != 900000000 )  {
            cout << "-E- FairParTSQLIo:: GLOBALSEQNO table error. Entry * = " <<   lastUsedSeqNo
                 << " but should be 900000000" << endl;
            fail = kTRUE;
          } else if  ( tableName != "*" ) {
            string tn3(tableName.Data(),3);
            if ( lastUsedSeqNo < 900000000 || lastUsedSeqNo > 999999999 ) {
              cout << "-E- FaiParTSQLIo :GLOBALSEQNO table error. Entry " <<  tableName
                   << " but should start with FAIRDB \n"
                   << "     and last used SEQNO: " << lastUsedSeqNo
                   << " should be in range 900000000..999999999" << endl;
              fail = kTRUE;
            }
          }
        }
      }

      if ( fail ) {
        cout << "-I- FairParTSQLIo::open() The GLOBALSEQNO table at DB entry# " << iEntry << " is already\n"
             << " existing but not aligned in sequence nr. range 900000000..999999999"
             << " quit rather than risk damage to this table ... \n" << endl;
        return kFALSE;
      }

      cout << "-I- FairParTSQLIo:open() Meta-structure for DB entry# " << iEntry << " looks OK ... continuing" << endl;
    }

  }//! entries

  // Activate SQL Io
  FairRuntimeDb::instance()->activateParIo(this);
  cout << "-I- FairParTSQLIo::open() connected with DB Entries# " << fConnections->GetNumDb() << endl;
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
