/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runParameterMQServer.cxx
 *
 * @since 2013-04-23
 * @author D. Klein, A. Rybalchenko
 */

#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "runSimpleMQStateMachine.h"

#include "ParameterMQServer.h"

#include "TApplication.h"

using namespace boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        options_description serverOptions("Parameter MQ Server options");
        serverOptions.add_options()
            ("first-input-name", value<std::string>()->default_value("first_input.root"), "First input file name")
            ("first-input-type", value<std::string>()->default_value("ROOT"), "First input file type (ROOT/ASCII)")
            ("second-input-name", value<std::string>()->default_value(""), "Second input file name")
            ("second-input-type", value<std::string>()->default_value("ROOT"), "Second input file type (ROOT/ASCII)")
            ("output-name", value<std::string>()->default_value(""), "Output file name")
            ("output-type", value<std::string>()->default_value("ROOT"), "Output file type")
            ("channel-name", value<std::string>()->default_value("data"), "Output channel name");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(serverOptions);
        config.ParseAll(argc, argv);

        TApplication app("ParameterMQServer", 0, 0);

        { // scope to destroy the device in case gApplication->Terminate() fails or aborts.
            ParameterMQServer server;
            runStateMachine(server, config);
        }

        LOG(DEBUG) << "Device exited, terminating TApplication...";
        gApplication->SetReturnFromRun(true);
        gApplication->Terminate();
        LOG(DEBUG) << "TApplication terminated.";
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "Unhandled Exception reached the top of main: "
                   << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
