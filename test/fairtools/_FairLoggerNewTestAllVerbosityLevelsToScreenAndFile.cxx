#include "_TestFairLoggerNew.h"


TEST_P(VerbosityLevelTest, testAllVerbosityLevelsToScreenAndFile)
{
  gLogger->SetLogVerbosityLevel(verbosityLevel.c_str());

  handler.BeginCapture();

  gLogger->SetLogFileName(OutFileName.c_str());
  gLogger->SetLogToScreen(true);
  gLogger->SetLogToFile(true);
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


  FairTestOutputHandler outputhandler(OutFileName);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    int Lines = expected.size();

    for (int i = 0; i < Lines; ++i) {
      EXPECT_TRUE( CheckVerboseOutput( expected[i], OutputString, verbosityLevel, outputhandler.GetCaptureLine(i) ) );
    }
  }

}

INSTANTIATE_TEST_CASE_P(TestAllVerbosityLevels,
                        VerbosityLevelTest,
                        ::testing::ValuesIn(VerbosityLevelArray));
