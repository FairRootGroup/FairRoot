#include "_TestFairLoggerNew.h"

TEST(FairToolsTestFatal, TestFatalError)
{
    gLogger->SetScreenStreamToCerr(true);
    ASSERT_THROW(LOG(fatal) << "This is a fatal problem", fair::FatalException);
    // TODO: check if cored dump is written to file
}
