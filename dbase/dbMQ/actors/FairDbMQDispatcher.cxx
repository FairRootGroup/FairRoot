/** 
 *  FairDbMQDispatcher.cxx 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#include "FairDbMQDispatcher.h"



using namespace std;


FairDbMQDispatcher::FairDbMQDispatcher(): 
	fContext(NULL)
   ,fFrontend(NULL)
   ,fBackend(NULL) 
{
	fContext = new db_zmq::context_t (1);

    fFrontend  = new db_zmq::socket_t (*fContext, ZMQ_ROUTER); 
    fBackend   = new db_zmq::socket_t (*fContext, ZMQ_ROUTER); 
   
    //  For clients
    fFrontend->bind("tcp://*:5555");    
    //  For workers
	fBackend->bind("tcp://*:5556");     
} 

FairDbMQDispatcher::~FairDbMQDispatcher()
{
	if(fContext) delete fContext;
	if(fFrontend)  delete fFrontend; 
	if(fBackend)  delete fBackend; 
} 



int FairDbMQDispatcher::Run()
{
	cout << "-I- FairDbMQDispatcher:: Queueing Daemon Started ..." << endl;

   
    while (1) {
	  
	  //  Initialize poll set
	  db_zmq::pollitem_t items [] = {
		//  Always poll for worker activity on *fBackend
		{ *fBackend,  0, ZMQ_POLLIN, 0 },
		//  Poll front-end only if we have available workers
		{ *fFrontend, 0, ZMQ_POLLIN, 0 }
	  };

	  if (fWorker_queue.size())
		db_zmq::poll (&items [0], 2, -1);
	  else
		db_zmq::poll (&items [0], 1, -1);
	  
	  //  Handle worker activity on backend socket
	  if (items [0].revents & ZMQ_POLLIN) {
		
		//  Queue worker address for LRU routing
		fWorker_queue.push(FairDbMQ::Recv (*fBackend));
		
		{
		  //  Second frame is empty
		  std::string empty = FairDbMQ::Recv (*fBackend);
		  assert (empty.size() == 0);
		}
		
		//  Third frame is READY or else a client reply address
		std::string client_addr = FairDbMQ::Recv (*fBackend);
		
		//  If client reply, send rest back to frontend
		if (client_addr.compare("ready") != 0) {
		  
		  {
			std::string empty = FairDbMQ::Recv (*fBackend);
			assert (empty.size() == 0);
		  }
          
		  std::string reply = FairDbMQ::Recv (*fBackend);
		  FairDbMQ::Sendmore (*fFrontend, client_addr);
		  FairDbMQ::Sendmore (*fFrontend, "");
		  FairDbMQ::Send     (*fFrontend, reply);
          
		  //if (--client_nbr == 0)
		  //	break;
		}
	  }

	  if (items [1].revents & ZMQ_POLLIN) {
		
		//  Now get next client request, route to LRU worker queue
		//  Protocol Client side is [address][empty][request]
		std::string client_addr = FairDbMQ::Recv (*fFrontend);
        
		{
		  std::string empty = FairDbMQ::Recv (*fFrontend);
		  assert (empty.size() == 0);
		}
        
		std::string request = FairDbMQ::Recv (*fFrontend);
		//worker_queue [0];
		std::string worker_addr = fWorker_queue.front();
		fWorker_queue.pop();
		
		FairDbMQ::Sendmore (*fBackend, worker_addr);
		FairDbMQ::Sendmore (*fBackend, "");
		FairDbMQ::Sendmore (*fBackend, client_addr);
		FairDbMQ::Sendmore (*fBackend, "");
		FairDbMQ::Send     (*fBackend, request);
	  }

    }//! while(1)

    sleep (1);
    return 0;
}