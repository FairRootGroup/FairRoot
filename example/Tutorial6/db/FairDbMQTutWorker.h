/** 
 *  FairDbMQTutWorker.h 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#ifndef FAIRDBMQTUTWORKER_H
#define FAIRDBMQTUTWORKER_H

#include "FairDbMQWorker.h"

class FairDbMQTutWorker: public FairDbMQWorker
{
	public:
 	FairDbMQTutWorker();
	virtual ~FairDbMQTutWorker(); 
 
  	virtual int Register(std::string p_name);
  	virtual bool Initialise(int rid);
    virtual void Serialize(TString& str, Int_t& p_size);

 
};




#endif
