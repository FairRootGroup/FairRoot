/********************************************************************************
 * Copyright (C) 2015-2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * @file fairmq/test/helper/runTestDevice.cxx
 */

#include "devices/TestPub.cxx"
#include "devices/TestPull.cxx"
#include "devices/TestPush.cxx"
#include "devices/TestRep.cxx"
#include "devices/TestReq.cxx"
#include "devices/TestSub.cxx"
#include "devices/TestTransferTimeout.cxx"
#include <boost/program_options.hpp>
#include <iostream>
#include <runFairMQDevice.h>
#include <string>

namespace bpo = boost::program_options;

auto addCustomOptions(bpo::options_description& options) -> void
{
}

auto getDevice(const FairMQProgOptions& config) -> FairMQDevicePtr
{
    using namespace std;
    using namespace fair::mq::test;

    auto id = config.GetValue<std::string>("id");
    if (0 == id.find("pull_"))
    {
        return new Pull;
    }
    else if (0 == id.find("push_"))
    {
        return new Push;
    }
    else if (0 == id.find("sub_"))
    {
        return new Sub;
    }
    else if (0 == id.find("pub_"))
    {
        return new Pub;
    }
    else if (0 == id.find("req_"))
    {
        return new Req;
    }
    else if (0 == id.find("rep_"))
    {
        return new Rep;
    }
    else if (0 == id.find("transfer_timeout_"))
    {
        return new TransferTimeout;
    }
    else
    {
        cerr << "Don't know id '" << id << "'" << endl;
        return nullptr;
    }
}
