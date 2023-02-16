/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runParameterMQServer.cxx
 *
 * @since 2013-04-23
 * @author D. Klein, A. Rybalchenko
 */

#include "FairRunFairMQDevice.h"
#include "ParameterMQServer.h"

#include <string>

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("first-input-name",    bpo::value<std::string>()->default_value(""),     "First input file name")
        ("first-input-type",    bpo::value<std::string>()->default_value("ROOT"), "First input file type (ROOT/ASCII)")
        ("second-input-name",   bpo::value<std::string>()->default_value(""),     "Second input file name")
        ("second-input-type",   bpo::value<std::string>()->default_value("ROOT"), "Second input file type (ROOT/ASCII)")
        ("output-name",         bpo::value<std::string>()->default_value(""),     "Output file name")
        ("output-type",         bpo::value<std::string>()->default_value("ROOT"), "Output file type")
        ("channel-name",        bpo::value<std::string>()->default_value(""),     "Output channel name")
        ("update-channel-name", bpo::value<std::string>()->default_value(""),     "Update channel name");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& /*config*/)
{
    return std::make_unique<ParameterMQServer>();
}
