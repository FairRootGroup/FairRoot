/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* 
 * File:   runMergerT7.cxx
 * Author: winckler
 *
 * Created on July 7, 2015, 4:28 PM
 */

// FairRoot - FairMQ
#include "FairMQMerger.h"
#include "runSimpleMQStateMachine.h"

 

int main(int argc, char** argv) 
{
    try
    {
        FairMQMerger merger;
        FairMQProgOptions config;
        config.UseConfigFile();
        if (config.ParseAll(argc, argv, true))
        {
            return 1;
        }

        runStateMachine(merger, config);
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
