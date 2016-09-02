#include "_TestFairLogger.h"

TEST_P(VerbosityLevelTest, testAllVerbosityLevelsToScreenAndFile)
{
  fLogger->SetLogVerbosityLevel(verbosityLevel.c_str());

  handler.BeginCapture();
  fLogger->SetLogFileName(OutFileName.c_str());
  fLogger->SetLogToScreen(true);
  fLogger->SetLogToFile(true);
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> expected = CreateExpectedLogLevels(logLevelSettingToTest);

  {
    SCOPED_TRACE(logLevelSettingToTest);
    int Lines = expected.size();

    for (int i = 0; i < Lines; ++i) {
      EXPECT_TRUE( CheckVerboseOutput( expected[i], OutputString, verbosityLevel, handler.GetCaptureLine(i) ) );
    }
  }


  std::vector<std::string> fileInfo;
  fileInfo=ReadLinesFromFile(OutFileName);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    int Lines = expected.size();

    for (int i = 0; i < Lines; ++i) {
      EXPECT_TRUE( CheckVerboseOutput( expected[i], OutputString, verbosityLevel, fileInfo[i] ) );
    }
  }
}

INSTANTIATE_TEST_CASE_P(TestAllVerbosityLevels,
                        VerbosityLevelTest,
                        ::testing::ValuesIn(VerbosityLevelArray));
