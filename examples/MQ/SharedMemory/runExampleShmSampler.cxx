/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <iostream>

#include "boost/program_options.hpp"

#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "FairMQExampleShmSampler.h"
#include "runSimpleMQStateMachine.h"

using namespace boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        int msgSize;
        int msgRate;

        options_description samplerOptions("Sampler options");
        samplerOptions.add_options()
            ("msg-size", value<int>(&msgSize)->default_value(1000), "Message size in bytes")
            ("msg-rate", value<int>(&msgRate)->default_value(0), "Msg rate limit in maximum number of messages per second");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(samplerOptions);
        config.ParseAll(argc, argv);

        FairMQExampleShmSampler sampler;
        sampler.SetProperty(FairMQExampleShmSampler::MsgSize, msgSize);
        sampler.SetProperty(FairMQExampleShmSampler::MsgRate, msgRate);

        runStateMachine(sampler, config);
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "Unhandled Exception: " << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
