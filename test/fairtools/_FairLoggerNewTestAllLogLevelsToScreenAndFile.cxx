#include "_TestFairLoggerNew.h"

TEST_P(LogLevelTest, testAllLogLevelsToScreenAndFile)
{
  gLogger->SetLogFileLevel(logLevelSettingToTest.c_str());
  gLogger->SetLogScreenLevel(logLevelSettingToTest.c_str());

  handler.BeginCapture();

  gLogger->SetLogFileName(OutFileName.c_str());
  gLogger->SetLogToScreen(true);
  gLogger->SetLogToFile(true);
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> expected = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckScreenOutput(expected);
  }

  FairTestOutputHandler outputhandler(OutFileName);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckFileOutput(expected, outputhandler);
  }

}

INSTANTIATE_TEST_CASE_P(TestAllLogLevels,
                        LogLevelTest,
                        ::testing::ValuesIn(TestLogs));
