#include "_TestFairLogger.h"

TEST_F(FairToolsTest, CheckWrongLogLevelSettings)
{

  fLogger->SetLogToFile(false);
  fLogger->SetLogToScreen(true);

  handler.BeginCapture();
  fLogger->SetLogScreenLevel("BLA");
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> expected = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  std::string outString="[ERROR  ] Log level \"BLA\" not supported. Use default level \"INFO\".";
  std::vector<std::string>::iterator it;
  it = expected.begin();
  it = expected.insert ( it , outString );

  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckScreenOutput(expected);
  }
}
