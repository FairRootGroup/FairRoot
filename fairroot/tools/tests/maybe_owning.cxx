/********************************************************************************
 *   Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMemory.h"

#include <catch2/catch_test_macros.hpp>
#include <set>

using fairroot::detail::maybe_owning_ptr;
using fairroot::detail::non_owning;

struct DestructAnalyzer
{
    unsigned int destructed = 0;
    std::set<char> whatwasdestructed;

    struct DestructMe
    {
        DestructAnalyzer& parent;
        char id;

        DestructMe(DestructAnalyzer& p, char aid)
            : parent(p)
            , id(aid)
        {}
        ~DestructMe()
        {
            parent.destructed++;
            parent.whatwasdestructed.insert(id);
        }
    };

    std::unique_ptr<DestructMe> create_one(char aid) { return std::make_unique<DestructMe>(*this, aid); }
    bool was_destructed(char aid) { return whatwasdestructed.count(aid) == 1; }
};

using MaybeOwning = maybe_owning_ptr<DestructAnalyzer::DestructMe>;

TEST_CASE("maybe_owning_ptr")
{
    DestructAnalyzer analyzer;

    auto item_a = analyzer.create_one('A');

    SECTION("DestructAnalyzer")
    {
        REQUIRE(analyzer.destructed == 0);
        item_a.reset();
        REQUIRE(analyzer.destructed == 1);
        REQUIRE(analyzer.was_destructed('A'));
    }
    SECTION("Pass ownership and go out of scope")
    {
        {
            MaybeOwning other;
            other = std::move(item_a);
            REQUIRE(!item_a);
            REQUIRE(other);
            REQUIRE(analyzer.destructed == 0);
        }
        REQUIRE(analyzer.destructed == 1);
        REQUIRE(analyzer.was_destructed('A'));
    }
    SECTION("Pass ownership and replace with reference")
    {
        auto item_b = analyzer.create_one('B');
        {
            MaybeOwning other;
            other = std::move(item_a);
            REQUIRE(!item_a);
            REQUIRE(other);
            other = MaybeOwning{item_b.get(), non_owning};
            REQUIRE(analyzer.destructed == 1);
            REQUIRE(analyzer.was_destructed('A'));
        }
        REQUIRE(analyzer.destructed == 1);
    }
    SECTION("Pass a reference and go out of scope")
    {
        {
            MaybeOwning other;
            other = MaybeOwning{item_a.get(), non_owning};
            REQUIRE(item_a);
            REQUIRE(other);
        }
        REQUIRE(analyzer.destructed == 0);
        REQUIRE(item_a);
    }
    SECTION("Pass a reference and replace with owning")
    {
        {
            MaybeOwning other;
            other = MaybeOwning{item_a.get(), non_owning};
            REQUIRE(item_a);
            REQUIRE(other);
            other = analyzer.create_one('B');
            REQUIRE(analyzer.destructed == 0);
        }
        REQUIRE(analyzer.destructed == 1);
        REQUIRE(analyzer.was_destructed('B'));
        REQUIRE(item_a);
    }
}
