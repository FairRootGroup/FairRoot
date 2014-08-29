#ifndef FAIRDBMQCLIENT_H
#define FAIRDBMQCLIENT_H

#include "FairDbMQ.h"

class FairDbMQClient
{
	public:
 	FairDbMQClient();
	virtual ~FairDbMQClient(); 
 
  	virtual int Run();

 	private:

    db_zmq::context_t *fContext;
    db_zmq::socket_t  *fSocket;

};




#endif