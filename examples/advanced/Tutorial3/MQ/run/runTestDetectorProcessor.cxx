/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runTestDetectorProcessor.cxx
 *
 * @since 2012-10-26
 * @author A. Rybalchenko, N. Winckler
 */

#include <iostream>

#include "boost/program_options.hpp"

#include "FairMQLogger.h"
#include "FairMQParser.h"
#include "FairMQProgOptions.h"

#include "FairMQProcessor.h"
#include "FairTestDetectorMQRecoTask.h"

using namespace std;
using namespace boost::program_options;

using TProcessorTaskBin         = FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorPayload::Digi,       TestDetectorPayload::Hit>;
using TProcessorTaskBoostBin    = FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, boost::archive::binary_iarchive, boost::archive::binary_oarchive>;
using TProcessorTaskBoostText   = FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, boost::archive::text_iarchive,   boost::archive::text_oarchive>;
using TProcessorTaskProtobuf    = FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorProto::DigiPayload,  TestDetectorProto::HitPayload>;
using TProcessorTaskTMessage    = FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TMessage,                        TMessage>;
#ifdef FLATBUFFERS
using TProcessorTaskFlatBuffers = FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorFlat::DigiPayload,   TestDetectorFlat::HitPayload>;
#endif
#ifdef MSGPACK
using TProcessorTaskMsgPack     = FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, MsgPack,                         MsgPack>;
#endif

template<typename T>
void runProcessor(FairMQProgOptions& config)
{
    FairMQProcessor processor;
    processor.CatchSignals();

    processor.SetConfig(config);

    if (config.GetValue<string>("processor-task") == "FairTestDetectorMQRecoTask")
    {
        T* task = new T();
        processor.SetTask(task);
    }
    else
    {
        LOG(ERROR) << "task not supported.";
        exit(1);
    }

    processor.ChangeState("INIT_DEVICE");
    processor.WaitForEndOfState("INIT_DEVICE");

    processor.ChangeState("INIT_TASK");
    processor.WaitForEndOfState("INIT_TASK");

    processor.ChangeState("RUN");
    processor.InteractiveStateLoop();
}

int main(int argc, char** argv)
{
    try
    {
        string dataFormat;
        string processorTask;

        options_description processorOptions("Processor options");
        processorOptions.add_options()
            ("data-format", value<string>(&dataFormat)->default_value("binary"), "Data format (binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage)")
            ("processor-task", value<string>(&processorTask)->default_value("FairTestDetectorMQRecoTask"), "Name of the Processor Task");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(processorOptions);
        config.ParseAll(argc, argv);

        if (dataFormat == "binary") { runProcessor<TProcessorTaskBin>(config); }
        else if (dataFormat == "boost") { runProcessor<TProcessorTaskBoostBin>(config); }
        else if (dataFormat == "boost-text") { runProcessor<TProcessorTaskBoostText>(config); }
#ifdef FLATBUFFERS
        else if (dataFormat == "flatbuffers") { runProcessor<TProcessorTaskFlatBuffers>(config); }
#endif
#ifdef MSGPACK
        else if (dataFormat == "msgpack") { runProcessor<TProcessorTaskMsgPack>(config); }
#endif
        else if (dataFormat == "protobuf") { runProcessor<TProcessorTaskProtobuf>(config); }
        else if (dataFormat == "tmessage") { runProcessor<TProcessorTaskTMessage>(config); }
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
