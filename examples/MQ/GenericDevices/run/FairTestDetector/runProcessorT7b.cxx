/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runProcessorBin.cxx
 * Author: winckler
 *
 * Created on December 2, 2014, 11:14 PM
 */

/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "GenericProcessor.h"
#include "runSimpleMQStateMachine.h"
 
#include "BoostSerializer.h"
#include "RootSerializer.h"

/// FairRoot - Tutorial7 
#include "InitProcessorConfig.h"
#include "MyDigiSerializer.h"
#include "MyHitSerializer.h"
#include "DigiToHitTask.h"


// FairRoot - Tutorial3 
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorHit.h"

// ////////////////////////////////////////////////////////////////////////

typedef GenericProcessor<MyDigiDeserializer_t,MyHitSerializer_t,DigiToHitTaskTuto3_t>           TProcessorBin;
typedef GenericProcessor<   
                            BoostDeSerializer<FairTestDetectorDigi,TClonesArray*>,
                            BoostSerializer<FairTestDetectorHit>,
                            DigiToHitTaskTuto3_t
                        >                                                                       TProcessorBoost;
typedef GenericProcessor<RootDeSerializer,RootSerializer,DigiToHitTaskTuto3_t>                  TProcessorRoot;

template<typename TProcessor>
inline void runProcessor(FairMQProgOptions& config)
{
    std::string diginame=config.GetValue<std::string>("digi-classname");
    std::string hitname=config.GetValue<std::string>("hit-classname");

    TProcessor processor;
    processor.InitInputContainer(diginame);
    processor.InitTask(hitname);
    runStateMachine(processor, config);
}

template<>
inline void runProcessor<TProcessorBoost>(FairMQProgOptions& config)
{
    std::string diginame=config.GetValue<std::string>("digi-classname");
    std::string hitname=config.GetValue<std::string>("hit-classname");

    TProcessorBoost processor;
    processor.InitInputContainer(diginame.c_str());
    processor.InitTask(hitname);
    runStateMachine(processor, config);
}

int main(int argc, char** argv)
{
    try
    {
        FairMQProgOptions config;
        InitConfig(config, argc, argv);

        std::string format = config.GetValue<std::string>("data-format");

        if (format == "Bin") { runProcessor<TProcessorBin>(config); }
            else if (format == "Boost") { runProcessor<TProcessorBoost>(config); }
            else if (format == "Root") { runProcessor<TProcessorRoot>(config); }
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
