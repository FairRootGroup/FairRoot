/* 
 * File:   processorFunctions.h
 * Author: winckler
 *
 * Created on July 11, 2015, 3:06 PM
 */

#ifndef PROCESSORFUNCTIONS_H
#define	PROCESSORFUNCTIONS_H

#include "runGenericDevices.h"

template<typename TGenProcessor, typename SpecFlag=NoSpecFlag>
inline int runProcessor(TGenProcessor& processor_,int argc, char** argv)
{
    namespace po = boost::program_options;
    FairMQProgOptions config;
    
    std::string diginame;
    std::string hitname;
    
    po::options_description processor_options("Processor options");
    processor_options.add_options()
        ("digi-classname", po::value<std::string>(&diginame)->default_value("MyDigi"), "Digi class name for initializing TClonesArray")
        ("hit-classname",  po::value<std::string>(&hitname)->default_value("MyHit"), "Hit class name for initializing TClonesArray")
    ;

    config.AddToCmdLineOptions(processor_options);
    config.AddToCfgFileOptions(processor_options,false);

    if (config.ParseAll(argc, argv, true))
    {
        return 1;
    }

    /// configure processor specific parts from parsed values
    // PolicyInit<T,U> : helper template function to handle different API of different policies (presence or not of InitTask and InitInputContainer )
    PolicyInit<SpecFlag> processorInit;
    processorInit.template InputContainer<TGenProcessor>(processor_,diginame);
    processorInit.template Task<TGenProcessor>(processor_,hitname);
    
    /// configure FairMQdevice parts from parsed values (here json file)
    /// and start the state machine
    runStateMachine(processor_,config);
    
    return 0;
}



#endif	/* PROCESSORFUNCTIONS_H */

