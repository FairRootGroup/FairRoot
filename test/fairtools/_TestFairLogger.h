/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
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
#include <regex>

static const char* const LogString[] = {
    "FATAL", "ERROR", "WARN", "INFO",
    "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4"
};

static const char* const TestLogs[] = {
    "ERROR", "WARN", "INFO",
    "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4"
};

static const char* const VerbosityLevelArray[] = {
    "LOW", "MEDIUM", "HIGH", "VERYHIGH"
};

// Base class to use the same basic setup for parameterized and non-parameterized tests.
// Here one defines everything which is common for all the different test cases
template <class T>
class _TestFairLoggerBase : public T
{
  protected:
    std::string fLogLevelSettingToTest;
    std::string fOutputString;
    std::string fOutFileName;
    FairLogger* fLogger;
    FairCaptureOutputNew fHandler;

    _TestFairLoggerBase()
        : fLogLevelSettingToTest("INFO")
        , fOutputString("I am here.")
        , fOutFileName("")
        , fLogger(FairLogger::GetLogger())
        , fHandler()
    {}

    _TestFairLoggerBase(const _TestFairLoggerBase&);
    _TestFairLoggerBase& operator=(const _TestFairLoggerBase&);

    ~_TestFairLoggerBase()
    {};

    virtual void SetUp()
    {
        SetFairLoggerDefaultValues();
        SetOutFileName();
    }

    virtual void TearDown()
    {}

    void SetOutFileName()
    {
        char fileName[25];
        if (tmpnam(fileName))
        {
            fOutFileName = fileName;
        }
    }

    void SetFairLoggerDefaultValues()
    {
        fLogger->SetLogToScreen(true);
        fLogger->SetLogToFile(false);
        fLogger->SetLogFileLevel("INFO");
        fLogger->SetLogScreenLevel("INFO");
        fLogger->SetLogVerbosityLevel("LOW");
        fLogger->SetScreenStreamToCerr(true);
    }

    void LogNoArguments()
    {
        // Log same message for all log levels
        fLogger->Error(MESSAGE_ORIGIN, fOutputString.c_str());
        fLogger->Warning(MESSAGE_ORIGIN, fOutputString.c_str());
        fLogger->Info(MESSAGE_ORIGIN, fOutputString.c_str());
        fLogger->Debug(MESSAGE_ORIGIN, fOutputString.c_str());
        fLogger->Debug1(MESSAGE_ORIGIN, fOutputString.c_str());
        fLogger->Debug2(MESSAGE_ORIGIN, fOutputString.c_str());
        fLogger->Debug3(MESSAGE_ORIGIN, fOutputString.c_str());
        fLogger->Debug4(MESSAGE_ORIGIN, fOutputString.c_str());
    }

    std::vector<std::string> CreateExpectedOutputNoArguments(std::string logLevel, std::string outStr)
    {
        std::vector<std::string> levelNames(LogString, LogString + 9);
        std::vector<std::string>::iterator pos = std::find(levelNames.begin(), levelNames.end(), logLevel);
        levelNames.erase(pos + 1, levelNames.end());
        levelNames.erase(levelNames.begin()); // don't use FATAL logLevel in this test

        std::vector<std::string> retVal;
        std::string fullOutputString;

        std::vector<std::string>::iterator iter;
        for (iter = levelNames.begin(); iter < levelNames.end(); iter++)
        {
            fullOutputString = "[" + *iter + "] " + outStr;
            retVal.push_back(fullOutputString);
        }

        return retVal;
    }

    std::vector<std::string> CreateExpectedLogLevels(std::string loglevel)
    {
        std::vector<std::string> levelNames(TestLogs, TestLogs + 8);
        std::vector<std::string>::iterator pos = std::find(levelNames.begin(), levelNames.end(), loglevel);
        levelNames.erase(pos + 1, levelNames.end());
        return levelNames;
    }

    void CheckScreenOutput(std::vector<std::string> v)
    {
        int noLines = fHandler.GetNumberOfLines();
        int expectedNumberOfLines = v.size();
        EXPECT_EQ(expectedNumberOfLines, noLines);

        int minLines = std::min(expectedNumberOfLines, noLines);

        for (int i = 0; i < minLines; ++i)
        {
            EXPECT_EQ(v[i], fHandler.GetCaptureLine(i));
        }
    }

    void CheckFileOutput(std::vector<std::string> v, FairTestOutputHandler _handler)
    {
        int noLines = _handler.GetNumberOfLines();
        int expectedNumberOfLines = v.size();
        EXPECT_EQ(expectedNumberOfLines, noLines);

        int minLines = std::min(expectedNumberOfLines, noLines);

        for (int i = 0; i < minLines; ++i)
        {
            EXPECT_EQ(v[i], _handler.GetCaptureLine(i));
        }
    }

    std::vector<std::string> ReadLinesFromFile(std::string fileName)
    {
        std::vector<std::string> list;
        std::string line;
        std::ifstream myfile(fileName.c_str());

        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                list.push_back(line);
            }
            myfile.close();
        }

        return list;
    }

    bool CheckVerboseOutput(std::string logLevel, std::string outputString, std::string verbosity, std::string resultString)
    {
        // Example Output for logging level INFO and different verbosity levels
        // LOW      :[INFO] I am here.
        // MEDIUM   :[19:07:13][INFO] I am here.
        // HIGH     :[process_name][19:07:13:123456][INFO] I am here.
        // VERYHIGH :[process_name][19:07:13:123456][INFO][_TestFairTools.cxx:78:LogNoArguments] I am here.
        std::string regexString;
        if (verbosity == "HIGH" || verbosity == "VERYHIGH")
        {
            regexString += "\\[.*]"; // process_name
            regexString += "\\[\\d{2}:\\d{2}:\\d{2}.\\d{6}]"; // timestamp with ns
        }
        else if (verbosity == "MEDIUM")
        {
            regexString += "\\[\\d{2}:\\d{2}:\\d{2}]"; // timestamp without ns
        }
        regexString += "\\[" + logLevel + "]"; // severity

        if (verbosity == "VERYHIGH")
        {
            regexString += "\\[.*:\\d{2}:.*]"; // file:line:function
        }

        regexString += "[ ]" + outputString + ".*";

        const std::regex e(regexString);
        return std::regex_match(resultString, e);
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
class LogLevelTest : public _TestFairLoggerBase<testing::TestWithParam<const char*>>
{
  protected:
    virtual void SetUp()
    {
        fLogLevelSettingToTest = GetParam();
        // fOutputString = "I am here.";
        // fLogger = FairLogger::GetLogger();
        SetOutFileName();
        SetFairLoggerDefaultValues();
    }
};

/*
 This is the derived class for the parameterized test case
 which test all verbosity levels.
*/
class VerbosityLevelTest : public _TestFairLoggerBase<testing::TestWithParam<const char*>>
{
  protected:
    VerbosityLevelTest()
        : fVerbosityLevel()
    {}

    virtual void SetUp()
    {
        fVerbosityLevel = GetParam();
        SetOutFileName();
        SetFairLoggerDefaultValues();
    }

    std::string fVerbosityLevel;
};
