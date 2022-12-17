#include "FairLogger.h"

#include "gtest/gtest.h"

TEST(FairLoggerTest, TestFatalError)
{
    FairLogger::GetLogger();
    ASSERT_THROW(LOG(fatal) << "This is a fatal problem", fair::FatalException);
    // TODO: check if cored dump is written to file
}
