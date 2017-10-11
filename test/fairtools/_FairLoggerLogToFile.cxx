#include "_TestFairLogger.h"

TEST(FairToolsTestLogToFile, TestLogFileNotOpen)
{
    FairLogger* fLogger = FairLogger::GetLogger();
    fLogger->Warning(MESSAGE_ORIGIN, "This is a problem");
}
