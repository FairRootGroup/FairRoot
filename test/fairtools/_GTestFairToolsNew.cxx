/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairLogger.h"
#include "FairCaptureOutput.h"
#include "FairTestOutputHandler.h"

#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <boost/regex.hpp>


static const char* const LogString[] = { "FATAL  ", "ERROR  ", "WARNING",
                                       "INFO   ", "DEBUG  ", "DEBUG1 ",
                                       "DEBUG2 ", "DEBUG3 ", "DEBUG4 "
                                       };


static const char* const TestLogs[] = { "ERROR", "WARNING",
                                        "INFO", "DEBUG", "DEBUG1",
                                        "DEBUG2", "DEBUG3", "DEBUG4"
                                      };

static const char* const VerbosityLevelArray[] = { "LOW", "MEDIUM", "HIGH"};


TEST(FairToolsTestFatal, TestFatalError)
{
  gLogger->SetScreenStreamToCerr(true);
  EXPECT_DEATH(LOG(FATAL) << "This is a fatal problem" << FairLogger::endl,
               "FATAL");
  // TODO: check if cored dump is written to file
}

// Base class to use the same basic setup for parameterized and
// non-parameterized tests
// Here one defines everything which is common for all the different
// test cases
template <class T> class _TestFairLoggerBase : public T
{
  protected:

    std::string logLevelSettingToTest;
    std::string OutputString;
    FairCaptureOutput handler;

    virtual void SetUp() {
      logLevelSettingToTest="INFO";
      OutputString = "I am here.";
      SetFairLoggerDefaultValues();
    }

    /*
    virtual void TearDown()
    {
      // Check for the existens of an output file, close and remove
      // the file if it exists.
      // If this is done the file handling can move from the single
      // test to the SetUp function of the base class
    }
    */
    void SetFairLoggerDefaultValues() {
      gLogger->SetLogToScreen(true);
      gLogger->SetLogToFile(false);
      gLogger->SetLogFileLevel("INFO");
      gLogger->SetLogScreenLevel("INFO");
      gLogger->SetLogVerbosityLevel("LOW");
      gLogger->SetScreenStreamToCerr(true);
    }

    void LogNoArguments() {
      // Log same message for all log levels
      LOG(ERROR) << OutputString.c_str() << FairLogger::endl;
      LOG(WARNING) << OutputString.c_str() << FairLogger::endl;
      LOG(INFO) << OutputString.c_str() << FairLogger::endl;
      LOG(DEBUG) << OutputString.c_str() << FairLogger::endl;
      LOG(DEBUG1) << OutputString.c_str() << FairLogger::endl;
      LOG(DEBUG2) << OutputString.c_str() << FairLogger::endl;
      LOG(DEBUG3) << OutputString.c_str() << FairLogger::endl;
      LOG(DEBUG4) << OutputString.c_str() << FairLogger::endl;
    }

    std::vector<std::string> CreateExpectedOutputNoArguments(std::string loglevel,
        std::string outString,
        std::string filename="") {

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

      std::vector<std::string>::iterator iter;
      for ( iter = levelNames.begin();
            iter < levelNames.end();
            iter++) {
        fullOutputString = "[" + *iter + "] " + outString;
        retVal.push_back(fullOutputString);
      }

      return retVal;
    }

    std::vector<std::string> CreateExpectedLogLevels(std::string loglevel) {

      std::vector<std::string> levelNames(TestLogs, TestLogs+8);
      std::vector<std::string>::iterator position =
        std::find(levelNames.begin(), levelNames.end(), loglevel);
      levelNames.erase(position+1, levelNames.end());
      return levelNames;
    }

    void CheckScreenOutput(std::vector<std::string> v) {
      int noLines = handler.GetNumberOfLines();
      int expectedNumberOfLines = v.size();
      EXPECT_EQ(expectedNumberOfLines,noLines);

      int minLines = std::min(expectedNumberOfLines,noLines);

      for (int i = 0; i < minLines; ++i) {
        EXPECT_EQ( v[i], handler.GetCaptureLine(i) );
      }
    }

    void CheckFileOutput(std::vector<std::string> v, FairTestOutputHandler _handler) {
      int noLines = _handler.GetNumberOfLines();
      int expectedNumberOfLines = v.size();
      EXPECT_EQ(expectedNumberOfLines,noLines);

      int minLines = std::min(expectedNumberOfLines,noLines);

      for (int i = 0; i < minLines; ++i) {
        EXPECT_EQ( v[i], _handler.GetCaptureLine(i) );
      }
    }

    bool CheckVerboseOutput(std::string logLevel, std::string outputString,
                            std::string verboseLevel, std::string resultString
                           ) {
      // Example Output for logging level INFO and different verbosity levels
      // verbosity Level:Output
      // LOW    :[INFO   ] I am here.
      // MEDIUM :[INFO   ] [_TestFairTools.cxx::LogNoArguments:78] I am here.
      // HIGH   :[INFO   ] [05.12.2011 12:00:10] [_TestFairTools.cxx::LogNoArguments:78] I am here.
      std::string regexString = "\\[" + logLevel + "[ ]*][ ]";
      if (verboseLevel.compare("HIGH") == 0) {
        regexString = regexString + "\\[\\d{2}\\.\\d{2}\\.\\d{4}[ ]\\d{2}:\\d{2}:\\d{2}][ ]";
        regexString = regexString + "\\[.*::.*:\\d{2}][ ]";
      }
      if (verboseLevel.compare("MEDIUM") == 0) {
        regexString = regexString + "\\[.*::.*:\\d{2}][ ]";
      }
      regexString = regexString + outputString + ".*";

      const boost::regex e(regexString);
      return regex_match(resultString, e);
    }
};

// This is the derived class for the non-parameterized test cases.
class  FairToolsTest : public _TestFairLoggerBase<testing::Test> {};

// This is the derived class for the parameterized test cases.
class LogLevelTest : public _TestFairLoggerBase<
  testing::TestWithParam<const char*> >
{
  protected:
    virtual void SetUp() {
      logLevelSettingToTest=GetParam();
      OutputString = "I am here.";
      SetFairLoggerDefaultValues();
    }
};

class VerbosityLevelTest : public _TestFairLoggerBase<
  testing::TestWithParam<const char*> >
{
  protected:
    virtual void SetUp() {
      logLevelSettingToTest="INFO";
      verbosityLevel=GetParam();
      OutputString = "I am here.";
      SetFairLoggerDefaultValues();
    }
    std::string verbosityLevel;
};

TEST_F(FairToolsTest, CheckDefaultSettings)
{
  handler.BeginCapture();
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckScreenOutput(v);
  }
}

TEST_F(FairToolsTest, CheckOutputOnlyToFile)
{
  handler.BeginCapture();

  char fileName[25];
  tmpnam(fileName);
  gLogger->SetLogFileName(fileName);
  gLogger->SetLogToFile(true);
  gLogger->SetLogToScreen(false);
  LogNoArguments();

  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  FairTestOutputHandler outputhandler(fileName);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckFileOutput(v, outputhandler);
  }
}

TEST_F(FairToolsTest, CheckWrongLogLevelSettings)
{

  gLogger->SetLogToFile(false);
  gLogger->SetLogToScreen(true);

  handler.BeginCapture();
  gLogger->SetLogScreenLevel("BLA");
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  std::string outString="[ERROR  ] Log level \"BLA\" not supported. Use default level \"INFO\".";
  std::vector<std::string>::iterator it;
  it = v.begin();
  it = v.insert ( it , outString );

  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckScreenOutput(v);
  }
}

TEST_F(FairToolsTest, CheckVerbosityLevelSettings)
{

  gLogger->SetLogToFile(false);
  gLogger->SetLogToScreen(true);

  handler.BeginCapture();
  gLogger->SetLogVerbosityLevel("BLA");
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  std::string outString="[ERROR  ] Verbosity level \"BLA\" not supported. Use default level \"LOW\".";
  std::vector<std::string>::iterator it;
  it = v.begin();
  it = v.insert ( it , outString );

  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckScreenOutput(v);
  }

}


TEST_F(FairToolsTest, testScreenAndFileOutputWithoutArgument)
{
  handler.BeginCapture();

  char fileName[25];
  tmpnam(fileName);
  gLogger->SetLogFileName(fileName);
  gLogger->SetLogToScreen(true);
  gLogger->SetLogToFile(true);
  LogNoArguments();

  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString, fileName);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckScreenOutput(v);
  }

  v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  FairTestOutputHandler outputhandler(fileName);

  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckFileOutput(v, outputhandler);
  }

}

TEST_P(LogLevelTest, testAllLogLevelsToScreenAndFile)
{
  gLogger->SetLogFileLevel(logLevelSettingToTest.c_str());
  gLogger->SetLogScreenLevel(logLevelSettingToTest.c_str());

  handler.BeginCapture();
  char fileName[25];
  tmpnam(fileName);
  gLogger->SetLogFileName(fileName);
  gLogger->SetLogToScreen(true);
  gLogger->SetLogToFile(true);
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString, fileName);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckScreenOutput(v);
  }

  v = CreateExpectedOutputNoArguments(logLevelSettingToTest, OutputString);
  FairTestOutputHandler outputhandler(fileName);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    CheckFileOutput(v, outputhandler);
  }

}

INSTANTIATE_TEST_CASE_P(TestAllLogLevels,
                        LogLevelTest,
                        ::testing::ValuesIn(TestLogs));


TEST_P(VerbosityLevelTest, testAllVerbosityLevelsToScreenAndFile)
{
  gLogger->SetLogVerbosityLevel(verbosityLevel.c_str());

  handler.BeginCapture();
  char fileName[25];
  tmpnam(fileName);
  gLogger->SetLogFileName(fileName);
  gLogger->SetLogToScreen(true);
  gLogger->SetLogToFile(true);
  LogNoArguments();
  handler.EndCapture();

  std::vector<std::string> v = CreateExpectedLogLevels(logLevelSettingToTest);

  {
    SCOPED_TRACE(logLevelSettingToTest);
    int Lines = v.size();

    for (int i = 0; i < Lines; ++i) {
      EXPECT_TRUE( CheckVerboseOutput( v[i], OutputString, verbosityLevel, handler.GetCaptureLine(i) ) );
    }
  }


  FairTestOutputHandler outputhandler(fileName);
  {
    SCOPED_TRACE(logLevelSettingToTest);
    int Lines = v.size();

    for (int i = 0; i < Lines; ++i) {
      EXPECT_TRUE( CheckVerboseOutput( v[i], OutputString, verbosityLevel, outputhandler.GetCaptureLine(i) ) );
    }
  }

}

INSTANTIATE_TEST_CASE_P(TestAllVerbosityLevels,
                        VerbosityLevelTest,
                        ::testing::ValuesIn(VerbosityLevelArray));
