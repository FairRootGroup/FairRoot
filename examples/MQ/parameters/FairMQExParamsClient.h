/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
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

#include <string>

#include "FairMQDevice.h"

class FairMQExParamsClient : public FairMQDevice
{
  public:
    FairMQExParamsClient();
    virtual ~FairMQExParamsClient();

  protected:
    virtual bool ConditionalRun();
    virtual void InitTask();

  private:
    int fRunId;
    std::string fParameterName;
    uint64_t fMaxIterations;
    uint64_t fNumIterations;
};

#endif /* FAIRMQEXPARAMSCLIENT_H */
