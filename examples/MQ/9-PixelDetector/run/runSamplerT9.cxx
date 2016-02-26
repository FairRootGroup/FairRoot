/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runSamplerRoot.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 1:57 PM
 */

// FairRoot - FairMQ
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "GenericSampler.h"
#include "runSimpleMQStateMachine.h" 

// FairRoot - Base/MQ
// sampler policies
#include "FairMQFileSource.h"
#include "RootSerializer.h"

// ////////////////////////////////////////////////////////////////////////

// build sampler type
typedef GenericSampler<FairMQFileSource_t, RootSerializer>           TSamplerTMessage;

int main(int argc, char** argv)
{
    try
    {
        
        std::string filename;
        std::string branchname;

        // define option description
        namespace po = boost::program_options;
        po::options_description sampler_options("Sampler options");
        sampler_options.add_options()
            ("input-name",    po::value<std::string>(&filename),                               "Path to the input file")
            ("input-branch",  po::value<std::string>(&branchname)->default_value("digidata"),  "Name of the Branch");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(sampler_options);

        if (config.ParseAll(argc, argv))
            return 1;

        
        TSamplerTMessage sampler;
        sampler.SetFileProperties(filename, branchname);

        // simple state machine helper function
        runStateMachine(sampler, config);

    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }
    return 0;
}

