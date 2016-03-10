
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

#include "MyDigiSerializer_protobuff.h"
#include "MyHitSerializer_protobuff.h"

#include "DigiToHitTask.h"
#include "MyDigi.h"
#include "MyHit.h"

// ////////////////////////////////////////////////////////////////////////

typedef GenericProcessor<MyDigiDeserializer_t,MyHitSerializer_t,DigiToHitTask>              TProcessorBin;
typedef GenericProcessor<   
                            BoostDeSerializer<MyDigi,TClonesArray*>,
                            BoostSerializer<MyHit>,
                            DigiToHitTask
                        >                                                                   TProcessorBoost;
typedef GenericProcessor<RootDeSerializer,RootSerializer,DigiToHitTask>                     TProcessorRoot;
typedef GenericProcessor<MyDigiProtoDeserializer,MyHitProtoSerializer,DigiToHitTask>          TProcessorProto;

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
            else if (format == "Proto") { runProcessor<TProcessorProto>(config); }
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