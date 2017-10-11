#include "_TestFairLoggerNew.h"

TEST(FairToolsTestFatal, TestFatalError1)
{
    gLogger->SetScreenStreamToCerr(true);
    gLogger->SetLogToFile(true);
    ASSERT_THROW(LOG(fatal) << "This is a another fatal problem", fair::FatalException);
    // TODO: check if cored dump is written to file
}

