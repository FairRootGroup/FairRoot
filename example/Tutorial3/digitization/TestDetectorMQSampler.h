/**
 * TestDetectorMQSampler.h
 *
 *  @since 2012-04-22
 *  @authors A. Rybalchenko
 */

#ifndef TESTDETECTORMQSAMPLER_H_
#define TESTDETECTORMQSAMPLER_H_

#include "FairMQSampler.h"

#include "TestDetectorPayload.h"

class TestDetectorMQSampler: public FairMQSampler
{
  public:
    TestDetectorMQSampler();
    virtual ~TestDetectorMQSampler();
    virtual void Init();

    //ClassDef(TestDetectorMQSampler,1);
};

#endif /* TESTDETECTORMQSAMPLER_H_ */
