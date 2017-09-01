/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "runFairMQDevice.h"
#include "BaseMQFileSink.h"

#include "MQPolicyDef.h" // fair::mq::policy::
#include "RootSerializer.h" // RootDeserializer
#include "TClonesArray.h" // data type for the InputPolicy

#include "RootOutFileManager.h" // OutputPolicy
#include "FairMBSRawItem.h" // data type for the OutputPolicy

// InputPolicy - initialize input and deserialize message into it
using RootDefaultInputPolicy = fair::mq::policy::InputPolicy<RootDeserializer, // deserializer from msg to input
                                                             TClonesArray, // input data type
                                                             fair::mq::policy::PointerType, // input pointer type (automatically selected)
                                                             fair::mq::policy::OpNewCreator, // input allocation
                                                             fair::mq::policy::NullptrInitializer, // input initialization
                                                             fair::mq::policy::RawPtrDeleter>; // input deleter

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("output-file-name",   po::value<std::string>(),                                  "Path to the input file")
        ("output-file-tree",   po::value<std::string>()->default_value("mbstree"),        "Name of the output tree")
        ("output-file-branch", po::value<std::string>()->default_value("FairMBSRawItem"), "Name of the output Branch")
        ("hit-classname",      po::value<std::string>()->default_value("FairMBSRawItem"), "Hit class name for initializing TClonesArray")
        ("output-file-option", po::value<std::string>()->default_value("RECREATE"),       "Root file option : UPDATE, RECREATE etc.")
        ("use-clones-array",   po::value<bool>()->default_value(true),                    "Use TClonesArray")
        ("flow-mode",          po::value<bool>()->default_value(true),                    "Flow mode");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
    BaseMQFileSink<RootDefaultInputPolicy, RootOutFileManager<FairMBSRawItem>>* sink = new BaseMQFileSink<RootDefaultInputPolicy, RootOutFileManager<FairMBSRawItem>>();

    // call function member from deserialization policy
    sink->InitInputData(config.GetValue<std::string>("hit-classname").c_str());

    return sink;
}
