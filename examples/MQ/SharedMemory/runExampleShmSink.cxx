/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <iostream>

#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "FairMQExampleShmSink.h"
#include "runSimpleMQStateMachine.h"

int main(int argc, char** argv)
{
    try
    {
        FairMQProgOptions config;

        if (config.ParseAll(argc, argv))
        {
            return 0;
        }

        FairMQExampleShmSink sink;

        runStateMachine(sink, config);
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "Unhandled Exception: " << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
