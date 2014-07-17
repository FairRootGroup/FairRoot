/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void testconn(){

// PostGreSQL
  //TSQLServer *serv = TSQLServer::Connect("pgsql://localhost:5432/postgres","postgres","pasglop1");   
  //  TSQLResult *res;

// open connection to MySQL server on localhost

//  MySQL Server
  TSQLServer *serv = TSQLServer::Connect("mysql://localhost/mysql", "scott", "tiger");
  if (serv!=0 && serv->IsConnected()){
	cout << "-I- MySQL server connected  server:# " << serv <<  endl;

// Statement 

   TSQLStatement* stmt = NULL; 
   stmt = serv->Statement("CREATE TABLE TESTTABLE (ID1 INT, ID2 INT, ID3 BLOB)");    
	  // stmt = serv->Statement("CREATE TABLE TESTTABLE (ID1 INT, ID2 INT, ID3 BYTEA)");    
   stmt->Process(); 
   delete stmt; 

// Insertion
   TSQLStatement* stmt2 = NULL; 
   stmt2 = serv->Statement("INSERT INTO TESTTABLE VALUES (?, ?, ?)", 100);
   //stmt2 = serv->Statement("INSERT INTO TESTTABLE VALUES ($1, $2, $3)", 100);
 
   Int_t arr[3]={0,0,0};
   TBufferFile b_write(TBuffer::kWrite);

   for(Int_t i=1;i<2;i++){
	 if (stmt2->NextIteration()){
       stmt2->SetInt(0,i*10+i);
       stmt2->SetInt(1,i*10+i);
       arr[0]=i; arr[1]=i+1; arr[2]=i+2;
       b_write.WriteArray(arr,3); 

       TString test_str;
       test_str.ReadBuffer(b_write.Buffer());  
       cout << " TString filled " << test_str.Data() << endl;

       stmt2->SetBinary(2,(void*) b_write.Buffer(), b_write.BufferSize());
             
     }
   }  
   stmt2->Process();


// Reading the BLOB 
   stmt = serv->Statement("SELECT * FROM TESTTABLE", 100);
    // process statement
    if (stmt->Process()) {
       // store result of statement in buffer
       stmt->StoreResult();

       // display info about selected field
       std::cout << "NumFields = " << stmt->GetNumFields() << std::endl;
       for (int n=0;n<stmt->GetNumFields();n++)
          std::cout << "Field " << n << "  = " << stmt->GetFieldName(n) << std::endl;

	   
       // extract rows one after another
       while (stmt->NextResultRow()) {
          Double_t id1 = stmt->GetDouble(0);
          UInt_t id2 = stmt->GetUInt(1);
          Int_t abuff[3];    
          Int_t size; 
          Bool_t test = stmt->GetBinary(2, abuff, size);   
		  TBufferFile tt(TBuffer::kRead,size,(void*)abuff,kFALSE);
		  tt.ReadArray(abuff);
 
         if (test)
          std::cout << id1 << " - " << id2 <<  "arr " << arr[0] << " - " << arr[1] << " - " << arr[2] << std::endl;
          else cout << " -I- BLOB Error " << endl; 
      }
    }

  

  }// !(db)



    




}
