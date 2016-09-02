#include "_TestFairLoggerNew.h"

TEST_F(FairToolsTest, CheckOutputOnlyToFile)
{

  handler.BeginCapture();

  gLogger->SetLogFileName(OutFileName.c_str());
  gLogger->SetLogToFile(true);
  gLogger->SetLogToScreen(false);
  LogNoArguments();

  handler.EndCapture();

  std::vector<std::string> expected = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  FairTestOutputHandler outputhandler(OutFileName);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckFileOutput(expected, outputhandler);
  }
}
