/* 
 * File:   baseMQtools.h
 * Author: winckler
 *
 * Created on November 19, 2014, 4:50 PM
 */

#ifndef FAIRMQTEMPLATE_H
#define FAIRMQTEMPLATE_H

// std
#include <iostream>
#include <type_traits>
#include <tuple>
#include <string>

// boost
#include <boost/archive/text_iarchive.hpp>

// FairRoot - FairMQ
#include "FairMQLogger.h"

namespace baseMQ
{
namespace tools
{
/// ///////////////////////// to print tuple elements ////////////////////////////////////////////
/// Define a type which holds an unsigned integer value
template<std::size_t>
struct int_{};

template <class Tuple, size_t Pos>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<Pos> )
{
    out << std::get< std::tuple_size<Tuple>::value-Pos >(t) << ',';
    return print_tuple(out, t, int_<Pos-1>());
}

template <class Tuple>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<1> )
{
    return out << std::get<std::tuple_size<Tuple>::value-1>(t);
}

template <class... Args>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t)
{
    out << '(';
    print_tuple(out, t, int_<sizeof...(Args)>());
    return out << ')';
}

/// ///////////////////////// --- RESOLVE --- /////////////////////////
namespace resolve
{
/// ////////////////////////////////////////////////////////////////////////
/// test function member signature in given class
namespace details
{
///////////////////////////////////////////////////////////////////////////
// test whether T has SetFileProperties member function
template<class T, class Sig, class=void>
struct has_SetFileProperties:std::false_type{};

template<class T, class R, class... Args>
struct has_SetFileProperties<T, R(Args...),
    typename std::enable_if<
      std::is_convertible<
        decltype(std::declval<T>().SetFileProperties(std::declval<Args>()...)),
        R
      >::value
      || std::is_same<R, void>::value // all return types are compatible with void
      // and, due to SFINAE, we can invoke T.foo(Args...) (otherwise previous clause fails)
      >::type
  >:std::true_type{};

///////////////////////////////////////////////////////////////////////////
// test whether T has InitTClonesArray member function
template<class T, class Sig, class=void>
struct has_InitTClonesArray:std::false_type{};

template<class T, class R, class... Args>
struct has_InitTClonesArray<T, R(Args...),
    typename std::enable_if<
      std::is_convertible<
        decltype(std::declval<T>().InitTClonesArray(std::declval<Args>()...)),
        R
      >::value
      || std::is_same<R, void>::value // all return types are compatible with void
      // and, due to SFINAE, we can invoke T.foo(Args...) (otherwise previous clause fails)
    >::type
  >:std::true_type{};

} // end namespace details

template <typename, typename T>
struct has_BoostSerialization
{
    static_assert(std::integral_constant<T, false>::value, "Second template parameter needs to be of function type.");
};

// specialization that does the checking

template <typename C, typename Ret, typename... Args>
struct has_BoostSerialization<C, Ret(Args...)>
{
  private:
    template <typename T>
    static constexpr auto check(T*)
        -> typename std::is_same<decltype(std::declval<T>().serialize(std::declval<Args>()...)),
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

template<class T, class Sig>
using has_SetFileProperties = std::integral_constant<bool, details::has_SetFileProperties<T, Sig>::value>;

template<class T, class Sig>
using has_InitTClonesArray = std::integral_constant<bool, details::has_InitTClonesArray<T, Sig>::value>;

} // end namespace resolve

/// ///////////////////////// --- TYPE INFO --- /////////////////////////
namespace typeinfo
{
template <typename T, typename Archive=boost::archive::text_iarchive>
void DataTypeInfo(std::string classname)
{
    MQLOG(INFO)<<"Info on type "<<classname;
    if(std::is_class<T>::value)
    {

        if (std::is_pod<T>::value)
        {
            MQLOG(INFO)<<classname<<" is POD" ;
        }
        else
        {
            MQLOG(INFO)<<classname<<" is not POD" ;
        }


        if (std::is_trivial<T>::value)
        {
            MQLOG(INFO)<<classname<<" is trivial" ;
        }
        else
        {
            MQLOG(INFO)<<classname<<" is not trivial" ;
        }


        // below commented because not yet implemented in gcc
        //if(std::is_trivially_copyable<TPayload>::value) not implemented yet in gcc 4.8.2
        //    MQLOG(INFO)<<classname<<" is trivially copyable" ;
        //else
        //    MQLOG(INFO)<<classname<<" is not trivially copyable" ;


        if (std::is_standard_layout<T>::value)
        {
            MQLOG(INFO)<<classname<<" is standard layout" ;
        }
        else
        {
            MQLOG(INFO)<<classname<<" is not standard layout" ;
        }


        if (resolve::has_BoostSerialization<T, void(Archive&, const unsigned int)>::value)
        {
            MQLOG(INFO)<<classname<<" is boost serializable" ;
        }
        else
        {
            if (resolve::has_BoostSerialization<T, void(Archive&)>::value)
            {
                MQLOG(INFO)<<classname<<" is boost serializable" ;
            }
            else
            {
                MQLOG(INFO)<<classname<<" has no void serialize(BoostArchive&) member" ;
            }
        }
    }
    else
    {
        MQLOG(INFO)<<classname<<" is not a class" ;
    }
    MQLOG(INFO)<<"";
};

} // end namespace TypeInfo

} // end namespace tools

} // end namespace BaseMQ

#endif /* FAIRMQTEMPLATE_H */
