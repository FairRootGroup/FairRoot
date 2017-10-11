#include "_TestFairLoggerNew.h"

TEST_F(FairToolsTest, CheckVerbosityLevelSettings)
{
    gLogger->SetLogToFile(false);
    gLogger->SetLogToScreen(true);

    fHandler.BeginCapture();

    gLogger->SetLogVerbosityLevel("BLA");
    LogNoArguments();

    fHandler.EndCapture();

    std::vector<std::string> expected = CreateExpectedOutputNoArguments(fLogLevelSettingToTest, fOutputString);
    std::string outString = "[ERROR] Unknown verbosity setting: 'BLA', setting to default 'low'.";
    std::vector<std::string>::iterator it;
    it = expected.begin();
    it = expected.insert(it, outString);

    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        CheckScreenOutput(expected);
    }
}
