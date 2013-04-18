#include "FairDbTutPar.h"
#include "TMath.h"
#include "FairDbOutRowStream.h"
#include "FairDbResult.h"
#include "FairDbValidityRec.h"
#include <iostream>
#include <memory>
using namespace std;

ClassImp(FairDbTutPar);

#include "FairDbResPtr.tpl"
template class  FairDbResultPtr<FairDbTutPar>;

#include "FairDbWriter.tpl"
template class  FairDbWriter<FairDbTutPar>;


FairDbTutPar::FairDbTutPar(const char* name, const char* title, const char* context)
  : FairParGenericSet(name,title,context)
{
  clear();
}


string FairDbTutPar::GetTableDescr(const char* alternateName)
{

  string sql("create table ");
  if ( alternateName ) { sql += alternateName; }
  else { sql += "FAIRDBTUTPAR"; }
  sql += "( SEQNO          INT NOT NULL,";
  sql += "  ROW_COUNTER    INT NOT NULL,";
  sql += "  TOPPITCH       DOUBLE,";
  sql += "  TOPANCHOR      DOUBLE,";
  sql += "  TOPNRFE        INT,";
  sql += "  FETYPE         TEXT,";
  sql += "  primary key(SEQNO,ROW_COUNTER))";
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




void FairDbTutPar::Fill(FairDbResultSet& rs,
                        const FairDbValidityRec* vrec)
{
  cout << " -I- FairDbTutPar::Fill(xxx) called " << endl;
  rs >> fTopPitch  >> fTopAnchor   >> fTopNrFE  >> fFeType;
  cout << " -I- FairDbTutPar::Filled(xxx) called values===> " << fTopPitch << " : " << fTopAnchor << " : " << fTopNrFE << " : " << fFeType << endl;
}

void FairDbTutPar::Store(FairDbOutRowStream& ors,
                         const FairDbValidityRec* vrec) const
{

  cout << " -I- FairDbTutPar::Store(xxx) called  " << fTopPitch << " : " << fTopAnchor << " : " << fTopNrFE << " : " << fFeType << endl;
  ors << fTopPitch  << fTopAnchor   << fTopNrFE  << fFeType;

}


void FairDbTutPar::Fill(UInt_t rid)
{

  ValTimeStamp ts(rid);
  ValContext context(Detector::kGfi,SimFlag::kData,ts);
  FairDbResultPtr<FairDbTutPar> rsCal(context, GetVersion());
  Int_t numRows = rsCal.GetNumRows();


  // Just use the latest row entry
  if ( numRows > 1 ) { numRows = 1; }

  for (int i = 0; i < numRows; ++i) {
    FairDbTutPar* cgd = (FairDbTutPar*) rsCal.GetRow(i);
    if (!cgd) { continue; }
    //cout << "Top Pitch " << cgd->GetTopPitch()
    //     << "Top Anchor: " << cgd->GetTopAnchor()
    //     << "Nr TopFe: " << cgd->GetNrTopFE()
    //     << "Fe Type: " << cgd->GetFeType()
    //     << endl;
    fTopPitch = cgd->GetTopPitch();
    fTopAnchor =  cgd->GetTopAnchor();
    fTopNrFE =  cgd->GetNrTopFE();
    fFeType = cgd->GetFeType();

  }

}


void FairDbTutPar::Store(UInt_t rid)
{
  // In this example we are fixing the database entry point. In the future
  // a variable entry can be set via the runtime DB directly.
  Int_t dbEntry = 0;
  Bool_t fail= kFALSE;

  FairDbMultConnector* fMultConn = FairDbTableProxyRegistry::Instance().fMultConnector;
  auto_ptr<FairDbStatement> stmtDbn(fMultConn->CreateStatement(dbEntry));
  if ( ! stmtDbn.get() ) {
    cout << "-E-  FairDbTutPar::Store()  Cannot get a statement for cascade entry " << dbEntry
         << "\n    Please check the ENV_TSQL_* environment.  Quitting ... " << endl;
    exit(1);
  }

  // The definition of FairDbTutPar is centralised in the FairDbTutPar class.
  // The corresponding SQL is executed as follows:
  std::vector<std::string> sql_cmds;
  TString atr(GetName());
  atr.ToUpper();

  // Check if for this connection entry the table already exists.
  // If not call the Class Table Descriptor function
  if (! fMultConn->GetConnection(dbEntry)->TableExists("FAIRDBTUTPAR") ) {
    sql_cmds.push_back(FairDb::GetValDescr("FAIRDBTUTPAR").Data());
    sql_cmds.push_back(FairDbTutPar::GetTableDescr());
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
  cout << "-I-FairDbTutPar ******* Store() called  ******** with RID#  " << rid <<  endl;

  FairDbWriter<FairDbTutPar>  aW(this->GetRangeDTF(rid),
                                 GetAggregateNo(), // Composite or Simple IO
                                 GetVersion(),  // Parameter version ( Set via the Container Factory)
                                 ValTimeStamp(0,0),0,"test parameter", "FAIRDBTUTPAR");
  aW.SetDbNo(dbEntry);
  aW.SetLogComment("Test Parameter");
  aW << (*this);
  if ( ! aW.Close() ) {
    fail = true;
    cout << "-E- FairDbTutPar::Store()  Cannot do IO on class# " << GetName() <<  endl;
  }


  // Print Info on the Central Log
  FairDbExceptionLog::GetGELog().Print();

  // end of store()
}
