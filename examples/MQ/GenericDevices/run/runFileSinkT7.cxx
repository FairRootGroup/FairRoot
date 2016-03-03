
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
#include "MyHitSerializer_protobuff.h"
#include "MyHit.h"

// Bin, Boost, Root suffixes = deserialization format
// In this example all Sinks store the data into Root file using the policy RootOutFileManager<MyHit>
typedef GenericFileSink<MyHitDeserializer_t, RootOutFileManager<MyHit>>                      TSinkBin;
typedef GenericFileSink<BoostDeSerializer<MyHit,TClonesArray*>, RootOutFileManager<MyHit>>   TSinkBoost;
typedef GenericFileSink<RootDeSerializer, RootOutFileManager<MyHit>>                         TSinkRoot;
typedef GenericFileSink<MyHitProtoDeserializer, RootOutFileManager<MyHit>>                   TSinkProto;



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
            else if (format == "Proto") { runSink<TSinkProto>(config); }
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
