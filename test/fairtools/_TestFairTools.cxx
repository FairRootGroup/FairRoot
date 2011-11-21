#include "FairLogger.h"
#include "FairCaptureOutput.h"
#include "FairTestOutputHandler.h"

#include "gtest/gtest.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <algorithm>

static const char* const LogString[] = { "FATAL  ", "ERROR  ", "WARNING",
                                       "INFO   ", "DEBUG  ", "DEBUG1 ",
                                       "DEBUG2 ", "DEBUG3 ", "DEBUG4 "
                                       };


static const char* const TestLogs[] = { "ERROR", "WARNING",
                                        "INFO", "DEBUG", "DEBUG1",
                                        "DEBUG2", "DEBUG3", "DEBUG4"
                                      };


void LogNoArguments(FairLogger* fLogger, std::string OutputString)
{
  // Same message for all log levels
  fLogger->Error(MESSAGE_ORIGIN, OutputString.c_str());
  fLogger->Warning(MESSAGE_ORIGIN, OutputString.c_str());
  fLogger->Info(MESSAGE_ORIGIN, OutputString.c_str());
  fLogger->Debug(MESSAGE_ORIGIN, OutputString.c_str());
  fLogger->Debug1(MESSAGE_ORIGIN, OutputString.c_str());
  fLogger->Debug2(MESSAGE_ORIGIN, OutputString.c_str());
  fLogger->Debug3(MESSAGE_ORIGIN, OutputString.c_str());
  fLogger->Debug4(MESSAGE_ORIGIN, OutputString.c_str());
}

std::vector<std::string> CreateExpectedOutputNoArguments(std::string loglevel,
    std::string outString,
    std::string filename="")
{

  //Put blanks to the string to have all strings the same length
  int size = loglevel.size();
  int maxsize = 7; // length of string "WARNING"
  for (int i=size; i<maxsize; i++) {
    loglevel += " ";
  }

  std::vector<std::string> levelNames(LogString, LogString+9);
  std::vector<std::string>::iterator position =
    std::find(levelNames.begin(), levelNames.end(), loglevel);
  levelNames.erase(position+1, levelNames.end());
  levelNames.erase(levelNames.begin()); // don't use FATAL loglevel in this test

  std::vector<std::string> retVal;
  std::string fullOutputString;
  if ( filename.compare("") != 0) {
    fullOutputString = "[INFO   ] Openning log file: " + filename;
    retVal.push_back(fullOutputString);
    retVal.push_back(" ");
  }

  std::vector<std::string>::iterator iter;
  for ( iter = levelNames.begin();
        iter < levelNames.end();
        iter++) {
    fullOutputString = "[" + *iter + "] " + outString + " ";
    retVal.push_back(fullOutputString);
  }

  return retVal;
}



void CheckScreenOutput(FairCaptureOutput handler, std::vector<std::string> v)
{
  int noLines = handler.GetNumberOfLines();
  int expectedNumberOfLines = v.size();
  EXPECT_EQ(expectedNumberOfLines,noLines);

  int minLines = std::min(expectedNumberOfLines,noLines);

  for (int i = 0; i < minLines; ++i) {
    EXPECT_EQ( v[i], handler.GetCaptureLine(i) );
  }
}

void CheckFileOutput(FairTestOutputHandler handler, std::vector<std::string> v)
{
  int noLines = handler.GetNumberOfLines();
  int expectedNumberOfLines = v.size();
  EXPECT_EQ(expectedNumberOfLines,noLines);

  int minLines = std::min(expectedNumberOfLines,noLines);

  for (int i = 0; i < minLines; ++i) {
    EXPECT_EQ( v[i], handler.GetCaptureLine(i) );
  }
}

TEST(FairToolsTest, callInstanceShouldWork)
{
  FairLogger* fLogger = FairLogger::GetLogger();
}

TEST(FairToolsTest, CheckDefaultSettings)
{
  // The default is to log everything from Info level upwards
  // to screen, no logging to file
  std::string OutputString = "I am here.";

  FairLogger* fLogger = FairLogger::GetLogger();
  FairCaptureOutput handler(true, false);
  handler.BeginCapture();
  LogNoArguments(fLogger, OutputString);
  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedOutputNoArguments("INFO", OutputString);
  CheckScreenOutput(handler, v);
}


TEST(FairToolsTest, CheckOutputOnlyToFile)
{
  // The default is to log everything from Info level upwards
  // to screen, no logging to file
  std::string OutputString = "I am here.";

  FairLogger* fLogger = FairLogger::GetLogger();

  FairCaptureOutput handler(true, false);
  handler.BeginCapture();

  char fileName[25];
  tmpnam(fileName);
  fLogger->SetLogFileName(fileName);
  fLogger->SetLogToFile(true);
  fLogger->SetLogToScreen(false);

  LogNoArguments(fLogger, OutputString);
  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedOutputNoArguments("INFO", OutputString);
  FairTestOutputHandler outputhandler(fileName);
  CheckFileOutput(outputhandler, v);
}


TEST(FairToolsTest, CheckWrongLogLevelSettings)
{
  // The default is to log everything from Info level upwards
  // to screen, no logging to file
  std::string OutputString = "I am here.";

  FairLogger* fLogger = FairLogger::GetLogger();
  fLogger->SetLogToFile(false);
  fLogger->SetLogToScreen(true);
  FairCaptureOutput handler(true, false);
  handler.BeginCapture();
  fLogger->SetLogScreenLevel("BLA");
  LogNoArguments(fLogger, OutputString);
  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedOutputNoArguments("INFO", OutputString);
  std::string outString="Log level \"BLA\" not supported. Use default level \"INFO\".";
  std::vector<std::string>::iterator it;
  it = v.begin();
  it = v.insert ( it , outString );

  CheckScreenOutput(handler, v);
}

TEST(FairToolsTest, CheckVerbosityLevelSettings)
{
  // The default is to log everything from Info level upwards
  // to screen, no logging to file
  std::string OutputString = "I am here.";


  FairLogger* fLogger = FairLogger::GetLogger();
  fLogger->SetLogToFile(false);
  fLogger->SetLogToScreen(true);
  FairCaptureOutput handler(true, false);
  handler.BeginCapture();
  fLogger->SetLogVerbosityLevel("BLA");
  LogNoArguments(fLogger, OutputString);
  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedOutputNoArguments("INFO", OutputString);
  std::string outString="Verbosity level \"BLA\" not supported. Use default level \"LOW\".";
  std::vector<std::string>::iterator it;
  it = v.begin();
  it = v.insert ( it , outString );

  CheckScreenOutput(handler, v);
}


TEST(FairToolsTest, testScreenAndFileOutputWithoutArgument)
{

  std::string OutputString = "I am here.";

  FairLogger* fLogger = FairLogger::GetLogger();

  FairCaptureOutput handler(true, false);
  handler.BeginCapture();
  char fileName[25];
  tmpnam(fileName);
  fLogger->SetLogFileName(fileName);
  fLogger->SetLogToScreen(true);
  fLogger->SetLogToFile(true);
  LogNoArguments(fLogger, OutputString);
  handler.EndCapture();

  //  std::string stringFileName(fileName);
  std::vector<std::string> v = CreateExpectedOutputNoArguments("INFO", OutputString, fileName);
  CheckScreenOutput(handler, v);

  v = CreateExpectedOutputNoArguments("INFO", OutputString);
  FairTestOutputHandler outputhandler(fileName);
  CheckFileOutput(outputhandler, v);
}

class LogLevelTest : public testing::TestWithParam<const char*>
{
  protected:
    virtual void SetUp() {
      logLevelSettingToTest=GetParam();
      OutputString = "I am here.";
      fLogger = FairLogger::GetLogger();
    }
    std::string logLevelSettingToTest;
    std::string OutputString;
    FairLogger* fLogger;
};


TEST_P(LogLevelTest, testAllLogLevelsToScreenAndFile)
{
  fLogger->SetLogFileLevel(logLevelSettingToTest.c_str());
  fLogger->SetLogScreenLevel(logLevelSettingToTest.c_str());

  FairCaptureOutput handler(true, false);
  handler.BeginCapture();
  char fileName[25];
  tmpnam(fileName);
  fLogger->SetLogFileName(fileName);
  fLogger->SetLogToScreen(true);
  fLogger->SetLogToFile(true);
  LogNoArguments(fLogger, OutputString);
  handler.EndCapture();

  //  std::string stringFileName(fileName);
  std::vector<std::string> v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString, fileName);
  //  std::vector<std::string> v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  CheckScreenOutput(handler, v);


  v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  FairTestOutputHandler outputhandler(fileName);
  CheckFileOutput(outputhandler, v);
}

INSTANTIATE_TEST_CASE_P(TestAllLogLevels,
                        LogLevelTest,
                        ::testing::ValuesIn(TestLogs));
