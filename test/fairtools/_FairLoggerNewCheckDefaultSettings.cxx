#include "_TestFairLoggerNew.h"

TEST_F(FairToolsTest, CheckDefaultSettings)
{
  handler.BeginCapture();
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> expected = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckScreenOutput(expected);
  }
}
