#include "_TestFairLogger.h"

/*
 First we have the test which doesn't need any fixture.
*/
TEST(FairToolsTestFatal, TestFatalError)
{
    FairLogger* fLogger = FairLogger::GetLogger();
    fLogger->SetScreenStreamToCerr(true);
    ASSERT_THROW(fLogger->Fatal(MESSAGE_ORIGIN, "This is a fatal problem"), fair::FatalException);
    // TODO: check if cored dump is written to file
}
