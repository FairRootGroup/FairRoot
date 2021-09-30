/********************************************************************************
 *    Copyright (C) 2021 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_CONFIG_H
#define FAIR_CONFIG_H

#include <string>

/// Global config
struct FairConfig
{
    /// @return VMC work directory
    /// An absolute unix filesystem path (starting with `/`)
    /// TODO Further define VMC work directory
    const std::string& GetVMCWorkDir() const;

    /// @return singleton instance
    static FairConfig& Instance();

  private:
    FairConfig();
    FairConfig(const FairConfig&) = delete;
    FairConfig& operator=(const FairConfig&) = delete;
    FairConfig(FairConfig&&) = delete;
    FairConfig& operator=(FairConfig&&) = delete;
    ~FairConfig() = default;

    std::string fVMCWorkDir;

    static std::string LoadVMCWorkDir();
};

#endif /* FAIR_CONFIG_H */
