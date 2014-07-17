/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQMerger.h
 *
 * @since 2012-12-06
 * @author D. Klein, A. Rybalchenko
 */

#ifndef FAIRMQMERGER_H_
#define FAIRMQMERGER_H_

#include "FairMQDevice.h"

class FairMQMerger : public FairMQDevice
{
  public:
    FairMQMerger();
    virtual ~FairMQMerger();

  protected:
    virtual void Run();
};

#endif /* FAIRMQMERGER_H_ */
