#ifndef FAIRDBMQDISPATCHER_H
#define FAIRDBMQDISPATCHER_H

#include <iostream>
#include <queue>
#include <csignal>


#include "FairDbMQ.h"

class FairDbMQDispatcher
{
	public:
 	FairDbMQDispatcher();
	virtual ~FairDbMQDispatcher(); 
 
  	virtual int Run();

 	private:

    db_zmq::context_t *fContext;
    db_zmq::socket_t  *fFrontend;
    db_zmq::socket_t  *fBackend;

    std::queue<std::string> fWorker_queue;
};




#endif