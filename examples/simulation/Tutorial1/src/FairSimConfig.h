/*********************************************************************************
 *  Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                               *
 *              This software is distributed under the terms of the              *
 *              GNU Lesser General Public Licence (LGPL) version 3,              *
 *                  copied verbatim in the file "LICENSE"                        *
 *********************************************************************************/
#ifndef FAIRSIMCONFIG
#define FAIRSIMCONFIG

#include <Rtypes.h>
#include <TString.h>
#include <string>

class FairSimConfig
{
  public:
    FairSimConfig() = default;
    virtual ~FairSimConfig() = default;

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
    bool fHelp{false};
    int fnEvents{1};
    std::string fEngine{"TGeant3"};
    bool fMultiThreaded{false};
    std::string fOutputFile{"sim.root"};
    std::string fParameterFile{"par.root"};
    int fRandomSeed{0};

    ClassDef(FairSimConfig, 0);
};

#endif
