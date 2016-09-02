#include "_TestFairLogger.h"

TEST(FairToolsTestFatal, TestFatalError1)
{
  FairLogger* fLogger = FairLogger::GetLogger();
  fLogger->SetScreenStreamToCerr(true);
  fLogger->SetLogToFile(true);
  EXPECT_DEATH(fLogger->Fatal(MESSAGE_ORIGIN, "This is a fatal problem"),
               "FATAL");
  // TODO: check if cored dump is written to file
}
