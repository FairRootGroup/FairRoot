/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runSamplerRoot.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 1:57 PM
 */

// FairRoot - FairMQ
#include "FairMQLogger.h"
#include "GenericSampler.h"
#include "runSimpleMQStateMachine.h" 

// FairRoot - Base/MQ
// sampler policies

 #include "FairMQFileSource.h"
 #include "SimpleTreeReader.h"

// FairRoot - Tutorial 7
#include "InitSamplerConfig.h"
#include "MyDigi.h"


// FairRoot - Base/MQ
// sampler & serialization policies
#include "BoostSerializer.h"
#include "RootSerializer.h"
#include "MyDigiSerializer.h"
#include "MyDigiSerializer_protobuff.h"

#include "TClonesArray.h"

// ////////////////////////////////////////////////////////////////////////


typedef SimpleTreeReader<TClonesArray> TreeReader_t;
// build sampler type
typedef GenericSampler<FairMQFileSource_t, MyDigiSerializer_t>       TSamplerBin;
typedef GenericSampler<FairMQFileSource_t, BoostSerializer<MyDigi> > TSamplerBoost;
typedef GenericSampler<FairMQFileSource_t, RootSerializer>           TSamplerTMessage;
typedef GenericSampler<FairMQFileSource_t, MyDigiProtoSerializer>    TSamplerProtoBuff;

typedef GenericSampler<TreeReader_t, MyDigiSerializer_t>       TSamplerBin2;
typedef GenericSampler<TreeReader_t, BoostSerializer<MyDigi> > TSamplerBoost2;
typedef GenericSampler<TreeReader_t, RootSerializer>           TSamplerTMessage2;
typedef GenericSampler<TreeReader_t, MyDigiProtoSerializer>    TSamplerProtoBuff2;


// define some helper functions
template<typename T, typename U>
using enable_if_base = typename std::enable_if<std::is_base_of<T,U>::value,int>::type;

struct SetSource
{
    SetSource() = default;
    // source policy "SimpleTreeReader" needs filename, treename and branchname
    template<typename TSampler, enable_if_base<TreeReader_t,TSampler> = 0>
    void Property(TSampler& sampler, FairMQProgOptions& config) 
    {
        std::string filename = config.GetValue<std::string>("input.file.name");
        std::string treename = config.GetValue<std::string>("input.file.tree");
        std::string branchname = config.GetValue<std::string>("input.file.branch");
        
        sampler.SetFileProperties(filename, treename, branchname);
    }
    // source policy "FairMQFileSource_t" needs filename, and branchname
    template<typename TSampler, enable_if_base<FairMQFileSource_t,TSampler> = 0>
    void Property(TSampler& sampler, FairMQProgOptions& config) 
    {
        std::string filename = config.GetValue<std::string>("input.file.name");
        std::string branchname = config.GetValue<std::string>("input.file.branch");
        sampler.SetFileProperties(filename, branchname);
    }
};


template<typename TSampler>
inline void runSampler(FairMQProgOptions& config)
{
    int eventRate = config.GetValue<int>("event-rate");
    TSampler sampler;
    /// configure sampler specific from parsed values
    sampler.SetProperty(TSampler::EventRate, eventRate);
    // call function member from sampler policy via a helper struct function defined above
    SetSource().Property(sampler,config);
    // simple state machine helper function
    runStateMachine(sampler, config);
}

int main(int argc, char** argv)
{
    try
    {
        FairMQProgOptions config;
        InitConfig(config, argc, argv);
        std::string format = config.GetValue<std::string>("data-format");
        std::string source = config.GetValue<std::string>("source-type");
        if(source == "FairMQFileSource")
        {
            if (format == "Bin") { runSampler<TSamplerBin>(config); }
                else if (format == "Boost") { runSampler<TSamplerBoost>(config); }
                else if (format == "Root") { runSampler<TSamplerTMessage>(config); }
                else if (format == "Proto") { runSampler<TSamplerProtoBuff>(config); }
                else
                {
                    LOG(ERROR) << "No valid data format provided. (--data-format binary|boost|tmessage). ";
                    return 1;
                }
        } 
        else 
            if(source == "SimpleTreeReader")
            {
                if (format == "Bin") { runSampler<TSamplerBin2>(config); }
                else if (format == "Boost") { runSampler<TSamplerBoost2>(config); }
                else if (format == "Root") { runSampler<TSamplerTMessage2>(config); }
                else if (format == "Proto") { runSampler<TSamplerProtoBuff2>(config); }
                else
                {
                    LOG(ERROR) << "No valid data format provided. (--data-format binary|boost|tmessage). ";
                    return 1;
                }
            }
            else
            {
                LOG(ERROR) << "No valid source provided. (--source-type FairMQFileSource|SimpleTreeReader). ";
            }
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }
    return 0;
}

