#include "_TestFairLoggerNew.h"

TEST_F(FairToolsTest, testScreenAndFileOutputWithoutArgument)
{
    fHandler.BeginCapture();

    gLogger->SetLogFileName(fOutFileName.c_str());
    gLogger->SetLogToScreen(true);
    gLogger->SetLogToFile(true);
    LogNoArguments();

    fHandler.EndCapture();

    std::vector<std::string> expected = CreateExpectedOutputNoArguments(fLogLevelSettingToTest, fOutputString);

    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        CheckScreenOutput(expected);
    }

    FairTestOutputHandler outputHandler(fOutFileName);
    {
        SCOPED_TRACE(fLogLevelSettingToTest);
        CheckFileOutput(expected, outputHandler);
    }
}
