#include "_TestFairLogger.h"

TEST_F(FairToolsTest, CheckOutputOnlyToFile)
{

  handler.BeginCapture();
  fLogger->SetLogFileName(OutFileName.c_str());
  fLogger->SetLogToFile(true);
  fLogger->SetLogToScreen(false);
  LogNoArguments();

  handler.EndCapture();

  std::vector<std::string> expected = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckFileOutput(expected, OutFileName);
  }
}
