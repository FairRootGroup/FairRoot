/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* 
 * File:   runFileSinkBin.cxx
 * Author: winckler
 *
 * Created on November 12, 2014, 6:39 PM
 */

// FairRoot - FairMQ
#include "GenericFileSink.h"
#include "runSimpleMQStateMachine.h"
 
// FairRoot - base/MQ
#include "RootOutFileManager.h"
#include "BoostSerializer.h"
#include "RootSerializer.h"

// FairRoot - Tutorial7
#include "InitFileSinkConfig.h"
#include "MyHitSerializer.h"

// FairRoot - Tutorial3
#include "FairTestDetectorHit.h"

// Bin, Boost, Root suffixes = deserialization format
// In this example all Sinks store the data into Root file using the policy RootOutFileManager<FairTestDetectorHit>
typedef GenericFileSink<Tuto3HitDeserializer_t, RootOutFileManager<FairTestDetectorHit>>                   TSinkBin;
typedef GenericFileSink<BoostDeSerializer<FairTestDetectorHit,TClonesArray*>, 
                                                                RootOutFileManager<FairTestDetectorHit>>   TSinkBoost;
typedef GenericFileSink<RootDeSerializer, RootOutFileManager<FairTestDetectorHit>>                         TSinkRoot;



template<typename TSink>
inline void runSink(FairMQProgOptions& config)
{
    std::string filename = config.GetValue<std::string>("output.file.name");
    std::string treename = config.GetValue<std::string>("output.file.tree");
    std::string branchname = config.GetValue<std::string>("output.file.branch");
    std::string fileoption = config.GetValue<std::string>("output.file.option");
    std::string hitname = config.GetValue<std::string>("hit-classname");

    TSink sink;
    // call function member from storage policy
    sink.SetFileProperties(filename, treename, branchname, hitname, fileoption, true);
    // call function member from deserialization policy
    sink.InitInputContainer(hitname);
    runStateMachine(sink, config);
}

template<>
inline void runSink<TSinkBoost>(FairMQProgOptions& config)
{
    std::string filename = config.GetValue<std::string>("output.file.name");
    std::string treename = config.GetValue<std::string>("output.file.tree");
    std::string branchname = config.GetValue<std::string>("output.file.branch");
    std::string fileoption = config.GetValue<std::string>("output.file.option");
    std::string hitname = config.GetValue<std::string>("hit-classname");

    TSinkBoost sink;
    // call function member from storage policy
    sink.SetFileProperties(filename, treename, branchname, hitname, fileoption, true);
    // call function member from deserialization policy (required for "container = new TClonesArrays(...)" )
    sink.InitInputContainer(hitname.c_str());
    runStateMachine(sink, config);
}


int main(int argc, char** argv)
{
    try
    {
        FairMQProgOptions config;
        InitConfig(config, argc, argv);

        std::string format = config.GetValue<std::string>("data-format");

        if (format == "Bin") { runSink<TSinkBin>(config); }
            else if (format == "Boost") { runSink<TSinkBoost>(config); }
            else if (format == "Root") { runSink<TSinkRoot>(config); }
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
