/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runTestDetectorSamplerBin.cxx
 *
 * @since 2013-04-29
 * @author A. Rybalchenko, N. Winckler
 */

#include <iostream>

#include "boost/program_options.hpp"

#include "FairMQLogger.h"
#include "FairMQParser.h"
#include "FairMQProgOptions.h"

#include "FairMQSampler.h"
#include "FairTestDetectorDigiLoader.h"

using namespace std;
using namespace boost::program_options;

using TSamplerBin         = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorPayload::Digi>>;
using TSamplerBoostBin    = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, boost::archive::binary_oarchive>>;
using TSamplerBoostText   = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, boost::archive::text_oarchive>>;
#ifdef PROTOBUF
using TSamplerProtobuf    = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorProto::DigiPayload>>;
#endif
using TSamplerTMessage    = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TMessage>>;
#ifdef FLATBUFFERS
using TSamplerFlatBuffers = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorFlat::DigiPayload>>;
#endif
#ifdef MSGPACK
using TSamplerMsgPack     = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, MsgPack>>;
#endif

template<typename T>
void runSampler(FairMQProgOptions& config)
{
    T sampler;
    sampler.CatchSignals();

    sampler.SetConfig(config);

    sampler.SetProperty(T::InputFile, config.GetValue<string>("input-file"));
    sampler.SetProperty(T::ParFile, config.GetValue<string>("parameter-file"));
    sampler.SetProperty(T::Branch, config.GetValue<string>("branch"));
    sampler.SetProperty(T::EventRate, config.GetValue<int>("event-rate"));
    sampler.SetProperty(T::ChainInput, config.GetValue<int>("chain-input"));

    sampler.ChangeState("INIT_DEVICE");
    sampler.WaitForEndOfState("INIT_DEVICE");

    sampler.ChangeState("INIT_TASK");
    sampler.WaitForEndOfState("INIT_TASK");

    sampler.ChangeState("RUN");
    sampler.InteractiveStateLoop();
}

int main(int argc, char** argv)
{
    try
    {
        string dataFormat;
        string inputFile;
        string parameterFile;
        string branch;
        int eventRate;
        int chainInput;

        options_description samplerOptions("Sampler options");
        samplerOptions.add_options()
            ("data-format", value<string>(&dataFormat)->default_value("binary"), "Data format (binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage)")
            ("input-file", value<string>(&inputFile)->required(), "Path to the input file")
            ("parameter-file", value<string>(&parameterFile)->required(), "path to the parameter file")
            ("branch", value<string>(&branch)->default_value("FairTestDetectorDigi"), "Name of the Branch")
            ("event-rate", value<int>(&eventRate)->default_value(0), "Event rate limit in maximum number of events per second")
            ("chain-input", value<int>(&chainInput)->default_value(0), "Chain input file more than once (default)");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(samplerOptions);
        config.ParseAll(argc, argv);

        if (dataFormat == "binary") { runSampler<TSamplerBin>(config); }
        else if (dataFormat == "boost") { runSampler<TSamplerBoostBin>(config); }
        else if (dataFormat == "boost-text") { runSampler<TSamplerBoostText>(config); }
#ifdef FLATBUFFERS
        else if (dataFormat == "flatbuffers") { runSampler<TSamplerFlatBuffers>(config); }
#endif
#ifdef MSGPACK
        else if (dataFormat == "msgpack") { runSampler<TSamplerMsgPack>(config); }
#endif
#ifdef PROTOBUF
        else if (dataFormat == "protobuf") { runSampler<TSamplerProtobuf>(config); }
#endif
        else if (dataFormat == "tmessage") { runSampler<TSamplerTMessage>(config); }
        else
        {
            LOG(ERROR) << "No valid data format provided. (--data-format binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage). ";
            return 1;
        }
    }
    catch (exception& e)
    {
        LOG(ERROR) << "Unhandled Exception reached the top of main: "
                   << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
