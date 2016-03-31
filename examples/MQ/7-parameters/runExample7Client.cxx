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

#include <iostream>

#include "FairMQLogger.h"
#include "FairMQParser.h"
#include "FairMQProgOptions.h"
#include "FairMQExample7Client.h"

using namespace std;
using namespace boost::program_options;

int main(int argc, char** argv)
{
    FairMQExample7Client client;
    client.CatchSignals();

    FairMQProgOptions config;

    try
    {
        string parameterName;

        options_description clientOptions("Parameter Client options");
        clientOptions.add_options()
            ("parameter-name", value<string>(&parameterName)->default_value("FairMQExample7ParOne"), "Parameter Name");

        config.AddToCmdLineOptions(clientOptions);

        if (config.ParseAll(argc, argv))
        {
            return 0;
        }

        client.SetConfig(config);
        client.SetProperty(FairMQExample7Client::ParameterName, parameterName);

        client.ChangeState("INIT_DEVICE");
        client.WaitForEndOfState("INIT_DEVICE");

        client.ChangeState("INIT_TASK");
        client.WaitForEndOfState("INIT_TASK");

        client.ChangeState("RUN");
        client.InteractiveStateLoop();
    }
    catch (exception& e)
    {
        LOG(ERROR) << e.what();
        LOG(INFO) << "Command line options are the following: ";
        config.PrintHelp();
        return 1;
    }

    return 0;
}
