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
#include "ParameterMQServer.h"
#include "TApplication.h"
#include "runSimpleMQStateMachine.h"

using namespace boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        std::string firstInputName;
        std::string firstInputType;
        std::string secondInputName;
        std::string secondInputType;
        std::string outputName;
        std::string outputType;

        options_description serverOptions("Parameter MQ Server options");
        serverOptions.add_options()
            ("first-input-name", value<std::string>(&firstInputName)->default_value("first_input.root"), "First input file name")
            ("first-input-type", value<std::string>(&firstInputType)->default_value("ROOT"), "First input file type (ROOT/ASCII)")
            ("second-input-name", value<std::string>(&secondInputName)->default_value(""), "Second input file name")
            ("second-input-type", value<std::string>(&secondInputType)->default_value("ROOT"), "Second input file type (ROOT/ASCII)")
            ("output-name", value<std::string>(&outputName)->default_value(""), "Output file name")
            ("output-type", value<std::string>(&outputType)->default_value("ROOT"), "Output file type");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(serverOptions);
        config.ParseAll(argc, argv);

        TApplication app("ParameterMQServer", 0, 0);

        ParameterMQServer server;
        server.SetProperty(ParameterMQServer::FirstInputName, firstInputName);
        server.SetProperty(ParameterMQServer::FirstInputType, firstInputType);
        server.SetProperty(ParameterMQServer::SecondInputName, secondInputName);
        server.SetProperty(ParameterMQServer::SecondInputType, secondInputType);
        server.SetProperty(ParameterMQServer::OutputName, outputName);
        server.SetProperty(ParameterMQServer::OutputType, outputType);

        runStateMachine(server, config);

        gApplication->Terminate();
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "Unhandled Exception reached the top of main: "
                   << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
