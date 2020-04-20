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
#include <string>
#include <tuple>
#include <type_traits>

// boost
#include <boost/archive/text_iarchive.hpp>

// FairRoot - FairMQ
#include "FairLogger.h"

namespace baseMQ {
namespace tools {
/// ///////////////////////// to print tuple elements ////////////////////////////////////////////
/// Define a type which holds an unsigned integer value
template<std::size_t>
struct int_
{};

template<typename Tuple, size_t Pos>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<Pos>)
{
    out << std::get<std::tuple_size<Tuple>::value - Pos>(t) << ',';
    return print_tuple(out, t, int_<Pos - 1>());
}

template<typename Tuple>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<1>)
{
    return out << std::get<std::tuple_size<Tuple>::value - 1>(t);
}

template<typename... Args>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t)
{
    out << '(';
    print_tuple(out, t, int_<sizeof...(Args)>());
    return out << ')';
}

namespace resolve {
/// test function member signature in given class

namespace details {

// test whether T has SetFileProperties member function
template<typename T, typename Sig, typename = void>
struct has_SetFileProperties : std::false_type
{};

template<typename T, typename R, typename... Args>
struct has_SetFileProperties<
    T,
    R(Args...),
    typename std::enable_if<
        std::is_convertible<decltype(std::declval<T>().SetFileProperties(std::declval<Args>()...)), R>::value
        || std::is_same<R, void>::value   // all return types are compatible with void
                                          // and, due to SFINAE, we can invoke T.foo(Args...) (otherwise previous clause
                                          // fails)
        >::type> : std::true_type
{};

// test whether T has InitTClonesArray member function
template<typename T, typename Sig, typename = void>
struct has_InitTClonesArray : std::false_type
{};

template<typename T, typename R, typename... Args>
struct has_InitTClonesArray<
    T,
    R(Args...),
    typename std::enable_if<
        std::is_convertible<decltype(std::declval<T>().InitTClonesArray(std::declval<Args>()...)), R>::value
        || std::is_same<R, void>::value   // all return types are compatible with void
                                          // and, due to SFINAE, we can invoke T.foo(Args...) (otherwise previous clause
                                          // fails)
        >::type> : std::true_type
{};

}   // end namespace details

template<typename T, typename Sig>
using has_SetFileProperties = std::integral_constant<bool, details::has_SetFileProperties<T, Sig>::value>;

template<typename T, typename Sig>
using has_InitTClonesArray = std::integral_constant<bool, details::has_InitTClonesArray<T, Sig>::value>;

}   // end namespace resolve

namespace typeinfo {
template<typename T, typename Archive = boost::archive::text_iarchive>
void DataTypeInfo(std::string classname)
{
    LOG(info) << "Info on type " << classname;

    if (std::is_class<T>::value) {

        if (std::is_pod<T>::value) {
            LOG(info) << classname << " is POD";
        } else {
            LOG(info) << classname << " is not POD";
        }

        if (std::is_trivial<T>::value) {
            LOG(info) << classname << " is trivial";
        } else {
            LOG(info) << classname << " is not trivial";
        }

        // below commented because not yet implemented in gcc
        // if(std::is_trivially_copyable<TPayload>::value) not implemented yet in gcc 4.8.2
        //    LOG(info) << classname << " is trivially copyable" ;
        // else
        //    LOG(info) << classname << " is not trivially copyable" ;

        if (std::is_standard_layout<T>::value) {
            LOG(info) << classname << " is standard layout";
        } else {
            LOG(info) << classname << " is not standard layout";
        }

        if (resolve::has_BoostSerialization<T, void(Archive&, const unsigned int)>::value) {
            LOG(info) << classname << " is boost serializable";
        } else {
            if (resolve::has_BoostSerialization<T, void(Archive&)>::value) {
                LOG(info) << classname << " is boost serializable";
            } else {
                LOG(info) << classname << " has no void serialize(BoostArchive&) member";
            }
        }
    } else {
        LOG(info) << classname << " is not a class";
    }
};

}   // namespace typeinfo

}   // end namespace tools

}   // namespace baseMQ

#endif /* FAIRMQTEMPLATE_H */
