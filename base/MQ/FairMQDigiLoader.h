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
#include <iostream> 
 /// Template header
template <typename T1, typename T2> class FairMQDigiLoader : public FairMQSamplerTask
{ 
public : 
 
    FairMQDigiLoader();
    virtual ~FairMQDigiLoader();
    virtual void Exec(Option_t* opt);
}; 

/// Template implementation is in FairMQDigiLoader.tpl :
#include "FairMQDigiLoader.tpl"

#endif	/* FAIRMQDIGILOADER_H */

