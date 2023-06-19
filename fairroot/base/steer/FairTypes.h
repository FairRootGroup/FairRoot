/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTypes.h
 *
 *  Created on: May 16, 2023
 *      Author: R.Karabowicz
 */

#ifndef FAIR_TYPES_H_
#define FAIR_TYPES_H_

#include <iostream>
#include <limits>

/**
 * \brief Main namespace for FairRoot classes / types
 *
 * All new public classes and types of FairRoot will be in this namespace.
 * Note: Nost classes are still in no namespace.
 */
namespace FairRoot {
/**
 * \brief Ordinal identification number of entry in IO stream
 *
 * Data stored in ROOT trees are gropued into entries,
 * essentially equivalent to HEP events
 */
struct EntryID
{
    using underlying_type = size_t;

    static const EntryID None;

    EntryID(underlying_type value)
        : fId(value)
    {}

    EntryID() = default;

    operator underlying_type() const { return fId; }

    friend auto operator<<(std::ostream& os, EntryID id) -> std::ostream&
    {
        if (id == None) {
            return os << "<No Entry>";
        }
        return os << static_cast<underlying_type>(id);
    }

    auto operator++()
    {
        if (fId != None) {
            ++fId;
        }
        return *this;
    }
    auto operator++(int)
    {
        auto temp = *this;
        if (fId != None) {
            ++fId;
        }
        return temp;
    }

    auto operator--()
    {
        if (fId != None) {
            --fId;
        }
        return *this;
    }
    auto operator--(int)
    {
        auto temp = *this;
        if (fId != None) {
            --fId;
        }
        return temp;
    }
    auto operator+=(const EntryID& rhs)
    {
        fId += rhs.fId;
        return *this;
    }
    auto operator-=(const EntryID& rhs)
    {
        fId -= rhs.fId;
        return *this;
    }

  private:
    underlying_type fId{std::numeric_limits<underlying_type>::max()};
};

/// \sa https://stackoverflow.com/questions/29432283/c-static-constexpr-field-with-incomplete-type/50295183#50295183
inline constexpr const EntryID EntryID::None{};
}   // namespace FairRoot

#endif   // FAIR_TYPES_H_
