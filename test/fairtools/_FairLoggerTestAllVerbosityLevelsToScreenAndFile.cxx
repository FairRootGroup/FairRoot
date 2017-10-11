#include "_TestFairLogger.h"

TEST_P(VerbosityLevelTest, testAllVerbosityLevelsToScreenAndFile)
{
    fLogger->SetLogVerbosityLevel(fVerbosityLevel.c_str());

    fHandler.BeginCapture();

    fLogger->SetLogFileName(fOutFileName.c_str());
    fLogger->SetLogToScreen(true);
    fLogger->SetLogToFile(true);
    LogNoArguments();

    fHandler.EndCapture();

    std::vector<std::string> expected = CreateExpectedLogLevels(fLogLevelSettingToTest);

    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        int lines = expected.size();

        for (int i = 0; i < lines; ++i)
        {
            EXPECT_TRUE(CheckVerboseOutput(expected[i], fOutputString, fVerbosityLevel, fHandler.GetCaptureLine(i)));
        }
    }

    std::vector<std::string> fileInfo;
    fileInfo = ReadLinesFromFile(fOutFileName);
    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        int lines = expected.size();

        for (int i = 0; i < lines; ++i)
        {
            EXPECT_TRUE(CheckVerboseOutput(expected[i], fOutputString, fVerbosityLevel, fileInfo[i]));
        }
    }
}

INSTANTIATE_TEST_CASE_P(TestAllVerbosityLevels, VerbosityLevelTest, ::testing::ValuesIn(VerbosityLevelArray));
