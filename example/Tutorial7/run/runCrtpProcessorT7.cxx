
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "GenericProcessor.h"
#include "BoostSerializer.h"
#include "RootSerializer.h"

/// FairRoot - Tutorial7 
#include "tuto7ProcessorFunctions.h"
#include "MyDigiSerializerCrtp.h"
#include "MyHitSerializerCrtp.h"
#include "DigiToHitTaskCrtp.h"
#include "MyDigi.h"
#include "MyHit.h"

// ////////////////////////////////////////////////////////////////////////

typedef GenericProcessor<MyDigiDeserializerCrtp_t,MyHitSerializerCrtp_t,DigiToHitTaskCrtp>      TProcessorBin;
typedef GenericProcessor<   
                            BoostDeSerializer<MyDigi,TClonesArray*>,
                            BoostSerializer<MyHit>,
                            DigiToHitTaskCrtp
                        >                                                                       TProcessorBoost;
typedef GenericProcessor<RootDeSerializer,RootSerializer,DigiToHitTaskCrtp>                     TProcessorRoot;

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