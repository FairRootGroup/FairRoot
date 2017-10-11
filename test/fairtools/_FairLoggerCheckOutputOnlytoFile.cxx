#include "_TestFairLogger.h"

TEST_F(FairToolsTest, CheckOutputOnlyToFile)
{
    fHandler.BeginCapture();

    fLogger->SetLogFileName(fOutFileName.c_str());
    fLogger->SetLogToFile(true);
    fLogger->SetLogToScreen(false);
    LogNoArguments();

    fHandler.EndCapture();

    std::vector<std::string> expected = CreateExpectedOutputNoArguments(fLogLevelSettingToTest, fOutputString);
    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        CheckFileOutput(expected, fOutFileName);
    }
}
