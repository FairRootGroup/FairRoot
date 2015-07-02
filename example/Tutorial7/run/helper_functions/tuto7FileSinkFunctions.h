/* 
 * File:   fileSinkFunctions.h
 * Author: winckler
 *
 * Created on July 11, 2015, 3:07 PM
 */

#ifndef FILESINKFUNCTIONS_H
#define	FILESINKFUNCTIONS_H

#include "runGenericDevices.h"

template<typename TGenSink, typename SpecFlag=NoSpecFlag>
inline int runFileSink(TGenSink& sink,int argc, char** argv)
{
    namespace po = boost::program_options;
    FairMQProgOptions config;
        
    std::string filename;
    std::string treename;
    std::string branchname;
    std::string hitname;
    std::string fileoption;
    
    po::options_description sink_options("File Sink options");
    sink_options.add_options()
        //TODO : make the semantic required for at least one source (and not both cfg & cmd)
        //("input.file.name",         value<std::string>(&filename)->required(),                       "Path to the input file")
        ("output.file.name",         po::value<std::string>(&filename),                                "Path to the input file")
        ("output.file.tree",         po::value<std::string>(&treename)->default_value("T7SinkTree"),   "Name of the output tree")
        ("output.file.branch",       po::value<std::string>(&branchname)->default_value("MyHit"),      "Name of the output Branch")
        ("output.file.option",       po::value<std::string>(&fileoption)->default_value("RECREATE"),   "Root file option : UPDATE, RECREATE etc.")
        ("hit-classname",            po::value<std::string>(&hitname)->default_value("MyHit"),         "Hit class name for initializing TClonesArray")
    ;

    config.AddToCmdLineOptions(sink_options);
    config.AddToCfgFileOptions(sink_options,false);

    if (config.ParseAll(argc, argv,true))
    {
        return 1;
    }
    
    /// configure sink specific from parsed values
    
    // call function member from sink policy (storage policy)
    sink.SetFileProperties(filename, treename, branchname, hitname, fileoption, true);
    
    // call function member from sink policy (input policy for deserialization) using the helper function to handle different API
    PolicyInit<SpecFlag> sinkInit;
    sinkInit.template InputContainer<TGenSink>(sink,hitname);
    
    
    /// configure FairMQdevice specific from parsed values (here json file)
    /// and start the state machine
    runStateMachine(sink, config);
    
    return 0;
}


#endif	/* FILESINKFUNCTIONS_H */

