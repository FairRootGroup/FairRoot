#include "_TestFairLogger.h"

TEST(FairToolsTestFatal, TestFatalError1)
{
    FairLogger* fLogger = FairLogger::GetLogger();
    fLogger->SetScreenStreamToCerr(true);
    fLogger->SetLogToFile(true);
    ASSERT_THROW(fLogger->Fatal(MESSAGE_ORIGIN, "This is a fatal problem"), fair::FatalException);
    // TODO: check if cored dump is written to file
}
