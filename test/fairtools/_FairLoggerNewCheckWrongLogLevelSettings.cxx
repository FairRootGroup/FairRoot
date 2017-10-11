#include "_TestFairLoggerNew.h"

TEST_F(FairToolsTest, CheckWrongLogLevelSettings)
{
    gLogger->SetLogToFile(false);
    gLogger->SetLogToScreen(true);

    fHandler.BeginCapture();

    gLogger->SetLogScreenLevel("BLA");
    LogNoArguments();

    fHandler.EndCapture();

    std::vector<std::string> expected = CreateExpectedOutputNoArguments(fLogLevelSettingToTest, fOutputString);
    std::string outString = "[ERROR] Unknown severity setting: 'BLA', setting to default 'info'.";
    std::vector<std::string>::iterator it;
    it = expected.begin();
    it = expected.insert(it, outString);

    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        CheckScreenOutput(expected);
    }
}
