/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExample7Client.h
 *
 * @since 2015-10-26
 * @author A. Rybalchenko
 */

#ifndef FAIRMQEXAMPLE7CLIENT_H_
#define FAIRMQEXAMPLE7CLIENT_H_

#include <string>

#include "FairMQDevice.h"

class FairMQExample7Client : public FairMQDevice
{
  public:
    FairMQExample7Client();
    virtual ~FairMQExample7Client();

  protected:
    virtual bool ConditionalRun();
    virtual void InitTask();

  private:
    int fRunId;
    std::string fParameterName;
    uint64_t fMaxIterations;
    uint64_t fNumIterations;
};

#endif /* FAIRMQEXAMPLE7CLIENT_H_ */
