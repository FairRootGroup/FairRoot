/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *             GNU Lesser General Public Licence (LGPL) version 3,              *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairLogger.h"

#include "FairCaptureOutputNew.h"
#include "FairTestNewOutputHandler.h"
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

/*
 Base class to use the same basic setup for parameterized and
 non-parameterized tests.
 Here one defines everything which is common for all the different
 test cases
*/
template <class T> class _TestFairLoggerBase : public T
{
  protected:

    std::string logLevelSettingToTest;
    std::string OutputString;
    std::string OutFileName;
    FairLogger* fLogger;
    FairCaptureOutputNew handler;

    _TestFairLoggerBase()
    : logLevelSettingToTest("INFO"),
      OutputString("I am here."),
      OutFileName(""),
      fLogger(FairLogger::GetLogger()),
      handler()
    {
    }

    _TestFairLoggerBase(const _TestFairLoggerBase&);
    _TestFairLoggerBase& operator=(const _TestFairLoggerBase&);

    ~_TestFairLoggerBase() {};

    virtual void SetUp() {
      SetFairLoggerDefaultValues();
      SetOutFileName();
    }

    virtual void TearDown() {
    }

    void SetOutFileName() {
      char fileName[25];
      tmpnam(fileName);
      OutFileName = fileName;
    }

    void SetFairLoggerDefaultValues() {
      fLogger->SetLogToScreen(true);
      fLogger->SetLogToFile(false);
      fLogger->SetLogFileLevel("INFO");
      fLogger->SetLogScreenLevel("INFO");
      fLogger->SetLogVerbosityLevel("LOW");
      fLogger->SetScreenStreamToCerr(true);
    }

    void LogNoArguments() {
      // Log same message for all log levels
      fLogger->Error(MESSAGE_ORIGIN, OutputString.c_str());
      fLogger->Warning(MESSAGE_ORIGIN, OutputString.c_str());
      fLogger->Info(MESSAGE_ORIGIN, OutputString.c_str());
      fLogger->Debug(MESSAGE_ORIGIN, OutputString.c_str());
      fLogger->Debug1(MESSAGE_ORIGIN, OutputString.c_str());
      fLogger->Debug2(MESSAGE_ORIGIN, OutputString.c_str());
      fLogger->Debug3(MESSAGE_ORIGIN, OutputString.c_str());
      fLogger->Debug4(MESSAGE_ORIGIN, OutputString.c_str());
    }

    std::vector<std::string>
    CreateExpectedOutputNoArguments(std::string loglevel,
                                    std::string outString) {

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
        fullOutputString = "[" + *iter + "] " + outString + " ";
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

    void CheckFileOutput(std::vector<std::string> v, std::string fileName) {
      std::vector<std::string> fileInfo;
      fileInfo=ReadLinesFromFile(fileName);
      int noLines = fileInfo.size();
      int expectedNumberOfLines = v.size();
      EXPECT_EQ(expectedNumberOfLines,noLines);

      int minLines = std::min(expectedNumberOfLines,noLines);

      for (int i = 0; i < minLines; ++i) {
        EXPECT_EQ( v[i], fileInfo[i] );
      }
    }

    std::vector<std::string> ReadLinesFromFile(std::string fileName) {

      std::vector<std::string> list;
      std::string line;
      std::ifstream myfile (fileName.c_str());

      if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
          list.push_back(line);
        }
        myfile.close();
      }

      return list;
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

/*
 This is the derived class for the non-parameterized test cases.
*/
class  FairToolsTest : public _TestFairLoggerBase<testing::Test> {};

/*
 This is the derived class for the parameterized test case
 which test all log levels.
*/
class LogLevelTest : public _TestFairLoggerBase<
  testing::TestWithParam<const char*> >
{
  protected:
    virtual void SetUp() {
      logLevelSettingToTest=GetParam();
//      OutputString = "I am here.";
//      fLogger = FairLogger::GetLogger();
      SetOutFileName();
      SetFairLoggerDefaultValues();
    }
};

/*
 This is the derived class for the parameterized test case
 which test all verbosity levels.
*/
class VerbosityLevelTest : public _TestFairLoggerBase<
  testing::TestWithParam<const char*> >
{


  protected:

    VerbosityLevelTest() : verbosityLevel("") {}

    virtual void SetUp() {
      verbosityLevel=GetParam();
      SetOutFileName();
      SetFairLoggerDefaultValues();
    }

    std::string verbosityLevel;
};
