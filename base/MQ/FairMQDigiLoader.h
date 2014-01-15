/* 
 * File:   FairMQDigiLoader.h
 * Author: winckler
 *
 * Created on January 17, 2014, 2:03 PM
 */

#ifndef FAIRMQDIGILOADER_H
#define	FAIRMQDIGILOADER_H


#include "FairMQSamplerTask.h"
#include "FairMQPayload.h"


class FairMQDigiLoader: public FairMQSamplerTask
{
  public:
    FairMQDigiLoader();
    virtual ~FairMQDigiLoader();
    virtual void Exec(Option_t* opt);
};

#endif	/* FAIRMQDIGILOADER_H */

