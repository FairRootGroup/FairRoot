#ifndef FAIRDBMQMSG_H
#define FAIRDBMQMSG_H

#include "FairDbMQUtils.h"
#include "FairDbMQError.h"

namespace db_zmq
{

typedef zmq_free_fn free_fn;


class message_t
    {
        friend class db_zmq::socket_t;

    public:

        inline message_t ()
        {
            int rc = zmq_msg_init (&msg);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline explicit message_t (size_t size_)
        {
            int rc = zmq_msg_init_size (&msg, size_);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline message_t (void *data_, size_t size_, free_fn *ffn_,
            void *hint_ = NULL)
        {
            int rc = zmq_msg_init_data (&msg, data_, size_, ffn_, hint_);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

#ifdef ZMQ_HAS_RVALUE_REFS
        inline message_t (message_t &&rhs) : msg (rhs.msg)
        {
            int rc = zmq_msg_init (&rhs.msg);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline message_t &operator = (message_t &&rhs)
        {
            std::swap (msg, rhs.msg);
            return *this;
        }
#endif

        inline ~message_t ()
        {
            int rc = zmq_msg_close (&msg);
            ZMQ_ASSERT (rc == 0);
        }

        inline void rebuild ()
        {
            int rc = zmq_msg_close (&msg);
            if (rc != 0)
                throw db_zmq::error_t ();
            rc = zmq_msg_init (&msg);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline void rebuild (size_t size_)
        {
            int rc = zmq_msg_close (&msg);
            if (rc != 0)
                throw db_zmq::error_t ();
            rc = zmq_msg_init_size (&msg, size_);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline void rebuild (void *data_, size_t size_, free_fn *ffn_,
            void *hint_ = NULL)
        {
            int rc = zmq_msg_close (&msg);
            if (rc != 0)
                throw db_zmq::error_t ();
            rc = zmq_msg_init_data (&msg, data_, size_, ffn_, hint_);
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline void move (message_t *msg_)
        {
            int rc = zmq_msg_move (&msg, &(msg_->msg));
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline void copy (message_t *msg_)
        {
            int rc = zmq_msg_copy (&msg, &(msg_->msg));
            if (rc != 0)
                throw db_zmq::error_t ();
        }

        inline void *data ()
        {
            return zmq_msg_data (&msg);
        }

        inline const void* data () const
        {
            return zmq_msg_data (const_cast<zmq_msg_t*>(&msg));
        }

        inline size_t size () const
        {
            return zmq_msg_size (const_cast<zmq_msg_t*>(&msg));
        }

    private:

        zmq_msg_t msg;
        message_t (const message_t&);
        void operator = (const message_t&);
    };
}

#endif
