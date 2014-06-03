/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbTutParBin.h"

#include "TMath.h"

#include "FairParamList.h"

#include "FairDbLogFormat.h"
#include "FairDbLogService.h"
#include "FairUtilStream.h"
#include "FairDbOutTableBuffer.h"
#include "FairDbStatement.h"
#include "FairDbStreamer.h"


#include <iostream>

using std::cout;
using std::endl;


ClassImp(FairDbTutParBin);

#include "FairDbReader.tpl"
template class  FairDbReader<FairDbTutParBin>;

#include "FairDbWriter.tpl"
template class  FairDbWriter<FairDbTutParBin>;



SVNID("$Id$");

FairDbTutParBin::FairDbTutParBin(const char* name, const char* title, const char* context,Bool_t own)
  : FairParGenericSet(name,title,context,own),
    fTopPitch(0.),
    fTopAnchor(0.),
    fTopNrFE(0),
    fFeType("")
{
  // Constructor
  // Create heap based TH1 object and fill with dummy
  // value

  fMyHisto = new TH1F("test_histo","test_histo",10,0,10);
  // Reset all parameters
  clear();

  // Set the default Db Entry to the first slot
  fDbEntry=0;
  //  Writer Meta-Class for SQL IO
  fParam_Writer=NULL;
  //  Reader Meta-Class for SQL IO
  fParam_Reader=NULL;
  // ConnectionPool
  fMultConn=FairDbTableInterfaceStore::Instance().fConnectionPool;

}


FairDbTutParBin::~FairDbTutParBin()
{

  if (fMyHisto) { delete fMyHisto; fMyHisto=NULL; }

  if (fParam_Writer) {
    delete fParam_Writer;
    fParam_Writer=NULL;
  }

  if (fParam_Reader) {
    delete fParam_Reader;
    fParam_Reader=NULL;
  }


}

string FairDbTutParBin::GetTableDefinition(const char* Name)
{
  string sql("create table ");
  if ( Name ) { sql += Name; }
  else { sql += "FAIRDBTUTPARBIN"; }
  sql += "( SEQNO          INT NOT NULL,";
  sql += "  ROW_ID         INT NOT NULL,";
  sql += "  TOPPITCH       DOUBLE,";
  sql += "  TOPANCHOR      DOUBLE,";
  sql += "  TOPNRFE        INT,";
  sql += "  FETYPE         TEXT,";
  sql += "  MYIARRAY       TEXT,";
  sql += "  MYDARRAY       TEXT,";
  sql += "  MYHISTO        TEXT,";
  sql += "  primary key(SEQNO,ROW_ID))";
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
  for(Int_t i=0; i<3; i++) { fMyIArray[i]=0; }
  for(Int_t i=0; i<10; i++) { fMyDArray[i]=0.1; }
  if(fMyHisto) { (fMyHisto)->Reset(); }
}



void FairDbTutParBin::Fill(FairDbResultPool& res_in,
                           const FairDbValRecord* valrec)
{

  // Instanciate  & clear() the Data Contents

  clear();

  FairDbStreamer dbIArray(fMyIArray,3);
  FairDbStreamer dbDArray(fMyDArray,10);
  FairDbStreamer dbHisto(fMyHisto);

  res_in >> fTopPitch  >> fTopAnchor   >> fTopNrFE  >> fFeType >> dbIArray >> dbDArray>> dbHisto;

  // Update data members
  dbIArray.Fill(fMyIArray);
  dbDArray.Fill(fMyDArray);
  dbHisto.Fill(fMyHisto);

}

void FairDbTutParBin::Store(FairDbOutTableBuffer& res_out,
                            const FairDbValRecord* valrec) const
{
  FairDbStreamer dbIArray(fMyIArray,3);
  FairDbStreamer dbDArray(fMyDArray,10);
  FairDbStreamer dbHisto(fMyHisto);
  res_out << fTopPitch  << fTopAnchor   << fTopNrFE  << fFeType << dbIArray << dbDArray << dbHisto;
}


void FairDbTutParBin::fill(UInt_t rid)
{
  // Get Reader Meta Class
  fParam_Reader=GetParamReader();

  // Define a Context
  ValTimeStamp ts(rid);
  ValCondition context(Detector::kGfi,DataType::kData,ts);

  // Activate reading for this Context
  fParam_Reader->Activate(context, GetVersion());

  // By default use the latest row entry
  // (Other rows would correspond to outdated versions)
  Int_t numRows = fParam_Reader->GetNumRows();
  // Just use the latest row entry
  if ( numRows > 1 ) { numRows = 1; }

  for (Int_t j = 0; j < numRows; ++j) {
    FairDbTutParBin* cgd = (FairDbTutParBin*) fParam_Reader->GetRow(j);
    if (!cgd) { continue; }
    fTopPitch = cgd->GetTopPitch();
    fTopAnchor =  cgd->GetTopAnchor();
    fTopNrFE =  cgd->GetNrTopFE();
    fFeType = cgd->GetFeType();
    Int_t* i_arr = cgd->GetMyIArray();
    Double_t* d_arr = cgd->GetMyDArray();
    for(Int_t i=0; i<3; i++) { fMyIArray[i]=i_arr[i]; }
    for(Int_t i=0; i<10; i++) { fMyDArray[i]=d_arr[i];}
    fMyHisto = cgd->GetMyHisto();
  }


}


void FairDbTutParBin::store(UInt_t rid)
{


  DBLOG("FairDb", FairDbLog::kWarning) << "FairDbTutParBin Store() " << endl;

  // Boolean IO test variable
  Bool_t fail= kFALSE;

  // Create a unique statement on choosen DB entry
  auto_ptr<FairDbStatement> stmtDbn(fMultConn->CreateStatement(GetDbEntry()));
  if ( ! stmtDbn.get() ) {
    cout << "-E-  FairDbTutParBin::Store()  Cannot create a statement for Database_id: " << GetDbEntry()
         << "\n    Please check the FAIRDB_TSQL_* environment.  Quitting ... " << endl;
    exit(1);
  }

  // Check if for this DB entry the table already exists.
  // If not call the corresponding Table Definition Function
  std::vector<std::string> sql_cmds;
  TString atr(GetName());
  atr.ToUpper();

  if (! fMultConn->GetConnection(GetDbEntry())->TableExists("FAIRDBTUTPARBIN") ) {
    sql_cmds.push_back(FairDb::GetValDefinition("FAIRDBTUTPARBIN").Data());
    sql_cmds.push_back(FairDbTutParBin::GetTableDefinition());
  }

  // Packed SQL commands executed internally via SQL processor
  std::vector<std::string>::iterator itr(sql_cmds.begin()), itrEnd(sql_cmds.end());
  while( itr != itrEnd ) {
    std::string& sql_cmd(*itr++);
    stmtDbn->Commit(sql_cmd.c_str());
    if ( stmtDbn->PrintExceptions() ) {
      fail = true;
      cout << "-E- FairDbTutParBin::Store() ******* Error Executing SQL commands ***********  " << endl;
    }

  }

  // Refresh list of tables in connected database
  // for the choosen DB entry
  fMultConn->GetConnection(GetDbEntry())->SetTableExists();

  // Writer Meta-Class Instance
  fParam_Writer = GetParamWriter();


  // Activate Writer Meta-Class with the proper
  // Validity Time Interval (run_id encapsulated)

  // Writer Activate() arguments list
  //                      <Arguments>                   <Type>                  <Comments>
  //
  //                      Validity Interval,            ValInterval
  //                      Composition      ,            Int_t                   set via cont. factory
  //                      Version          ,            Int_t                   set via cont. factory
  //                      DbEntry          ,            Int_t                   set via cont. factory
  //                      LogTitle         ,            std::string             set via cont. factory

  fParam_Writer->Activate(GetValInterval(rid),GetComboNo(), GetVersion(),GetDbEntry(),GetLogTitle());

  // Object to Table mapping
  *fParam_Writer<< (*this);

  // Check for eventual IO problems
  if ( !fParam_Writer->Close() ) {
    fail = true;
    cout << "-E- FairDbTutPar::Store() ******** Cannot do IO on class: " << GetName() <<  endl;
  }


}



void FairDbTutParBin::FillDummy()
{
  // Initializing array
  for(Int_t i=0; i<3; i++) { fMyIArray[i]=(i+1)*10.; }
  for(Int_t i=0; i<10; i++) { fMyDArray[i]=0.1*(i+1); }

  fMyHisto->Fill(1);
  fMyHisto->Fill(2);
  fMyHisto->Fill(3);

}


void FairDbTutParBin::Print()
{
  std::cout<<""<<std::endl;
  std::cout<<"    Top Pitch    = "<<fTopPitch<<std::endl;
  std::cout<<"    Top Anchor   = "<<fTopAnchor<< std::endl;
  std::cout<<"    Nr of Frontends (Top Side)   = "<<fTopNrFE<<std::endl;
  std::cout<<"    Frontend type name is        = "<<fFeType<<std::endl;

  std::cout<<"    Array of <Int>               : "<<std::endl;
  for(Int_t i=0; i<3; i++) {
    std::cout<<"                   arr[ "<< i <<  " ] = " << fMyIArray[i]<< std::endl;
  }

  std::cout<<"    Array of <Double>               : "<<std::endl;
  for(Int_t i=0; i<10; i++) {
    std::cout<<"                   arr[ "<< i <<  " ] = " << fMyDArray[i]<< std::endl;
  }


  cout << "      TH1F  histogram ptr# : "  << fMyHisto << endl;
  if (fMyHisto) { fMyHisto->Print(); }
}





