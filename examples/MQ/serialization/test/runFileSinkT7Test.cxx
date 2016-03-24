
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
#include "MyHit.h"



template<typename FileSinkType>
class GenSinkTest : public FileSinkType
{
    using FileSinkType::CheckCurrentState;
    using FileSinkType::RUNNING;
    using FileSinkType::fTransportFactory;
    
    using FileSinkType::deserialization_type::DeserializeMsg;
    using FileSinkType::sink_type::AddToFile;
    
public:
    using FileSinkType::fChannels;
    GenSinkTest() : FileSinkType() {}
    virtual ~GenSinkTest(){}
    virtual void Run()
    {
        int receivedMsg = 0;
        const FairMQChannel& inputChannel = fChannels.at("data-in").at(0);
        while (CheckCurrentState(RUNNING))
        {
            std::unique_ptr<FairMQMessage> msg(fTransportFactory->CreateMessage());
            if (inputChannel.Receive(msg) > 0)
            {
                AddToFile(DeserializeMsg(msg.get()));
                receivedMsg++;
            }
            if(receivedMsg==100)
                break;
        }
        LOG(INFO) << "Received " << receivedMsg << " messages!";
    }
};



typedef GenericFileSink<MyHitDeserializer_t, RootOutFileManager<MyHit>>                      TSinkBin;
typedef GenericFileSink<BoostDeSerializer<MyHit,TClonesArray*>, RootOutFileManager<MyHit>>   TSinkBoost;
typedef GenericFileSink<RootDeSerializer, RootOutFileManager<MyHit>>                         TSinkRoot;

typedef GenSinkTest<TSinkBin>     TSinkBinTest;
typedef GenSinkTest<TSinkBoost>   TSinkBoostTest;
typedef GenSinkTest<TSinkRoot>    TSinkRootTest;

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
    runNonInteractiveStateMachine(sink, config);
}

template<>
inline void runSink<TSinkBoostTest>(FairMQProgOptions& config)
{
    std::string filename = config.GetValue<std::string>("output.file.name");
    std::string treename = config.GetValue<std::string>("output.file.tree");
    std::string branchname = config.GetValue<std::string>("output.file.branch");
    std::string fileoption = config.GetValue<std::string>("output.file.option");
    std::string hitname = config.GetValue<std::string>("hit-classname");

    TSinkBoostTest sink;
    // call function member from storage policy
    sink.SetFileProperties(filename, treename, branchname, hitname, fileoption, true);
    // call function member from deserialization policy (required for "container = new TClonesArrays(...)" )
    sink.InitInputContainer(hitname.c_str());
    runNonInteractiveStateMachine(sink, config);
}


int main(int argc, char** argv)
{
    try
    {
        FairMQProgOptions config;
        InitConfig(config, argc, argv);

        std::string format = config.GetValue<std::string>("data-format");

        if (format == "Bin") { runSink<TSinkBinTest>(config); }
            else if (format == "Boost") { runSink<TSinkBoostTest>(config); }
            else if (format == "Root") { runSink<TSinkRootTest>(config); }
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
