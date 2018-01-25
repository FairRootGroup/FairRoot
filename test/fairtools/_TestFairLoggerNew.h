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
    FairCaptureOutputNew fHandler;

    _TestFairLoggerBase()
        : fLogLevelSettingToTest("INFO")
        , fOutputString("I am here.")
        , fOutFileName()
        , fHandler()
    {}

    _TestFairLoggerBase(const _TestFairLoggerBase&);
    _TestFairLoggerBase& operator=(const _TestFairLoggerBase&);

    ~_TestFairLoggerBase()
    {}

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
        gLogger->SetLogToScreen(true);
        gLogger->SetLogToFile(false);
        gLogger->SetLogFileLevel("INFO");
        gLogger->SetLogScreenLevel("INFO");
        gLogger->SetLogVerbosityLevel("LOW");
        gLogger->SetScreenStreamToCerr(true);
    }

    void LogNoArguments()
    {
        // Log same message for all log levels
        LOG(error) << fOutputString.c_str();
        LOG(warn) << fOutputString.c_str();
        LOG(info) << fOutputString.c_str();
        LOG(debug) << fOutputString.c_str();
        LOG(debug1) << fOutputString.c_str();
        LOG(debug2) << fOutputString.c_str();
        LOG(debug3) << fOutputString.c_str();
        LOG(debug4) << fOutputString.c_str();
    }

    std::vector<std::string> CreateExpectedOutputNoArguments(std::string loglevel, std::string outStr)
    {
        std::vector<std::string> levelNames(LogString, LogString + 9);
        std::vector<std::string>::iterator pos = std::find(levelNames.begin(), levelNames.end(), loglevel);
        levelNames.erase(pos + 1, levelNames.end());
        levelNames.erase(levelNames.begin()); // don't use FATAL loglevel in this test

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
        fOutputString = "I am here.";
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
        : fVerbosityLevel("")
    {}

    virtual void SetUp()
    {
        fLogLevelSettingToTest = "INFO";
        fVerbosityLevel = GetParam();
        fOutputString = "I am here.";
        SetOutFileName();
        SetFairLoggerDefaultValues();
    }
    std::string fVerbosityLevel;
};
