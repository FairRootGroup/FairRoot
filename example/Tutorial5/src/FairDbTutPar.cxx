#include "FairDbTutPar.h"

#include "FairDb.h"                     // for GetValDefinition
#include "FairDbConnection.h"           // for FairDbConnection
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog
#include "FairDbConnectionPool.h"        // for FairDbConnectionPool
#include "FairDbOutTableBuffer.h"         // for FairDbOutRowStream
#include "FairDbReader.h"               // for FairDbReader
#include "FairDbResult.h"               // for FairDbResultSet
#include "FairDbStatement.h"            // for FairDbStatement
#include "FairDbTableInterfaceStore.h"   // for FairDbTableInterfaceStore
#include "FairDbValRecord.h"
#include "FairDbWriter.h"               // for FairDbWriter
#include "FairParamList.h"              // for FairParamList

#include "Riosfwd.h"                    // for ostream
#include "TString.h"                    // for TString

#include <stdlib.h>                     // for exit
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <memory>                       // for auto_ptr, etc
#include <vector>                       // for vector, vector<>::iterator


using namespace std;

ClassImp(FairDbTutPar);

#include "FairDbReader.tpl"
template class  FairDbReader<FairDbTutPar>;

#include "FairDbWriter.tpl"
template class  FairDbWriter<FairDbTutPar>;


FairDbTutPar::FairDbTutPar(const char* name, const char* title, const char* context)
  : FairParGenericSet(name,title,context),
    fTopPitch(0.),
    fTopAnchor(0.),
    fTopNrFE(0),
    fFeType("")
{
//  clear();
}


string FairDbTutPar::GetTableDefinition(const char* Name)
{

  string sql("create table ");
  if ( Name ) { sql += Name; }
  else { sql += "FAIRDBTUTPAR"; }
  sql += "( SEQNO          INT NOT NULL,";
  sql += "  ROW_ID         INT NOT NULL,";
  sql += "  TOPPITCH       DOUBLE,";
  sql += "  TOPANCHOR      DOUBLE,";
  sql += "  TOPNRFE        INT,";
  sql += "  FETYPE         TEXT,";
  sql += "  primary key(SEQNO,ROW_ID))";
  return sql;
}

void FairDbTutPar::putParams(FairParamList* list)
{
  std::cout<<"-I- FairDbTutPar::putParams() called"<<std::endl;
  if(!list) { return; }
  list->add("top_pitch",  fTopPitch);
  list->add("top_anchor", fTopAnchor);
  list->add("nr_fe_top",  fTopNrFE);
  list->add("fe_Type",    (Text_t*) &fFeType);
}

Bool_t FairDbTutPar::getParams(FairParamList* list)
{
  if (!list) { return kFALSE; }
  if (!list->fill("top_pitch", &fTopPitch)) { return kFALSE; }
  if (!list->fill("top_anchor", &fTopAnchor)) { return kFALSE; }
  if (!list->fill("nr_fe_top", &fTopNrFE)) { return kFALSE; }
  Text_t feName[80];
  if (!list->fill("fe_Type",feName,80)) { return kFALSE; }
  fFeType = feName;
  return kTRUE;
}

void FairDbTutPar::clear()
{
  cout << "-I- clear called \n" << endl;
  fTopPitch=fTopAnchor=0.0;
  fTopNrFE=0;
  fFeType="";
}


void FairDbTutPar::Print()
{
  std::cout<<"Tutorial SQL  Parameters:"<<std::endl;
  std::cout<<"   Top Pitch    = "<<fTopPitch<<std::endl;
  std::cout<<"   Top Anchor   = "<<fTopAnchor<< std::endl;
  std::cout<<"   Nr of Frontends (Top Side)   = "<<fTopNrFE<<std::endl;
  std::cout<<"   Frontend type name is        = "<<fFeType<<std::endl;
}




void FairDbTutPar::Fill(FairDbResultPool& res_in,
                        const FairDbValRecord* valrec)
{
  res_in >> fTopPitch  >> fTopAnchor   >> fTopNrFE  >> fFeType;
}

void FairDbTutPar::Store(FairDbOutTableBuffer& res_out,
                         const FairDbValRecord* valrec) const
{
  res_out << fTopPitch  << fTopAnchor   << fTopNrFE  << fFeType;
}


void FairDbTutPar::fill(UInt_t rid)
{

  ValTimeStamp ts(rid);
  ValCondition context(Detector::kGfi,DataType::kData,ts);
  FairDbReader<FairDbTutPar> rsCal(context, GetVersion());
  Int_t numRows = rsCal.GetNumRows();


  // By default use the latest row entry
  // (Other rows would correspond to outdated versions)
  if ( numRows > 1 ) { numRows = 1; }

  for (int i = 0; i < numRows; ++i) {
    FairDbTutPar* cgd = (FairDbTutPar*) rsCal.GetRow(i);
    if (!cgd) { continue; }
    fTopPitch = cgd->GetTopPitch();
    fTopAnchor =  cgd->GetTopAnchor();
    fTopNrFE =  cgd->GetNrTopFE();
    fFeType = cgd->GetFeType();
  }

}


void FairDbTutPar::store(UInt_t rid)
{
  // In this example we are fixing the database entry point. In the future
  // a variable entry can be set via the runtime DB directly.
  Int_t dbEntry = 0;
  Bool_t fail= kFALSE;

  FairDbConnectionPool* fMultConn = FairDbTableInterfaceStore::Instance().fConnectionPool;
  auto_ptr<FairDbStatement> stmtDbn(fMultConn->CreateStatement(dbEntry));
  if ( ! stmtDbn.get() ) {
    cout << "-E-  FairDbTutPar::Store()  Cannot create statement for Database_id: " << dbEntry
         << "\n    Please check the FAIRDB_TSQL_* environment.  Quitting ... " << endl;
    exit(1);
  }

  // The definition of FairDbTutPar is centralised in the FairDbTutPar class.
  // The corresponding SQL is executed as follows:
  std::vector<std::string> sql_cmds;
  TString atr(GetName());
  atr.ToUpper();

  // Check if for this connection entry the table already exists.
  // If not call the Class Table Definition function
  if (! fMultConn->GetConnection(dbEntry)->TableExists("FAIRDBTUTPAR") ) {
    sql_cmds.push_back(FairDb::GetValDefinition("FAIRDBTUTPAR").Data());
    sql_cmds.push_back(FairDbTutPar::GetTableDefinition());
  }

  // Now execute the assemble list of SQL commands.
  std::vector<std::string>::iterator itr(sql_cmds.begin()), itrEnd(sql_cmds.end());
  while( itr != itrEnd ) {
    std::string& sql_cmd(*itr++);
    stmtDbn->ExecuteUpdate(sql_cmd.c_str());
    if ( stmtDbn->PrintExceptions() ) {
      fail = true;
      cout << "-E- FairDbTutPar::Store() ******* Error Executing SQL commands ***********  " << endl;
    }

  }

  // Refresh list of tables in connected database
  // for the choosen DB entry
  fMultConn->GetConnection(dbEntry)->SetTableExists();

  FairDbWriter<FairDbTutPar>  aW(this->GetValInterval(rid),
                                 GetAggregateNo(), // Composite or Simple IO
                                 GetVersion(),  // Parameter version ( Set via the Container Factory)
                                 ValTimeStamp(0,0),0,"test parameter", "FAIRDBTUTPAR");
  aW.SetDbNo(dbEntry);
  aW.SetLogComment("Test Parameter");
  aW << (*this);
  if ( ! aW.Close() ) {
    fail = true;
    cout << "-E- FairDbTutPar::Store() ******** Cannot do IO on class: " << GetName() <<  endl;
  }
}
