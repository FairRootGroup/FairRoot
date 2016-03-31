/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runFileSink.cxx
 *
 * @since 2013-01-21
 * @author A. Rybalchenko
 */

#include <iostream>

#include "boost/program_options.hpp"

#include "FairMQLogger.h"
#include "FairMQParser.h"
#include "FairMQProgOptions.h"

#include "FairTestDetectorFileSink.h"


using namespace std;
using namespace boost::program_options;

using TSinkBin                    = FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorPayload::Hit>;
using TSinkBoostBin               = FairTestDetectorFileSink<FairTestDetectorHit, boost::archive::binary_iarchive>;
using TSinkBoostText              = FairTestDetectorFileSink<FairTestDetectorHit, boost::archive::text_iarchive>;
using TSinkProtobuf               = FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorProto::HitPayload>;
using TSinkTMessage               = FairTestDetectorFileSink<FairTestDetectorHit, TMessage>;
#ifdef FLATBUFFERS
using TSinkFlatBuffers            = FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorFlat::HitPayload>;
#endif
#ifdef MSGPACK
using TSinkMsgPack                = FairTestDetectorFileSink<FairTestDetectorHit, MsgPack>;
#endif

template<typename T>
void runFileSink(FairMQProgOptions& config)
{
    T filesink;
    filesink.CatchSignals();

    filesink.SetConfig(config);

    filesink.ChangeState("INIT_DEVICE");
    filesink.WaitForEndOfState("INIT_DEVICE");

    filesink.ChangeState("INIT_TASK");
    filesink.WaitForEndOfState("INIT_TASK");

    filesink.InitOutputFile(config.GetValue<string>("id") + config.GetValue<string>("data-format"));

    filesink.ChangeState("RUN");
    filesink.InteractiveStateLoop();
}

int main(int argc, char** argv)
{
    FairMQProgOptions config;

    try
    {
        string dataFormat;

        options_description sinkOptions("Sink options");
        sinkOptions.add_options()
            ("data-format", value<string>(&dataFormat)->default_value("binary"), "Data format (binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage)");

        config.AddToCmdLineOptions(sinkOptions);

        if (config.ParseAll(argc, argv))
        {
            return 0;
        }

        if (dataFormat == "binary") { runFileSink<TSinkBin>(config); }
        else if (dataFormat == "boost") { runFileSink<TSinkBoostBin>(config); }
        else if (dataFormat == "boost-text") { runFileSink<TSinkBoostText>(config); }
#ifdef FLATBUFFERS
        else if (dataFormat == "flatbuffers") { runFileSink<TSinkFlatBuffers>(config); }
#endif
#ifdef MSGPACK
        else if (dataFormat == "msgpack") { runFileSink<TSinkMsgPack>(config); }
#endif
        else if (dataFormat == "protobuf") { runFileSink<TSinkProtobuf>(config); }
        else if (dataFormat == "tmessage") { runFileSink<TSinkTMessage>(config); }
        else
        {
            LOG(ERROR) << "No valid data format provided. (--data-format binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage). ";
            return 1;
        }
    }
    catch (exception& e)
    {
        LOG(ERROR) << e.what();
        LOG(INFO) << "Command line options are the following: ";
        config.PrintHelp();
        return 1;
    }

    return 0;
}
