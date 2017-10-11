#include "_TestFairLoggerNew.h"

TEST_F(FairToolsTest, CheckOutputOnlyToFile)
{
    fHandler.BeginCapture();

    gLogger->SetLogFileName(fOutFileName.c_str());
    gLogger->SetLogToFile(true);
    gLogger->SetLogToScreen(false);
    LogNoArguments();

    fHandler.EndCapture();

    std::vector<std::string> expected = CreateExpectedOutputNoArguments(fLogLevelSettingToTest, fOutputString);
    FairTestOutputHandler outputhandler(fOutFileName);
    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        CheckFileOutput(expected, outputhandler);
    }
}
