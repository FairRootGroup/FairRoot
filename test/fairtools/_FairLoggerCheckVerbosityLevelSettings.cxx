#include "_TestFairLogger.h"

TEST_F(FairToolsTest, CheckVerbosityLevelSettings)
{

  fLogger->SetLogToFile(false);
  fLogger->SetLogToScreen(true);

  handler.BeginCapture();
  fLogger->SetLogVerbosityLevel("BLA");
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> expected = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  std::string outString="[ERROR  ] Verbosity level \"BLA\" not supported. Use default level \"LOW\".";
  std::vector<std::string>::iterator it;
  it = expected.begin();
  it = expected.insert ( it , outString );

  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckScreenOutput(expected);
  }

}
