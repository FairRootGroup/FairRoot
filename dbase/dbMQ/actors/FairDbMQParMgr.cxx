/** 
 *  FairDbMQParMgr.cxx 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#include "FairDbMQParMgr.h"


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


FairDbMQParMgr::FairDbMQParMgr(): 
	fContext(NULL)
   ,fSocket(NULL)
   ,fRtdb(FairRuntimeDb::instance())
{
	fContext = new db_zmq::context_t (1);
    fSocket  = new db_zmq::socket_t (*fContext, ZMQ_REQ ); 
    // for tracing      
    FairDbMQ::SetId (*fSocket);   
    fSocket->connect("tcp://localhost:5555");
} 

FairDbMQParMgr::~FairDbMQParMgr()
{
	if(fContext) {delete fContext; fContext=NULL;}
	if(fSocket)  {delete fSocket; fSocket=NULL;} 
    if (fRtdb)   {delete fRtdb; fRtdb=NULL;} 
} 


void FairDbMQParMgr::PrintParCache()
{
  
   for ( TParCache::const_iterator it1 = fParCache.begin(); it1 != fParCache.end(); it1++)
   {
   	  cout << "ParName: " << it1->first << endl;
      TParMap m_par = it1->second;

	for ( TParMap::const_iterator it = m_par.begin(); it != m_par.end(); it++)
		{
    		cout << "Rid: " << it->first << endl;
    		FairDbObjTableMap* obj = it->second; 
    		cout << "Object: " << endl;
     		obj->Print();
  		}
	}
}


FairDbObjTableMap* FairDbMQParMgr::Register(string p_name)
{
  FairDbObjTableMap* par = (FairDbObjTableMap*)(fRtdb->findContainer(p_name.c_str()));
  if( par )
  {
   // do nothing 
  }else
  {
   // create the container	 
   par = (FairDbObjTableMap*)(fRtdb->getContainer(p_name.c_str()));
  } 
   return par;
}



FairDbObjTableMap* FairDbMQParMgr::Initialise(string p_name, int rid)
{
    TParMap m_par = fParCache[p_name];
    // check if par already exist
    TParMap::iterator it    = m_par.begin();
    TParMap::iterator end   = m_par.end();
    if(it==end)
    {
    	std::cout << "-I- FairDbMQParMgr no object found in map, create it ...  " << std::endl;	
     	// No object 
     	FairDbObjTableMap* par = (FairDbObjTableMap*)(fRtdb->findContainer(p_name.c_str()));	
     	// Send a RID 
     	ostringstream conv;
     	conv << rid; 
     	FairDbMQ::Send(*fSocket,conv.str());
     	// Get Reply from RTDB service daemon    
     	std::string reply = FairDbMQ::Recv (*fSocket);
     
      	if(reply.compare("OK")==0) {
	       	std::cout << "-I- FairDbMQParMgr :::: Client get reply ... OK .. do nothing... " << std::endl;
     	}else {						
        	std::cout << "-I- FairDbMQParMgr :::: Client get reply ... now deserializing " << std::endl;   
        
         //CHECK ME ....... 
          par->Deserialize(reply);
          fParCache[p_name][rid]=par; 
        }	
     return par; 
    }
    else
	{
	 // object already there 
	 TParMap::iterator iter = m_par.upper_bound(rid);
	 FairDbObjTableMap* par =(--iter)->second;	
     return par;  
	}

	 return 0;
}