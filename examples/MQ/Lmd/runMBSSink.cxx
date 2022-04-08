/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "BaseMQFileSink.h"
#include "FairMBSRawItem.h"   // data type for the OutputPolicy
#include "FairRunFairMQDevice.h"
#include "IOPolicy.h"             // fair::mq::policy::
#include "RootOutFileManager.h"   // OutputPolicy
#include "RootSerializer.h"       // RootSerializer

#include <TClonesArray.h>   // data type for the InputPolicy

// InputPolicy - initialize input and deserialize message into it
using RootDefaultInputPolicy =
    fair::mq::policy::InputPolicy<RootSerializer,                         // deserializer from msg to input
                                  TClonesArray,                           // input data type
                                  fair::mq::policy::PointerType,          // input pointer type (automatically selected)
                                  fair::mq::policy::OpNewCreator,         // input allocation
                                  fair::mq::policy::NullptrInitializer,   // input initialization
                                  fair::mq::policy::RawPtrDeleter>;       // input deleter

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("output-file-name",   bpo::value<std::string>(),                                  "Path to the input file")
        ("output-file-tree",   bpo::value<std::string>()->default_value("mbstree"),        "Name of the output tree")
        ("output-file-branch", bpo::value<std::string>()->default_value("FairMBSRawItem"), "Name of the output Branch")
        ("hit-classname",      bpo::value<std::string>()->default_value("FairMBSRawItem"), "Hit class name for initializing TClonesArray")
        ("output-file-option", bpo::value<std::string>()->default_value("RECREATE"),       "Root file option : UPDATE, RECREATE etc.")
        ("use-clones-array",   bpo::value<bool>()->default_value(true),                    "Use TClonesArray")
        ("flow-mode",          bpo::value<bool>()->default_value(true),                    "Flow mode")
        ("in-chan-name",       bpo::value<std::string>()->default_value("data"),           "input channel name");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    using Sink = BaseMQFileSink<RootDefaultInputPolicy, RootOutFileManager<FairMBSRawItem>>;
    auto sink = std::make_unique<Sink>();

    // call function member from deserialization policy
    sink->InitInputData(config.GetValue<std::string>("hit-classname").c_str());

    return sink;
}
