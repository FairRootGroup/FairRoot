#include "_TestFairLogger.h"

TEST_F(FairToolsTest, testScreenAndFileOutputWithoutArgument)
{
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
