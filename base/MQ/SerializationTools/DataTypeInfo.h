/* 
 * File:   DataTypeInfo.h
 * Author: winckler
 *
 * Created on November 10, 2014, 7:04 PM
 */

#ifndef CHECKDATA_H
#define	CHECKDATA_H

// std
#include <string>

// boost
#include <boost/archive/binary_iarchive.hpp>

// FairRoot
#include "FairMQLogger.h"
#include "has_BoostSerialization.h"

typedef boost::archive::binary_iarchive TBoostArchive;

template <typename T, typename Archive=TBoostArchive>
void DataTypeInfo(std::string classname)
{
    MQLOG(INFO)<<"Info on type "<<classname;
    if(std::is_class<T>::value)
    {
        
        if(std::is_pod<T>::value)
            MQLOG(INFO)<<classname<<" is POD" ;
        else
            MQLOG(INFO)<<classname<<" is not POD" ;


        if(std::is_trivial<T>::value)
            MQLOG(INFO)<<classname<<" is trivial" ;
        else
            MQLOG(INFO)<<classname<<" is not trivial" ;
        
        
        //if(std::is_trivially_copyable<TPayload>::value) not implemented yet in gcc 4.8.2
        //    MQLOG(INFO)<<classname<<" is trivially copyable" ;
        //else
        //    MQLOG(INFO)<<classname<<" is not trivially copyable" ;


        if(std::is_standard_layout<T>::value)
            MQLOG(INFO)<<classname<<" is standard layout" ;
        else
            MQLOG(INFO)<<classname<<" is not standard layout" ;


        if (has_BoostSerialization<T, void(Archive&, const unsigned int)>::value)
            MQLOG(INFO)<<classname<<" is boost serializable" ;
        else
        {
            if (has_BoostSerialization<T, void(Archive&)>::value)
                MQLOG(INFO)<<classname<<" is boost serializable" ;
            else
                MQLOG(INFO)<<classname<<" has no void serialize(BoostArchive&) member" ;
        }
    }
    else
    {
        MQLOG(INFO)<<classname<<" is not a class" ;
    }
    MQLOG(INFO)<<"";
};



#define GET_F(funcname) #funcname
#define FUNC_NAME InitTClonesArray

template <typename, typename T>
struct has_funcMember
{
    static_assert(std::integral_constant<T, false>::value, "Second template parameter needs to be of function type.");
};

// specialization that does the checking

template <typename C, typename Ret, typename... Args>
struct has_funcMember<C, Ret(Args...)>
{
  private:
    template <typename T>
    static constexpr auto check(T*)
        -> typename std::is_same<decltype(std::declval<T>().FUNC_NAME(std::declval<Args>()...)),
                                 Ret // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                                 >::type
    {
        return {};
    }; // attempt to call it and see if the return type is correct

    template <typename>
    static constexpr std::false_type check(...)
    {
        return {};
    };

    typedef decltype(check<C>(0)) type;

  public:
    static constexpr bool value = type::value;
};


void func ( void (*f)(int) );

#endif	/* CHECKDATA_H */

