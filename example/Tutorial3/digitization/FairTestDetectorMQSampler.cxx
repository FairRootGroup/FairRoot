/**
 * TestDetectorMQSampler.cxx
 *
 *  @since 2012-04-2
 *  @authors A. Rybalchenko
 */

#include "FairTestDetectorMQSampler.h"

#include "FairTestDetectorDigiLoader.h"


TestDetectorMQSampler::TestDetectorMQSampler()
{
}

TestDetectorMQSampler::~TestDetectorMQSampler()
{
}

void TestDetectorMQSampler::Init()
{
  if (fBranch == TestDetectorBranch::TestDetectorDigis) {
    fSamplerTask = new TestDetectorDigiLoader();
  }

  FairMQSampler::Init();
}
