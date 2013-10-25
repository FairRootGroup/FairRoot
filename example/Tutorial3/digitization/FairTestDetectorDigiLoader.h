/**
 * TestDetectorDigiLoader.h
 *
 *  @since 2012-04-22
 *  @author A. Rybalchenko
 */

#ifndef TESTDETECTORDIGILOADER_H_
#define TESTDETECTORDIGILOADER_H_

#include "FairMQSamplerTask.h"
#include "FairTestDetectorPayload.h"


class TestDetectorDigiLoader: public FairMQSamplerTask
{
  public:
    TestDetectorDigiLoader();
    virtual ~TestDetectorDigiLoader();
    void Exec(Option_t* opt);
};

#endif /* TESTDETECTORDIGILOADER_H_ */
