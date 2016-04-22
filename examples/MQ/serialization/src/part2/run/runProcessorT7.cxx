
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "runSimpleMQStateMachine.h"
#include "InitProcessorConfig.h"

#include "MyDigi.h"
#include "MyHit.h"

// template processor device
#include "GenericProcessor.h"
// task policy
#include "MyDigiToHitTask.h"
// input/output policy definition
#include "PolicyDefinition.h"

// define root policies
namespace mq = fairroot::examples::processor_policy;

typedef GenericProcessor< mq::root::u_ptr::input,   mq::root::u_ptr::output,   MyDigiToHitTask > TProcessorRoot_uptr;
typedef GenericProcessor< mq::root::r_ptr::input,   mq::root::r_ptr::output,   MyDigiToHitTask > TProcessorRoot;
typedef GenericProcessor< mq::boost::r_ptr::input,  mq::boost::r_ptr::output,  MyDigiToHitTask > TProcessorBoost;
typedef GenericProcessor< mq::binary::r_ptr::input, mq::binary::r_ptr::output, MyDigiToHitTask > TProcessorBin;
typedef GenericProcessor< mq::proto::r_ptr::input,  mq::proto::r_ptr::output,  MyDigiToHitTask > TProcessorProto;

template<typename TProcessor>
inline void runProcessor(FairMQProgOptions& config)
{
    std::string diginame=config.GetValue<std::string>("digi-classname");
    std::string hitname=config.GetValue<std::string>("hit-classname");

    TProcessor processor;
    processor.InitInputData(diginame.c_str());
    processor.InitOutputData(hitname.c_str());
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
                LOG(ERROR) << "No valid data format provided. (--data-format binary|boost|root|proto). ";
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
