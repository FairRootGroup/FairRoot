/**
 * TestDetectorMQSampler.h
 *
 *  @since 2012-04-22
 *  @authors A. Rybalchenko
 */

#ifndef TESTDETECTORMQSAMPLER_H_
#define TESTDETECTORMQSAMPLER_H_

#include "FairMQSampler.h"

#include "FairTestDetectorPayload.h"

class TestDetectorMQSampler: public FairMQSampler
{
  public:
    TestDetectorMQSampler();
    virtual ~TestDetectorMQSampler();
  protected:
    virtual void Init();
};

#endif /* TESTDETECTORMQSAMPLER_H_ */
