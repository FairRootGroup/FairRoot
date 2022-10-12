/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExParamsClient.h
 *
 * @since 2015-10-26
 * @author A. Rybalchenko
 */

#ifndef FAIRMQEXPARAMSCLIENT_H
#define FAIRMQEXPARAMSCLIENT_H

#include "FairMQ.h"   // for fair::mq::Device

#include <cstdint>   // uint64_t
#include <string>

class FairMQExParamsClient : public fair::mq::Device
{
  public:
    FairMQExParamsClient();
    ~FairMQExParamsClient() override;

  protected:
    bool ConditionalRun() override;
    void InitTask() override;

  private:
    int fRunId;
    std::string fParameterName;
    uint64_t fMaxIterations;
    uint64_t fNumIterations;
};

#endif /* FAIRMQEXPARAMSCLIENT_H */
