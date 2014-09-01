/** 
 *  FairDbMQWorker.h 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#ifndef FAIRDBMQWORKER_H
#define FAIRDBMQWORKER_H

#include <map>

#include "FairRuntimeDb.h"
#include "FairDbObjTableMap.h"
#include "FairDbMQ.h"



using namespace std;

class FairDbMQWorker
{
	public:
 	FairDbMQWorker();
	virtual ~FairDbMQWorker(); 
 
    void SetIoInput(string io_input);
    void SetIoOuput(string io_ouput); 

    virtual int Register(string p_name){;}
    virtual bool Initialise(int rid){;}
    virtual void Serialize(TString& str, Int_t& p_size){;} 

  	virtual int Run();
    
    void PrintCache();
    inline bool IsMapEmpty();
    
 	protected:

    db_zmq::context_t *fContext;
    db_zmq::socket_t  *fSocket;

    string fIo_input;
    string fIo_output;

    // RTDB 
	FairRuntimeDb* fRtdb;

	// Parameter pool
 
    map<string, FairDbObjTableMap*> fParMap;
};


inline bool FairDbMQWorker::IsMapEmpty()
{
	map<string, FairDbObjTableMap*>::iterator it  = fParMap.begin();
	map<string, FairDbObjTableMap*>::iterator end = fParMap.end();

	return (it == end);
}



#endif