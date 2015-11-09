/* 
 * File:   SamplerFunctions.h
 * Author: winckler
 *
 * Created on July 11, 2015, 3:05 PM
 */

#ifndef SAMPLERFUNCTIONS_H
#define SAMPLERFUNCTIONS_H

#include "FairMQProgOptions.h"

inline int InitConfig(FairMQProgOptions& config, int argc, char** argv)
{
    namespace po = boost::program_options;

    po::options_description sampler_options("Sampler options");
    sampler_options.add_options()
        ("event-rate",              po::value<int>()->default_value(0),                   "Event rate limit in maximum number of events per second")
        // TODO : make the semantic required for at least one source (and not both cfg & cmd)
        // ("input.file.name",         value<std::string>(&filename)->required(),                       "Path to the input file")
        ("input.file.name",         po::value<std::string>(),                                             "Path to the input file")
        ("input.file.tree",         po::value<std::string>()->default_value("cbmsim"),                    "Name of the tree")
        ("input.file.branch",       po::value<std::string>()->default_value("digidata"),                  "Name of the Branch")
        ("data-format",             po::value<std::string>()->default_value("Binary"),                    "Data format (binary/boost/protobuf/tmessage)")
        ("source-type",             po::value<std::string>()->default_value("FairMQFileSource"),          "Source implementation type : FairFileSource or SimpleTreeReader")
    ;

    config.AddToCmdLineOptions(sampler_options);
    config.AddToCfgFileOptions(sampler_options, false);

    if (config.ParseAll(argc, argv, true))
    {
        return 1;
    }

    return 0;
}

#endif /* SAMPLERFUNCTIONS_H */

