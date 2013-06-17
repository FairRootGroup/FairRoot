#include "FairDbTutParBin.h"

#include "TMath.h"

#include "FairUtilStream.h"
#include "FairDbOutRowStream.h"
#include "FairDbResult.h"
#include "FairDbStatement.h"
#include "FairDbValidityRec.h"
#include "FairDbStreamer.h"
#include <iostream>

using std::cout;
using std::endl;


ClassImp(FairDbTutParBin);

#include "FairDbResPtr.tpl"
template class  FairDbResultPtr<FairDbTutParBin>;

#include "FairDbWriter.tpl"
template class  FairDbWriter<FairDbTutParBin>;

//TH1F* FairDbTutParBin::fMyHisto=0;

FairDbTutParBin::FairDbTutParBin(const char* name, const char* title, const char* context)
  : FairParGenericSet(name,title,context),
    fTopPitch(0.),
    fTopAnchor(0.),
    fTopNrFE(0),
    fFeType("")
{
  // Constructor
  // Create heap based TH1 object and fill with dummy
  // values
  fMyHisto = new TH1F("test","test",10,0,10);

  // Reset all values
}

FairDbTutParBin::~FairDbTutParBin()
{
  if (fMyHisto) { delete fMyHisto; }
  fMyHisto=0;
}


string FairDbTutParBin::GetTableDescr(const char* alternateName)
{
  string sql("create table ");
  if ( alternateName ) { sql += alternateName; }
  else { sql += "FAIRDBTUTPARBIN"; }
  sql += "( SEQNO          INT NOT NULL,";
  sql += "  ROW_COUNTER    INT NOT NULL,";
  sql += "  TOPPITCH       DOUBLE,";
  sql += "  TOPANCHOR      DOUBLE,";
  sql += "  TOPNRFE        INT,";
  sql += "  FETYPE         TEXT,";
  sql += "  MYARRAY        TEXT,";
  sql += "  MYHISTO        TEXT,";
  sql += "  primary key(SEQNO,ROW_COUNTER))";
  return sql;
}

void FairDbTutParBin::putParams(FairParamList* list)
{
  std::cout<<"-I- FairDbTutParBin::putParams() called"<<std::endl;
  if(!list) { return; }
  list->add("top_pitch",  fTopPitch);
  list->add("top_anchor", fTopAnchor);
  list->add("nr_fe_top",  fTopNrFE);
  list->add("fe_Type",    (Text_t*) &fFeType);
}

Bool_t FairDbTutParBin::getParams(FairParamList* list)
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

void FairDbTutParBin::clear()
{
  fTopPitch=fTopAnchor=0.0;
  fTopNrFE=0;
  fFeType="";
  for(Int_t i=0; i<3; i++) { fMyArray[i]=0; }
  fMyHisto->Reset();
}


void FairDbTutParBin::FillDummy()
{
  // Initializing array
  fMyArray[0]=11.;
  fMyArray[1]=22.;
  fMyArray[2]=44.;

  fMyHisto->Fill(1);
  fMyHisto->Fill(2);
  fMyHisto->Fill(3);

}


void FairDbTutParBin::Print()
{
  std::cout<<"-I- Tutorial SQL Parameters streamed:"<<std::endl;
  std::cout<<"    Top Pitch    = "<<fTopPitch<<std::endl;
  std::cout<<"    Top Anchor   = "<<fTopAnchor<< std::endl;
  std::cout<<"    Nr of Frontends (Top Side)   = "<<fTopNrFE<<std::endl;
  std::cout<<"    Frontend type name is        = "<<fFeType<<std::endl;
  std::cout<<"    Array of <Int>               : "<<std::endl;
  for(Int_t i=0; i<3; i++) {
    std::cout<<"                   arr[ "<< i <<  " ] = " << fMyArray[i]<< std::endl;
  }
  cout << "      TH1F  histogram ptr# : "  << fMyHisto << endl;
  if (fMyHisto) { fMyHisto->Print(); }
}




void FairDbTutParBin::Fill(FairDbResultSet& rs,
                           const FairDbValidityRec* vrec)
{

  // Instanciate  & clear() the Data Contents
  clear();

  FairDbStreamer dbArray(fMyArray,3);
  FairDbStreamer dbHisto(fMyHisto);

  rs >> fTopPitch  >> fTopAnchor   >> fTopNrFE  >> fFeType >> dbArray >> dbHisto;

  // Update data members
  dbArray.Fill(fMyArray);
  dbHisto.Fill(fMyHisto);


  fMyHisto->Print();
}

void FairDbTutParBin::Store(FairDbOutRowStream& ors,
                            const FairDbValidityRec* vrec) const
{
  FairDbStreamer dbArray(fMyArray,3);
  FairDbStreamer dbHisto(fMyHisto);
  ors << fTopPitch  << fTopAnchor   << fTopNrFE  << fFeType << dbArray << dbHisto;
}


void FairDbTutParBin::Fill(UInt_t rid)
{

  ValTimeStamp ts(rid);
  ValContext context(Detector::kGfi,SimFlag::kData,ts);
  FairDbResultPtr<FairDbTutParBin> rsCal(context, GetVersion());
  Int_t numRows = rsCal.GetNumRows();

  // Just use the latest row entry
  if ( numRows > 1 ) { numRows = 1; }

  for (int i = 0; i < numRows; ++i) {
    FairDbTutParBin* cgd = (FairDbTutParBin*) rsCal.GetRow(i);
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
    Int_t* arr = cgd->GetMyArray();
    for(Int_t i=0; i<3; i++) { fMyArray[i]=arr[i]; }
    fMyHisto = cgd->GetMyHisto();
  }

}


void FairDbTutParBin::Store(UInt_t rid)
{
  // In this example we are fixing the database entry point. In the future
  // a variable entry can be set via the runtime DB directly.
  Int_t dbEntry = 0;
  Bool_t fail= kFALSE;

  FairDbMultConnector* fMultConn = FairDbTableProxyRegistry::Instance().fMultConnector;
  auto_ptr<FairDbStatement> stmtDbn(fMultConn->CreateStatement(dbEntry));
  if ( ! stmtDbn.get() ) {
    cout << "-E-  FairDbTutParBin::Store()  Cannot get a statement for cascade entry " << dbEntry
         << "\n    Please check the ENV_TSQL_* environment.  Quitting ... " << endl;
    exit(1);
  }

  // The definition of FairDbTutParBin is centralised in the FairDbTutParBin class.
  // The corresponding SQL is executed as follows:
  std::vector<std::string> sql_cmds;
  TString atr(GetName());
  atr.ToUpper();

  // Check if for this connection entry the table already exists.
  // If not call the Class Table Descriptor function
  if (! fMultConn->GetConnection(dbEntry)->TableExists("FAIRDBTUTPARBIN") ) {
    sql_cmds.push_back(FairDb::GetValDescr("FAIRDBTUTPARBIN").Data());
    sql_cmds.push_back(FairDbTutParBin::GetTableDescr());
  }

  // Now execute the assemble list of SQL commands.
  std::vector<std::string>::iterator itr(sql_cmds.begin()), itrEnd(sql_cmds.end());
  while( itr != itrEnd ) {
    std::string& sql_cmd(*itr++);
    stmtDbn->ExecuteUpdate(sql_cmd.c_str());
    if ( stmtDbn->PrintExceptions() ) {
      fail = true;
      cout << "-E- FairDbTutParBin::Store() ******* Error Executing SQL commands ***********  " << endl;
    }

  }

  // Refresh list of tables in connected database
  // for the choosen DB entry
  fMultConn->GetConnection(dbEntry)->SetTableExists();
  FairDbWriter<FairDbTutParBin>  aW(GetRangeDTF(rid),
                                    GetAggregateNo(), // Composite or Simple IO
                                    GetVersion(),  // Parameter version ( Set via the Container Factory)
                                    ValTimeStamp(0,0),0,"test parameter binary", "FAIRDBTUTPARBIN");
  aW.SetDbNo(dbEntry);
  aW.SetLogComment("Test Parameter");
  //  aW.SetContObj(this);
  aW << (*this);
  if ( ! aW.Close() ) {
    fail = true;
    cout << "-E- FairDbTutParBin::Store()  Cannot do IO on class# " << GetName() <<  endl;
  }

  // Print Info on the Central Log
  FairDbExceptionLog::GetGELog().Print();
}
