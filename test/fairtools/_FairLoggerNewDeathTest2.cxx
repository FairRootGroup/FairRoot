#include "_TestFairLoggerNew.h"

TEST(FairToolsTestFatal, TestFatalError1)
{
  gLogger->SetScreenStreamToCerr(true);
  gLogger->SetLogToFile(true);
  EXPECT_DEATH(LOG(FATAL) << "This is a another fatal problem" << FairLogger::endl,
              "FATAL");
  // TODO: check if cored dump is written to file
}

