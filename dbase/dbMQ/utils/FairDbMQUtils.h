/** 
 *  FairDbMQUtils.h 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#ifndef FAIRDBMQUTILS_H
#define FAIRDBMQUTILS_H

#include <zmq.h>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <exception>

// explicit deleted marked members function C++0x
#if (defined(__GNUC__) && (__GNUC__ > 4 || \
      (__GNUC__ == 4 && __GNUC_MINOR__ > 2)) && \
      defined(__GXX_EXPERIMENTAL_CXX0X__))
    #define ZMQ_HAS_RVALUE_REFS
    #define ZMQ_DELETED_FUNCTION = delete
#elif defined(__clang__)
    #if __has_feature(cxx_rvalue_references)
        #define ZMQ_HAS_RVALUE_REFS
    #endif

    #if __has_feature(cxx_deleted_functions)
        #define ZMQ_DELETED_FUNCTION 
    #endif
#else
    #define ZMQ_DELETED_FUNCTION
#endif

#ifndef NDEBUG
#   define ZMQ_ASSERT(expression) assert(expression)
#else
#   define ZMQ_ASSERT(expression) (expression)
#endif



namespace db_zmq
{
 
    class  error_t;
    class  message_t;
    class  context_t;
    class  socket_t;    
      
}
    
    

#endif
