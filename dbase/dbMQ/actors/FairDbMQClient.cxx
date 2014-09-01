/** 
 *  FairDbMQClient.cxx 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#include "FairDbMQClient.h"


#include <iostream>
#include <csignal>


using namespace std;

FairDbMQClient::FairDbMQClient(): 
	fContext(NULL)
   ,fSocket(NULL)
{
	fContext = new db_zmq::context_t (1);
    fSocket  = new db_zmq::socket_t (*fContext, ZMQ_REQ ); 
    // for tracing      
    FairDbMQ::SetId (*fSocket);   
    fSocket->connect("tcp://localhost:5555");
} 

FairDbMQClient::~FairDbMQClient()
{
	if(fContext) delete fContext;
	if(fSocket)  delete fSocket; 
} 


int FairDbMQClient::Run()
{
	//  Send request, get reply
  std::cout << "-I- Client:: send request: " << "hello" << std::endl;
  FairDbMQ::Send (*fSocket, "hello");
  std::string reply = FairDbMQ::Recv (*fSocket);
  std::cout << "-I- Client get reply: " << reply << std::endl;
}
