/* 
 * File:   processorFunctions.h
 * Author: winckler
 *
 * Created on July 11, 2015, 3:06 PM
 */

#ifndef PROCESSORFUNCTIONS_H
#define PROCESSORFUNCTIONS_H

#include "FairMQProgOptions.h"

inline int InitConfig(FairMQProgOptions& config, int argc, char** argv)
{
    namespace po = boost::program_options;
    po::options_description processor_options("Processor options");
    processor_options.add_options()
        ("digi-classname", po::value<std::string>()->default_value("MyDigi"), "Digi class name for initializing TClonesArray")
        ("hit-classname",  po::value<std::string>()->default_value("MyHit"),  "Hit class name for initializing TClonesArray")
        ("data-format",    po::value<std::string>()->default_value("Binary"), "Data format (binary/boost/protobuf/tmessage)")
    ;

    config.AddToCmdLineOptions(processor_options);
    config.AddToCfgFileOptions(processor_options,false);

    if (config.ParseAll(argc, argv, true))
    {
        return 1;
    }

    return 0;
}

#endif /* PROCESSORFUNCTIONS_H */
