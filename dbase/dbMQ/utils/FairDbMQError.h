#ifndef FAIRDBMQERROR_H
#define FAIRDBMQERROR_H

#include "FairDbMQUtils.h"


namespace db_zmq
{

class error_t : public std::exception
    {
    public:
	  error_t () : errnum (zmq_errno ()) {}
	  virtual const char *what () const throw ();
      int num() const;
	  
    private:
	  int errnum;
	};
 
    
}

#endif
