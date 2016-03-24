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
#include "GenExPart1Sampler.h"
#include "runSimpleMQStateMachine.h" 


// FairRoot - Tutorial 7
#include "MyDigi.h"

#include "TClonesArray.h"
#include "FairMQProgOptions.h"


int main(int argc, char** argv)
{
    try
    {
        // create option manager object
        FairMQProgOptions config;

        // define option description
        namespace po = boost::program_options;
        po::options_description sampler_options("Sampler options");
        sampler_options.add_options()
            ("input-file", po::value<std::string>(), "Path to the input file");

        // add option descritpion to the command line option manager
        config.AddToCmdLineOptions(sampler_options);

        // parse command lines
        if (config.ParseAll(argc, argv))
        {
            return 1;
        }

        //get parsed input-file option
        std::string filename = config.GetValue<std::string>("input-file");
        
        // create sampler 
        GenExPart1Sampler sampler;
        sampler.SetFileName(filename);

        // start simple state machine
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

