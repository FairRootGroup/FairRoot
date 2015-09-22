/* 
 * File:   SamplerFunctions.h
 * Author: winckler
 *
 * Created on July 11, 2015, 3:05 PM
 */

#ifndef SAMPLERFUNCTIONS_H
#define	SAMPLERFUNCTIONS_H

#include "runGenericDevices.h"

// dummy function to illustrate the task container feature
void myfuncHello(){LOG(INFO)<<"Hello ";}
void myfuncWorld(){LOG(INFO)<<"World ";}

template<typename TGenSampler>
inline int runSampler(TGenSampler& sampler_, int argc, char** argv)
{
    namespace po = boost::program_options;
    FairMQProgOptions config;
        
    int eventRate;
    std::string filename;
    std::string treename;
    std::string branchname;
    bool taskman;

    po::options_description sampler_options("Sampler options");
    sampler_options.add_options()
        ("event-rate",              po::value<int>(&eventRate)->default_value(0),                   "Event rate limit in maximum number of events per second")
        //TODO : make the semantic required for at least one source (and not both cfg & cmd)
        //("input.file.name",         value<std::string>(&filename)->required(),                       "Path to the input file")
        ("input.file.name",         po::value<std::string>(&filename),                               "Path to the input file")
        ("input.file.tree",         po::value<std::string>(&treename)->default_value("T7DataTree"),  "Name of the tree")
        ("input.file.branch",       po::value<std::string>(&branchname)->default_value("T7digidata"),"Name of the Branch")
        ("register-task-sampler",   po::value<bool>(&taskman)->default_value(false), "Register simple example")
    ;

    
    
    config.AddToCmdLineOptions(sampler_options);
    config.AddToCfgFileOptions(sampler_options,false);

    if (config.ParseAll(argc, argv,true))
    {
        return 1;
    }
    
    
    if(taskman)
    {
        sampler_.RegisterTask(
        [](SimpleTreeReader<TClonesArray>* t, std::map<int, std::function<void()> >& task_list) 
        { 
            task_list[0]=std::bind(myfuncHello);
            task_list[1]=std::bind(myfuncWorld);
            //task_list[2]=std::bind( &U::blah, t );
            //task_list[3]=std::bind( &TGenSampler::template MultiPartTask<5>, t );
        }
    );
    }
    
    /// configure sampler specific from parsed values
    sampler_.SetProperty(TGenSampler::EventRate, eventRate);
    // call function member from sampler policy
    sampler_.SetFileProperties(filename, treename, branchname);
    
    /// configure FairMQdevice specific from parsed values (here json file)
    /// and start the state machine
    runStateMachine(sampler_, config);
    
    return 0;
}

template<typename TGenSampler>
inline int InitSamplerSetting(TGenSampler& sampler_, FairMQProgOptions& config, int argc, char** argv)
{
    namespace po = boost::program_options;
    //FairMQProgOptions config;
        
    int eventRate;
    std::string filename;
    std::string treename;
    std::string branchname;

    po::options_description sampler_options("Sampler options");
    sampler_options.add_options()
        ("event-rate",              po::value<int>(&eventRate)->default_value(0),                   "Event rate limit in maximum number of events per second")
        //TODO : make the semantic required for at least one source (and not both cfg & cmd)
        //("input.file.name",         value<std::string>(&filename)->required(),                       "Path to the input file")
        ("input.file.name",         po::value<std::string>(&filename),                               "Path to the input file")
        ("input.file.tree",         po::value<std::string>(&treename)->default_value("T7DataTree"),  "Name of the tree")
        ("input.file.branch",       po::value<std::string>(&branchname)->default_value("T7digidata"),"Name of the Branch")
        ("register-task-sampler",   po::value<bool>()->default_value(false), "Register simple example")
    ;
    
    config.AddToCmdLineOptions(sampler_options);
    config.AddToCfgFileOptions(sampler_options,false);

    if (config.ParseAll(argc, argv,true))
    {
        return 1;
    }
    
    /// configure sampler specific from parsed values
    sampler_.SetProperty(TGenSampler::EventRate, eventRate);
    // call function member from sampler policy
    sampler_.SetFileProperties(filename, treename, branchname);
    
    return 0;
}

#endif	/* SAMPLERFUNCTIONS_H */

