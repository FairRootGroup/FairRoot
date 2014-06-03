/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQProcessorTask.h
 *
 * @since Dec 6, 2012-12-06
 * @author: D. Klein, A. Rybalchenko
 */

#ifndef FAIRMQPROCESSORTASK_H_
#define FAIRMQPROCESSORTASK_H_

#include <vector>

#include "FairMQMessage.h"
#include "FairTask.h"


class FairMQProcessorTask : public FairTask
{
  public:
    FairMQProcessorTask();
    virtual ~FairMQProcessorTask();
    virtual void Exec(FairMQMessage* msg, Option_t* opt) = 0;
};

#endif /* FAIRMQPROCESSORTASK_H_ */
