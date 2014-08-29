#include "FairDbMQUtils.h"



virtual const char* error_t::what () const throw ()
{
  return zmq_strerror (errnum);
}

int error_t::num () const
{
  return errnum;
}
