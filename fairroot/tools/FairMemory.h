/********************************************************************************
 *    Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRROOT_MEMORY_H_
#define FAIRROOT_MEMORY_H_

#include <memory>
#include <optional>

/**
 * \brief Internal implementation details
 *
 * Any declarations in here are strictly for internal usage.
 * They may never enter public APIs.
 *
 * \note Anything in here can change at any time without notice!
 */
namespace fairroot::detail
{

template<typename T, typename Deleter = std::default_delete<T>>
struct optional_deleter
{
    std::optional<Deleter> deleter{std::in_place};

    optional_deleter() = default;
    optional_deleter(const Deleter& x)
        : deleter(std::in_place, x)
    {}
    optional_deleter(std::nullopt_t)
        : deleter()
    {}

    void operator()(T* ptr) const
    {
        if (deleter) {
            (*deleter)(ptr);
        }
    }
};

/**
 * \brief unique_ptr that alternatively can hold a reference
 *
 * In rare cases we need a unique_ptr that can alternatively
 * contain a reference (and thus not delete its content
 * on destruction).
 *
 * \note Think twice before using this!
 *
 * It's mostly meant for cases, where FairRoot has a public API
 * that enforces this behaviour. This should be deprecated and
 * removed sooner than later.
 *
 * \note Avoid `reset(T*)` as it does not change the Deleter's setting
 *       and thus can have surprising effects.
 */
template<typename T, typename Deleter = std::default_delete<T>>
using maybe_owning_ptr = std::unique_ptr<T, optional_deleter<T, Deleter>>;

inline constexpr auto non_owning = std::nullopt;

}   // namespace fairroot::detail

#endif
