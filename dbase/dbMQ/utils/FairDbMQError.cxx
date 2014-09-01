/** 
 *  FairDbMQError.cxx 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#include "FairDbMQError.h"


const char* db_zmq::error_t::what () const throw ()
{
  return zmq_strerror (errnum);
}

int db_zmq::error_t::num () const
{
  return errnum;
}
