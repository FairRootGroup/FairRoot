#include "_TestFairLoggerNew.h"

TEST_F(FairToolsTest, CheckDefaultSettings)
{
    fHandler.BeginCapture();

    LogNoArguments();

    fHandler.EndCapture();

    std::vector<std::string> expected = CreateExpectedOutputNoArguments(fLogLevelSettingToTest, fOutputString);
    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        CheckScreenOutput(expected);
    }
}
