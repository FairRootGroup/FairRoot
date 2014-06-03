/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* 
 * File:   has_BoostSerialization.h
 * Author: winckler
 *
 * Created on April 28, 2014, 10:20 AM
 */

#ifndef HAS_BOOSTSERIALIZATION_H
#define HAS_BOOSTSERIALIZATION_H

#include <type_traits>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///  template function that check whether a class T is Boost serializable or not
/// it search for a function member of T (and parent classes) named serialize with argument. c++11 required

// Primary template with a static assertion
// for a meaningful error message
// if it ever gets instantiated.
// We could leave it undefined if we didn't care.

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

#endif /* HAS_BOOSTSERIALIZATION_H */
