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

// FairRoot - Base/MQ
// sampler policies

#include "FairFileSource.h"
 #include "FairSourceMQInterface.h"

// FairRoot - Tutorial 7
#include "tuto7SamplerFunctions.h"
#include "MyDigi.h"


// FairRoot - Base/MQ
// sampler & serialization policies
#include "BoostSerializer.h"
#include "RootSerializer.h"
#include "MyDigiSerializerCrtp.h"
// FairRoot - Tutorial 7
#include "tuto7SamplerFunctions.h"
#include "MyDigi.h"

#include "FairRunAna.h"
#include "TClonesArray.h"

// ////////////////////////////////////////////////////////////////////////


typedef FairSourceMQInterface<FairFileSource,TClonesArray>  TSourcePolicy;

// build sampler type
typedef GenericSampler<TSourcePolicy, MyDigiSerializerCrtp_t>   TSamplerBin;
typedef GenericSampler<TSourcePolicy, BoostSerializer<MyDigi> > TSamplerBoost;
typedef GenericSampler<TSourcePolicy, RootSerializer>           TSamplerTMessage;



template<typename TSampler>
inline void runSampler(FairMQProgOptions& config)
{
    int eventRate = config.GetValue<int>("event-rate");
    std::string filename = config.GetValue<std::string>("input.file.name");
    std::string branchname = config.GetValue<std::string>("input.file.branch");
    

    TSampler sampler;
    /// configure sampler specific from parsed values
    sampler.SetProperty(TSampler::EventRate, eventRate);
    // call function member from sampler policy
    sampler.SetFileProperties(filename, branchname);
//*
    sampler.CustomInitSourceRunAna([=](FairFileSource** fSource, TClonesArray** fData, FairRunAna** fRunAna)
            {
                
            *fRunAna = new FairRunAna();
            *fSource = new FairFileSource(filename.c_str());
            (*fSource)->Init();
            (*fSource)->ActivateObject((TObject**)fData,branchname.c_str());
            }
        );

        // */

    runStateMachine(sampler, config);
}


int main(int argc, char** argv)
{
    try
    {
        
        FairMQProgOptions config;
        InitConfig(config, argc, argv);

        std::string format = config.GetValue<std::string>("data-format");

        if (format == "Bin") { runSampler<TSamplerBin>(config); }
            else if (format == "Boost") { runSampler<TSamplerBoost>(config); }
            else if (format == "Root") { runSampler<TSamplerTMessage>(config); }
            else
            {
                LOG(ERROR) << "No valid data format provided. (--data-format binary|boost|tmessage). ";
                return 1;
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
