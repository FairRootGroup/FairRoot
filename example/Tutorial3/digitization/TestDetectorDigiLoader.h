/* 
 * File:   TestDetectorDigiLoader.h
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 * Created on February 8, 2014, 1:48 AM
 */

#ifndef TESTDETECTORDIGILOADER_H
#define	TESTDETECTORDIGILOADER_H

//#include "FairMQPayload.h"
//#include "FairTestDetectorPayload.h"
#include "FairMQSamplerTask.h"
#include "FairMQDigiLoader.h"
#include <iostream> 
 /// Template header
template <typename T1, typename T2> class TestDetectorDigiLoader : public FairMQDigiLoader<T1,T2>
//: public FairMQSamplerTask
{ 
public : 
 
    TestDetectorDigiLoader();
    virtual ~TestDetectorDigiLoader();
    virtual void Exec(Option_t* opt);
}; 

/// Template implementation is in TestDetectorDigiLoader.tpl :
#include "TestDetectorDigiLoader.tpl"

#endif	/* TESTDETECTORDIGILOADER_H */

