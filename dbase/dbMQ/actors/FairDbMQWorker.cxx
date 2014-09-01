/** 
 *  FairDbMQWorker.cxx 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#include "FairDbMQWorker.h"


#include <iostream>
#include <csignal>

#include "TString.h"

#include "FairMQLogger.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include "FairParTSQLIo.h"


#include "FairDbStreamer.h"
#include "FairParSet.h"



using namespace std;


FairDbMQWorker::FairDbMQWorker(): 
	fContext(NULL)
   ,fSocket(NULL)
   ,fIo_input("")
   ,fIo_output("")
   ,fRtdb(FairRuntimeDb::instance())
{
	fContext = new db_zmq::context_t (1);
    fSocket  = new db_zmq::socket_t (*fContext, ZMQ_REQ ); 
    // for tracing      
    FairDbMQ::SetId (*fSocket);   
    fSocket->connect("tcp://localhost:5556");
} 

FairDbMQWorker::~FairDbMQWorker()
{
	if(fContext) {delete fContext; fContext=NULL;}
	if(fSocket)  {delete fSocket; fSocket=NULL;} 
    if (fRtdb)   {delete fRtdb; fRtdb=NULL;} 
} 

void FairDbMQWorker::SetIoInput(string io_input)
{
  
    TString workdir = getenv("VMCWORKDIR"); 
	 
	 if (!fRtdb->getFirstInput() ) 
	 { 
	 	LOG(DEBUG) << "-I- FairDbMQWorker::Run() Set Io input: "  << endl;
	    string::size_type idx;
        idx = io_input.rfind('.');
        if(idx != std::string::npos)
        {
        	//File based IO
    		std::string ext = io_input.substr(idx+1);
            if (!ext.compare("root")) 
            {
            	//ROOT File IO as first input
				Bool_t kParameterMerged = kTRUE;
	   			FairParRootFileIo* db_input = new FairParRootFileIo(kParameterMerged);
	   			TString filename = workdir  + io_input.c_str();  
	   			LOG(DEBUG) << "-I- FairDbMQWorker:: input IO: ROOT File: "  << filename <<   endl;
	   			db_input->open(filename.Data());
	   			fRtdb->setOutput(db_input);
			}
			else
			{		

				// Set the Ascii IO as first input
				FairParAsciiFileIo* db_input =  new FairParAsciiFileIo();
	   			TString filename = workdir  + io_input.c_str();
	            LOG(DEBUG) << "-I- FairDbMQWorker:: input IO: Text File: "  << filename <<   endl;
	            db_input->open(filename.Data(),"in");
	            fRtdb->setFirstInput(db_input); 
			}


      	}
		else
		{
			LOG(DEBUG) << "-I- FairDbMQWorker:: input IO: TSQLIO  "  << endl;
    	 	// Set the SQL based IO as first input
	   		FairParTSQLIo*  db_input = new FairParTSQLIo();
	   		db_input->SetVerbosity(1);
	   		db_input->open();
	   		fRtdb->setFirstInput(db_input);		
		}

     }
     else
     {
		LOG(DEBUG) << "-E- FairDbMQWorker::Run() already set Io input !... "  << endl;

     } //!(input)
}


void FairDbMQWorker::SetIoOuput(string io_output)
{
  
    TString workdir = getenv("VMCWORKDIR"); 
	 
	 if (!fRtdb->getOutput() ) 
	 { 
	 	LOG(DEBUG) << "-I- FairDbMQWorker::Run() Set Io Output: "  << endl;
	    string::size_type idx;
        idx = io_output.rfind('.');
        if(idx != std::string::npos)
        {
        	//File based IO
    		std::string ext = io_output.substr(idx+1);
            if (!ext.compare("root")) 
            {
            	//ROOT File IO as first input
				Bool_t kParameterMerged = kTRUE;
	   			FairParRootFileIo* db_output = new FairParRootFileIo(kParameterMerged);
	   			TString filename = workdir + io_output.c_str();  
	   			db_output->open(filename.Data());
	   			fRtdb->setOutput(db_output);


			}
			else
			{		
				// Set the Ascii IO as first input
				FairParAsciiFileIo* db_output =  new FairParAsciiFileIo();
	   			TString filename = workdir + io_output.c_str();
	            db_output->open(filename.Data(),"in");
	            fRtdb->setOutput(db_output); 
			}


      	}
		else
		{
    	 	// Set the SQL based IO as first input
	   		FairParTSQLIo* db_output = new FairParTSQLIo();
	   		db_output->SetVerbosity(1);
	   		db_output->open();
	   		fRtdb->setOutput(db_output);		
		}

     }
     else
     {
		LOG(DEBUG) << "-E- FairDbMQWorker::Run() already set Io Output !... "  << endl;

     } //!(output)
}


void FairDbMQWorker::PrintCache()
{
for ( std::map<string,FairDbObjTableMap*>::const_iterator it = fParMap.begin(); it != fParMap.end(); it++)
	{
    	cout << "Key: " << it->first << endl;
    	FairDbObjTableMap* obj = it->second; 
    	cout << "Values" << endl;
     	obj->Print();
  	}
}


int FairDbMQWorker::Run()
{
   		 
	 //  Tell backend we're ready for work
	 std::cout << "-I-  FairDbMQWorker::Run() RTDB initialised ... ready to work ...: " << std::endl; 
	 FairDbMQ::Send (*fSocket, "ready");
	 
	 
	 std::cout << "-I-  FairDbMQWorker Local cache container " << std::endl; 
     PrintCache();

	 while (1) {

	
	   std::string address = FairDbMQ::Recv (*fSocket);
	   {
		 std::string empty = FairDbMQ::Recv (*fSocket);
		 assert (empty.size() == 0);
	   }
	   
	    //  Get request, send reply
	    std::string request = FairDbMQ::Recv (*fSocket);
	    int rid = atoi(request.c_str()); 
	    std::cout << "-I- FairDbMQWorker:: get request for RID# " << rid << std::endl;

   	   
        TString serialized_str;
        int par_size;

		if (!IsMapEmpty())
		 {
        	Initialise(rid);
        	Serialize(serialized_str,par_size);       	
		    cout << " -I- FairDbMQWorker:: serializing: " << serialized_str << " size: " << par_size << endl;
		 }


	   // Send the reply  
	   FairDbMQ::Sendmore (*fSocket, address);
	   FairDbMQ::Sendmore (*fSocket, "");
	   FairDbMQ::Send     (*fSocket, serialized_str.Data());
	   //FairDbMQ::Send     (*fSocket, "OK");
	   std::cout << "-I- FairDbMQWorker send reply@: " <<  address << " :OK " << std::endl;
	   
	   //sleep(10);   
	 }//!(while) 
	 
	 
	 return 0;
}