#ifndef FAIRDBMQMISC_H
#define FAIRDBMQMISC_H

#include "FairDbMQUtils.h"
#include "FairDbMQError.h"

namespace db_zmq
{

  typedef zmq_pollitem_t pollitem_t;

    inline int poll (zmq_pollitem_t *items_, int nitems_, long timeout_ = -1)
    {
        int rc = zmq_poll (items_, nitems_, timeout_);
        if (rc < 0)
            throw db_zmq::error_t ();
        return rc;
    }

    inline void version (int *major_, int *minor_, int *patch_)
    {
        zmq_version (major_, minor_, patch_);
    }

}

#endif
