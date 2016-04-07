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

        options_description samplerOptions("Sampler options");
        samplerOptions.add_options()
            ("msg-size", value<int>(&msgSize)->default_value(1000), "Message size in bytes");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(samplerOptions);

        if (config.ParseAll(argc, argv))
        {
            return 0;
        }

        FairMQExampleShmSampler sampler;
        sampler.SetProperty(FairMQExampleShmSampler::MsgSize, msgSize);

        runStateMachine(sampler, config);
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "Unhandled Exception: " << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
