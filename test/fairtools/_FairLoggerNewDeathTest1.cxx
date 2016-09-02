#include "_TestFairLoggerNew.h"

TEST(FairToolsTestFatal, TestFatalError)
{
  gLogger->SetScreenStreamToCerr(true);
  EXPECT_DEATH(LOG(FATAL) << "This is a fatal problem" << FairLogger::endl,
              "FATAL");
  // TODO: check if cored dump is written to file
}
