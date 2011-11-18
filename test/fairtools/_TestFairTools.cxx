#include "FairLogger.h"
#include "FairCaptureOutput.h"
#include "FairTestOutputHandler.h"

#include "gtest/gtest.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <algorithm>

TEST(FairToolsTest, callInstanceShouldWork)
{
  FairLogger* fLogger = FairLogger::GetLogger();
}

TEST(FairToolsTest, testScreenOutputwithoutArgument)
{
  FairLogger* fLogger = FairLogger::GetLogger();

  FairCaptureOutput handler(true, false);
  handler.BeginCapture();

  fLogger->Error(MESSAGE_ORIGIN,"I am here.");
  fLogger->Info(MESSAGE_ORIGIN,"I am here.");
  fLogger->Debug(MESSAGE_ORIGIN,"I am here.");
  fLogger->Debug1(MESSAGE_ORIGIN,"I am here.");
  fLogger->Debug2(MESSAGE_ORIGIN,"I am here.");
  fLogger->Debug3(MESSAGE_ORIGIN,"I am here.");
  fLogger->Debug4(MESSAGE_ORIGIN,"I am here.");

  handler.EndCapture();

  int noLines = handler.GetNumberOfLines();
  const char* expectedValue[] = {"[ERROR  ] I am here. ", "[INFO   ] I am here. "};
  std::vector<std::string> v(expectedValue, expectedValue + 2);
  int expectedNumberOfLines = v.size();
  EXPECT_EQ(expectedNumberOfLines,noLines);

  int minLines = std::min(expectedNumberOfLines,noLines);

  for (int i = 0; i < minLines; ++i) {
    EXPECT_EQ( v[i], handler.GetCaptureLine(i) );
  }
}
