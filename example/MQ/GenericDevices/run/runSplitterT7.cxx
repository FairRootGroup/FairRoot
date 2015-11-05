/* 
 * File:   runSplitterT7.cxx
 * Author: winckler
 *
 * Created on July 7, 2015, 4:28 PM
 */

// FairRoot - FairMQ
#include "FairMQSplitter.h"
#include "runSimpleMQStateMachine.h"

int main(int argc, char** argv) 
{
    try
    {
        FairMQSplitter splitter;
        FairMQProgOptions config;
        config.UseConfigFile();
        if (config.ParseAll(argc, argv, true))
        {
            return 1;
        }

        runStateMachine(splitter, config);
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}

