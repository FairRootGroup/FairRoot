/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairLogger.h"
#include "FairSimConfig.h"

#include "../macros/run_tutorial1_binary.C"

int main(int argc, char* argv[])
{
    FairSimConfig simConfig;
    
    int value = simConfig.ParseCommandLine(argc, argv);
    
    if(value)
    {
        return 0;
    }
    
    if(simConfig.IsHelp())
    {
        simConfig.PrintHelpMessage();
        return 0;
    }
    
    LOG(info) << "Executing runTutorial1";
    
    run_tutorial1_main(simConfig);
    
    return 0;
}
