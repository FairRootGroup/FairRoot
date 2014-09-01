/** 
 *  FairDbMQSocket.h 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#ifndef FAIRDBMQSOCKET_H
#define FAIRDBMQSOCKET_H

#include "FairDbMQUtils.h"
#include "FairDbMQContext.h"


namespace db_zmq 
{

class socket_t
    {
    public:

        inline socket_t (db_zmq::context_t &context_, int type_)
        {
            ptr = zmq_socket (context_.ptr, type_);
            if (ptr == NULL)
                throw db_zmq::error_t ();
        }

#ifdef ZMQ_HAS_RVALUE_REFS
        inline socket_t(socket_t&& rhs) : ptr(rhs.ptr)
        {
            rhs.ptr = NULL;
        }
        inline socket_t& operator=(socket_t&& rhs)
        {
            std::swap(ptr, rhs.ptr);
            return *this;
        }
#endif

        inline ~socket_t ()
        {
            close();
        }

        inline operator void* ()
        {
            return ptr;
        }

        inline void close()
        {
            if(ptr == NULL)
                // In case already closed
                return ;
            int rc = zmq_close (ptr);
            ZMQ_ASSERT (rc == 0);
            ptr = 0 ;
        }

        inline void setsockopt (int option_, const void *optval_,
            size_t optvallen_)
        {
            int rc = zmq_setsockopt (ptr, option_, optval_, optvallen_);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline void getsockopt (int option_, void *optval_,
            size_t *optvallen_)
        {
            int rc = zmq_getsockopt (ptr, option_, optval_, optvallen_);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline void bind (const char *addr_)
        {
            int rc = zmq_bind (ptr, addr_);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline void connect (const char *addr_)
        {
            int rc = zmq_connect (ptr, addr_);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline bool connected()
        {
            return(ptr != NULL);
        }

        inline size_t send (const void *buf_, size_t len_, int flags_ = 0)
        {
            int nbytes = zmq_send (ptr, buf_, len_, flags_);
            if (nbytes >= 0)
                return (size_t) nbytes;
            if (zmq_errno () == EAGAIN)
                return 0;
            throw db_zmq::error_t ();
        }

        inline bool send (db_zmq::message_t &msg_, int flags_ = 0)
        {
            int nbytes = zmq_msg_send (&(msg_.msg), ptr, flags_);
            if (nbytes >= 0)
                return true;
            if (zmq_errno () == EAGAIN)
                return false;
            throw db_zmq::error_t ();
        }

        inline size_t recv (void *buf_, size_t len_, int flags_ = 0)
        {
            int nbytes = zmq_recv (ptr, buf_, len_, flags_);
            if (nbytes >= 0)
                return (size_t) nbytes;
            if (zmq_errno () == EAGAIN)
                return 0;
            throw db_zmq::error_t ();
        }

        inline bool recv (db_zmq::message_t *msg_, int flags_ = 0)
        {
            int nbytes = zmq_msg_recv (&(msg_->msg), ptr, flags_);
            if (nbytes >= 0)
                return true;
            if (zmq_errno () == EAGAIN)
                return false;
            throw db_zmq::error_t ();
        }

    private:

        void *ptr;

        socket_t (const socket_t&) ZMQ_DELETED_FUNCTION;
        void operator = (const socket_t&) ZMQ_DELETED_FUNCTION;
    };

}
#endif