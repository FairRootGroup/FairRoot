#ifndef FAIRDBMQ_H
#define FAIRDBMQ_H

#include "zmq.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h> 
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>

#include "FairDbMQUtils.h"
#include "FairDbMQError.h"
#include "FairDbMQMsg.h"
#include "FairDbMQContext.h"
#include "FairDbMQSocket.h"
#include "FairDbMQMisc.h"



namespace FairDbMQ
{
   std::string Recv (db_zmq::socket_t & socket); 
   bool Send (db_zmq::socket_t & socket, const std::string & string);
   bool Sendmore (db_zmq::socket_t & socket, const std::string & string);
   void Print (db_zmq::socket_t & socket);
   int64_t Clock (void);
   void Sleep (int msecs);
   void SignalHandler (int signal_value);
   void CatchSignals ();


// Define a bunch of inline functions.

#define within(num) (int) ((float) (num) * random () / (RAND_MAX + 1.0))

 inline std::string SetId (db_zmq::socket_t & socket)
{
    std::stringstream ss;
    ss << std::hex << std::uppercase
          << std::setw(4) << std::setfill('0') << within (0x10000) << "-"
          << std::setw(4) << std::setfill('0') << within (0x10000);
    socket.setsockopt(ZMQ_IDENTITY, ss.str().c_str(), ss.str().length());
    return ss.str();
}



}




#endif //!FAIRDBMQ
