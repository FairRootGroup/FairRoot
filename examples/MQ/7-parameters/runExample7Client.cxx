/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runExample7Client.cxx
 *
 * @since 2013-04-23
 * @author D. Klein, A. Rybalchenko
 */

#include "boost/program_options.hpp"

#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "FairMQExample7Client.h"

using namespace boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        std::string parameterName;

        options_description clientOptions("Parameter Client options");
        clientOptions.add_options()
            ("parameter-name", value<std::string>(&parameterName)->default_value("FairMQExample7ParOne"), "Parameter Name");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(clientOptions);
        config.ParseAll(argc, argv);

        FairMQExample7Client client;
        client.CatchSignals();
        client.SetConfig(config);
        client.SetProperty(FairMQExample7Client::ParameterName, parameterName);

        client.ChangeState("INIT_DEVICE");
        client.WaitForEndOfState("INIT_DEVICE");

        client.ChangeState("INIT_TASK");
        client.WaitForEndOfState("INIT_TASK");

        client.ChangeState("RUN");
        client.InteractiveStateLoop();
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "Unhandled Exception reached the top of main: "
                   << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
