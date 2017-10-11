#include "_TestFairLoggerNew.h"


TEST_P(VerbosityLevelTest, testAllVerbosityLevelsToScreenAndFile)
{
    gLogger->SetLogVerbosityLevel(fVerbosityLevel.c_str());

    fHandler.BeginCapture();

    gLogger->SetLogFileName(fOutFileName.c_str());
    gLogger->SetLogToScreen(true);
    gLogger->SetLogToFile(true);
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


    FairTestOutputHandler outputHandler(fOutFileName);
    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        int lines = expected.size();

        for (int i = 0; i < lines; ++i)
        {
            EXPECT_TRUE(CheckVerboseOutput(expected[i], fOutputString, fVerbosityLevel, outputHandler.GetCaptureLine(i)));
        }
    }
}

INSTANTIATE_TEST_CASE_P(TestAllVerbosityLevels, VerbosityLevelTest, ::testing::ValuesIn(VerbosityLevelArray));
