/** 
 *  FairDbMQTutWorker.cxx 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#include "FairDbMQTutWorker.h"
#include "FairDbTutPar2.h"

FairDbMQTutWorker::FairDbMQTutWorker() : FairDbMQWorker()
{
	// ctor
}

FairDbMQTutWorker::~FairDbMQTutWorker()
{
	// dtor
	if(fRtdb) fRtdb->saveOutput();  
}

int FairDbMQTutWorker::Register(string p_name)
{

 // Parameter managing according to Container Factory definition 	
 if(!p_name.compare("TUTParDefault"))
 {
 	cout << "-I- FairDbMQTutWorker:: FairDbTutPar2 is created" << endl;
	FairDbTutPar2* par = (FairDbTutPar2*)(fRtdb->getContainer(p_name.c_str()));	
    fParMap[p_name]=par;
 }

 
}

bool FairDbMQTutWorker::Initialise(int rid)
{
	cout << "-I- FairDbMQTutWorker:: Initialise" << endl;

    // Check if required parameter exits in RTDB
	FairDbTutPar2* par = (FairDbTutPar2*)(fRtdb->findContainer("TUTParDefault"));
	   if (par) { 
		 cout << endl;
		 cout << "-I- FairDbMQTutWorker:: init parameter for runId: "  <<  rid << endl;
		 fRtdb->initContainers(rid);
		 par->Print();
		 //fRtdb->saveOutput();
		 cout << "-I- FairDbMQTutWorker:: parameter initialised for runId: "  <<  rid << endl;
	   }
 return true;
}

void FairDbMQTutWorker::Serialize(TString& str, Int_t& p_size)
{
	   FairDbTutPar2 * par = (FairDbTutPar2*)(fRtdb->findContainer("TUTParDefault"));
	   if (par)
	   {
	   	par->Serialize(str,p_size); 
	  	cout << " -I- FairDbMQTutWorker:: serializing: " << str << " size: " << p_size << endl;	 
       } 
}

