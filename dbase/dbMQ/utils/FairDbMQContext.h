/** 
 *  FairDbMQContext.h 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#ifndef FAIRDBMQCONTEXT_H
#define FAIRDBMQCONTEXT_H

#include "FairDbMQUtils.h"

namespace db_zmq
{

class context_t
    {
        friend class db_zmq::socket_t;

    public:

        inline explicit context_t (int io_threads_)
        {
            ptr = zmq_init (io_threads_);
            if (ptr == NULL)
                throw db_zmq::error_t ();
        }

#ifdef ZMQ_HAS_RVALUE_REFS
        inline context_t (context_t &&rhs) : ptr (rhs.ptr)
        {
            rhs.ptr = NULL;
        }
        inline context_t &operator = (context_t &&rhs)
        {
            std::swap (ptr, rhs.ptr);
            return *this;
        }
#endif

        inline ~context_t ()
        {
            close();
        }

        inline void close()
        {
            if (ptr == NULL)
                return;
            int rc = zmq_term (ptr);
            ZMQ_ASSERT (rc == 0);
            ptr = NULL;
        }

        // useful functionality for C API
        inline operator void* ()
        {
            return ptr;
        }

    private:

        void *ptr;

        context_t (const context_t&);
        void operator = (const context_t&);
    };

}

#endif
