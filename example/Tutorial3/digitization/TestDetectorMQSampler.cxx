/**
 * TestDetectorMQSampler.cxx
 *
 *  @since 2012-04-2
 *  @authors A. Rybalchenko
 */

#include "TestDetectorMQSampler.h"

#include "TestDetectorDigiLoader.h"


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

//ClassImp(TestDetectorMQSampler)
