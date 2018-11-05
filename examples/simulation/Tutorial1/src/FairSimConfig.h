/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRSIMCONFIG
#define FAIRSIMCONFIG

#include "boost/program_options.hpp"
#include <string>

#include "Rtypes.h"
#include "TString.h"

namespace po = boost::program_options;

class FairSimConfig
{
  public:
    FairSimConfig();
    virtual ~FairSimConfig();

    int ParseCommandLine(int argc, char* argv[]);

    void PrintHelpMessage();

    bool IsHelp() const { return fHelp; }
    int GetNEvents() const { return fnEvents; }
    TString GetEngine() const { return TString(fEngine); }
    bool IsMultiThreaded() const { return fMultiThreaded; }
    TString GetOutputFile() const { return TString(fOutputFile); }
    TString GetParameterFile() const { return TString(fParameterFile); }
    int GetRandomSeed() const { return fRandomSeed; }

  private:
    po::options_description fDescription; //!
    po::variables_map fMap;               //!

    bool fHelp;
    int fnEvents;
    std::string fEngine;
    bool fMultiThreaded;
    std::string fOutputFile;
    std::string fParameterFile;
    int fRandomSeed;

    ClassDef(FairSimConfig, 1)
};

#endif
