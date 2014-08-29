#ifndef FAIRDBMQPARMGR_H
#define FAIRDBMQPARMGR_H

#include <map>

#include "FairRuntimeDb.h"
#include "FairDbObjTableMap.h"
#include "FairDbMQ.h"


using namespace std;




class FairDbMQParMgr
{

typedef map<int, FairDbObjTableMap*> TParMap;
typedef map<string, TParMap> TParCache;	

    public:
 	FairDbMQParMgr();
	virtual ~FairDbMQParMgr(); 
 
    virtual FairDbObjTableMap* Register(string p_name);
    virtual FairDbObjTableMap* Initialise(string p_name, int rid);

    
    void PrintParCache();
    inline bool IsParCacheEmpty();
    
 	protected:
    db_zmq::context_t *fContext;
    db_zmq::socket_t  *fSocket;

    // RTDB 
	FairRuntimeDb* fRtdb;
	// DB Cache
    TParCache fParCache; 
};


inline bool FairDbMQParMgr::IsParCacheEmpty()
{
    TParCache::iterator it  = fParCache.begin();
    TParCache::iterator end = fParCache.end();
    return (it == end);
}



#endif