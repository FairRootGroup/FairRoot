/* 
 * File:   fileSinkFunctions.h
 * Author: winckler
 *
 * Created on July 11, 2015, 3:07 PM
 */

#ifndef FILESINKFUNCTIONS_H
#define FILESINKFUNCTIONS_H

#include "FairMQProgOptions.h"
 
inline int InitConfig(FairMQProgOptions& config,int argc, char** argv)
{
    namespace po = boost::program_options;

    po::options_description sink_options("File Sink options");
    sink_options.add_options()
        // TODO : make the semantic required for at least one source (and not both cfg & cmd)
        //("input.file.name",         value<std::string>(&filename)->required(),                       "Path to the input file")
        ("output.file.name",         po::value<std::string>(),                              "Path to the input file")
        ("output.file.tree",         po::value<std::string>()->default_value("T7SinkTree"), "Name of the output tree")
        ("output.file.branch",       po::value<std::string>()->default_value("MyHit"),      "Name of the output Branch")
        ("output.file.option",       po::value<std::string>()->default_value("RECREATE"),   "Root file option : UPDATE, RECREATE etc.")
        ("hit-classname",            po::value<std::string>()->default_value("MyHit"),      "Hit class name for initializing TClonesArray")
        ("data-format",              po::value<std::string>()->default_value("Binary"),     "Data format (binary/boost/protobuf/tmessage)")
    ;

    config.AddToCmdLineOptions(sink_options);
    config.AddToCfgFileOptions(sink_options, false);

    if (config.ParseAll(argc, argv, true))
    {
        return 1;
    }

    return 0;
}










#endif	/* FILESINKFUNCTIONS_H */

