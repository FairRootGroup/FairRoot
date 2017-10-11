#include "_TestFairLogger.h"


TEST_P(LogLevelTest, testAllLogLevelsToScreenAndFile)
{
    fLogger->SetLogFileLevel(fLogLevelSettingToTest.c_str());
    fLogger->SetLogScreenLevel(fLogLevelSettingToTest.c_str());

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

INSTANTIATE_TEST_CASE_P(TestAllLogLevels, LogLevelTest, ::testing::ValuesIn(TestLogs));
