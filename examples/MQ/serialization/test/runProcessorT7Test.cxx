
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
#include "MyDigi.h"
#include "MyHit.h"

// ////////////////////////////////////////////////////////////////////////

template<typename ProcessorType>
class GenProcessorTest : public ProcessorType
{
    using ProcessorType::fTransportFactory;
    using ProcessorType::CheckCurrentState;
    using ProcessorType::RUNNING;
    
    using ProcessorType::deserialization_type::DeserializeMsg;
    using ProcessorType::serialization_type::SerializeMsg;
    using ProcessorType::serialization_type::SetMessage;
    using ProcessorType::proc_task_type::GetOutputData;
    using ProcessorType::proc_task_type::ExecuteTask;
    
public:
    using ProcessorType::fChannels;
    GenProcessorTest() : ProcessorType() {}
    virtual ~GenProcessorTest(){}
    virtual void Run()
    {
        int receivedMsgs = 0;
        int sentMsgs = 0;
        const FairMQChannel& inputChannel = fChannels["data-in"].at(0);
        const FairMQChannel& outputChannel = fChannels["data-out"].at(0);
        while (CheckCurrentState(RUNNING))
        {
            std::unique_ptr<FairMQMessage> msg(fTransportFactory->CreateMessage());
            ++receivedMsgs;
            if (inputChannel.Receive(msg) > 0)
            {
                ExecuteTask(DeserializeMsg(msg.get()));
                SetMessage(msg.get());
                outputChannel.Send(SerializeMsg(GetOutputData()));
                sentMsgs++;
            }
            if(receivedMsgs==100 && sentMsgs==100)
                break;
        }
        LOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
    }
};

typedef GenericProcessor<MyDigiDeserializer_t,MyHitSerializer_t,DigiToHitTask>              TProcessorBin;
typedef GenericProcessor<   
                            BoostDeSerializer<MyDigi,TClonesArray*>,
                            BoostSerializer<MyHit>,
                            DigiToHitTask
                        >                                                                   TProcessorBoost;
typedef GenericProcessor<RootDeSerializer,RootSerializer,DigiToHitTask>                     TProcessorRoot;

typedef GenProcessorTest<TProcessorBin>     TProcessorBinTest;
typedef GenProcessorTest<TProcessorBoost>   TProcessorBoostTest;
typedef GenProcessorTest<TProcessorRoot>    TProcessorRootTest;

template<typename TProcessor>
inline void runProcessor(FairMQProgOptions& config)
{
    std::string diginame=config.GetValue<std::string>("digi-classname");
    std::string hitname=config.GetValue<std::string>("hit-classname");

    TProcessor processor;
    processor.InitInputContainer(diginame);
    processor.InitTask(hitname);
    runNonInteractiveStateMachine(processor, config);
}

template<>
inline void runProcessor<TProcessorBoostTest>(FairMQProgOptions& config)
{
    std::string diginame=config.GetValue<std::string>("digi-classname");
    std::string hitname=config.GetValue<std::string>("hit-classname");

    TProcessorBoostTest processor;
    processor.InitInputContainer(diginame.c_str());
    processor.InitTask(hitname);
    runNonInteractiveStateMachine(processor, config);
}

int main(int argc, char** argv)
{
    try
    {
        FairMQProgOptions config;
        InitConfig(config, argc, argv);

        std::string format = config.GetValue<std::string>("data-format");

        if (format == "Bin") { runProcessor<TProcessorBinTest>(config); }
            else if (format == "Boost") { runProcessor<TProcessorBoostTest>(config); }
            else if (format == "Root") { runProcessor<TProcessorRootTest>(config); }
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
