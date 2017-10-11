#include "_TestFairLogger.h"

TEST_F(FairToolsTest, testScreenAndFileOutputWithoutArgument)
{
    fHandler.BeginCapture();

    fLogger->SetLogFileName(fOutFileName.c_str());
    fLogger->SetLogToScreen(true);
    fLogger->SetLogToFile(true);
    LogNoArguments();

    fHandler.EndCapture();

    std::vector<std::string> expected = CreateExpectedOutputNoArguments(fLogLevelSettingToTest, fOutputString);
    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        CheckScreenOutput(expected);
    }

    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        CheckFileOutput(expected, fOutFileName);
    }
}
