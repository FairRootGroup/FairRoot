/**
 * File:   TestDetectorDigiLoader.h
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 */

#ifndef TESTDETECTORDIGILOADER_H
#define	TESTDETECTORDIGILOADER_H

#include <iostream>

#include "FairMQSamplerTask.h"

template <typename T1, typename T2>
class TestDetectorDigiLoader : public FairMQSamplerTask
{
public:
    TestDetectorDigiLoader();
    virtual ~TestDetectorDigiLoader();
    virtual void Exec(Option_t* opt);
};


#include "TestDetectorDigiLoader.tpl"

#endif /* TESTDETECTORDIGILOADER_H */

