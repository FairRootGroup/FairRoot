#include "_TestFairLogger.h"


TEST_P(LogLevelTest, testAllLogLevelsToScreenAndFile)
{
  fLogger->SetLogFileLevel(logLevelSettingToTest.c_str());
  fLogger->SetLogScreenLevel(logLevelSettingToTest.c_str());

  handler.BeginCapture();
  fLogger->SetLogFileName(OutFileName.c_str());
  fLogger->SetLogToScreen(true);
  fLogger->SetLogToFile(true);
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> expected = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckScreenOutput(expected);
  }

  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckFileOutput(expected, OutFileName);
  }

}

INSTANTIATE_TEST_CASE_P(TestAllLogLevels,
                        LogLevelTest,
                        ::testing::ValuesIn(TestLogs));
